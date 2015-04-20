#ifndef RAPP_ASIO_SERVICE_HTTP
#define RAPP_ASIO_SERVICE_HTTP
#include "Includes.ihh"

namespace rapp {
namespace services {

#define hostname "localhost"
    
/**
 * @class asio_service_http
 * @brief base class for asynchronous http websockets used for connecting to cloud services
 * @version 5
 * @date 18-April-2015
 * @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 * 
 * @see http://www.jmarshall.com/easy/http/#postmethod for HTTP Protocol details
 * @warning this class does not support SSL/TLS sockets
 * 
 * TODO: TEST This class has NOT been TESTED with LARGE Replies!!!
 *       TEST handle_read_content and handle_read_headers THERE MIGHT BE A BUG!
 */
class asio_service_http : public asio_socket
{
  public:
  
      
    /**
     * @brief Construct the async client. 
     * @param header must be a form for HOP
     * @param post must contain the names JSON data sent to HOP
     */
    asio_service_http (
                        const std::string & header,
                        const std::string & post
                      )
    : header_ ( header ), post_ ( post ) {}
    
    
    /**
     * @param header is the actual HTTP Header crafted accordingly
     * @param post is the actual $_POST field following the HTTP Header
     * @param callback is a lamda or function pointer with the specific signature, that is invoked upon reply acquisition
     */
    asio_service_http (
                        const std::string & header,
                        const std::string & post,
                        std::function<void( boost::asio::streambuf & )> callback
                      )
    : header_ ( header ), post_ ( post ), callback_ ( callback ) {}

    
    /** 
     * Schedule this client as a job for execution using
     * @param query defines the actual URL/URI
     * @param resolver is the URL/URI resolver reference
     * @param io_service is the service queue on which this job will be scheduled to run
     */
    void Schedule ( 
                     boost::asio::ip::tcp::resolver::query & query,
                     boost::asio::ip::tcp::resolver & resolver,
                     boost::asio::io_service & io_service
                  )
    {
        if ( !socket_ )
            socket_ = std::unique_ptr<boost::asio::ip::tcp::socket>( new boost::asio::ip::tcp::socket( io_service ) );
        
        std::ostream request_stream ( &request_ );
        request_stream << header_ << post_ << "\r\n";
        
        resolver.async_resolve( query,
                                boost::bind( & asio_service_http::handle_resolve,
                                             this,
                                             boost::asio::placeholders::error,
                                             boost::asio::placeholders::iterator ) );
    }
    
  protected:  

      
    /// Hidden empty constructor is meant to be used only by inheriting classes
    asio_service_http ( ) = default;
      
    
    /**
     * @brief Handle the Reply Buffer
     * @note you have to override this method if inheriting from this class
     */
    virtual void handle_reply ( )
    {   
        std::string raw ( ( std::istreambuf_iterator<char>( &response_ ) ), std::istreambuf_iterator<char>() );
    }
    
    
    /**
     * @brief Handle an Error
     * @param error is the raised error from the client
     */
    virtual void error_handler ( const boost::system::error_code & error )
    {
        std::cerr << "http error: " << error.message() << std::endl;
    }

    
    /**
     * @brief Hndle Invalid Query - e.g.: response which states our query was invalid
     * @param message is the message received from the service
     */
    virtual void invalid_request ( const std::string message )
    {
        std::cerr << "http invalid request: " <<  message << std::endl;
    }
    
    
    /** 
     * @brief Callback for Handling Address Resolution
     * @param err is a possible error
     * @param endpoint_iterator is boost's hostname address handler
     */
    void handle_resolve ( 
                            const boost::system::error_code & err,
                            boost::asio::ip::tcp::resolver::iterator endpoint_iterator
                        )
    {
        if ( !socket_ )
            throw std::runtime_error ( "asio_service_http::handle_resolve socket ptr null" );
        if (!err)
        {
            auto endpoint = * endpoint_iterator;
            socket_->async_connect ( endpoint,
                                     boost::bind ( &asio_service_http::handle_connect,
                                                   this,
                                                   boost::asio::placeholders::error, 
                                                   ++endpoint_iterator ) );
        }
        else 
            error_handler( err );
    }

    
    /**
     * @brief Callback for Handling Connection Events
     * @param err is a possible error
     * @param endpoint_iterator is boosts' hostname address handler
     */
    void handle_connect ( 
                            const boost::system::error_code & err,
                            boost::asio::ip::tcp::resolver::iterator endpoint_iterator
                        )
    {
        if ( !socket_ )
            throw std::runtime_error ( "asio_service_http::handle_connect socket ptr null" );
        if ( !err )
        {
            boost::asio::async_write( *socket_.get(),
                                      request_,
                                      boost::bind ( &asio_service_http::handle_write_request, 
                                                    this,
                                                    boost::asio::placeholders::error ) );
        }
        else if ( endpoint_iterator != boost::asio::ip::tcp::resolver::iterator() )
        {
            socket_->close();   
            auto endpoint = *endpoint_iterator;
            socket_->async_connect( endpoint,
                                    boost::bind ( &asio_service_http::handle_connect, 
                                                  this,
                                                  boost::asio::placeholders::error, 
                                                  ++endpoint_iterator ) );
        }
        else error_handler( err );
    }

    
    /**
     * @brief Callback for handling request and waiting for response
     * @param err is a possible error
     */
    void handle_write_request ( const boost::system::error_code & err )
    {
        if ( !socket_ )
            throw std::runtime_error ( "asio_service_http::handle_write_request socket ptr null" );
        if ( !err )
        {
            // Read the response status line - Callback handler is ::handle_read_status_line
            boost::asio::async_read_until( *socket_.get(),
                                        response_, 
                                        "\r\n",
                                        boost::bind( &asio_service_http::handle_read_status_line, 
                                                        this,
                                                        boost::asio::placeholders::error ) );
        }
        else 
            error_handler( err );
    }
    
    
    /**
     * @brief Callback for handling HTTP Header Response Data
     * @param err is a possible error message
     */
    void handle_read_status_line ( const boost::system::error_code & err )
    {
        if ( !socket_ )
            throw std::runtime_error ( "asio_service_http::handle_read_status_line socket ptr null" );    
        if (!err)
        {
            // Check that HTTP Header Response is OK.
            std::istream response_stream( &response_);
            std::string http_version;
            response_stream >> http_version;
            unsigned int status_code;
            response_stream >> status_code;
            std::string status_message;
            std::getline( response_stream, status_message );
            
            if ( !response_stream || http_version.substr(0, 5) != "HTTP/" )
            {
                invalid_request( "http Invalid response" );
                return;
            }
            if ( status_code != 200 )
            {
                invalid_request( std::to_string( status_code ) );
                return;
            }
            // Read the response headers, which are terminated by a blank line. This is HTTP Protocol 1.0 & 1.1
            boost::asio::async_read_until( *socket_.get(),
                                            response_, 
                                            "\r\n\r\n",
                                            boost::bind ( &asio_service_http::handle_read_headers, 
                                                          this,
                                                          boost::asio::placeholders::error ) );
        }
        else 
            error_handler( err );
    }

    
    /**
     * @brief Callback for Handling Headers
     * @param err is a possible error message
     */
    void handle_read_headers ( const boost::system::error_code & err )
    {
        if ( !socket_ )
            throw std::runtime_error ( "asio_service_http::handle_read_headers socket ptr null" );
        
        if ( !err )
        {
            // Start reading Content data until EOF (see handle_read_content)
            boost::asio::async_read ( *socket_.get(),
                                       response_,
                                       boost::asio::transfer_at_least( 1 ),
                                       boost::bind( &asio_service_http::handle_read_content, 
                                                     this,
                                                     boost::asio::placeholders::error ) );
            // Now call the callback
            if ( callback_ )
                callback_( response_ );
            
            // Or we handle it oursleves
            else
                handle_reply();
        }
        else error_handler( err );
    }
    
    
    /**
     * @brief Callback for Handling Actual Data Contents
     * @param err is a possible error message
     */
    void handle_read_content ( const boost::system::error_code & err )
    {
        if ( !socket_ )
            throw std::runtime_error ( "asio_service_http::handle_read_content socket ptr null" );
        if ( !err )
        {
            // Continue reading remaining data until EOF - It reccursively calls its self
            boost::asio::async_read ( *socket_.get(),
                                       response_,
                                       boost::asio::transfer_at_least( 1 ),
                                        boost::bind( &asio_service_http::handle_read_content, 
                                                     this,
                                                     boost::asio::placeholders::error ) );
        }
        else if ( err != boost::asio::error::eof )
            error_handler( err );
    }
    

    
    /// Header that will be used
    std::string header_;
    
    /// Actual post Data
    std::string post_;
    
    /// Optional Callback Handler
    std::function<void( boost::asio::streambuf & )> callback_;
    
    /// Actual Socket
    std::unique_ptr<boost::asio::ip::tcp::socket> socket_;
    
    /// Request Container
    boost::asio::streambuf request_;
    
    /// Response Container
    boost::asio::streambuf response_;
    
};


}
}

#endif

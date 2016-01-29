#ifndef RAPP_ASIO_SERVICE_HTTP
#define RAPP_ASIO_SERVICE_HTTP
#include "Includes.ihh"

namespace rapp {
namespace services {
    
/**
 * @class asio_service_http
 * @brief base class for asynchronous http websockets used for connecting to cloud services
 * @version 6
 * @date 26-April-2015
 * @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 * 
 * @see http://www.jmarshall.com/easy/http/#postmethod for HTTP Protocol details
 * @warning this class does not support SSL/TLS sockets
 */
class asio_service_http : public asio_socket
{
public:
      
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
    
    /// Handle an Error @param error is the raised error from the client
    void error_handler ( const boost::system::error_code & error )
    {
        std::cerr << "asio_service_http error: " << error.message() << std::endl;
    }

    /// Handle Invalid Query - e.g.: response which states our query was invalid @param message is the message received from the service
    void invalid_request ( const std::string message )
    {
        std::cerr << "asio_service_http invalid request: " <<  message << std::endl;
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
        assert( socket );
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
     * Callback for Handling Connection Events
     * @param err is a possible error
     * @param endpoint_iterator is boosts' hostname address handler
     */
    void handle_connect ( 
                            const boost::system::error_code & err,
                            boost::asio::ip::tcp::resolver::iterator endpoint_iterator
                        )
    {
        assert ( socket_ );
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

    /// Callback for handling request and waiting for response @param err is a possible error
    void handle_write_request ( const boost::system::error_code & err )
    {
        assert( socket_ );
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
    
    /// Callback for handling HTTP Header Response Data @param err is a possible error message
    void handle_read_status_line ( const boost::system::error_code & err )
    {
        assert ( socket_ );
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

    /// Callback for Handling Headers @param err is a possible error message
    void handle_read_headers ( const boost::system::error_code & err )
    {
        assert ( socket_ );
        if ( !err )
        {
            // Start reading Content data until EOF (see handle_read_content)
            boost::asio::async_read_until ( *socket_.get(),
                                             response_,
                                             "\r\n\r\n",
                                             boost::bind( &asio_service_http::handle_read_content, 
                                                          this,
                                                          boost::asio::placeholders::error ) );
        }
        else error_handler( err );
    }
    
    /// Callback for Handling Actual Data Contents @param err is a possible error message
    void handle_read_content ( const boost::system::error_code & err )
    {
        assert ( socket_ );
        if ( !err )
        {
            // Continue reading remaining data until EOF - It reccursively calls its self
            boost::asio::async_read ( *socket_.get(),
                                       response_,
                                       boost::asio::transfer_at_least( 1 ),
                                       boost::bind( &asio_service_http::handle_read_content, 
                                                     this,
                                                     boost::asio::placeholders::error ) );

            // Parse HTTP Content.
            std::string json ( ( std::istreambuf_iterator<char>( &response_ ) ), 
                                 std::istreambuf_iterator<char>() );

            // find the "\r\n\r\b"
            std::size_t i = json.find("\r\n\r\n");
            if ( i != std::string::npos )
                json = json.substr( i + 4, std::string::npos );
            else
                throw std::runtime_error( "can't find double return carriage after header" );

            // Now call the callback
            assert( callback_ );
            callback_( json );
        }
        else if ( err != boost::asio::error::eof )
            error_handler( err );
    }
    
    /// Create a random boundary for the multipart/form in HTTP
    std::string randomBoundary ( ) const
    {
        std::string chars( "abcdefghijklmnopqrstuvwxyz"
                           "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                           "1234567890" );
        
        boost::random::random_device rng;
        std::string uid;
        
        // Randomly chose 16 characters
        boost::random::uniform_int_distribution<> index_dist(0, chars.size() - 1);
        for ( int i = 0; i < 16; ++i )
            uid.push_back( chars[index_dist(rng)] );
        
        return uid;
    }

    std::string escape_string(const std::string & str) 
    {
        std::ostringstream ss;
        for (auto iter = str.cbegin(); iter != str.cend(); iter++)
        {
            switch (*iter)
            {
                case '\\': ss << "\\\\"; break;
                case '"': ss << "\\\""; break;
                case '/': ss << "\\/"; break;
                case '\b': ss << "\\b"; break;
                case '\f': ss << "\\f"; break;
                case '\n': ss << "\\n"; break;
                case '\r': ss << "\\r"; break;
                case '\t': ss << "\\t"; break;
                default: ss << *iter; break;
            }
        }
        return ss.str();
    } 

    
    /// Header that will be used
    std::string header_;
    
    /// Actual post Data
    std::string post_;
    
    /// Callback Handler - use with std::bind or boost variant
    std::function<void( std::string )> callback_;
    
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

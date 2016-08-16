#ifndef RAPP_CLOUD_EMAIL
#define RAPP_CLOUD_EMAIL
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \brief fetch email(s)
 * \class email_fetch
 * \version 0.7.0
 * \date 15 August 2016
 */
class email_fetch :  public caller, public http_request
{
public:
    /** 
     * \brief construct in order to acquire email(s)
     * \param email: user's email address
     * \param pwd: user's plain-text password
     * \param server: email imap address
     * \param port: email imap port
     * \param email_status: which mail is requested (ALL, UNSEEN)
     * \param from_date: fetch emails since date (unix timestamp)
     * \param to_date: fetch emails to date (unix timestamp)
     * \param num_emails: number of emails requested
     * \param callback will receive a JSON string with acquired email(s)
     */
     email_fetch(
                 const std::string email,
                 const std::string pwd,
                 const std::string server,
                 const std::string port,
                 const std::string email_status,
                 const unsigned int from_date,
                 const unsigned int to_date,
                 const unsigned int num_emails,
                 std::function<void(std::string)> callback
                )
	: http_header("POST /hop/email_fetch HTTP/1.1\r\n"), 
      http_post(http_header::get_boundary()), 
      delegate_(callback)
	{
        boost::property_tree::ptree tree;
        tree.put("email", email);
        tree.put("passwd", pwd);
        tree.put("server", server);
        tree.put("port", port);
        tree.put("email_status", email_status);
        tree.put("from_date", from_date);
        tree.put("to_date", to_date);
        tree.put("num_emails", num_emails);
        
		std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);

		// JSON PDT value unquote `from_date`
		auto str = misc::json_unquote_pdt_value<unsigned int>()(ss.str(), from_date);
		// JSON PDT value unquote `to_date`
		str = misc::json_unquote_pdt_value<unsigned int>()(str, to_date);
		// JSON PDT value unquote `num_emails`
        std::string json = misc::json_unquote_pdt_value<unsigned int>()(str, num_emails);

        http_post::add_content("json", json, false); 
        http_post::end();
     
	}

    /**
     * \brief handle platform's JSON reply
     */
	void deserialise(std::string json) const
    {
        std::stringstream ss(json);
        delegate_(std::move(json));
    }


    /**
    * \brief method to fill the buffer with http_post and http_header information
    * \param info is the data of the platform    
    */
    boost::asio::streambuf fill_buffer(rapp::cloud::platform info)
    {
           return std::move(http_request::fill_buffer(info));
    }
    
private:
    // 
    std::function<void(std::string)> delegate_;
};

/**
 * \brief send an email
 * \class email_send
 * \version 0.7.0
 * \date 15 August 2016
 */
class email_send :  public caller, public http_request
{
public:
    /** 
     * \brief construct in order to send email
     * \param email: user's email address
     * \param pwd: user's plain-text password
     * \param server: email imap address
     * \param port: email imap port
     * \param recipients: vector of email addresses
     * \param body: email body
     * \param subject: email subject
     * \param data: data attached to the email
     * \param callback may receive a JSON reply of error(s)
     */
     email_send(
                 const std::string email,
                 const std::string pwd,
                 const std::string server,
                 const std::string port,
                 const std::vector<std::string> recipients,
                 const std::string body,
                 const std::string subject,
                 const std::vector<rapp::types::byte> data,
                 std::function<void(std::string)> callback
               )
	: http_header("POST /hop/email_send HTTP/1.1\r\n"), 
      http_post(http_header::get_boundary()), 
      delegate_(callback)
	{
        std::string fname = rapp::misc::random_boundary();

        boost::property_tree::ptree tree;
        tree.put("email", email);
        tree.put("passwd", pwd);
        tree.put("server", server);
        tree.put("port", port);
        tree.put("body", body);
        tree.put("subject", subject);

        boost::property_tree::ptree array;
        for (const auto rec : recipients) {
            array.push_back(std::make_pair("", rec));
        }
        tree.add_child("recipients", array);
        tree.put("file", fname);

		std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);

        std::string json =ss.str();
		http_post::add_content("json", json, false); 
        http_post::add_content("file", fname, data); 
        http_post::end();
    }
    /**
     * \brief handle platform's JSON reply
     */
	void deserialise(std::string json) const
    {
        std::stringstream ss(json);
        delegate_(std::move(json));
    }
   

    /**
    * \brief method to fill the buffer with http_post and http_header information
    * \param info is the data of the platform    
    */
    boost::asio::streambuf fill_buffer(rapp::cloud::platform info)
    {
           return std::move(http_request::fill_buffer(info));
    }
   
private:
    /// 
    std::function<void(std::string)> delegate_;
};
}
}
#endif

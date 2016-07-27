#ifndef RAPP_CLOUD_EMAIL
#define RAPP_CLOUD_EMAIL
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \brief fetch email(s)
 * \class email_fetch
 * \version 0.6.0
 * \date May 2016
 */
class email_fetch : public asio_service_http
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
	: asio_service_http(), delegate_(callback)
	{
        boost::property_tree::ptree tree;
        tree.put("email", email);
        tree.put("passwd", pwd);
        tree.put("server", server);
        tree.put("port", port);
        tree.put("email_status", email_status);
        tree.put("from_date", boost::lexical_cast<std::string>(from_date));
        tree.put("to_date", boost::lexical_cast<std::string>(to_date));
        tree.put("num_emails", boost::lexical_cast<std::string>(num_emails));
        
		std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);
        post_ = ss.str();

		// set the HTTP header URI pramble and the Content-Type
        head_preamble_.uri = "POST /hop/email_fetch HTTP/1.1\r\n";
        head_preamble_.content_type = "Content-Type: application/x-www-form-urlencoded";

        callback_ = std::bind(&email_fetch::handle_reply, this, std::placeholders::_1);
	}
private:
    /**
     * \brief handle platform's JSON reply
     */
	void handle_reply(std::string json)
    {
        std::stringstream ss(json);
        delegate_(std::move(json));
    }
    /// 
    std::function<void(std::string)> delegate_;
};

/**
 * \brief send an email
 * \class email_send
 * \version 0.6.0
 * \date May 2016
 */
class email_send : public asio_service_http
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
	: asio_service_http(), delegate_(callback)
	{
        std::string boundary = rapp::misc::random_boundary();
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

        post_  = "--" + boundary + "\r\n"
               + "Content-Disposition: form-data; name=\"json\"\r\n\r\n"
               + ss.str() + "\r\n";

        // new multipart - append binary data 
        post_ += "--" + boundary + "\r\n"
              + "Content-Disposition: form-data; name=\"file_uri\"; filename\"" + fname + "\"\r\n"
              + "Content-Transfer-Encoding: binary\r\n\r\n";

        post_.insert(post_.end(), data.begin(), data.end());
        post_ += "\r\n--" + boundary + "--";

		// set the HTTP header URI pramble and the Content-Type
        head_preamble_.uri = "POST /hop/email_send HTTP/1.1\r\n";
        head_preamble_.content_type = "Content-Type: multipart/form-data; boundary=" + boundary;

        callback_ = std::bind(&email_send::handle_reply, this, std::placeholders::_1);
    }
private:
    /**
     * \brief handle platform's JSON reply
     */
	void handle_reply(std::string json)
    {
        std::stringstream ss(json);
        delegate_(std::move(json));
    }
    /// 
    std::function<void(std::string)> delegate_;
};
}
}
#endif

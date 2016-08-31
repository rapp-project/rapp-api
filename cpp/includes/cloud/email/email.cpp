#include "email.hpp"
namespace rapp {
namespace cloud {

email_fetch::email_fetch(
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
: http_request("POST /hop/email_fetch HTTP/1.1\r\n"), 
  delegate_(callback)
{
    std::string ss;
    json json_doc = {{"email", email},
                     {"passwd", pwd},
                     {"server", server},
                     {"port", port},
                     {"email_status", email_status},
                     {"from_date", from_date},
                     {"to_date", to_date},
                     {"num_emails", num_emails}};

    ss = json_doc.dump(4);
    http_request::add_content("json", ss, false); 
    http_request::close();
 
}

/**
 * \brief handle platform's JSON reply
 */
void email_fetch::deserialise(std::string json) const
{
    std::stringstream ss(json);
    delegate_(std::move(json));
}

// Class email_send
email_send::email_send(
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
: http_request("POST /hop/email_send HTTP/1.1\r\n"), 
  delegate_(callback)
{
    std::string fname = rapp::misc::random_boundary();

    json json_doc = {{"email", email},
                     {"passwd", pwd},
                     {"server", server},
                     {"port", port},
                     {"body", body},
                     {"subject", subject}};

    std::string ss = json_doc.dump(4);
    http_request::add_content("json", ss, false); 
    http_request::add_content("file", fname, data); 
    http_request::close();
}
/**
 * \brief handle platform's JSON reply
 */
void email_send::deserialise(std::string json) const
{
    std::stringstream ss(json);
    delegate_(std::move(json));
}

}
}

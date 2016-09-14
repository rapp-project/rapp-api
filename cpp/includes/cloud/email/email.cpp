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
                           std::function<void(std::vector<std::tuple<std::string, 
                                                                     std::vector<std::string>,
                                                                     std::string,
                                                                     std::string,
                                                                     std::vector<std::string>>>)> callback
                        )
: http_request("POST /hop/email_fetch HTTP/1.1\r\n"), 
  delegate_(callback)
{
    http_request::make_multipart_form();
    json json_doc = {{"email", email},
                     {"passwd", pwd},
                     {"server", server},
                     {"port", port},
                     {"email_status", email_status},
                     {"from_date", from_date},
                     {"to_date", to_date},
                     {"num_emails", num_emails}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::close();
}

/**
 * \brief handle platform's JSON reply
 */
void email_fetch::deserialise(std::string json) const
{
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    nlohmann::json json_f;
    try {
        json_f = json::parse(json);
    }
    catch (std::exception & e) {
        std::cerr << "Exception " << e.what() << std::endl;
    }
    auto error = misc::get_json_value<std::string>("error", json_f);
    if (!error.empty()) {
        std::cerr << "error JSON: " << error <<std::endl;
    }
    else {
        std::vector<std::tuple<std::string, 
                               std::vector<std::string>,
                               std::string,
                               std::string,
                               std::vector<std::string>>> emails;

        for (auto it_s : json_f["emails"]) {
            emails.push_back(std::make_tuple(misc::get_json_value<std::string>("sender", it_s),
                                             misc::get_json_value<std::vector<std::string>>("receivers", it_s),
                                             misc::get_json_value<std::string>("body", it_s),
                                             misc::get_json_value<std::string>("date", it_s),
                                             misc::get_json_value<std::vector<std::string>>("attachments", it_s))); 
         } 
         delegate_(emails);
    }
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
    http_request::make_multipart_form();
    std::string fname = rapp::misc::random_boundary();
    json json_doc = {{"email", email},
                     {"passwd", pwd},
                     {"server", server},
                     {"port", port},
                     {"recipients", recipients},
                     {"body", body},
                     {"subject", subject}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::add_content("file", fname, data); 
    http_request::close();
}

email_send::email_send(
                         const std::string email,
                         const std::string pwd,
                         const std::string server,
                         const std::string port,
                         const std::vector<std::string> recipients,
                         const std::string body,
                         const std::string subject,
                         std::function<void(std::string)> callback
                      )
: http_request("POST /hop/email_send HTTP/1.1\r\n"), 
  delegate_(callback)
{
    http_request::make_multipart_form();
    std::string fname = rapp::misc::random_boundary();
    json json_doc = {{"email", email},
                     {"passwd", pwd},
                     {"server", server},
                     {"port", port},
                     {"recipients", recipients},
                     {"body", body},
                     {"subject", subject}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::close();
}

void email_send::deserialise(std::string json) const
{
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }
    nlohmann::json json_f;
    try {
        json_f = json::parse(json);
    }
    catch (std::exception & e) {
        std::cerr << "Exception " << e.what() << std::endl;
    }
    auto error = misc::get_json_value<std::string>("error", json_f);
    if (!error.empty()) {
        std::cerr << "error JSON: " << error <<std::endl;
    }
    else {
        delegate_(error);
    }
}

}
}

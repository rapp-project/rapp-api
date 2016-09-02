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

    std::vector<std::string> vector_emails;
    auto json_f = json::parse(json);
    try {
         //Fill the vector_services with names and urls
         for (auto it_s : json_f["emails"]){

            /*services.first = it_s["name"];
            services.second = it_s["url"];           
            vector_services.push_back(services);
         */
         } 
        delegate_(vector_emails);
        // Get "error" from json
        std::string error = json_f["error"];
        if (!error.empty()) {
             std::cerr << "error JSON: " << error << std::endl; 
        }
    }
    catch (std::exception & e) {
        std::cerr << "Exception " << e.what() << std::endl;
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
                     {"body", body},
                     {"subject", subject}};
    http_request::add_content("json", json_doc.dump(-1), true);
    http_request::add_content("file", fname, data); 
    http_request::close();
}
/**
 * \brief handle platform's JSON reply
 */
void email_send::deserialise(std::string json) const
{
    if (json.empty()) {
        throw std::runtime_error("empty json reply");
    }

    std::vector<std::string> vector_emails;
    auto json_f = json::parse(json);
    try {
        // Get "error" from json
        std::string error = json_f["error"];
        if (!error.empty()) {
             std::cerr << "error JSON: " << error << std::endl; 
        }
    }
    catch (std::exception & e) {
        std::cerr << "Exception " << e.what() << std::endl;
    }
}

}
}

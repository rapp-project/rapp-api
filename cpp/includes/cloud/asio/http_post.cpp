#include "http_post.hpp"
namespace rapp {
namespace cloud {

http_post::http_post(std::string boundary)
: boundary_(boundary)
{}

void http_post::add_content(
							 const std::string name, 
							 const std::string content,
							 bool newline
							)
{
	if (name.empty() || content.empty()) {
		throw std::runtime_error("empty param(s)");
	}
	data_ += "--" + boundary_ + "\r\n";
	data_ += "Content-Disposition: form-data; name=\""\ + name + "\"\r\n\r\n";
	data_ += content;  
	if (newline) {
		data_ += "\r\n";
	}
}

void http_post::add_content(
							  const std::string name,
							  const std::string filename,
							  const std::vector<rapp::types::byte> bytes
							)
{
	if (name.empty() || filename.empty() || bytes.size() == 0) {
		throw std::runtime_error("empty param(s)");
	}
	data_ += "--" + boundary_ + "\r\n";
	data_ += "Content-Disposition: form-data; name=\""\ + name + "\"\";";
	data_ += " filename=\"" + filename + "\"\r\n";
	data_ += "Content-Transfer-Encoding: binary\r\n\r\n";
	data_.insert(data_.end(), bytes.begin(), bytes.end());
	data_ += "\r\n";
}

void http_post::end()
{
	if (open_) {
		open_ = false;
		data_ += "--" + boundary + "--\r\n";
	}
}

std::string http_post::to_string() const
{
	return data_;
}

unsigned int http_post::size() const
{
	return data_.size() * sizeof(std::string::value_type);
}

}
}

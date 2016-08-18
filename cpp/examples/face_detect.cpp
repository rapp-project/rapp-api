#include "cloud/service_controller/service_controller.hpp"
#include "cloud/vision/face_detection/face_detection.hpp"
#include "objects/picture/picture.hpp"

#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;
///
/// Pass as param a PNG image
///
int main(int argc, char* argv[])
{

  std::string addr;
  std::string port;
  std::string token;
  std::string file;

  // Declare the supported options.
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help,h", "produce help message")
    ("addr,a", po::value<std::string>(&addr)->default_value("localhost"), "platform host name or ip address")
    ("port,p", po::value<std::string>(&port)->default_value("9001"), "platform port")
    ("token,t", po::value<std::string>(&token)->default_value("rapp_token"), "user token")
    ("file", po::value<std::string>(&file), "test filename")
    ;

  po::positional_options_description pos_desc; 
  pos_desc.add("file", -1); 

  po::variables_map vm;

  po::store(po::command_line_parser(argc, argv).options(desc) 
      .positional(pos_desc).run(), 
      vm); 


  if (vm.count("help")) {
    std::cout << desc << "\n";
    return 1;
  }

  po::notify(vm);    

  if (vm.count("file")) {
    std::cout << "Input file: " << file << "\n";
  } else {
    std::cout << "No input file specified.\n";
    return 1;
  }


  // service controler
  rapp::cloud::platform_info info = {addr, port, token}; 
  rapp::cloud::service_controller ctrl(info);

  // load the image from argv[1]
  auto pic = rapp::object::picture(file);

  // callback lambda
  auto callback = [&](std::vector<rapp::object::face> faces)
  {std::cout << "found " << faces.size() << " faces!" << std::endl;};

  // detect faces
  ctrl.make_call<rapp::cloud::face_detection>(pic, false, callback);
  return 0;
}

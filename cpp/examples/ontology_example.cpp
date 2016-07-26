#include "cloud/service_controller/service_controller.hpp"
#include "cloud/ontology/ontology.hpp"
#include <iostream>
///
/// query subclasses and superclass of of argv[1]
///
int main(int argc, char* argv[])
{
    if (argc > 1) {
        std::cout << "query sub/super classes of: " << argv[1] << std::endl;
        std::string query = argv[1];

        // service controler
        rapp::cloud::platform_info info = {"155.207.19.229", "9001", "rapp_token"}; 
		rapp::cloud::service_controller ctrl(info);

        // sub-class callback - print each sub-class
        auto sb_cb = [](std::vector<std::string> classes)
                     { 
                        for (const auto & str : classes) {
                            std::cout << str << std::endl;
                        }
                     };

        // super-class callback - print each super-class
        auto sp_cb = [](std::vector<std::string> classes)
                     {
                        for (const auto & str : classes) {
                            std::cout << str << std::endl;
                        }
                     };

		// make two asyncrhonous calls
        ctrl.make_call<rapp::cloud::ontology_subclasses_of>(query, false, sb_cb);
        ctrl.make_call<rapp::cloud::ontology_superclasses_of>(query, false, sp_cb);

        return 0;
    }
}

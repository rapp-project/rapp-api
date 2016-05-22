#include "cloud/service_controller/service_controller.hpp"
#include "cloud/ontology/ontology.hpp"
#include <iostream>
///
/// query subclasses and superclass of of argv[1]
///
int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        std::cout << "query sub/super classes of: " << argv[1] << std::endl;
        std::string query = argv[1];
		std::string token = "my_token";

        // Service Controller 
        rapp::cloud::service_controller ctrl;

        // Subclass Ontologies callback
        auto sb_cb = [](std::vector<std::string> classes)
                     { 
                        for (const auto & str : classes)
                            std::cout << str << std::endl;
                     };

        // the caller object
        auto sub_call = std::make_shared<rapp::cloud::ontology_subclasses_of>(query, false, sb_cb, token);

        // Superclass Ontologies
        auto sp_cb = [](std::vector<std::string> classes)
                     {
                        for (const auto & str : classes)
                            std::cout << str << std::endl;
                     };
        
		// the caller
        auto super_call = std::make_shared<rapp::cloud::ontology_superclasses_of>(query, false, sp_cb, token);

        // Request from service controller to run this job
        ctrl.run_job(sub_call);
        ctrl.run_job(super_call);
        return 0;
    }
}

#include "../includes/service/service_controller/service_controller.hpp"
#include "../includes/cloud/ontologySubClassesOf/ontologySubClassesOf.hpp"
#include "../includes/cloud/ontologySuperClassesOf/ontologySuperClassesOf.hpp"
#include "../includes/cloud/ontologyIsSubSuperClassOf/ontologyIsSubSuperClassOf.hpp"
#include <iostream>

int main ( int argc, char* argv[] )
{
    // Service Controller 
    rapp::services::service_controller ctrl;
    
    // Subclass Ontologies
    auto cb1 = []( std::vector<std::string> classes )
               { 
                    for ( const auto & str : classes )
                        std::cout << str << std::endl;
               };
                    
    auto subclassHandle = std::make_shared<rapp::cloud::ontologySubClassesOf>( "Oven", cb1 );
   
    // Superclass Ontologies
    auto cb2 = []( std::vector<std::string> classes )
                 {
                    for ( const auto & str : classes )
                        std::cout << str << std::endl;
                 };
    
    auto superclassHandle = std::make_shared<rapp::cloud::ontologySuperClassesOf>( "Oven", cb2 );

    // SubSuperClass Of
    auto cb3 = []( std::vector<std::string> classes )
                 {
                    for ( const auto & str : classes )
                        std::cout << str << std::endl;
                 };

    auto subsuperclassHandle = std::make_shared<rapp::cloud::ontologyIsSubSuperClassOf>( "Oven", "SpatialThing", false, cb3 );

    // Request from service controller to run this job
    ctrl.runJob ( subclassHandle );
    ctrl.runJob ( superclassHandle );
    ctrl.runJob ( subsuperclassHandle );

    return 0;
}

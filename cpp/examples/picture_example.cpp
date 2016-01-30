#include "../includes/objects/picture/picture.hpp"
#include <memory>
///
/// Open a picture and load it into an object
///
int main(int argc, char * argv[])
{
    if (argc == 2)
    {
        std::string file(argv[1]);
        // Open picture.
        auto pic = rapp::object::picture(file);
        pic.save("copy_of_"+file);
        std::cout << "Picture is a " << pic.type() << std::endl;
    }
    return 0;
}

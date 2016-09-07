#include "objects/picture/picture.hpp"
#include <memory>
///
/// Open a picture and load it into an object
///
int main()
{
    std::string file("?");

    // Open picture.
    auto pic = rapp::object::picture(file);
    pic.save("copy_of_"+file);

    // get magic bytes and infer picture type
    std::cout << "Picture is a " << pic.type() << std::endl;

    return 0;
}

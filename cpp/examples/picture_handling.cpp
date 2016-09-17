#include <rapp/objects/picture.hpp>
#include <memory>
///
/// Open a picture and load it into an object
///
int main()
{
    std::string file("data/object_classes_picture_1.png");

    // Open picture.
    auto pic = rapp::object::picture(file);
    pic.save("copy_of_" + file);

    // get magic bytes and infer picture type
    std::cout << "Picture is a " << pic.type() << std::endl;

    return 0;
}

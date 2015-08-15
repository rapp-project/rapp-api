#ifndef RAPP_OBJECT_PICTURE
#define RAPP_OBJECT_PICTURE
#include "Includes.ihh"

namespace rapp {
namespace object {

/**
 * @class picture
 * @brief class which wraps around raw bytes of a picture
 * @version 2
 * @date 6-February-2015
 * @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 * 
 */
class picture
{
public:

    /// Construct from a file-path
    picture ( const std::string filepath );

    /// Construct using an open file stream
    picture ( std::ifstream & bytestream );

    /// Construct using raw byte array
    picture ( std::vector<rapp::types::byte> bytearray );

    /// Copy constructor
    picture ( const picture & ) = default;

    /// Get picture as array of bytes
    std::vector<rapp::types::byte> bytearray ( ) const;

    /// Are pictures same ?
    bool operator== ( const picture & ) const;

    /// Assignment operator
    picture & operator= ( const picture & ) = default;

    /// Save picture to filepath
    bool save ( const std::string filepath );

    /// Print buffer on std::out
    void echo ( ) const;

private:

    // Hide empty constructor    
    picture ( ) = delete;

    // Parse the bytestream into the bytearray
    void openCopy_ ( std::ifstream & bytestream );

    
    std::vector<rapp::types::byte> bytearray_;
};

}
}
#endif

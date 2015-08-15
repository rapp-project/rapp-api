#include "picture.hpp"

namespace rapp {
namespace object {

picture::picture ( const std::string filepath )
{
    std::ifstream bytestream( filepath, std::ios::in | std::ios::binary | std::ios::ate );
    if ( !bytestream.is_open() )
        throw std::runtime_error ( "picture: could not open bytestream for " + filepath );
    
    picture::openCopy_ ( bytestream );
}

picture::picture ( std::ifstream & bytestream )
{
    picture::openCopy_ ( bytestream );
}

picture::picture ( std::vector<rapp::types::byte> bytearray )
{
    bytearray_ = bytearray;
}

std::vector<rapp::types::byte> picture::bytearray ( ) const
{
    return bytearray_;
}

bool picture::save ( const std::string filepath )
{
    std::ofstream os ( filepath, std::ios::out | std::ofstream::binary );
    if ( os.is_open() )
    {
        std::copy( bytearray_.begin(), bytearray_.end(), std::ostreambuf_iterator<rapp::types::byte>( os ) );
        os.close();
        return true;
    }
    return false;
}

bool picture::operator== ( const picture & rhs ) const
{
    return ( this->bytearray_ == rhs.bytearray_ );
}

void picture::echo ( ) const
{
    for ( const auto & byte : bytearray_ )
        std::cout << byte;
    std::cout << std::endl;
}

void picture::openCopy_ ( std::ifstream & bytestream )
{
    bytestream.seekg( 0, std::ios_base::end);
    std::streampos fileSize = bytestream.tellg();
    bytearray_.resize( fileSize );
    bytestream.seekg( 0, std::ios_base::beg );
    bytestream.read( &bytearray_[0], fileSize );
}



}
}

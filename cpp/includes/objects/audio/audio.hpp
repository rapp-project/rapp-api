#ifndef RAPP_OBJECT_AUDIO
#define RAPP_OBJECT_AUDIO
#include "Includes.ihh"
namespace rapp {
namespace object {
/**
 * @class audio
 * @brief class which wraps around raw bytes of an audiofile
 * @version 1
 * @date 16-August-2015
 * @author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class audio
{
public:

    /// Construct from a file-path
    audio ( const std::string filepath )
    {
        std::ifstream bytestream( filepath, 
                                  std::ios::in | std::ios::binary | std::ios::ate );

        if ( !bytestream.is_open() )
            throw std::runtime_error ( "audio: could not open bytestream for " + filepath );
        else
            openCopy_ ( bytestream );
    }

    /// Construct using an open file stream
    audio ( std::ifstream & bytestream )
    {
        openCopy_( bytestream );
    }

    /// Copy constructor
    audio ( const audio & ) = default;

    /// Get audio as array of bytes
    std::vector<rapp::types::byte> bytearray ( ) const
    {
        return bytearray_;
    }

    /// Are audios same ?
    bool operator== ( const audio & rhs ) const
    {
        return ( this->bytearray_ == rhs.bytearray_ );
    }

    /// Assignment operator
    audio & operator= ( const audio & ) = default;

    /// Save audio to filepath
    bool save ( const std::string filepath )
    {
        std::ofstream os ( filepath, std::ios::out | std::ofstream::binary );
        if ( os.is_open() )
        {
            std::copy( bytearray_.begin(), bytearray_.end(), 
                       std::ostreambuf_iterator<rapp::types::byte>( os ) );
            os.close();
            return true;
        }
        else
            return false;
    }

private:

    // Delete empty constructor    
    audio ( ) = delete;

    // Copy the bytestream into the bytearray
    void openCopy_ ( std::ifstream & bytestream )
    {
        bytestream.seekg( 0, std::ios_base::end );
        std::streampos fileSize = bytestream.tellg();
        bytearray_.resize( fileSize );
        bytestream.seekg( 0, std::ios_base::beg );
        bytestream.read( &bytearray_[0], fileSize );
    }

    // Actual bytes of audio file
    std::vector<rapp::types::byte> bytearray_;
};
}
}
#endif

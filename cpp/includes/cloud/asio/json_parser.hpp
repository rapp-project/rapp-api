#ifndef RAPP_ASIO_JSON_PARSER
#define RAPP_ASIO_JSON_PARSER
namespace rapp{
namespace cloud{
/**
 * \class 
 * \brief
 * \version 0.7.0
 * \date August 2016
 * \author Maria Ramos <m.ramos@ortelio.co.uk>
 */
class json_parser
{
public:
    /// \brief JSON deserialisation interface
    virtual void deserialise(std::string) const = 0;
};
}
}
#endif

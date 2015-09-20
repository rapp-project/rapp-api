#ifndef RAPP_ROBOT_COMM
#define RAPP_ROBOT_COMM
#include "Includes.ihh"
namespace rapp {
namespace robot {
/**
 * @class communication
 * @brief Abstract Base Class (ABC) Interface for Robot Communication
 * @version 1
 * @date 20-September-2015
 * @author Alex Giokas <a.gkiokas@ortelio.co.uk>
 *
 * This class specifies the interface for all communications.
 * It is your responsibility to implement them appropriately.
 */
class communication
{
  public:
    
    enum class Language {ENGLISH, GREEK};

    /// Produce Audio from robot's speakers
    // TODO: Explain all parameters
    virtual bool playAudio ( 
                              const std::string & file_path, 
                              double position, 
                              double volume, 
                              double balance, 
                              bool play_in_loop
                           )  = 0;

    /// Produce speec from text
    virtual bool textToSpeech (
                                 const std::string str, 
                                 Language language = Language::ENGLISH
                              )  = 0;

    /// ?
    virtual std::string wordSpotting ( 
                                        std::array<std::string> dictionary, 
                                        unsigned int size
                                     )  = 0;

    /// Record audio
    // TODO: explain parameters 
    virtual bool captureAudio ( 
                                 std::shared_ptr<rapp:object::audio> buffer, 
                                 float waiting_time, 
                                 float microphone_energy
                              )  = 0;

    /// Get Microphone Energy - NOTE what is the Param @name used for?
    virtual float getMicrophoneEnergy( std::string name ) const = 0;

    /// Record Voice - NOTE: @param audio pointer will be updated
    /// If this method is asynchronous or multi-threaded, then you
    /// need to lock the pointer in your implementation.
    virtual bool voiceRecord ( const std::shared_ptr<rapp::object::audio> ) = 0;

};
}
}
#endif

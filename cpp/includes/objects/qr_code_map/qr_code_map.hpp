#ifndef RAPP_OBJECT_QRCODEMAP
#define RAPP_OBJECT_QRCODEMAP

#include "includes.ihh"

namespace rapp {
namespace object {

/**
 * @class qr_code_map
 * @brief class which should encapsulate map of qr codes in environment 
 * @version 1
 * @date 10-May-2016
 * @author Wojciech Dudek <dudekwa@gmail.com>
 */


struct qr_code_map
{
  public:
    
    /**
     * @brief Consruct using path header, definition of success/error code, vector of path points
     * @param labels is vector of qr codes labels (e.g. ids)
     * @param poses is vector of qr codes poses
     */

    std::vector<std::string> labels;
    std::vector<pose> poses;
    qr_code_map ( 
              std::vector<std::string> labels,
              std::vector<pose> poses
            )
    : labels ( labels ),
      poses ( poses )
    { }
    
    /// Allow Empty Consructor
    qr_code_map ( ) = default;
    
    /// Copy Conatructor
    qr_code_map ( const qr_code_map & ) = default;

    
    /** 
     * @brief Equality operator
     * @note compare all components
     */
    bool operator== ( const qr_code_map & rhs ) const
    {
      if (this->labels== rhs.labels){
        if (this->poses== rhs.poses){
        return true;
      }
      }
      return false;
    }


};
}
}
#endif

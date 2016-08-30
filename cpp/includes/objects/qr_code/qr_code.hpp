#ifndef RAPP_OBJECT_QRCODE
#define RAPP_OBJECT_QRCODE
/**
 * Copyright 2015 RAPP
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * #http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "includes.ihh"
namespace rapp {
namespace object {
/**
 * \class qrCode
 * \brief class which should encapsulate a QR code
 * \version 0.7.0
 * \date 25 August 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
class qr_code
{
public:
    /**
     * \brief Construct using code coordinates (a rectangle) and a label (URL, email, string, etc)
     * \param centre_x is coordinate
     * \param centre_y is coordinate
     * \param label is message embedded in QR
     */
    qr_code( 
              float centre_x,
              float centre_y,
              std::string label
           );
    
    /// \brief Allow Empty Constructor
    qr_code() = default;
    
    /// \brief Copy Constructor
    qr_code(const qr_code &) = default;
    
    /** 
     * \brief Equality operator
     * \note the message is case insensitvely compared
     */
    bool operator==(const qr_code & rhs) const;

    /// \brief Get the qr Label
    std::string label() const;
    
private:
      float centre_x__ = -1;
      float centre_y__ = -1;
      std::string message__ ;
};
}
}
#endif

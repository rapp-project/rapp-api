#ifndef RAPP_OBJECT_QRCODE3D
#define RAPP_OBJECT_QRCODE3D

#include "includes.ihh"

namespace rapp {
namespace object {

/**
 * @class qr_code_3d
 * @brief class which should encapsulate a QR code in camera coordinate system and in robot coordinate system
 * @version 1
 * @date 09-November-2015
 * @author Jan Figat <jfigat@ia.pw.edu.pl>
 */
struct qr_code_3d
{
    bool is_qr_code_found;
    int number_of_qr_codes;//number of detected QRcodes
    std::vector<std::vector<std::vector<double>>> landmark_in_camera_coordinate;//Transformation matrix from camera to Landmark
    std::vector<std::vector<std::vector<double>>> landmark_in_robot_coordinate;//Transformation matrix from camera to robot
    std::vector<std::string> qr_message; //vector for messages from QRcodes

    void clear()
    {
        is_qr_code_found = false;
        number_of_qr_codes = 0;
        landmark_in_camera_coordinate.clear();
        landmark_in_robot_coordinate.clear();
        qr_message.clear();
    }
};

}
}
#endif

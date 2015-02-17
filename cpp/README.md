This is work in progress (17-February-2015)
Alex Gkiokas <a.gkiokas@ortelio.co.uk>

Directory tree:

/includes -> all include headers and cpp implementation files
/tests -> simple tests which serve as an example demo for your convenience
rapp -> global header, imports all required headers for your convenience


Requirements:

GCC > 4.7.1 	This is very important, your compiler MUST SUPPORT C++11 (and not C++0X)
		OpenNao (Gentoo 2.1.2.17) ships with gcc 4.5 which is not enough.
		Currently the only solution is to download, build and install GCC from source.

BOOST > 1.49	This is the only external dependency of RAPP API, other than C++11.


Building:

mkdir build
cd build
cmake ..
make (or make -j4, make -j8)
sudo make install
    

Using it:

#include <rapp/rapp>

Then link with it, using lrapp-0.1.so (shared library) or with the static version.
For linking instructions, please have a look at CMake helpfiles.

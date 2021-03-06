astro
=====

What is it?
-----------

**astro** is a C++ astronomical library. Functionality includes:
* Calculating the following for all the majory planetary bodies at any
given UTC date:
    * Right ascension;
    * Declination;
    * Distance from the earth;
    * Heliocentric coordinates in the orbital plane;
    * Heliocentric coordinates in the J2000 ecliptic plane;
    * Geocentric ecliptic coordinates;
    * Geocentric equatorial coordinates; and
    * Zodiac coordinates of the form 15GE23.
* Solving Kepler's equation;
* Converting degrees to hour/minute/second and degree/minute/second formats;
* Finding the Julian date for any given UTC date; and
* Converting rectangular to spherical coordinates.

Who maintains it?
-----------------
**astro** is written and maintained by Paul Griffiths.

The latest version
------------------
Details of the latest version can be found on the GitHub project page at
<https://github.com/paulgriffiths/astro>.

Documentation
-------------
Up-to-date documentation can be found at
<https://github.com/paulgriffiths/astro/wiki>.


Installation
------------
**astro** is written in C++. It requires the **utctime** library, which
can be found at <https://github.com/paulgriffiths/utctime>.

Download the source code and edit the file `Makefile` to modify the
following variables:
* LIB_INSTALL_PATH
* INC_INSTALL_PATH

with the directories to which to install the library and the header files,
and the variables:
* UTC_INC_PATH
* UTC_LIB_PATH

with the directories in which the UTCTime library and headers are installed.

From the command line, run `make` and then `make install` to deploy the
library and header files. Run `make sample` to build an example program
with the installed library. `#include <paulgrif/astro.h>` to use the
library.

a sample program. Include the files in your project to access the functionality. 
Licensing
---------
Please see the file called LICENSE.

Contacts
--------
* If you have a concrete bug report for **astro** please go to the GitHub
issue tracker at <https://github.com/paulgriffiths/astro/issues>.

/*
 *  planets.cpp
 *  ===========
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Implementation of solar system planets.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include "astro_common_types.h"
#include "planets.h"

using namespace astro;

/*
 *  Override helio_XXX_coords() member functions for Sun.
 *
 *  Heliocentric coordinates for the Sun will obviously always be zero.
 */

RectCoords Sun::helio_orb_coords() const {
    return RectCoords();
}

RectCoords Sun::helio_ecl_coords() const {
    return RectCoords();
}



/*
 *  Override geo_XXX_coords() member functions for Earth.
 *
 *  Geocentric coordinates for the Earth will obviously always be zero.
 */

RectCoords Earth::geo_ecl_coords() const {
    return RectCoords();
}

RectCoords Earth::geo_equ_coords() const {
    return RectCoords();
}


/*
 *  Returns the planet's name.
 */

std::string Earth::name() const {
    return "Earth";
}

std::string Sun::name() const {
    return "Sun";
}

std::string Mercury::name() const {
    return "Mercury";
}

std::string Venus::name() const {
    return "Venus";
}

std::string Mars::name() const {
    return "Mars";
}

std::string Jupiter::name() const {
    return "Jupiter";
}

std::string Saturn::name() const {
    return "Saturn";
}

std::string Uranus::name() const {
    return "Uranus";
}

std::string Neptune::name() const {
    return "Neptune";
}

std::string Pluto::name() const {
    return "Pluto";
}

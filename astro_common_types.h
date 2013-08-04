/*
 *  astro_common_types.h
 *  ====================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Common types used by the astronomical library
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_ASTRO_COMMON_TYPES_H
#define PG_ASTRO_COMMON_TYPES_H

namespace astro {

enum planets {sun, mercury, venus, earth, mars,
              jupiter, saturn, uranus, neptune, pluto};

enum zodiac {ARIES, TAURUS, GEMINI, CANCER, LEO, VIRGO,
             LIBRA, SCORPIO, SAGITTARIUS, CAPRICORN, AQUARIUS, PISCES};

struct ZodiacInfo {
    double right_ascension;
    int sign_index;
    const char * sign_name;
    const char * sign_short_name;
    int degrees;
    int minutes;
    int seconds;
};

struct HMS {
    int hours;
    int minutes;
    int seconds;
};

struct DMS {
    int degrees;
    int minutes;
    int seconds;
};

struct SphCoords {
    double right_ascension;
    double declination;
    double distance;
};

struct RectCoords {
    double x;
    double y;
    double z;
};

struct OrbElem {
    double sma;     // Semi-major axis
    double ecc;     // Eccentricity
    double inc;     // Inclination
    double ml;      // Mean longitude
    double lp;      // Longitude perihelion
    double lan;     // Longitude ascending node
    double man;     // Mean anomaly
    double arp;     // Argument of perihelion
};

const double PI = 3.14159265358979323846;

const double EPOCH_J2000 = 2451545;

}           //  namespace astro

#endif          // PG_ASTRO_COMMON_TYPES_H

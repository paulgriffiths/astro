/*
 *  astrofunc.h
 *  ===========
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to astronomical functions and constants.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_ASTROFUNC_H
#define PG_ASTROFUNC_H

#include <string>
#include <cmath>

namespace astro {

/*
 *  Structures
 */

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


/*
 *  Constants & enumerations
 */

const char * const ZODIAC_SIGNS[] = {
    "Aries", "Taurus", "Gemini", "Cancer",
    "Leo", "Virgo", "Libra", "Scorpio",
    "Sagittarius", "Capricorn", "Aquarius", "Pisces"
};

const char * const ZODIAC_SIGNS_SHORT[] = {
    "AR", "TA", "GE", "CN", "LE", "VI",
    "LI", "SC", "SG", "CP", "AQ", "PI"
};

const double PI = 3.14159265358979323846;

const double EPOCH_J2000 = 2451545;

enum zodiac {ARIES, TAURUS, GEMINI, CANCER, LEO, VIRGO,
             LIBRA, SCORPIO, SAGITTARIUS, CAPRICORN, AQUARIUS, PISCES};


/*
 *  Function prototypes
 */

void deg_to_hms(const double degrees, HMS& hmsout);
void deg_to_dms(const double degrees, DMS& dmsout);
double hypot(const double opp, const double adj);
void get_zodiac_info(const double rasc, ZodiacInfo& zInfo);
double julian_date(tm * utc_time);
tm get_utc_tm(tm * utc_time);
double kepler(const double m_anom, const double ecc);
void rec_to_sph(const RectCoords& rcd, SphCoords& scd);
const char * zodiac_sign(const double rasc);
const char * zodiac_sign_short(const double rasc);
std::string rasc_to_zodiac(const double rasc);
std::string rasc_string(const double rasc);
std::string decl_string(const double decl);


/*
 *  Inline functions
 */

/*
 *  Returns a double representing an angle in degrees in the
 *  range 0 <= d < 360, when the supplied angle may or may
 *  not be outside of this range.
 */

inline double normalize_degrees(const double angle) {
    return angle - 360 * floor(angle / 360);
}


/*
 *  Converts radians to degrees.
 */

inline double degrees(const double radians) {
    return radians / (PI / 180);
}


/*
 *  Converts degrees to radians.
 */

inline double radians(const double degrees) {
    return degrees * (PI / 180);
}

}           //  namespace astro

#endif          // PG_ASTROFUNC_H

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


#ifndef PG_ASTRO_ASTROFUNC_H
#define PG_ASTRO_ASTROFUNC_H

#include <string>
#include <cmath>
#include "astro_common_types.h"


namespace astro {

/*
 *  Constants
 */

const double PI = 3.14159265358979323846;


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

inline double degrees(const double rads) {
    return rads / (PI / 180);
}


/*
 *  Converts degrees to radians.
 */

inline double radians(const double degs) {
    return degs * (PI / 180);
}

}           //  namespace astro

#endif          // PG_ASTRO_ASTROFUNC_H

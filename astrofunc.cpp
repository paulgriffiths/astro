/*
 *  astrofunc.cpp
 *  =============
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Implementation of astronomical functions.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <sstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include "astro_common_types.h"
#include "astrofunc.h"
#include "utc_time.h"

using std::cos;
using std::sin;
using std::atan;
using std::atan2;
using std::fabs;
using std::floor;
using std::ceil;
using std::pow;
using std::sqrt;
using std::time;
using std::mktime;
using std::gmtime;
using std::difftime;

using namespace astro;


/*
 *  Converts a degree angle to hours, minutes and seconds
 *  and stores the result (and modifies) the supplied
 *  HMS struct.
 */

void astro::deg_to_hms(const double degrees, HMS& hmsout) {
    static const double secs_in_a_day = 86400;
    static const double secs_in_an_hour = 3600;
    const double norm_degs = normalize_degrees(degrees);
    const int total_seconds = floor((norm_degs / 360) * secs_in_a_day);

    hmsout.hours = total_seconds / secs_in_an_hour;
    hmsout.minutes = (total_seconds - hmsout.hours * secs_in_an_hour) / 60;
    hmsout.seconds = total_seconds - hmsout.hours * secs_in_an_hour -
                     hmsout.minutes * 60;

    assert(hmsout.hours >= 0);
    assert(hmsout.hours < 24);
    assert(hmsout.minutes >= 0);
    assert(hmsout.minutes < 60);
    assert(hmsout.seconds >= 0);
    assert(hmsout.seconds < 60);
}


/*
 *  Converts a degree angle to degrees, minutes and seconds
 *  and stores the result (and modifies) the supplied
 *  DMS struct.
 */

void astro::deg_to_dms(const double degrees, DMS& dmsout) {
    static const double secs_in_an_hour = 3600;
    const int total_seconds = degrees > 0 ? floor(degrees * secs_in_an_hour) :
                                            ceil(degrees * secs_in_an_hour);

    dmsout.degrees = total_seconds / secs_in_an_hour;
    dmsout.minutes = (total_seconds - dmsout.degrees * secs_in_an_hour) / 60;
    dmsout.seconds = total_seconds - dmsout.degrees * secs_in_an_hour -
                                     dmsout.minutes * 60;
    
    assert(dmsout.minutes > -60);
    assert(dmsout.minutes < 60);
    assert(dmsout.seconds > -60);
    assert(dmsout.seconds < 60);
}


/*
 *  Calculates the length of the hypotenuse using Pythagoras.
 */

double astro::hypot(const double opp, const double adj) {
    return sqrt(pow(opp, 2) + pow(adj, 2));
}


/*
 *  Calculates information pertaining to the zodiacal position
 *  of the supplied right ascension, and stores the result in
 *  (and modifies) the supplied ZodiacInfo struct.
 */

void astro::get_zodiac_info(const double rasc, ZodiacInfo& zInfo) {
    static const char * const zodiac_signs[] = {
        "Aries", "Taurus", "Gemini", "Cancer",
        "Leo", "Virgo", "Libra", "Scorpio",
        "Sagittarius", "Capricorn", "Aquarius", "Pisces"
    };
    static const char * const zodiac_signs_short[] = {
        "AR", "TA", "GE", "CN", "LE", "VI",
        "LI", "SC", "SG", "CP", "AQ", "PI"
    };

    const double norm_degs = normalize_degrees(rasc);
    DMS dms;
    deg_to_dms(norm_degs, dms);

    zInfo.right_ascension = norm_degs;
    zInfo.sign_index = dms.degrees / 30;

    assert(zInfo.sign_index >= 0);
    assert(zInfo.sign_index < 12);

    zInfo.sign_name = zodiac_signs[zInfo.sign_index];
    zInfo.sign_short_name = zodiac_signs_short[zInfo.sign_index];
    zInfo.degrees = dms.degrees % 30;

    assert(zInfo.degrees >= 0);
    assert(zInfo.degrees < 30);

    zInfo.minutes = dms.minutes;
    zInfo.seconds = dms.seconds;
}


/*
 *  Calculates the Julian Date for the supplied UTC time.
 *
 *  The supplied time is a standard tm struct representing
 *  a UTC time. The supplied time is modified by mktime(),
 *  but the modified information will not be reliable, since
 *  julian_date() interprets the tm struct as UTC time, and
 *  mktime() will interpret it as local time.
 */

double astro::julian_date(const utctime::UTCTime& utc_time) {
    static const double epoch_j2000 = 2451545;
    static const double secs_in_a_day = 86400;
    static const time_t ts_epoch_j2000 = utctime::get_utc_timestamp(2000,
                                           1, 1, 12, 0, 0);
        
    const double seconds_since_j2000 = difftime(utc_time.timestamp(),
                                                ts_epoch_j2000);
    return epoch_j2000 + seconds_since_j2000 / secs_in_a_day;
}


/*
 *  Returns a tm struct containing the current UTC time if the
 *  supplied argument is 0, or returns the provided argument with
 *  the tm_isdst member zeroed out, in case the user omitted to
 *  zero it (there is no concept of daylight savings time with UTC).
 */

tm astro::get_utc_tm(tm * utc_time) {
    if ( utc_time ) {
        (*utc_time).tm_isdst = 0;
        return *utc_time;
    }

    time_t cal_time = time(0);
    tm * ut_tm = gmtime(&cal_time);
    return *ut_tm;
}


/*
 *  Solves Kepler's equation.
 *
 *  Arguments:
 *    m_anom - mean anomaly, in radians
 *    ecc - eccentricity
 *
 *  Returns:
 *    the eccentric anomaly, in radians.
 */

double astro::kepler(const double m_anom, const double ecc) {
    const double desired_accuracy = 1e-6;

    assert(ecc >= 0);       // Eccentricity is 0 for a circle
    assert(ecc < 1);        // Eccentricity is less than 1 for an ellipse

    double e_anom = m_anom;
    double diff;

    do {
        diff = e_anom - ecc * sin(e_anom) - m_anom;
        e_anom -= diff / (1 - ecc * cos(e_anom));
    } while ( fabs(diff) > desired_accuracy );

    return e_anom;
}


/*
 *  Converts rectangular coordinates to spherical coordinates.
 *
 *  This function stores the result in (and modifies) the supplied
 *  SphCoords struct.
 */

void astro::rec_to_sph(const RectCoords& rcd, SphCoords& scd) {
    scd.right_ascension = degrees(atan2(rcd.y, rcd.x));
    scd.declination = degrees(atan(rcd.z / hypot(rcd.x, rcd.y)));
    scd.distance = sqrt(pow(rcd.x, 2) + pow(rcd.y, 2) + pow(rcd.z, 2));
}


/*
 *  Returns a pointer to a C string representation of the
 *  of the name of the zodiac sign which contains the supplied
 *  right ascension.
 */

const char * astro::zodiac_sign(const double rasc) {
    ZodiacInfo zInfo;
    get_zodiac_info(rasc, zInfo);
    return zInfo.sign_name;
}


/*
 *  Returns a pointer to a C string representation of the
 *  of the short name of the zodiac sign which contains the supplied
 *  right ascension.
 */

const char * astro::zodiac_sign_short(const double rasc) {
    ZodiacInfo zInfo;
    get_zodiac_info(rasc, zInfo);
    return zInfo.sign_short_name;
}


/*
 *  Returns a zodiacal coordinate of the form 20GE19 for
 *  the supplied right ascension.
 */

std::string astro::rasc_to_zodiac(const double rasc) {
    ZodiacInfo zInfo;
    get_zodiac_info(rasc, zInfo);

    std::ostringstream oStream;
    oStream << std::setfill('0');
    oStream << std::setw(2) << zInfo.degrees << zInfo.sign_short_name
            << std::setw(2) << zInfo.minutes;
    
    return oStream.str();
}


/*
 *  Returns a string representation in the form "12h 10m 30s" of
 *  the hours-minutes-seconds representation of the supplied right
 *  ascension.
 */

std::string astro::rasc_string(const double rasc) {
    HMS hms;
    deg_to_hms(rasc, hms);

    std::ostringstream oStream;
    oStream << std::setfill('0');
    oStream << std::setw(2) << hms.hours << "h "
            << std::setw(2) << hms.minutes << "m "
            << std::setw(2) << hms.seconds << "s";
    
    return oStream.str();
}


/*
 *  Returns a string representation in the form "+212d 10m 30s" of
 *  the degrees-minutes-seconds representation of the supplied
 *  declination.
 */

std::string astro::decl_string(const double decl) {
    DMS dms;
    deg_to_dms(decl, dms);

    std::ostringstream oStream;
    oStream << std::setfill('0');
    oStream << (decl >= 0 ? "+" : "")
            << std::setw(2) << dms.degrees << "d "
            << std::setw(2) << fabs(dms.minutes) << "m "
            << std::setw(2) << fabs(dms.seconds) << "s";
    
    return oStream.str();
}

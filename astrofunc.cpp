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


#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

#include <cmath>
#include <cassert>
#include <ctime>

#include "astro_common_types.h"
#include "astrofunc.h"

using namespace astro;


namespace {

const char * const ZODIAC_SIGNS[] = {
    "Aries", "Taurus", "Gemini", "Cancer",
    "Leo", "Virgo", "Libra", "Scorpio",
    "Sagittarius", "Capricorn", "Aquarius", "Pisces"
};

const char * const ZODIAC_SIGNS_SHORT[] = {
    "AR", "TA", "GE", "CN", "LE", "VI",
    "LI", "SC", "SG", "CP", "AQ", "PI"
};

}           //  namespace


/*
 *  Converts a degree angle to hours, minutes and seconds
 *  and stores the result (and modifies) the supplied
 *  HMS struct.
 */

void astro::deg_to_hms(const double degrees, HMS& hmsout) {
    const double norm_degs = normalize_degrees(degrees);
    const int total_seconds = floor((norm_degs / 360) * 86400);

    hmsout.hours = total_seconds / 3600;
    hmsout.minutes = (total_seconds - hmsout.hours * 3600) / 60;
    hmsout.seconds = total_seconds - hmsout.hours * 3600 - hmsout.minutes * 60;

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
    const int total_seconds = degrees > 0 ? floor(degrees * 3600) :
                                            ceil(degrees * 3600);

    dmsout.degrees = total_seconds / 3600;
    dmsout.minutes = (total_seconds - dmsout.degrees * 3600) / 60;
    dmsout.seconds = total_seconds - dmsout.degrees * 3600 -
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
    const double norm_degs = normalize_degrees(rasc);
    DMS dms;
    deg_to_dms(norm_degs, dms);

    zInfo.right_ascension = norm_degs;
    zInfo.sign_index = dms.degrees / 30;

    assert(zInfo.sign_index >= 0);
    assert(zInfo.sign_index < 12);

    zInfo.sign_name = ZODIAC_SIGNS[zInfo.sign_index];
    zInfo.sign_short_name = ZODIAC_SIGNS_SHORT[zInfo.sign_index];
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

double astro::julian_date(tm * utc_time) {
    double seconds_since_j2000;

    if ( utc_time == 0 ) {

        //  If no time was specified, just get the difference in
        //  seconds between the current UNIX timestamp, and the
        //  UNIX timestamp at J2000.

        const time_t unix_epoch_j2000 = 946728000;
        const time_t utc_t = time(0);
        seconds_since_j2000 = difftime(utc_t, unix_epoch_j2000);

    } else {

        //  If a time was specified, we're interpreting it as UTC,
        //  so we have some work to do.

        //  First calculate the UNIX timestamp for Jan 1, 2000, 12:00pm,
        //  as if the current system were on GMT. Make sure we ignore
        //  DST, although it'll be off on Jan 1 anyway.

        tm j2000_epoch_tm;
        j2000_epoch_tm.tm_sec = 0;
        j2000_epoch_tm.tm_min = 0;
        j2000_epoch_tm.tm_hour = 12;
        j2000_epoch_tm.tm_mday = 1;
        j2000_epoch_tm.tm_mon = 0;
        j2000_epoch_tm.tm_year = 100;
        j2000_epoch_tm.tm_isdst = 0;
        const time_t j2000_epoch = mktime(&j2000_epoch_tm);

        //  Then get the UNIX timestamp for the specified time, again
        //  as if the current system were on GMT. This time we really
        //  do need to be sure we're ignoring DST, as UTC has no
        //  concept of it and the date specified might be during the
        //  summer.
        //
        //  Note that this assumes that, after ignoring DST, there is
        //  no difference between local time and UTC except a constant
        //  time offset.

        tm calc_time = *utc_time;
        calc_time.tm_isdst = 0;
        const time_t utc_t = mktime(&calc_time);

        //  Then calculate the difference between the two times.

        seconds_since_j2000 = difftime(utc_t, j2000_epoch);

    }
        
    return EPOCH_J2000 + seconds_since_j2000 / 86400;
}


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

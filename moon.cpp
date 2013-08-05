/*
 *  base_planet.cpp
 *  ===============
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Implementation of abstract base Planet class.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cmath>
#include "astro_common_types.h"
#include "astrofunc.h"
#include "base_planet.h"
#include "moon.h"

using std::cos;
using std::sin;
using std::sqrt;
using std::pow;
using std::strftime;

using namespace astro;

namespace {

//  Orbital elements for each planet at J2000

const OrbElem ELEMENTS_Y2000[] = {
    {60.2666, 0.0549, 5.1454, 198.5516, 83.1862, 125.1228, 0, 0},   // Moon
    {1, 0.016709, 0, 278.9874, -77.0596, 0, 0, 0}                   // Sun
};

const OrbElem ELEMENTS_DAY[] = {
    {0, 0, 0, 13.1763964649, 0.111403514, -0.0529538083, 0, 0},
    {0, -0.000000001151, 0, 0.98564735200, 0.00004709350, 0, 0, 0}
};

}           //  namespace


/*
 *  Returns orbital elements for the specified time.
 */

OrbElem MoonBase::calc_orbital_elements(std::tm* calc_time) const {
    double seconds_since_y2000;

    if ( calc_time == 0 ) {

        //  If no time was specified, just get the difference in
        //  seconds between the current UNIX timestamp, and the
        //  UNIX timestamp at J2000.

        const time_t unix_epoch_y2000 = 946684800;
        const time_t utc_t = time(0);
        seconds_since_y2000 = difftime(utc_t, unix_epoch_y2000);

    } else {

        //  If a time was specified, we're interpreting it as UTC,
        //  so we have some work to do.

        //  First calculate the UNIX timestamp for Jan 1, 2000, 12:00pm,
        //  as if the current system were on GMT. Make sure we ignore
        //  DST, although it'll be off on Jan 1 anyway.

        tm y2000_epoch_tm;
        y2000_epoch_tm.tm_sec = 0;
        y2000_epoch_tm.tm_min = 0;
        y2000_epoch_tm.tm_hour = 0;
        y2000_epoch_tm.tm_mday = 1;
        y2000_epoch_tm.tm_mon = 0;
        y2000_epoch_tm.tm_year = 100;
        y2000_epoch_tm.tm_isdst = 0;
        const time_t y2000_epoch = mktime(&y2000_epoch_tm);

        //  Then get the UNIX timestamp for the specified time, again
        //  as if the current system were on GMT. This time we really
        //  do need to be sure we're ignoring DST, as UTC has no
        //  concept of it and the date specified might be during the
        //  summer.
        //
        //  Note that this assumes that, after ignoring DST, there is
        //  no difference between local time and UTC except a constant
        //  time offset.

        tm calc_time_copy = *calc_time;
        calc_time_copy.tm_isdst = 0;
        const time_t utc_t = mktime(&calc_time_copy);

        //  Then calculate the difference between the two times.

        seconds_since_y2000 = difftime(utc_t, y2000_epoch);
    }

    const double dys = seconds_since_y2000 / (60 * 60 * 24);
    OrbElem oes;
    oes.sma = ELEMENTS_Y2000[m_moon_number].sma +
              ELEMENTS_DAY[m_moon_number].sma * dys;
    oes.ecc = ELEMENTS_Y2000[m_moon_number].ecc +
              ELEMENTS_DAY[m_moon_number].ecc * dys;
    oes.inc = radians(ELEMENTS_Y2000[m_moon_number].inc +
                      ELEMENTS_DAY[m_moon_number].inc * dys);
    oes.ml = radians(ELEMENTS_Y2000[m_moon_number].ml +
                     ELEMENTS_DAY[m_moon_number].ml * dys);
    oes.lp = radians(ELEMENTS_Y2000[m_moon_number].lp +
                     ELEMENTS_DAY[m_moon_number].lp * dys);
    oes.lan = radians(ELEMENTS_Y2000[m_moon_number].lan +
                      ELEMENTS_DAY[m_moon_number].lan * dys);
    oes.man = oes.ml - oes.lp;
    oes.arp = oes.lp - oes.lan;

    return oes;
}

std::string MoonBase::name() const {
return "MoonBase";
}

std::string Moon::name() const {
return "Moon";
}

std::string SunForMoon::name() const {
return " - XXXX - Sun For Moon - XXXX -";
}


/*
 *  Override these functions, since we only need SunForMoon
 *  for its OrbitalElements. There has to be a better way than this.
 */

RectCoords SunForMoon::helio_orb_coords() const {
    const RectCoords gec = {0, 0, 0};
    return gec;
}

RectCoords SunForMoon::helio_ecl_coords() const {
    const RectCoords gec = {0, 0, 0};
    return gec;
}

RectCoords SunForMoon::geo_ecl_coords() const {
    const RectCoords gec = {0, 0, 0};
    return gec;
}

RectCoords SunForMoon::geo_equ_coords() const {
    const RectCoords gec = {0, 0, 0};
    return gec;
}

double SunForMoon::right_ascension() const {
    return 0;
}

double SunForMoon::declination() const {
    return 0;
}

double SunForMoon::distance() const {
    return 0;
}

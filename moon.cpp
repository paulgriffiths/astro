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


#include <string>
#include <ctime>
#include <cmath>
#include "astro_common_types.h"
#include "astrofunc.h"
#include "planet.h"
#include "moon.h"

using std::cos;
using std::sin;
using std::atan2;
using std::sqrt;
using std::pow;

using namespace astro;


/*
 *  Provide definition of pure virtual destructor.
 */

MoonBase::~MoonBase() {}


/*
 *  Returns orbital elements for the specified time.
 */

OrbElem MoonBase::calc_orbital_elements(std::tm* calc_time,
                                        const OrbElem& y2000_oes,
                                        const OrbElem& day_oes) const {
    double seconds_since_y2000;

    if ( calc_time == 0 ) {

        //  If no time was specified, just get the difference in
        //  seconds between the current UNIX timestamp, and the
        //  UNIX timestamp at Y2000.
        //
        //  Note that this functionality does not appear to take
        //  leap seconds into account, and the number of seconds
        //  since Y2000 is short by a few (maybe 15). This is not
        //  much, but it does create a small but noticeable
        //  difference for the moon, as it orbits relatively
        //  quickly.

        static const time_t unix_epoch_y2000 = 946598400;
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
        y2000_epoch_tm.tm_mday = 31;
        y2000_epoch_tm.tm_mon = 11;
        y2000_epoch_tm.tm_year = 99;
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

    static const double secs_in_a_day = 86400;
    const double days = seconds_since_y2000 / secs_in_a_day;

    OrbElem oes;

    oes.sma = y2000_oes.sma + day_oes.sma * days;
    oes.ecc = y2000_oes.ecc + day_oes.ecc * days;
    oes.inc = radians(y2000_oes.inc + day_oes.inc * days);
    oes.ml = radians(y2000_oes.ml + day_oes.ml * days);
    oes.lp = radians(y2000_oes.lp + day_oes.lp * days);
    oes.lan = radians(y2000_oes.lan + day_oes.lan * days);
    oes.man = oes.ml - oes.lp;
    oes.arp = oes.lp - oes.lan;

    return oes;
}


/*
 *  Returns geocentric ecliptic coordinates.
 */

RectCoords MoonBase::geo_ecl_coords() const {
    const RectCoords hoc = helio_orb_coords();
    const RectCoords hec = helio_ecl_coords();
    RectCoords gec;

    double lon = atan2(hec.y, hec.x);
    double lat = atan2(hec.z, hypot(hec.x, hec.y));
    double rhc = hoc.z;

    tm calc_time = get_calc_time();
    SunForMoon sfm(&calc_time);
    const OrbElem m_oes = get_orbital_elements();
    const OrbElem s_oes = sfm.get_orbital_elements();

    //  Calculate mean elongation and argument
    //  of latitude for the moon.

    const double mel = m_oes.ml - s_oes.ml;
    const double arl = m_oes.ml - m_oes.lan;

    //  Adjust for longitude perturbations

    double dlon = -1.274 * sin(m_oes.man - 2 * mel);
    dlon += 0.658 * sin(2 * mel);
    dlon -= 0.186 * sin(s_oes.man);
    dlon -= 0.059 * sin(2 * m_oes.man - 2 * mel);
    dlon -= 0.057 * sin(m_oes.man - 2 * mel + s_oes.man);
    dlon += 0.053 * sin(m_oes.man + 2 * mel);
    dlon += 0.046 * sin(2 * m_oes.ml - s_oes.man);
    dlon += 0.041 * sin(m_oes.man - s_oes.man);
    dlon -= 0.035 * sin(m_oes.ml);
    dlon -= 0.031 * sin(m_oes.man + s_oes.man);
    dlon -= 0.015 * sin(2 * arl - 2 * mel);
    dlon += 0.011 * sin(m_oes.man - 4 * mel);
    lon = radians(dlon) + lon;

    //  Adjust for latitude perturbations

    double dlat = -0.173 * sin(arl - 2 * mel);
    dlat -= 0.055 * sin(m_oes.man - arl - 2 * mel);
    dlat -= 0.046 * sin(m_oes.man + arl - 2 * mel);
    dlat += 0.033 * sin(arl + 2 * mel);
    dlat += 0.017 * sin(2 * m_oes.man + arl);
    lat = radians(dlat) + lat;

    //  Adjust for rhc perturbations

    rhc = rhc - 0.58 * cos(m_oes.man - 2 * mel);
    rhc -= 0.46 * cos(2 * mel);

    //  Calculate cartesian coordinates of geocentric lunar position

    gec.x = rhc * cos(lon) * cos(lat);
    gec.y = rhc * sin(lon) * cos(lat);
    gec.z = rhc * sin(lat);

    return gec;
}


/*
 *  Provide name() functions.
 */

std::string Moon::name() const {
    return "Moon";
}

std::string SunForMoon::name() const {
    return " - XXXX - Sun For Moon - XXXX -";
}

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

//  Orbital elements for each planet at Y2000

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
 *  Return the orbital elements.
 */

OrbElem MoonBase::get_orbital_elements() const {
    return m_oes;
}


/*
 *  Returns orbital elements for the specified time.
 */

OrbElem MoonBase::calc_orbital_elements(std::tm* calc_time) const {
    double seconds_since_y2000;

    if ( calc_time == 0 ) {

        //  If no time was specified, just get the difference in
        //  seconds between the current UNIX timestamp, and the
        //  UNIX timestamp at J2000.
        //
        //  Note that this functionality does not appear to take
        //  leap seconds into account, and the number of seconds
        //  since Y2000 is short by a few (maybe 15). This is not
        //  much, but it does create a small but noticeable
        //  difference for the moon, as it orbits relatively
        //  quickly.

        const time_t unix_epoch_y2000 = 946598400;
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

    const double dys = seconds_since_y2000 / (60 * 60 * 24);
    OrbElem oes;
    oes.sma = ELEMENTS_Y2000[m_number].sma +
              ELEMENTS_DAY[m_number].sma * dys;
    oes.ecc = ELEMENTS_Y2000[m_number].ecc +
              ELEMENTS_DAY[m_number].ecc * dys;
    oes.inc = radians(ELEMENTS_Y2000[m_number].inc +
                      ELEMENTS_DAY[m_number].inc * dys);
    oes.ml = radians(ELEMENTS_Y2000[m_number].ml +
                     ELEMENTS_DAY[m_number].ml * dys);
    oes.lp = radians(ELEMENTS_Y2000[m_number].lp +
                     ELEMENTS_DAY[m_number].lp * dys);
    oes.lan = radians(ELEMENTS_Y2000[m_number].lan +
                      ELEMENTS_DAY[m_number].lan * dys);
    oes.man = oes.ml - oes.lp;
    oes.arp = oes.lp - oes.lan;

    return oes;
}


/*
 *  Calculates the planet's heliocentric orbital coordinates.
 */

RectCoords MoonBase::helio_orb_coords() const {
    RectCoords hoc;

    const double e_anom = kepler(m_oes.man, m_oes.ecc);

    hoc.x = m_oes.sma * (cos(e_anom) - m_oes.ecc);
    hoc.y = m_oes.sma * sqrt(1 - pow(m_oes.ecc, 2)) * sin(e_anom);
    hoc.z = hypot(hoc.x, hoc.y);

    return hoc;
}


/*
 *  Calculates the planet's heliocentric ecliptic coordinates.
 */

RectCoords MoonBase::helio_ecl_coords() const {
    const RectCoords hoc = helio_orb_coords();
    RectCoords hec;

    hec.x = (((cos(m_oes.arp) * cos(m_oes.lan) -
               sin(m_oes.arp) * sin(m_oes.lan) * cos(m_oes.inc)) * hoc.x) +
             ((-sin(m_oes.arp) * cos(m_oes.lan) -
                cos(m_oes.arp) * sin(m_oes.lan) * cos(m_oes.inc)) * hoc.y));
    hec.y = (((cos(m_oes.arp) * sin(m_oes.lan) +
               sin(m_oes.arp) * cos(m_oes.lan) * cos(m_oes.inc)) * hoc.x) +
             ((-sin(m_oes.arp) * sin(m_oes.lan) +
                cos(m_oes.arp) * cos(m_oes.lan) * cos(m_oes.inc)) * hoc.y));
    hec.z = ((sin(m_oes.arp) * sin(m_oes.inc) * hoc.x) +
             (cos(m_oes.arp) * sin(m_oes.inc) * hoc.y));
            
    return hec;
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

    tm temp_tm = m_calc_time;
    SunForMoon sfm(&temp_tm);
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
 *  Calculates the planet's geocentric equatorial coordinates.
 */

RectCoords MoonBase::geo_equ_coords() const {
    static const double obliquity = radians(23.43928);
    const RectCoords hec = geo_ecl_coords();
    RectCoords gec;

    gec.x = hec.x;
    gec.y = hec.y * cos(obliquity) - hec.z * sin(obliquity);
    gec.z = hec.y * sin(obliquity) + hec.z * cos(obliquity);

    return gec;
}


/*
 *  Calculates the planet's right ascension.
 */

double MoonBase::right_ascension() const {
    const RectCoords gqc = geo_equ_coords();
    SphCoords sph;
    rec_to_sph(gqc, sph);

    return sph.right_ascension;
}


/*
 *  Calculates the planet's declination
 */

double MoonBase::declination() const {
    const RectCoords gqc = geo_equ_coords();
    SphCoords sph;
    rec_to_sph(gqc, sph);

    return sph.declination;
}


/*
 *  Calculates the planet's distance
 */

double MoonBase::distance() const {
    const RectCoords gqc = geo_equ_coords();
    SphCoords sph;
    rec_to_sph(gqc, sph);

    return sph.distance;
}


std::string Moon::name() const {
return "Moon";
}

std::string SunForMoon::name() const {
return " - XXXX - Sun For Moon - XXXX -";
}

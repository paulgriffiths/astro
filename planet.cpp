/*
 *  planet.cpp
 *  ==========
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Implementation of abstract Planet class.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <string>
#include <cmath>
#include <paulgrif/utctime.h>
#include "astro_common_types.h"
#include "astrofunc.h"
#include "major_body.h"
#include "planets.h"

using std::cos;
using std::sin;
using std::sqrt;
using std::pow;

using namespace astro;


/*
 *  Define pure virtual destructor.
 */

Planet::~Planet() {}


/*
 *  Returns a UTCTime class containing the calculation time
 */

const utctime::UTCTime& Planet::get_calc_time() const {
    return m_calc_time;
}


/*
 *  Returns a string representation of the calculation time of the planet.
 */

std::string Planet::calc_time_string() const {
    return m_calc_time.time_string();
}


/*
 *  Return the orbital elements.
 */

const OrbElem& Planet::get_orbital_elements() const {
    return m_oes;
}


/*
 *  Calculates the planet's heliocentric orbital coordinates.
 */

RectCoords Planet::helio_orb_coords() const {
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

RectCoords Planet::helio_ecl_coords() const {
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
 *  Calculates the planet's geocentric equatorial coordinates.
 */

RectCoords Planet::geo_equ_coords() const {
    static const double obliquity = radians(23.43928);
    const RectCoords gec = geo_ecl_coords();
    RectCoords gqc;

    gqc.x = gec.x;
    gqc.y = gec.y * cos(obliquity) - gec.z * sin(obliquity);
    gqc.z = gec.y * sin(obliquity) + gec.z * cos(obliquity);

    return gqc;
}


/*
 *  Calculates the planet's right ascension.
 */

double Planet::right_ascension() const {
    const RectCoords gqc = geo_equ_coords();
    SphCoords sph;
    rec_to_sph(gqc, sph);

    return sph.right_ascension;
}


/*
 *  Calculates the planet's declination
 */

double Planet::declination() const {
    const RectCoords gqc = geo_equ_coords();
    SphCoords sph;
    rec_to_sph(gqc, sph);

    return sph.declination;
}


/*
 *  Calculates the planet's distance
 */

double Planet::distance() const {
    const RectCoords gqc = geo_equ_coords();
    SphCoords sph;
    rec_to_sph(gqc, sph);

    return sph.distance;
}

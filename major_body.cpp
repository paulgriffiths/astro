/*
 *  major_body.cpp
 *  ==============
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Implementation of abstract MajorBody base class for regular
 *  Solar System planets.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include "astro_common_types.h"
#include "astrofunc.h"
#include "major_body.h"
#include "planets.h"
#include "utc_time.h"

using namespace astro;


/*
 *  Provide definition of pure virtual destructor.
 */

MajorBody::~MajorBody() {}


/*
 *  Returns orbital elements for the specified time.
 *
 *  Arguments:
 *    calc_time - a pointer to a std::tm struct representing the
 *                UTC time for which to calculate, or 0 (NULL) for
 *                the current time.
 *    j2000_oes - an OrbElem struct representing the actual orbital
 *                elements at J2000
 *    century_oes - an OrbElem struct representing the changes in orbital
 *                  elements per Julian century.
 *
 *  Returns:
 *    An OrbElem struct containing the orbital elements for the
 *    specified time.
 */

OrbElem
MajorBody::calc_orbital_elements(const utctime::UTCTime& calc_time,
                                 const OrbElem& j2000_oes,
                                 const OrbElem& century_oes) const {
    static const double epoch_j2000 = 2451545;
    static const double jdays_per_cent = 36525;
    const double jcents = (julian_date(calc_time) - epoch_j2000) /
                          jdays_per_cent;

    OrbElem oes;
    oes.sma = j2000_oes.sma + century_oes.sma * jcents;
    oes.ecc = j2000_oes.ecc + century_oes.ecc * jcents;
    oes.inc = radians(j2000_oes.inc + century_oes.inc * jcents);
    oes.ml = radians(j2000_oes.ml + century_oes.ml * jcents);
    oes.lp = radians(j2000_oes.lp + century_oes.lp * jcents);
    oes.lan = radians(j2000_oes.lan + century_oes.lan * jcents);
    oes.man = oes.ml - oes.lp;
    oes.arp = oes.lp - oes.lan;

    return oes;
}


/*
 *  Calculates the planet's geocentric ecliptic coordinates.
 */

RectCoords MajorBody::geo_ecl_coords() const {
    const RectCoords eec = Earth(get_calc_time()).helio_ecl_coords();
    const RectCoords hec = helio_ecl_coords();

    RectCoords gec;

    gec.x = hec.x - eec.x;
    gec.y = hec.y - eec.y;
    gec.z = hec.z - eec.z;

    return gec;
}

/*
 *  base_planet.h
 *  =============
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to abstract Planet base class.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_ASTRO_BASE_PLANET_H
#define PG_ASTRO_BASE_PLANET_H

#include <string>
#include <ctime>
#include "astro_common_types.h"
#include "astrofunc.h"

namespace astro {

/*
 *  Planet abstract base class definition.
 */

class Planet {
    public:
        explicit Planet(const planets pnum, std::tm* ct) :
            m_number(pnum),
            m_calc_time(get_utc_tm(ct)),
            m_oes(calc_orbital_elements(ct)) {}
        virtual ~Planet() {}

        virtual std::string name() const = 0;
        std::string calc_time() const;

        OrbElem get_orbital_elements() const;
        virtual RectCoords helio_orb_coords() const;
        virtual RectCoords helio_ecl_coords() const;
        virtual RectCoords geo_ecl_coords() const;
        virtual RectCoords geo_equ_coords() const;
        double right_ascension() const;
        double declination() const;
        double distance() const;

    private:
        const planets m_number;
        const tm m_calc_time;
        const OrbElem m_oes;

        OrbElem calc_orbital_elements(std::tm* calc_time) const;
};

}           //  namespace astro

#endif          // PG_ASTRO_BASE_PLANET_H

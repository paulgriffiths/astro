/*
 *  planet.h
 *  ========
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to abstract Planet base class.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_ASTRO_PLANET_H
#define PG_ASTRO_PLANET_H

#include <string>
#include <ctime>
#include "astro_common_types.h"
#include "astrofunc.h"

namespace astro {

class Planet {
    public:
        explicit Planet(std::tm* calc_time, const OrbElem& oes) :
            m_calc_time(get_utc_tm(calc_time)),
            m_oes(oes) {}
        virtual ~Planet() = 0;

        virtual std::string name() const = 0;
        const tm& get_calc_time() const;
        std::string calc_time_string() const;

        OrbElem get_orbital_elements() const;
        virtual RectCoords helio_orb_coords() const;
        virtual RectCoords helio_ecl_coords() const;
        virtual RectCoords geo_ecl_coords() const = 0;
        virtual RectCoords geo_equ_coords() const;
        double right_ascension() const;
        double declination() const;
        double distance() const;

    private:
        const tm m_calc_time;
        const OrbElem m_oes;
};

}           //  namespace astro

#endif          // PG_ASTRO_PLANET_H

/*
 *  moon.h
 *  ======
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to Moon class.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_ASTRO_MOON_H
#define PG_ASTRO_MOON_H

#include <string>
#include <ctime>
#include "astro_common_types.h"
#include "astrofunc.h"
#include "base_planet.h"

namespace astro {

class MoonBase {
    public:
        explicit MoonBase(const moon_planets moon_number, std::tm* ct) :
            m_number(moon_number),
            m_calc_time(get_utc_tm(ct)),
            m_oes(calc_orbital_elements(ct)) {}
        virtual ~MoonBase() {}

        virtual std::string name() const = 0;
        OrbElem get_orbital_elements() const;
        virtual RectCoords helio_orb_coords() const;
        virtual RectCoords helio_ecl_coords() const;
        virtual RectCoords geo_ecl_coords() const;
        virtual RectCoords geo_equ_coords() const;
        double right_ascension() const;
        double declination() const;
        double distance() const;

    private:
        const moon_planets m_number;
        const tm m_calc_time;
        const OrbElem m_oes;

        OrbElem calc_orbital_elements(std::tm* calc_time) const;
};

class Moon : public MoonBase {
    public:
        explicit Moon(std::tm* ct) :
            MoonBase(moon_moon, ct) {}
        ~Moon() {}

        virtual std::string name() const;
};

class SunForMoon : public MoonBase {
    public:
        explicit SunForMoon(std::tm* ct) :
            MoonBase(moon_sun, ct) {}
        ~SunForMoon() {}

        virtual std::string name() const;
};

}           //  namespace astro

#endif          // PG_ASTRO_MOON_H

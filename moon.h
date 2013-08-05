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

class MoonBase : public Planet {
    public:
        explicit MoonBase(std::tm* ct, moon_planets moon_number) :
            Planet(moon, ct),
            m_moon_number(moon_number) {}
        ~MoonBase() {}

        virtual std::string name() const = 0;
        virtual OrbElem calc_orbital_elements(std::tm* calc_time) const;

    private:
        const moon_planets m_moon_number;
};

class Moon : public MoonBase {
    public:
        explicit Moon(std::tm* ct) :
            MoonBase(ct, moon_moon) {}
        ~Moon() {}

        virtual std::string name() const;
};

class SunForMoon : public MoonBase {
    public:
        explicit SunForMoon(std::tm* ct) :
            MoonBase(ct, moon_sun) {}
        ~SunForMoon() {}

        virtual std::string name() const;
        virtual RectCoords helio_orb_coords() const;
        virtual RectCoords helio_ecl_coords() const;
        virtual RectCoords geo_ecl_coords() const;
        virtual RectCoords geo_equ_coords() const;
        double right_ascension() const;
        double declination() const;
        double distance() const;
};

}           //  namespace astro

#endif          // PG_ASTRO_MOON_H

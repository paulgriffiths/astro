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
#include "planet.h"
#include "utc_time.h"

namespace astro {

class MoonBase : public Planet {
    public:
        explicit MoonBase(const utctime::UTCTime& ct,
                          OrbElem y2000_oes,
                          OrbElem day_oes) :
            Planet(ct, calc_orbital_elements(ct, y2000_oes, day_oes)) {}
        virtual ~MoonBase() = 0;

        virtual RectCoords geo_ecl_coords() const;

    private:
        OrbElem calc_orbital_elements(const utctime::UTCTime& calc_time,
                                      const OrbElem& y2000_oes,
                                      const OrbElem& day_oes) const;
};

class Moon : public MoonBase {
    public:
        explicit Moon(const utctime::UTCTime ct) :
            MoonBase(ct,
                     OrbElem(60.2666, 0.0549,
                             5.1454, 198.5516,
                             83.1862, 125.1228, 0, 0),
                     OrbElem(0, 0,
                             0, 13.1763964649,
                             0.111403514, -0.0529538083, 0, 0)) {}

        virtual std::string name() const;
};

class SunForMoon : public MoonBase {
    public:
        explicit SunForMoon(const utctime::UTCTime ct) :
            MoonBase(ct,
                     OrbElem(1, 0.016709,
                             0, 278.9874,
                             -77.0596, 0, 0, 0),
                     OrbElem(0, -0.000000001151,
                             0, 0.98564735200,
                             0.00004709350, 0, 0, 0)) {}

        virtual std::string name() const;
};

}           //  namespace astro

#endif          // PG_ASTRO_MOON_H

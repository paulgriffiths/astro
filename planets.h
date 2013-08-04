/*
 *  planets.h
 *  =========
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to solar system planet classes.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_ASTRO_PLANETS_H
#define PG_ASTRO_PLANETS_H

#include <string>
#include <ctime>
#include "astrofunc.h"
#include "base_planet.h"

namespace astro {

/*
 *  Derived planetary classes
 */

class Sun: public Planet {
    public:
        explicit Sun(std::tm* ct) :
            Planet(sun, ct) {};
        ~Sun() {};

        virtual std::string name() const;
        virtual RectCoords helio_orb_coords() const;
        virtual RectCoords helio_ecl_coords() const;
};

class Earth: public Planet {
    public:
        explicit Earth(std::tm* ct) :
            Planet(earth, ct) {};
        ~Earth() {};

        virtual std::string name() const;

        virtual RectCoords geo_ecl_coords() const;
        virtual RectCoords geo_equ_coords() const;
};

class Mercury: public Planet {
    public:
        explicit Mercury(std::tm* ct) :
            Planet(mercury, ct) {};
        ~Mercury() {};

        virtual std::string name() const;
};

class Venus: public Planet {
    public:
        explicit Venus(std::tm* ct) :
            Planet(venus, ct) {};
        ~Venus() {};

        virtual std::string name() const;
};

class Mars: public Planet {
    public:
        explicit Mars(std::tm* ct) :
            Planet(mars, ct) {};
        ~Mars() {};

        virtual std::string name() const;
};

class Jupiter: public Planet {
    public:
        explicit Jupiter(std::tm* ct) :
            Planet(jupiter, ct) {};
        ~Jupiter() {};

        virtual std::string name() const;
};

class Saturn: public Planet {
    public:
        explicit Saturn(std::tm* ct) :
            Planet(saturn, ct) {};
        ~Saturn() {};

        virtual std::string name() const;
};

class Uranus: public Planet {
    public:
        explicit Uranus(std::tm* ct) :
            Planet(uranus, ct) {};
        ~Uranus() {};

        virtual std::string name() const;
};

class Neptune: public Planet {
    public:
        explicit Neptune(std::tm* ct) :
            Planet(neptune, ct) {};
        ~Neptune() {};

        virtual std::string name() const;
};

class Pluto: public Planet {
    public:
        explicit Pluto(std::tm* ct) :
            Planet(pluto, ct) {};
        ~Pluto() {};

        virtual std::string name() const;
};

}           //  namespace astro

#endif          // PG_ASTRO_PLANETS_H

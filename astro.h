/*
 *  astro.h
 *  =======
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to planet classes.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_ASTRO_H
#define PG_ASTRO_H

#include <string>
#include <ctime>
#include "astrofunc.h"

namespace astro {

struct OrbElem {
    double sma;     // Semi-major axis
    double ecc;     // Eccentricity
    double inc;     // Inclination
    double ml;      // Mean longitude
    double lp;      // Longitude perihelion
    double lan;     // Longitude ascending node
    double man;     // Mean anomaly
    double arp;     // Argument of perihelion
};

enum planets {sun, mercury, venus, earth, mars,
              jupiter, saturn, uranus, neptune, pluto};

class Planet {
    public:
        explicit Planet(const planets pnum, tm * ct) :
            m_number(pnum),
            m_calc_time(get_utc_tm(ct)),
            m_oes(calc_orbital_elements(ct)) {}
        virtual ~Planet() {}
        virtual std::string name() const = 0;
        std::string calc_time() const;

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

    protected:
        const OrbElem m_oes;

    private:
        OrbElem calc_orbital_elements(tm * calc_time) const;

};

class Mars: public Planet {
    public:
        explicit Mars(tm * ct) :
            Planet(mars, ct) {};
        ~Mars() {};

        virtual std::string name() const;
};

class Mercury: public Planet {
    public:
        explicit Mercury(tm * ct) :
            Planet(mercury, ct) {};
        ~Mercury() {};

        virtual std::string name() const;
};

class Venus: public Planet {
    public:
        explicit Venus(tm * ct) :
            Planet(venus, ct) {};
        ~Venus() {};

        virtual std::string name() const;
};

class Jupiter: public Planet {
    public:
        explicit Jupiter(tm * ct) :
            Planet(jupiter, ct) {};
        ~Jupiter() {};

        virtual std::string name() const;
};

class Saturn: public Planet {
    public:
        explicit Saturn(tm * ct) :
            Planet(saturn, ct) {};
        ~Saturn() {};

        virtual std::string name() const;
};

class Uranus: public Planet {
    public:
        explicit Uranus(tm * ct) :
            Planet(uranus, ct) {};
        ~Uranus() {};

        virtual std::string name() const;
};

class Neptune: public Planet {
    public:
        explicit Neptune(tm * ct) :
            Planet(neptune, ct) {};
        ~Neptune() {};

        virtual std::string name() const;
};

class Pluto: public Planet {
    public:
        explicit Pluto(tm * ct) :
            Planet(pluto, ct) {};
        ~Pluto() {};

        virtual std::string name() const;
};

class Earth: public Planet {
    public:
        explicit Earth(tm * ct) :
            Planet(earth, ct) {};
        ~Earth() {};

        virtual std::string name() const;

        virtual RectCoords geo_ecl_coords() const;
        virtual RectCoords geo_equ_coords() const;
};

class Sun: public Planet {
    public:
        explicit Sun(tm * ct) :
            Planet(sun, ct) {};
        ~Sun() {};

        virtual std::string name() const;
        virtual RectCoords helio_orb_coords() const;
        virtual RectCoords helio_ecl_coords() const;
};

void show_planet_positions(std::ostream& out);

}           //  namespace astro

#endif          // PG_ASTRO_H

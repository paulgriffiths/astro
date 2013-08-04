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
            m_calc_time(),
            m_oes(calc_orbital_elements(ct)) {}
        virtual ~Planet() {}
        virtual std::string name() const = 0;

    private:
        const planets m_number;
        const tm m_calc_time;
        const OrbElem m_oes;

        OrbElem calc_orbital_elements(tm * calc_time) const;

};

class Mars: public Planet {
    public:
        explicit Mars(tm * ct) :
            Planet(mars, ct) {};
        ~Mars() {};

        virtual std::string name() const;
};

}           //  namespace astro

#endif          // PG_ASTRO_H

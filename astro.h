// astro.h
// Copyright 2013 Paul Griffiths

#ifndef PG_ASTRO_H
#define PG_ASTRO_H

#include <string>
#include <ctime>

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
private:
    const planets number;
    time_t calc_time;
    OrbElem oes;

    void calc_orbital_elements(const double calc_time, OrbElem& oes);

public:
    Planet(planets pnum, time_t ct);
    virtual ~Planet();
    std::string name(void) const;
};

class Mars: public Planet {
public:
    Mars();
    ~Mars();
};

#endif          // PG_ASTRO_H

/*
 *  astro_common_types.h
 *  ====================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Common types used by the astronomical library
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_ASTRO_COMMON_TYPES_H
#define PG_ASTRO_COMMON_TYPES_H

namespace astro {

struct ZodiacInfo {
    double right_ascension;
    int sign_index;
    const char * sign_name;
    const char * sign_short_name;
    int degrees;
    int minutes;
    int seconds;

    ZodiacInfo() :
        right_ascension(0), sign_index(0),
        sign_name(0), sign_short_name(0),
        degrees(0), minutes(0), seconds(0) {}
};

struct HMS {
    int hours;
    int minutes;
    int seconds;

    HMS() :
        hours(0), minutes(0), seconds(0) {}
};

struct DMS {
    int degrees;
    int minutes;
    int seconds;

    DMS() :
        degrees(0), minutes(0), seconds(0) {}
};

struct SphCoords {
    double right_ascension;
    double declination;
    double distance;

    SphCoords() :
        right_ascension(0), declination(0), distance(0) {}
};

struct RectCoords {
    double x;
    double y;
    double z;

    RectCoords():
        x(0), y(0), z(0) {}
};

struct OrbElem {
    double sma;     // Semi-major axis
    double ecc;     // Eccentricity
    double inc;     // Inclination
    double ml;      // Mean longitude
    double lp;      // Longitude perihelion
    double lan;     // Longitude ascending node
    double man;     // Mean anomaly
    double arp;     // Argument of perihelion

    OrbElem() :
        sma(0), ecc(0), inc(0), ml(0),
        lp(0), lan(0), man(0), arp(0) {}

    OrbElem(const double sma, const double ecc,
            const double inc, const double ml,
            const double lp, const double lan,
            const double man, const double arp) :
        sma(sma), ecc(ecc), inc(inc), ml(ml),
        lp(lp), lan(lan), man(man), arp(arp) {}
};

}           //  namespace astro

#endif          // PG_ASTRO_COMMON_TYPES_H

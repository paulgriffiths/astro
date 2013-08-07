/*
 *  astro.h
 *  =======
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Main interface to astronomical library.
 *
 *  The primary motivation for creating this library was to provide a
 *  way of calculating the positions of all the major Solar System
 *  planets, and the Moon, at any time within the (relatively recent)
 *  past and future.
 *
 *  The calculations for all planets, excluding the moon, are valid the 
 *  time period 1800 through 2050, and are subject to the following
 *  approximate errors:
 *
 *    -- Right Ascension, +/- 50 arcsecs for all planets except Jupiter and
 *       Saturn, +/- 400 arcsecs for Jupiter, +/- 600 arcsecs for Saturn
 *    -- Declination, +/- 8 arcsecs for all planets except Jupiter and
 *       Saturn, +/- 10 arcsecs for Jupiter, +/- 25 arcsecs for Saturn
 *    -- Distance, +/- 25 km for the inner planets, and +/- between 200
 *       and 1,500 km for Jupiter through Pluto
 *
 *  Right ascension and declination calculations for the moon are accurate to
 *  within approximately 4 arcminutes. 
 *
 *  Planetary data and mathematical formulae obtained from NASA's
 *  Jet Propulsion Laboratory at:
 *    http://ssd.jpl.nasa.gov/txt/aprx_pos_planets.pdf
 *
 *  Much useful information and assistance also gained from
 *  Keith Burnett's pages at:
 *    http://www.stargazing.net/kepler/ellipse.html
 *    http://www.stargazing.net/kepler/moon2.html
 *
 *  and from Paul Schlyter's page at:
 *    http://www.stjarnhimlen.se/comp/ppcomp.html
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_ASTRO_H
#define PG_ASTRO_H

#include "utc_time.h"
#include "astro_common_types.h"
#include "astrofunc.h"
#include "planet.h"
#include "major_body.h"
#include "planets.h"
#include "moon.h"
#include "planet_func.h"

#endif          // PG_ASTRO_H

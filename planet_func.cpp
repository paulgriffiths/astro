/*
 *  planet_func.cpp
 *  ===============
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Implementation of planetary functions.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <iostream>
#include <iomanip>
#include "astrofunc.h" 
#include "planets.h"
#include "moon.h"
#include "planet_func.h"
#include "utc_time.h"

using namespace astro;


/*
 *  Standalone function to output all the planetary positions.
 */

void astro::show_planet_positions(std::ostream& out) {

    //  Set up planets

    utctime::UTCTime utc;

    const Sun sun(utc);
    const Mercury mercury(utc);
    const Venus venus(utc);
    const Mars mars(utc);
    const Jupiter jupiter(utc);
    const Saturn saturn(utc);
    const Uranus uranus(utc);
    const Neptune neptune(utc);
    const Pluto pluto(utc);
    const Moon moon(utc);

    const Planet* planets[] = {&sun, &mercury, &venus,
                               &mars, &jupiter, &saturn,
                               &uranus, &neptune, &pluto, &moon};

    //  Set up ios flags, and set precision

    const std::ios_base::fmtflags original_flags = out.flags();
    const std::streamsize origprec = out.precision(7);
    out.setf(out.fixed);
    
    //  Output planetary positions

    out << "Current planetary data for "
        << sun.calc_time_string()
        << std::endl << std::endl;

    out << "PLANET    R.ASCENSION   DECLINATION  DIST (AU)*"
        << " ZODIAC ZODIAC SIGN"
        << std::endl;
    out << "=======   ===========  ============= =========="
        << " ====== ==========="
        << std::endl;

    for ( int i = 0; i < 10; ++i ) {
        out.unsetf(std::ios::right);
        out.setf(std::ios::left, std::ios::adjustfield);
        out << std::setw(8) << planets[i]->name();
        out.unsetf(std::ios::left);
        out.setf(std::ios::right, std::ios::adjustfield);
        out << ": "
            << rasc_string(planets[i]->right_ascension()) << ", "
            << decl_string(planets[i]->declination()) << ", "
            << std::setw(10) << planets[i]->distance() << " "
            << rasc_to_zodiac(planets[i]->right_ascension()) << " "
            << zodiac_sign(planets[i]->right_ascension())
            << std::endl;
    }

    std::cout << std::endl
              << "* Distance for the moon given in Earth radii."
              << std::endl;

    //  Set ios flags and precision back to original values

    out.precision(origprec);
    out.flags(original_flags);
}

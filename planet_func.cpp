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
#include "astro_common_types.h"
#include "astrofunc.h" 
#include "planets.h"
#include "planet_func.h"

using namespace astro;


/*
 *  Standalone function to output all the planetary positions.
 */

void astro::show_planet_positions(std::ostream& out) {

    //  Set up planets

    const Sun sun(0);
    const Mercury mercury(0);
    const Venus venus(0);
    const Mars mars(0);
    const Jupiter jupiter(0);
    const Saturn saturn(0);
    const Uranus uranus(0);
    const Neptune neptune(0);
    const Pluto pluto(0);

    const Planet* planets[] = {&sun, &mercury, &venus,
                               &mars, &jupiter, &saturn,
                               &uranus, &neptune, &pluto};

    //  Set up ios flags, and set precision

    const std::ios_base::fmtflags original_flags = out.flags();
    const std::streamsize origprec = out.precision(7);
    out.setf(out.fixed);
    
    //  Output planetary positions

    out << "Current planetary data for "
        << sun.calc_time()
        << std::endl << std::endl;

    out << "PLANET    R.ASCENSION   DECLINATION  DIST (AU)*"
        << " ZODIAC ZODIAC SIGN"
        << std::endl;
    out << "=======   ===========  ============= =========="
        << " ====== ==========="
        << std::endl;

    for ( int i = 0; i < 9; ++i ) {
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

    //  Set ios flags and precision back to original values

    out.precision(origprec);
    out.flags(original_flags);
}

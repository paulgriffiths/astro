/*
 *  main.cpp
 *  ========
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Basic (very basic) usage of astronomical library.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */

#include <iostream>
#include "astro.h"

int main(void) {
    astro::show_planet_positions(std::cout);
    return 0;
}

#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdio>

#include "astro.h"

int main(void) {

    // Test planet

    tm ct;
    ct.tm_sec = 0;
    ct.tm_min = 21;
    ct.tm_hour = 19;
    ct.tm_mday = 5;
    ct.tm_mon = 4;
    ct.tm_year = 80;

    astro::Mars myplanet(0);
    //astro::Mars myplanet(&ct);    //  Uncomment to set specific calc time

    tm utc_time = astro::get_utc_tm(0);

    std::cout << "UTC time is " << utc_time.tm_hour << ":"
              << utc_time.tm_min << ":"
              << utc_time.tm_sec << " according to get_utc_tm()."
              << std::endl;

    astro::show_planet_positions(std::cout);

    astro::Moon moon(0);

    astro::OrbElem oes = moon.get_orbital_elements();

    return 0;
}

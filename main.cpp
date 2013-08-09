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
#include <ctime>
#include "astro.h"

void show_times();

int main(void) {
    utctime::UTCTime utc(2013, 3, 10, 4, 0, 0);
//    return 0;
    astro::show_planet_positions(std::cout);
    show_times();
    return 0;
}

void show_times() {
    char buffer[100];

    const int year = 2013;
    const int month = 3;
    int day = 10;
    
    for ( int hour = 0; hour < 24; ++hour ) {
        utctime::UTCTime utc(year, month, day, hour, 0, 0);

        time_t ts = utc.timestamp();

        //  Output local time of returned timestamp

        tm* ptm = localtime(&ts);
        if ( ptm == 0 ) {
            std::cerr << "Couldn't get time!" << std::endl;
            return;
        }

        tm local_tm = *ptm;
        strftime(buffer, 100, "%b %d, %y %H:%M loc", &local_tm);
        std::cout << buffer << " : ";

        //  Output GMT time of returned timestamp

        ptm = gmtime(&ts);
        if ( ptm == 0 ) {
            std::cerr << "Couldn't get time!" << std::endl;
            return;
        }

        tm gm_tm = *ptm;
        strftime(buffer, 100, "%b %d, %y %H:%M loc", &gm_tm);
        std::cout << buffer << " : ";

        //  Output what UTCTime class says UTC time is

        std::cout << utc.time_string_inet()
                  << std::endl;
    }
}



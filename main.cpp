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
#include <cstdlib>
#include "astro.h"

void show_times();

int main(void) {
    try {
        utctime::UTCTime utc(1, 12, 31, 6, 6, 6);
    } catch(utctime::UTCTimeException& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    utctime::UTCTime utc;
    std::cout << "Current UTC time is: " << utc.time_string()
              << std::endl << std::endl;

    astro::show_planet_positions(std::cout);
    return 0;
}


/*
 *  Function shows, for a timestamp returned by a UTCTime class,
 *  the results of localtime(), gmtime(), and the UTC time that
 *  the UTCTime class thinks it generated. Used for debugging
 *  purposes.
 */

void show_times() {
    char buffer[100];

    const int year = 2013;
    const int month = 4;
    int day = 7;
    
    //  Set timezone (POSIX extension)

    setenv("TZ", "EST-10EST-9:03:00,M10,1.0,M4.1.0/3", 1);

    //  Shows times for each hour in the selected day

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



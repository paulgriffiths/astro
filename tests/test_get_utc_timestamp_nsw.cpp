/*
 *  test_get_utc_timestamp_nsw.cpp
 *  =============================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Unit tests for test_get_utc_timestamp.cpp using NSW timezone.
 *
 *  Requires POSIX extensions.
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include <cstdlib>
#include "../utc_time.h"

using namespace utctime;


TEST_GROUP(GetUTCTimestampNSWGroup) {
};


/*
 *  Tests get_utc_timestamp() function.
 *
 *  NOTE: April 7, 31, 2013 was chosen for this test as Daylight Saving
 *  Time ended on that day in New South Wales on that
 *  day.
 */

TEST(GetUTCTimestampNSWGroup, GetTimeStamp1Test) {
    const int year = 2013;
    const int month = 4;
    const int day = 7;
    int secs_diff;

    setenv("TZ", "EST-10EST,M10.1.0,M4.1.0/3", 1);

    for ( int hour = 0; hour < 24; ++hour ) {
        for ( int minute = 0; minute < 60; minute += 15 ) {
            time_t check_timestamp = get_utc_timestamp(year, month, day,
                                                       hour, minute, 0);
            CHECK(check_utc_timestamp(check_timestamp, secs_diff,
                                      year, month, day,
                                      hour, minute, 0));
        }
    }
}


/*
 *  Test day before...
 */

TEST(GetUTCTimestampNSWGroup, GetTimeStamp2Test) {
    const int year = 2013;
    const int month = 4;
    const int day = 6;
    int secs_diff;

    setenv("TZ", "EST-10EST,M10.1.0,M4.1.0/3", 1);

    for ( int hour = 0; hour < 24; ++hour ) {
        for ( int minute = 0; minute < 60; minute += 15 ) {
            time_t check_timestamp = get_utc_timestamp(year, month, day,
                                                       hour, minute, 0);
            CHECK(check_utc_timestamp(check_timestamp, secs_diff,
                                      year, month, day,
                                      hour, minute, 0));
        }
    }
}


/*
 *  ...and day after
 */

TEST(GetUTCTimestampNSWGroup, GetTimeStamp3Test) {
    const int year = 2013;
    const int month = 4;
    const int day = 8;
    int secs_diff;

    setenv("TZ", "EST-10EST,M10.1.0,M4.1.0/3", 1);

    for ( int hour = 0; hour < 24; ++hour ) {
        for ( int minute = 0; minute < 60; minute += 15 ) {
            time_t check_timestamp = get_utc_timestamp(year, month, day,
                                                       hour, minute, 0);
            CHECK(check_utc_timestamp(check_timestamp, secs_diff,
                                      year, month, day,
                                      hour, minute, 0));
        }
    }
}


/*
 *  Tests get_utc_timestamp() function.
 *
 *  NOTE: October 6, 2013 was chosen for this test as Daylight Saving
 *  Time began on that day in New South Wales on that
 *  day.
 */

TEST(GetUTCTimestampNSWGroup, GetTimeStamp4Test) {
    const int year = 2013;
    const int month = 10;
    const int day = 6;
    int secs_diff;

    setenv("TZ", "EST-10EST,M10.1.0,M4.1.0/3", 1);

    for ( int hour = 0; hour < 24; ++hour ) {
        for ( int minute = 0; minute < 60; minute += 15 ) {
            time_t check_timestamp = get_utc_timestamp(year, month, day,
                                                       hour, minute, 0);
            CHECK(check_utc_timestamp(check_timestamp, secs_diff,
                                      year, month, day,
                                      hour, minute, 0));
        }
    }
}


/*
 *  Test day before...
 */

TEST(GetUTCTimestampNSWGroup, GetTimeStamp5Test) {
    const int year = 2013;
    const int month = 10;
    const int day = 5;
    int secs_diff;

    setenv("TZ", "EST-10EST,M10.1.0,M4.1.0/3", 1);

    for ( int hour = 0; hour < 24; ++hour ) {
        for ( int minute = 0; minute < 60; minute += 15 ) {
            time_t check_timestamp = get_utc_timestamp(year, month, day,
                                                       hour, minute, 0);
            CHECK(check_utc_timestamp(check_timestamp, secs_diff,
                                      year, month, day,
                                      hour, minute, 0));
        }
    }
}


/*
 *  ...and day after
 */

TEST(GetUTCTimestampNSWGroup, GetTimeStamp6Test) {
    const int year = 2013;
    const int month = 10;
    const int day = 7;
    int secs_diff;

    setenv("TZ", "EST-10EST,M10.1.0,M4.1.0/3", 1);

    for ( int hour = 0; hour < 24; ++hour ) {
        for ( int minute = 0; minute < 60; minute += 15 ) {
            time_t check_timestamp = get_utc_timestamp(year, month, day,
                                                       hour, minute, 0);
            CHECK(check_utc_timestamp(check_timestamp, secs_diff,
                                      year, month, day,
                                      hour, minute, 0));
        }
    }
}


/*
 *  test_get_utc_timestamp.cpp
 *  ==========================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Unit tests for test_get_utc_timestamp.cpp
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include "../utc_time.h"

using namespace utctime;


TEST_GROUP(GetUTCTimestampGroup) {
};


/*
 *  Tests get_utc_timestamp() function.
 *
 *  NOTE: March 10, 2013 was chosen for this test as Daylight Saving
 *  Time started on that day in the eastern United States on that
 *  day. Running this test may not be as meaningful in a location
 *  where DST did not begin on that day.
 */
/*
TEST(GetUTCTimestampGroup, GetTimeStamp1Test) {
    const int year = 2013;
    const int month = 3;
    const int day = 10;

    for ( int hour = 0; hour < 24; ++hour ) {
        for ( int minute = 0; minute < 60; minute += 15 ) {
            time_t check_timestamp = get_utc_timestamp(year, month, day,
                                                       hour, minute, 0);
            CHECK(check_utc_timestamp(check_timestamp,
                                      year, month, day,
                                      hour, minute, 0));
        }
    }
}
*/

/*
 *  Check the day before, too.
 */

TEST(GetUTCTimestampGroup, GetTimeStamp2Test) {
    const int year = 2013;
    const int month = 3;
    const int day = 9;

    for ( int hour = 0; hour < 24; ++hour ) {
        for ( int minute = 0; minute < 60; minute += 15 ) {
            time_t check_timestamp = get_utc_timestamp(year, month, day,
                                                       hour, minute, 0);
            CHECK(check_utc_timestamp(check_timestamp,
                                      year, month, day,
                                      hour, minute, 0));
        }
    }
}


/*
 *  Tests get_utc_timestamp() function.
 *
 *  NOTE: November 3, 2013 was chosen for this test as Daylight Saving
 *  Time ended on that day in the eastern United States on that
 *  day. Running this test may not be as meaningful in a location
 *  where DST did not begin on that day.
 */

TEST(GetUTCTimestampGroup, GetTimeStamp3Test) {
    const int year = 2013;
    const int month = 10;
    const int day = 3;

    for ( int hour = 0; hour < 24; ++hour ) {
        for ( int minute = 0; minute < 60; minute += 15 ) {
            time_t check_timestamp = get_utc_timestamp(year, month, day,
                                                       hour, minute, 0);
            CHECK(check_utc_timestamp(check_timestamp,
                                      year, month, day,
                                      hour, minute, 0));
        }
    }
}


/*
 *  Check the previous day, too.
 */

TEST(GetUTCTimestampGroup, GetTimeStamp4Test) {
    const int year = 2013;
    const int month = 10;
    const int day = 2;

    for ( int hour = 0; hour < 24; ++hour ) {
        for ( int minute = 0; minute < 60; minute += 15 ) {
            time_t check_timestamp = get_utc_timestamp(year, month, day,
                                                       hour, minute, 0);
            CHECK(check_utc_timestamp(check_timestamp,
                                      year, month, day,
                                      hour, minute, 0));
        }
    }
}


/*
 *  Check another random day.
 */

TEST(GetUTCTimestampGroup, GetTimeStamp5Test) {
    const int year = 1980;
    const int month = 4;
    const int day = 5;

    for ( int hour = 0; hour < 24; ++hour ) {
        for ( int minute = 0; minute < 60; minute += 15 ) {
            time_t check_timestamp = get_utc_timestamp(year, month, day,
                                                       hour, minute, 0);
            CHECK(check_utc_timestamp(check_timestamp,
                                      year, month, day,
                                      hour, minute, 0));
        }
    }
}


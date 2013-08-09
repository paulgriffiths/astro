/*
 *  test_tm_adj_day_secs_diff.cpp
 *  =============================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Unit tests for tm_adj_day_secs_diff() function.
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include "../utc_time.h"

using namespace utctime;


TEST_GROUP(AdjDaySecsDiffGroup) {
};


/*
 *  Tests structs tm a regular hour apart, same day
 */

TEST(AdjDaySecsDiffGroup, AdjDaySecsDiff1Test) {
    tm first;
    first.tm_year = 2013;
    first.tm_mon = 7;
    first.tm_mday = 8;
    first.tm_hour = 20;
    first.tm_min = 17;
    first.tm_sec = 10;

    tm second;
    second.tm_year = 2013;
    second.tm_mon = 7;
    second.tm_mday = 8;
    second.tm_hour = 21;
    second.tm_min = 17;
    second.tm_sec = 10;

    const int test_result = tm_adj_day_secs_diff(first, second);
    CHECK_EQUAL(3600, test_result);
}


/*
 *  Tests structs tm a negative hour apart, same day
 */

TEST(AdjDaySecsDiffGroup, AdjDaySecsDiff2Test) {
    tm first;
    first.tm_year = 2013;
    first.tm_mon = 7;
    first.tm_mday = 8;
    first.tm_hour = 20;
    first.tm_min = 17;
    first.tm_sec = 10;

    tm second;
    second.tm_year = 2013;
    second.tm_mon = 7;
    second.tm_mday = 8;
    second.tm_hour = 21;
    second.tm_min = 17;
    second.tm_sec = 10;

    const int test_result = tm_adj_day_secs_diff(second, first);
    CHECK_EQUAL(-3600, test_result);
}


/*
 *  Tests structs tm 3.5 hours apart, across a day
 */

TEST(AdjDaySecsDiffGroup, AdjDaySecsDiff3Test) {
    tm first;
    first.tm_year = 2013;
    first.tm_mon = 7;
    first.tm_mday = 8;
    first.tm_hour = 22;
    first.tm_min = 15;
    first.tm_sec = 15;

    tm second;
    second.tm_year = 2013;
    second.tm_mon = 7;
    second.tm_mday = 9;
    second.tm_hour = 1;
    second.tm_min = 45;
    second.tm_sec = 15;

    const int test_result = tm_adj_day_secs_diff(first, second);
    CHECK_EQUAL(12600, test_result);
}


/*
 *  Tests structs tm negative 3.5 hours apart, across a day
 */

TEST(AdjDaySecsDiffGroup, AdjDaySecsDiff4Test) {
    tm first;
    first.tm_year = 2013;
    first.tm_mon = 7;
    first.tm_mday = 8;
    first.tm_hour = 22;
    first.tm_min = 15;
    first.tm_sec = 15;

    tm second;
    second.tm_year = 2013;
    second.tm_mon = 7;
    second.tm_mday = 9;
    second.tm_hour = 1;
    second.tm_min = 45;
    second.tm_sec = 15;

    const int test_result = tm_adj_day_secs_diff(second, first);
    CHECK_EQUAL(-12600, test_result);
}


/*
 *  Tests structs tm a regular hour apart, same day, with
 *  distorted days
 */

TEST(AdjDaySecsDiffGroup, AdjDaySecsDiff5Test) {
    tm first;
    first.tm_year = 2013;
    first.tm_mon = 2;
    first.tm_mday = 24; 
    first.tm_hour = 20;
    first.tm_min = 17;
    first.tm_sec = 10;

    tm second;
    second.tm_year = 2013;
    second.tm_mon = 7;
    second.tm_mday = 8;
    second.tm_hour = 21;
    second.tm_min = 17;
    second.tm_sec = 10;

    const int test_result = tm_adj_day_secs_diff(first, second);
    CHECK_EQUAL(3600, test_result);
}


/*
 *  Tests structs tm a negative hour apart, same day, with
 *  distorted days.
 */

TEST(AdjDaySecsDiffGroup, AdjDaySecsDiff6Test) {
    tm first;
    first.tm_year = 2013;
    first.tm_mon = 2;
    first.tm_mday = 23;
    first.tm_hour = 20;
    first.tm_min = 17;
    first.tm_sec = 10;

    tm second;
    second.tm_year = 2013;
    second.tm_mon = 7;
    second.tm_mday = 8;
    second.tm_hour = 21;
    second.tm_min = 17;
    second.tm_sec = 10;

    const int test_result = tm_adj_day_secs_diff(second, first);
    CHECK_EQUAL(-3600, test_result);
}


/*
 *  Tests structs tm 3.5 hours apart, across a day, with
 *  distorted days.
 */

TEST(AdjDaySecsDiffGroup, AdjDaySecsDiff7Test) {
    tm first;
    first.tm_year = 2013;
    first.tm_mon = 3;
    first.tm_mday = 27;
    first.tm_hour = 22;
    first.tm_min = 15;
    first.tm_sec = 15;

    tm second;
    second.tm_year = 2013;
    second.tm_mon = 7;
    second.tm_mday = 9;
    second.tm_hour = 1;
    second.tm_min = 45;
    second.tm_sec = 15;

    const int test_result = tm_adj_day_secs_diff(first, second);
    CHECK_EQUAL(12600, test_result);
}


/*
 *  Tests structs tm negative 3.5 hours apart, across a day, with
 *  distorted days.
 */

TEST(AdjDaySecsDiffGroup, AdjDaySecsDiff8Test) {
    tm first;
    first.tm_year = 2013;
    first.tm_mon = 3;
    first.tm_mday = 23;
    first.tm_hour = 22;
    first.tm_min = 15;
    first.tm_sec = 15;

    tm second;
    second.tm_year = 2013;
    second.tm_mon = 7;
    second.tm_mday = 9;
    second.tm_hour = 1;
    second.tm_min = 45;
    second.tm_sec = 15;

    const int test_result = tm_adj_day_secs_diff(second, first);
    CHECK_EQUAL(-12600, test_result);
}


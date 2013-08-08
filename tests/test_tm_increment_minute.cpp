/*
 *  test_tm_increment_minute.cpp
 *  ============================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Unit tests for tm_increment_minute() function.
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include "../utc_time.h"

using namespace utctime;


TEST_GROUP(TmIncrementMinuteGroup) {
};


/*
 *  Increment one minute in middle of day.
 */

TEST(TmIncrementMinuteGroup, Inc1Test) {
    tm test_tm;
    test_tm.tm_year = 2012;
    test_tm.tm_mon = 2;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 11;
    test_tm.tm_min = 23;
    test_tm.tm_sec = 13;

    tm_increment_minute(&test_tm);

    CHECK_EQUAL(2012, test_tm.tm_year);
    CHECK_EQUAL(2, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(11, test_tm.tm_hour);
    CHECK_EQUAL(24, test_tm.tm_min);
    CHECK_EQUAL(13, test_tm.tm_sec);
}


/*
 *  Increment one minute in middle of day at end of hour
 */

TEST(TmIncrementMinuteGroup, Inc2Test) {
    tm test_tm;
    test_tm.tm_year = 2012;
    test_tm.tm_mon = 2;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 11;
    test_tm.tm_min = 59;
    test_tm.tm_sec = 13;

    tm_increment_minute(&test_tm);

    CHECK_EQUAL(2012, test_tm.tm_year);
    CHECK_EQUAL(2, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(12, test_tm.tm_hour);
    CHECK_EQUAL(0, test_tm.tm_min);
    CHECK_EQUAL(13, test_tm.tm_sec);
}


/*
 *  Increment several minutes crossing an hour.
 */

TEST(TmIncrementMinuteGroup, Inc3Test) {
    tm test_tm;
    test_tm.tm_year = 2012;
    test_tm.tm_mon = 2;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 11;
    test_tm.tm_min = 47;
    test_tm.tm_sec = 13;

    tm_increment_minute(&test_tm, 32);

    CHECK_EQUAL(2012, test_tm.tm_year);
    CHECK_EQUAL(2, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(12, test_tm.tm_hour);
    CHECK_EQUAL(19, test_tm.tm_min);
    CHECK_EQUAL(13, test_tm.tm_sec);
}


/*
 *  Increment a lot of minutes.
 */

TEST(TmIncrementMinuteGroup, Inc4Test) {
    tm test_tm;
    test_tm.tm_year = 2012;
    test_tm.tm_mon = 2;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 11;
    test_tm.tm_min = 17;
    test_tm.tm_sec = 13;

    tm_increment_minute(&test_tm, 259);

    CHECK_EQUAL(2012, test_tm.tm_year);
    CHECK_EQUAL(2, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(15, test_tm.tm_hour);
    CHECK_EQUAL(36, test_tm.tm_min);
    CHECK_EQUAL(13, test_tm.tm_sec);
}


/*
 *  Increment negative minutes.
 */

TEST(TmIncrementMinuteGroup, Inc5Test) {
    tm test_tm;
    test_tm.tm_year = 2012;
    test_tm.tm_mon = 2;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 11;
    test_tm.tm_min = 17;
    test_tm.tm_sec = 13;

    tm_increment_minute(&test_tm, -22);

    CHECK_EQUAL(2012, test_tm.tm_year);
    CHECK_EQUAL(2, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(10, test_tm.tm_hour);
    CHECK_EQUAL(55, test_tm.tm_min);
    CHECK_EQUAL(13, test_tm.tm_sec);
}

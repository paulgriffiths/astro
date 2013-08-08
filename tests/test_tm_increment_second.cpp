/*
 *  test_tm_increment_second.cpp
 *  ============================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Unit tests for tm_increment_second() function.
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include "../utc_time.h"

using namespace utctime;


TEST_GROUP(TmIncrementSecondGroup) {
};


/*
 *  Increment one second in middle of day.
 */

TEST(TmIncrementSecondGroup, Inc1Test) {
    tm test_tm;
    test_tm.tm_year = 2012;
    test_tm.tm_mon = 2;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 11;
    test_tm.tm_min = 23;
    test_tm.tm_sec = 13;

    tm_increment_second(&test_tm);

    CHECK_EQUAL(2012, test_tm.tm_year);
    CHECK_EQUAL(2, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(11, test_tm.tm_hour);
    CHECK_EQUAL(23, test_tm.tm_min);
    CHECK_EQUAL(14, test_tm.tm_sec);
}


/*
 *  Increment one second in middle of day at end of minute
 */

TEST(TmIncrementSecondGroup, Inc2Test) {
    tm test_tm;
    test_tm.tm_year = 2012;
    test_tm.tm_mon = 2;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 11;
    test_tm.tm_min = 33;
    test_tm.tm_sec = 59;

    tm_increment_second(&test_tm);

    CHECK_EQUAL(2012, test_tm.tm_year);
    CHECK_EQUAL(2, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(11, test_tm.tm_hour);
    CHECK_EQUAL(34, test_tm.tm_min);
    CHECK_EQUAL(0, test_tm.tm_sec);
}


/*
 *  Increment several seconds crossing an hour.
 */

TEST(TmIncrementSecondGroup, Inc3Test) {
    tm test_tm;
    test_tm.tm_year = 2012;
    test_tm.tm_mon = 2;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 11;
    test_tm.tm_min = 47;
    test_tm.tm_sec = 48;

    tm_increment_second(&test_tm, 32);

    CHECK_EQUAL(2012, test_tm.tm_year);
    CHECK_EQUAL(2, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(11, test_tm.tm_hour);
    CHECK_EQUAL(48, test_tm.tm_min);
    CHECK_EQUAL(20, test_tm.tm_sec);
}


/*
 *  Increment a lot of seconds.
 */

TEST(TmIncrementSecondGroup, Inc4Test) {
    tm test_tm;
    test_tm.tm_year = 2012;
    test_tm.tm_mon = 2;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 11;
    test_tm.tm_min = 17;
    test_tm.tm_sec = 13;

    tm_increment_second(&test_tm, 521);

    CHECK_EQUAL(2012, test_tm.tm_year);
    CHECK_EQUAL(2, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(11, test_tm.tm_hour);
    CHECK_EQUAL(25, test_tm.tm_min);
    CHECK_EQUAL(54, test_tm.tm_sec);
}


/*
 *  Increment negative seconds.
 */

TEST(TmIncrementSecondGroup, Inc5Test) {
    tm test_tm;
    test_tm.tm_year = 2012;
    test_tm.tm_mon = 2;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 11;
    test_tm.tm_min = 17;
    test_tm.tm_sec = 13;

    tm_increment_second(&test_tm, -22);

    CHECK_EQUAL(2012, test_tm.tm_year);
    CHECK_EQUAL(2, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(11, test_tm.tm_hour);
    CHECK_EQUAL(16, test_tm.tm_min);
    CHECK_EQUAL(51, test_tm.tm_sec);
}

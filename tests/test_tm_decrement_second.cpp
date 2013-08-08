/*
 *  test_tm_decrement_second.cpp
 *  ============================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Unit tests for tm_decrement_second() function.
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include "../utc_time.h"

using namespace utctime;


TEST_GROUP(TmDecrementSecondGroup) {
};


/*
 *  Decrement one second in middle of day.
 */

TEST(TmDecrementSecondGroup, Dec1Test) {
    tm test_tm;
    test_tm.tm_year = 2012;
    test_tm.tm_mon = 2;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 11;
    test_tm.tm_min = 23;
    test_tm.tm_sec = 13;

    tm_decrement_second(&test_tm);

    CHECK_EQUAL(2012, test_tm.tm_year);
    CHECK_EQUAL(2, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(11, test_tm.tm_hour);
    CHECK_EQUAL(23, test_tm.tm_min);
    CHECK_EQUAL(12, test_tm.tm_sec);
}


/*
 *  Decrement one second in middle of day at start of minute
 */

TEST(TmDecrementSecondGroup, Dec2Test) {
    tm test_tm;
    test_tm.tm_year = 2012;
    test_tm.tm_mon = 2;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 11;
    test_tm.tm_min = 33;
    test_tm.tm_sec = 0;

    tm_decrement_second(&test_tm);

    CHECK_EQUAL(2012, test_tm.tm_year);
    CHECK_EQUAL(2, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(11, test_tm.tm_hour);
    CHECK_EQUAL(32, test_tm.tm_min);
    CHECK_EQUAL(59, test_tm.tm_sec);
}


/*
 *  Decrement several seconds crossing an hour.
 */

TEST(TmDecrementSecondGroup, Dec3Test) {
    tm test_tm;
    test_tm.tm_year = 2012;
    test_tm.tm_mon = 2;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 11;
    test_tm.tm_min = 47;
    test_tm.tm_sec = 15;

    tm_decrement_second(&test_tm, 32);

    CHECK_EQUAL(2012, test_tm.tm_year);
    CHECK_EQUAL(2, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(11, test_tm.tm_hour);
    CHECK_EQUAL(46, test_tm.tm_min);
    CHECK_EQUAL(43, test_tm.tm_sec);
}


/*
 *  Decrement a lot of seconds.
 */

TEST(TmDecrementSecondGroup, Dec4Test) {
    tm test_tm;
    test_tm.tm_year = 2012;
    test_tm.tm_mon = 2;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 11;
    test_tm.tm_min = 17;
    test_tm.tm_sec = 13;

    tm_decrement_second(&test_tm, 521);

    CHECK_EQUAL(2012, test_tm.tm_year);
    CHECK_EQUAL(2, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(11, test_tm.tm_hour);
    CHECK_EQUAL(8, test_tm.tm_min);
    CHECK_EQUAL(32, test_tm.tm_sec);
}


/*
 *  Decrement negative seconds.
 */

TEST(TmDecrementSecondGroup, Dec5Test) {
    tm test_tm;
    test_tm.tm_year = 2012;
    test_tm.tm_mon = 2;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 11;
    test_tm.tm_min = 17;
    test_tm.tm_sec = 13;

    tm_decrement_second(&test_tm, -22);

    CHECK_EQUAL(2012, test_tm.tm_year);
    CHECK_EQUAL(2, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(11, test_tm.tm_hour);
    CHECK_EQUAL(17, test_tm.tm_min);
    CHECK_EQUAL(35, test_tm.tm_sec);
}

/*
 *  test_tm_decrement_minute.cpp
 *  ============================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Unit tests for tm_decrement_minute() function.
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include "../utc_time.h"

using namespace utctime;


TEST_GROUP(TmDecrementMinuteGroup) {
};


/*
 *  Decrement one minute in middle of day.
 */

TEST(TmDecrementMinuteGroup, Dec1Test) {
    tm test_tm;
    test_tm.tm_year = 2012;
    test_tm.tm_mon = 2;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 11;
    test_tm.tm_min = 23;
    test_tm.tm_sec = 13;

    tm_decrement_minute(&test_tm);

    CHECK_EQUAL(2012, test_tm.tm_year);
    CHECK_EQUAL(2, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(11, test_tm.tm_hour);
    CHECK_EQUAL(22, test_tm.tm_min);
    CHECK_EQUAL(13, test_tm.tm_sec);
}


/*
 *  Decrement one minute in middle of day at start of hour
 */

TEST(TmDecrementMinuteGroup, Dec2Test) {
    tm test_tm;
    test_tm.tm_year = 2012;
    test_tm.tm_mon = 2;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 11;
    test_tm.tm_min = 0;
    test_tm.tm_sec = 13;

    tm_decrement_minute(&test_tm);

    CHECK_EQUAL(2012, test_tm.tm_year);
    CHECK_EQUAL(2, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(10, test_tm.tm_hour);
    CHECK_EQUAL(59, test_tm.tm_min);
    CHECK_EQUAL(13, test_tm.tm_sec);
}


/*
 *  Decrement several minutes crossing an hour.
 */

TEST(TmDecrementMinuteGroup, Dec3Test) {
    tm test_tm;
    test_tm.tm_year = 2012;
    test_tm.tm_mon = 2;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 11;
    test_tm.tm_min = 17;
    test_tm.tm_sec = 13;

    tm_decrement_minute(&test_tm, 32);

    CHECK_EQUAL(2012, test_tm.tm_year);
    CHECK_EQUAL(2, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(10, test_tm.tm_hour);
    CHECK_EQUAL(45, test_tm.tm_min);
    CHECK_EQUAL(13, test_tm.tm_sec);
}


/*
 *  Decrement a lot of minutes.
 */

TEST(TmDecrementMinuteGroup, Dec4Test) {
    tm test_tm;
    test_tm.tm_year = 2012;
    test_tm.tm_mon = 2;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 11;
    test_tm.tm_min = 17;
    test_tm.tm_sec = 13;

    tm_decrement_minute(&test_tm, 259);

    CHECK_EQUAL(2012, test_tm.tm_year);
    CHECK_EQUAL(2, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(6, test_tm.tm_hour);
    CHECK_EQUAL(58, test_tm.tm_min);
    CHECK_EQUAL(13, test_tm.tm_sec);
}


/*
 *  Decrement negative minutes.
 */

TEST(TmDecrementMinuteGroup, Dec5Test) {
    tm test_tm;
    test_tm.tm_year = 2012;
    test_tm.tm_mon = 2;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 11;
    test_tm.tm_min = 17;
    test_tm.tm_sec = 13;

    tm_decrement_minute(&test_tm, -22);

    CHECK_EQUAL(2012, test_tm.tm_year);
    CHECK_EQUAL(2, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(11, test_tm.tm_hour);
    CHECK_EQUAL(39, test_tm.tm_min);
    CHECK_EQUAL(13, test_tm.tm_sec);
}

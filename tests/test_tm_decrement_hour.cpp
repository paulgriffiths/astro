/*
 *  test_tm_decrement_hour.cpp
 *  ==========================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Unit tests for tm_decrement_hour() function.
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include "../utc_time.h"

using namespace utctime;


TEST_GROUP(TmDecrementHourGroup) {
};


/*
 *  Tests function for March 1, 2012, 00:00. Should go to February 29,
 *  2012, 23:00, since 2012 was a leap year.
 */

TEST(TmDecrementHourGroup, Dec1Test) {
    tm test_tm;
    test_tm.tm_year = 2012;
    test_tm.tm_mon = 2;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 0;
    test_tm.tm_min = 0;
    test_tm.tm_sec = 0;

    tm_decrement_hour(&test_tm);

    CHECK_EQUAL(2012, test_tm.tm_year);
    CHECK_EQUAL(1, test_tm.tm_mon);
    CHECK_EQUAL(29, test_tm.tm_mday);
    CHECK_EQUAL(23, test_tm.tm_hour);
    CHECK_EQUAL(0, test_tm.tm_min);
    CHECK_EQUAL(0, test_tm.tm_sec);
}

/*
 *  Tests function for March 1, 2000, 00:00. Should go to February 29,
 *  2012, 23:00, since 2012 was a leap year.
 */

TEST(TmDecrementHourGroup, Dec2Test) {
    tm test_tm;
    test_tm.tm_year = 2000;
    test_tm.tm_mon = 2;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 0;
    test_tm.tm_min = 0;
    test_tm.tm_sec = 0;

    tm_decrement_hour(&test_tm);

    CHECK_EQUAL(2000, test_tm.tm_year);
    CHECK_EQUAL(1, test_tm.tm_mon);
    CHECK_EQUAL(29, test_tm.tm_mday);
    CHECK_EQUAL(23, test_tm.tm_hour);
    CHECK_EQUAL(0, test_tm.tm_min);
    CHECK_EQUAL(0, test_tm.tm_sec);
}

/*
 *  Tests function for March 1, 1900, 00:00. Should go to February 28,
 *  2012, 23:00, since 2012 was *not* a leap year.
 */

TEST(TmDecrementHourGroup, Dec3Test) {
    tm test_tm;
    test_tm.tm_year = 1900;
    test_tm.tm_mon = 2;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 0;
    test_tm.tm_min = 0;
    test_tm.tm_sec = 0;

    tm_decrement_hour(&test_tm);

    CHECK_EQUAL(1900, test_tm.tm_year);
    CHECK_EQUAL(1, test_tm.tm_mon);
    CHECK_EQUAL(28, test_tm.tm_mday);
    CHECK_EQUAL(23, test_tm.tm_hour);
    CHECK_EQUAL(0, test_tm.tm_min);
    CHECK_EQUAL(0, test_tm.tm_sec);
}

/*
 *  Tests function for March 1, 2013, 00:00. Should go to February 28,
 *  2012, 23:00, since 2013 was *not* a leap year.
 */

TEST(TmDecrementHourGroup, Dec4Test) {
    tm test_tm;
    test_tm.tm_year = 2013;
    test_tm.tm_mon = 2;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 0;
    test_tm.tm_min = 0;
    test_tm.tm_sec = 0;

    tm_decrement_hour(&test_tm);

    CHECK_EQUAL(2013, test_tm.tm_year);
    CHECK_EQUAL(1, test_tm.tm_mon);
    CHECK_EQUAL(28, test_tm.tm_mday);
    CHECK_EQUAL(23, test_tm.tm_hour);
    CHECK_EQUAL(0, test_tm.tm_min);
    CHECK_EQUAL(0, test_tm.tm_sec);
}

/*
 *  Tests function for January 1, 2013, 00:00. Should go to December 31,
 *  2012, 23:00.
 */

TEST(TmDecrementHourGroup, Dec5Test) {
    tm test_tm;
    test_tm.tm_year = 2013;
    test_tm.tm_mon = 0;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 0;
    test_tm.tm_min = 0;
    test_tm.tm_sec = 0;

    tm_decrement_hour(&test_tm);

    CHECK_EQUAL(2012, test_tm.tm_year);
    CHECK_EQUAL(11, test_tm.tm_mon);
    CHECK_EQUAL(31, test_tm.tm_mday);
    CHECK_EQUAL(23, test_tm.tm_hour);
    CHECK_EQUAL(0, test_tm.tm_min);
    CHECK_EQUAL(0, test_tm.tm_sec);
}

/*
 *  Tests function for February 1, 2013, 00:00. Should go to January 31,
 *  2013, 23:00.
 */

TEST(TmDecrementHourGroup, Dec6Test) {
    tm test_tm;
    test_tm.tm_year = 2013;
    test_tm.tm_mon = 1;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 0;
    test_tm.tm_min = 0;
    test_tm.tm_sec = 0;

    tm_decrement_hour(&test_tm);

    CHECK_EQUAL(2013, test_tm.tm_year);
    CHECK_EQUAL(0, test_tm.tm_mon);
    CHECK_EQUAL(31, test_tm.tm_mday);
    CHECK_EQUAL(23, test_tm.tm_hour);
    CHECK_EQUAL(0, test_tm.tm_min);
    CHECK_EQUAL(0, test_tm.tm_sec);
}

/*
 *  Tests function for April 1, 2013, 00:00. Should go to March 31,
 *  2013, 23:00.
 */

TEST(TmDecrementHourGroup, Dec7Test) {
    tm test_tm;
    test_tm.tm_year = 2013;
    test_tm.tm_mon = 3;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 0;
    test_tm.tm_min = 0;
    test_tm.tm_sec = 0;

    tm_decrement_hour(&test_tm);

    CHECK_EQUAL(2013, test_tm.tm_year);
    CHECK_EQUAL(2, test_tm.tm_mon);
    CHECK_EQUAL(31, test_tm.tm_mday);
    CHECK_EQUAL(23, test_tm.tm_hour);
    CHECK_EQUAL(0, test_tm.tm_min);
    CHECK_EQUAL(0, test_tm.tm_sec);
}

/*
 *  Tests function for May 1, 2013, 00:00. Should go to April 30,
 *  2013, 23:00.
 */

TEST(TmDecrementHourGroup, Dec8Test) {
    tm test_tm;
    test_tm.tm_year = 2013;
    test_tm.tm_mon = 4;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 0;
    test_tm.tm_min = 0;
    test_tm.tm_sec = 0;

    tm_decrement_hour(&test_tm);

    CHECK_EQUAL(2013, test_tm.tm_year);
    CHECK_EQUAL(3, test_tm.tm_mon);
    CHECK_EQUAL(30, test_tm.tm_mday);
    CHECK_EQUAL(23, test_tm.tm_hour);
    CHECK_EQUAL(0, test_tm.tm_min);
    CHECK_EQUAL(0, test_tm.tm_sec);
}

/*
 *  Tests function for June 1, 2013, 00:00. Should go to May 31,
 *  2013, 23:00.
 */

TEST(TmDecrementHourGroup, Dec9Test) {
    tm test_tm;
    test_tm.tm_year = 2013;
    test_tm.tm_mon = 5;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 0;
    test_tm.tm_min = 0;
    test_tm.tm_sec = 0;

    tm_decrement_hour(&test_tm);

    CHECK_EQUAL(2013, test_tm.tm_year);
    CHECK_EQUAL(4, test_tm.tm_mon);
    CHECK_EQUAL(31, test_tm.tm_mday);
    CHECK_EQUAL(23, test_tm.tm_hour);
    CHECK_EQUAL(0, test_tm.tm_min);
    CHECK_EQUAL(0, test_tm.tm_sec);
}

/*
 *  Tests function for July 1, 2013, 00:00. Should go to June 30,
 *  2013, 23:00.
 */

TEST(TmDecrementHourGroup, Dec10Test) {
    tm test_tm;
    test_tm.tm_year = 2013;
    test_tm.tm_mon = 6;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 0;
    test_tm.tm_min = 0;
    test_tm.tm_sec = 0;

    tm_decrement_hour(&test_tm);

    CHECK_EQUAL(2013, test_tm.tm_year);
    CHECK_EQUAL(5, test_tm.tm_mon);
    CHECK_EQUAL(30, test_tm.tm_mday);
    CHECK_EQUAL(23, test_tm.tm_hour);
    CHECK_EQUAL(0, test_tm.tm_min);
    CHECK_EQUAL(0, test_tm.tm_sec);
}

/*
 *  Tests function for August 1, 2013, 00:00. Should go to July 31,
 *  2013, 23:00.
 */

TEST(TmDecrementHourGroup, Dec11Test) {
    tm test_tm;
    test_tm.tm_year = 2013;
    test_tm.tm_mon = 7;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 0;
    test_tm.tm_min = 0;
    test_tm.tm_sec = 0;

    tm_decrement_hour(&test_tm);

    CHECK_EQUAL(2013, test_tm.tm_year);
    CHECK_EQUAL(6, test_tm.tm_mon);
    CHECK_EQUAL(31, test_tm.tm_mday);
    CHECK_EQUAL(23, test_tm.tm_hour);
    CHECK_EQUAL(0, test_tm.tm_min);
    CHECK_EQUAL(0, test_tm.tm_sec);
}

/*
 *  Tests function for September 1, 2013, 00:00. Should go to August 31,
 *  2013, 23:00.
 */

TEST(TmDecrementHourGroup, Dec12Test) {
    tm test_tm;
    test_tm.tm_year = 2013;
    test_tm.tm_mon = 8;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 0;
    test_tm.tm_min = 0;
    test_tm.tm_sec = 0;

    tm_decrement_hour(&test_tm);

    CHECK_EQUAL(2013, test_tm.tm_year);
    CHECK_EQUAL(7, test_tm.tm_mon);
    CHECK_EQUAL(31, test_tm.tm_mday);
    CHECK_EQUAL(23, test_tm.tm_hour);
    CHECK_EQUAL(0, test_tm.tm_min);
    CHECK_EQUAL(0, test_tm.tm_sec);
}

/*
 *  Tests function for October 1, 2013, 00:00. Should go to September 30,
 *  2013, 23:00.
 */

TEST(TmDecrementHourGroup, Dec13Test) {
    tm test_tm;
    test_tm.tm_year = 2013;
    test_tm.tm_mon = 9;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 0;
    test_tm.tm_min = 0;
    test_tm.tm_sec = 0;

    tm_decrement_hour(&test_tm);

    CHECK_EQUAL(2013, test_tm.tm_year);
    CHECK_EQUAL(8, test_tm.tm_mon);
    CHECK_EQUAL(30, test_tm.tm_mday);
    CHECK_EQUAL(23, test_tm.tm_hour);
    CHECK_EQUAL(0, test_tm.tm_min);
    CHECK_EQUAL(0, test_tm.tm_sec);
}


/*
 *  Tests function for November 1, 2013, 00:00. Should go to October 31,
 *  2013, 23:00.
 */

TEST(TmDecrementHourGroup, Dec14Test) {
    tm test_tm;
    test_tm.tm_year = 2013;
    test_tm.tm_mon = 10;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 0;
    test_tm.tm_min = 0;
    test_tm.tm_sec = 0;

    tm_decrement_hour(&test_tm);

    CHECK_EQUAL(2013, test_tm.tm_year);
    CHECK_EQUAL(9, test_tm.tm_mon);
    CHECK_EQUAL(31, test_tm.tm_mday);
    CHECK_EQUAL(23, test_tm.tm_hour);
    CHECK_EQUAL(0, test_tm.tm_min);
    CHECK_EQUAL(0, test_tm.tm_sec);
}


/*
 *  Tests function for December 1, 2013, 00:00. Should go to November 30,
 *  2013, 23:00.
 */

TEST(TmDecrementHourGroup, Dec15Test) {
    tm test_tm;
    test_tm.tm_year = 2013;
    test_tm.tm_mon = 11;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 0;
    test_tm.tm_min = 0;
    test_tm.tm_sec = 0;

    tm_decrement_hour(&test_tm);

    CHECK_EQUAL(2013, test_tm.tm_year);
    CHECK_EQUAL(10, test_tm.tm_mon);
    CHECK_EQUAL(30, test_tm.tm_mday);
    CHECK_EQUAL(23, test_tm.tm_hour);
    CHECK_EQUAL(0, test_tm.tm_min);
    CHECK_EQUAL(0, test_tm.tm_sec);
}


/*
 *  Tests function for December 1, 2013, 06:00. Should go to December 1,
 *  2013, 06:00.
 */

TEST(TmDecrementHourGroup, Dec16Test) {
    tm test_tm;
    test_tm.tm_year = 2013;
    test_tm.tm_mon = 11;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 6;
    test_tm.tm_min = 0;
    test_tm.tm_sec = 0;

    tm_decrement_hour(&test_tm);

    CHECK_EQUAL(2013, test_tm.tm_year);
    CHECK_EQUAL(11, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(5, test_tm.tm_hour);
    CHECK_EQUAL(0, test_tm.tm_min);
    CHECK_EQUAL(0, test_tm.tm_sec);
}


/*
 *  Tests function for December 3, 2013, 00:00. Should go to December 2,
 *  2013, 23:00.
 */

TEST(TmDecrementHourGroup, Dec17Test) {
    tm test_tm;
    test_tm.tm_year = 2013;
    test_tm.tm_mon = 11;
    test_tm.tm_mday = 2;
    test_tm.tm_hour = 0;
    test_tm.tm_min = 0;
    test_tm.tm_sec = 0;

    tm_decrement_hour(&test_tm);

    CHECK_EQUAL(2013, test_tm.tm_year);
    CHECK_EQUAL(11, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(23, test_tm.tm_hour);
    CHECK_EQUAL(0, test_tm.tm_min);
    CHECK_EQUAL(0, test_tm.tm_sec);
}


/*
 *  Tests decrement by 2 hours.
 */

TEST(TmDecrementHourGroup, Dec18Test) {
    tm test_tm;
    test_tm.tm_year = 2013;
    test_tm.tm_mon = 11;
    test_tm.tm_mday = 2;
    test_tm.tm_hour = 16;
    test_tm.tm_min = 23;
    test_tm.tm_sec = 13;

    tm_decrement_hour(&test_tm, 2);

    CHECK_EQUAL(2013, test_tm.tm_year);
    CHECK_EQUAL(11, test_tm.tm_mon);
    CHECK_EQUAL(2, test_tm.tm_mday);
    CHECK_EQUAL(14, test_tm.tm_hour);
    CHECK_EQUAL(23, test_tm.tm_min);
    CHECK_EQUAL(13, test_tm.tm_sec);
}


/*
 *  Tests decrement by -2 hours.
 */

TEST(TmDecrementHourGroup, Dec19Test) {
    tm test_tm;
    test_tm.tm_year = 2013;
    test_tm.tm_mon = 11;
    test_tm.tm_mday = 2;
    test_tm.tm_hour = 16;
    test_tm.tm_min = 23;
    test_tm.tm_sec = 13;

    tm_decrement_hour(&test_tm, -2);

    CHECK_EQUAL(2013, test_tm.tm_year);
    CHECK_EQUAL(11, test_tm.tm_mon);
    CHECK_EQUAL(2, test_tm.tm_mday);
    CHECK_EQUAL(18, test_tm.tm_hour);
    CHECK_EQUAL(23, test_tm.tm_min);
    CHECK_EQUAL(13, test_tm.tm_sec);
}


/*
 *  Tests decrement by 24 hours.
 */

TEST(TmDecrementHourGroup, Dec20Test) {
    tm test_tm;
    test_tm.tm_year = 2013;
    test_tm.tm_mon = 11;
    test_tm.tm_mday = 2;
    test_tm.tm_hour = 16;
    test_tm.tm_min = 23;
    test_tm.tm_sec = 13;

    tm_decrement_hour(&test_tm, 24);

    CHECK_EQUAL(2013, test_tm.tm_year);
    CHECK_EQUAL(11, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(16, test_tm.tm_hour);
    CHECK_EQUAL(23, test_tm.tm_min);
    CHECK_EQUAL(13, test_tm.tm_sec);
}


/*
 *  Tests decrement by 197 hours.
 */

TEST(TmDecrementHourGroup, Dec21Test) {
    tm test_tm;
    test_tm.tm_year = 2013;
    test_tm.tm_mon = 11;
    test_tm.tm_mday = 12;
    test_tm.tm_hour = 16;
    test_tm.tm_min = 23;
    test_tm.tm_sec = 13;

    tm_decrement_hour(&test_tm, 197);

    CHECK_EQUAL(2013, test_tm.tm_year);
    CHECK_EQUAL(11, test_tm.tm_mon);
    CHECK_EQUAL(4, test_tm.tm_mday);
    CHECK_EQUAL(11, test_tm.tm_hour);
    CHECK_EQUAL(23, test_tm.tm_min);
    CHECK_EQUAL(13, test_tm.tm_sec);
}


/*
 *  test_tm_increment_hour.cpp
 *  ==========================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Unit tests for tm_increment_hour() function.
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include "../utc_time.h"

using namespace utctime;


TEST_GROUP(TmIncrementHourGroup) {
};


/*
 *  Tests function for January 31, 2013, 23:00, should go to Febuary 1,
 *  2013, 00:00.
 */

TEST(TmIncrementHourGroup, Inc1Test) {
    tm test_tm;
    test_tm.tm_year = 2013;
    test_tm.tm_mon = 0;
    test_tm.tm_mday = 31;
    test_tm.tm_hour = 23;
    test_tm.tm_min = 0;
    test_tm.tm_sec = 0;

    tm_increment_hour(&test_tm);

    CHECK_EQUAL(2013, test_tm.tm_year);
    CHECK_EQUAL(1, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(0, test_tm.tm_hour);
    CHECK_EQUAL(0, test_tm.tm_min);
    CHECK_EQUAL(0, test_tm.tm_sec);
}

/*
 *  Tests function for February 28, 2013, 23:00, should go to March 1,
 *  2013, 00:00, since 2013 was not a leap year.
 */

TEST(TmIncrementHourGroup, Inc2Test) {
    tm test_tm;
    test_tm.tm_year = 2013;
    test_tm.tm_mon = 1;
    test_tm.tm_mday = 28;
    test_tm.tm_hour = 23;
    test_tm.tm_min = 0;
    test_tm.tm_sec = 0;

    tm_increment_hour(&test_tm);

    CHECK_EQUAL(2013, test_tm.tm_year);
    CHECK_EQUAL(2, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(0, test_tm.tm_hour);
    CHECK_EQUAL(0, test_tm.tm_min);
    CHECK_EQUAL(0, test_tm.tm_sec);
}

/*
 *  Tests function for February 28, 2012, 23:00, should go to February 29,
 *  2012, 00:00, since 2012 was a leap year.
 */

TEST(TmIncrementHourGroup, Inc3Test) {
    tm test_tm;
    test_tm.tm_year = 2012;
    test_tm.tm_mon = 1;
    test_tm.tm_mday = 28;
    test_tm.tm_hour = 23;
    test_tm.tm_min = 0;
    test_tm.tm_sec = 0;

    tm_increment_hour(&test_tm);

    CHECK_EQUAL(2012, test_tm.tm_year);
    CHECK_EQUAL(1, test_tm.tm_mon);
    CHECK_EQUAL(29, test_tm.tm_mday);
    CHECK_EQUAL(0, test_tm.tm_hour);
    CHECK_EQUAL(0, test_tm.tm_min);
    CHECK_EQUAL(0, test_tm.tm_sec);
}

/*
 *  Tests function for February 28, 1900, 23:00. Should go to February 29,
 *  1900, 00:00, since 1900 was *not* a leap year.
 */

TEST(TmIncrementHourGroup, Inc4Test) {
    tm test_tm;
    test_tm.tm_year = 1900;
    test_tm.tm_mon = 1;
    test_tm.tm_mday = 28;
    test_tm.tm_hour = 23;
    test_tm.tm_min = 0;
    test_tm.tm_sec = 0;

    tm_increment_hour(&test_tm);

    CHECK_EQUAL(1900, test_tm.tm_year);
    CHECK_EQUAL(2, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(0, test_tm.tm_hour);
    CHECK_EQUAL(0, test_tm.tm_min);
    CHECK_EQUAL(0, test_tm.tm_sec);
}

/*
 *  Tests function for February 28, 1600, 23:00. Should go to February 29,
 *  1600, 00:00, since 1600 *was* a leap year.
 */

TEST(TmIncrementHourGroup, Inc5Test) {
    tm test_tm;
    test_tm.tm_year = 1600;
    test_tm.tm_mon = 1;
    test_tm.tm_mday = 28;
    test_tm.tm_hour = 23;
    test_tm.tm_min = 0;
    test_tm.tm_sec = 0;

    tm_increment_hour(&test_tm);

    CHECK_EQUAL(1600, test_tm.tm_year);
    CHECK_EQUAL(1, test_tm.tm_mon);
    CHECK_EQUAL(29, test_tm.tm_mday);
    CHECK_EQUAL(0, test_tm.tm_hour);
    CHECK_EQUAL(0, test_tm.tm_min);
    CHECK_EQUAL(0, test_tm.tm_sec);
}

/*
 *  Tests function for March 31, 2013, 23:00. Should go to April 1,
 *  2013, 00:00.
 */

TEST(TmIncrementHourGroup, Inc6Test) {
    tm test_tm;
    test_tm.tm_year = 2013;
    test_tm.tm_mon = 2;
    test_tm.tm_mday = 31;
    test_tm.tm_hour = 23;
    test_tm.tm_min = 0;
    test_tm.tm_sec = 0;

    tm_increment_hour(&test_tm);

    CHECK_EQUAL(2013, test_tm.tm_year);
    CHECK_EQUAL(3, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(0, test_tm.tm_hour);
    CHECK_EQUAL(0, test_tm.tm_min);
    CHECK_EQUAL(0, test_tm.tm_sec);
}

/*
 *  Tests function for April 30, 2013, 23:00. Should go to May 1,
 *  2013, 00:00.
 */

TEST(TmIncrementHourGroup, Inc7Test) {
    tm test_tm;
    test_tm.tm_year = 2013;
    test_tm.tm_mon = 3;
    test_tm.tm_mday = 30;
    test_tm.tm_hour = 23;
    test_tm.tm_min = 0;
    test_tm.tm_sec = 0;

    tm_increment_hour(&test_tm);

    CHECK_EQUAL(2013, test_tm.tm_year);
    CHECK_EQUAL(4, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(0, test_tm.tm_hour);
    CHECK_EQUAL(0, test_tm.tm_min);
    CHECK_EQUAL(0, test_tm.tm_sec);
}

/*
 *  Tests function for May 31, 2013, 23:00. Should go to June 1,
 *  2013, 00:00.
 */

TEST(TmIncrementHourGroup, Inc8Test) {
    tm test_tm;
    test_tm.tm_year = 2013;
    test_tm.tm_mon = 4;
    test_tm.tm_mday = 31;
    test_tm.tm_hour = 23;
    test_tm.tm_min = 0;
    test_tm.tm_sec = 0;

    tm_increment_hour(&test_tm);

    CHECK_EQUAL(2013, test_tm.tm_year);
    CHECK_EQUAL(5, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(0, test_tm.tm_hour);
    CHECK_EQUAL(0, test_tm.tm_min);
    CHECK_EQUAL(0, test_tm.tm_sec);
}

/*
 *  Tests function for June 30, 2013, 23:00. Should go to July 1,
 *  2013, 00:00.
 */

TEST(TmIncrementHourGroup, Inc9Test) {
    tm test_tm;
    test_tm.tm_year = 2013;
    test_tm.tm_mon = 5;
    test_tm.tm_mday = 30;
    test_tm.tm_hour = 23;
    test_tm.tm_min = 0;
    test_tm.tm_sec = 0;

    tm_increment_hour(&test_tm);

    CHECK_EQUAL(2013, test_tm.tm_year);
    CHECK_EQUAL(6, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(0, test_tm.tm_hour);
    CHECK_EQUAL(0, test_tm.tm_min);
    CHECK_EQUAL(0, test_tm.tm_sec);
}

/*
 *  Tests function for July 31, 2013, 23:00. Should go to August 1,
 *  2013, 00:00.
 */

TEST(TmIncrementHourGroup, Inc10Test) {
    tm test_tm;
    test_tm.tm_year = 2013;
    test_tm.tm_mon = 6;
    test_tm.tm_mday = 31;
    test_tm.tm_hour = 23;
    test_tm.tm_min = 0;
    test_tm.tm_sec = 0;

    tm_increment_hour(&test_tm);

    CHECK_EQUAL(2013, test_tm.tm_year);
    CHECK_EQUAL(7, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(0, test_tm.tm_hour);
    CHECK_EQUAL(0, test_tm.tm_min);
    CHECK_EQUAL(0, test_tm.tm_sec);
}

/*
 *  Tests function for August 31, 2013, 23:00. Should go to September 1,
 *  2013, 00:00.
 */

TEST(TmIncrementHourGroup, Inc11Test) {
    tm test_tm;
    test_tm.tm_year = 2013;
    test_tm.tm_mon = 7;
    test_tm.tm_mday = 31;
    test_tm.tm_hour = 23;
    test_tm.tm_min = 0;
    test_tm.tm_sec = 0;

    tm_increment_hour(&test_tm);

    CHECK_EQUAL(2013, test_tm.tm_year);
    CHECK_EQUAL(8, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(0, test_tm.tm_hour);
    CHECK_EQUAL(0, test_tm.tm_min);
    CHECK_EQUAL(0, test_tm.tm_sec);
}

/*
 *  Tests function for September 30, 2013, 23:00. Should go to October 1,
 *  2013, 00:00.
 */

TEST(TmIncrementHourGroup, Inc12Test) {
    tm test_tm;
    test_tm.tm_year = 2013;
    test_tm.tm_mon = 8;
    test_tm.tm_mday = 30;
    test_tm.tm_hour = 23;
    test_tm.tm_min = 0;
    test_tm.tm_sec = 0;

    tm_increment_hour(&test_tm);

    CHECK_EQUAL(2013, test_tm.tm_year);
    CHECK_EQUAL(9, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(0, test_tm.tm_hour);
    CHECK_EQUAL(0, test_tm.tm_min);
    CHECK_EQUAL(0, test_tm.tm_sec);
}

/*
 *  Tests function for October 31, 2013, 23:00. Should go to November 1,
 *  2013, 00:00.
 */

TEST(TmIncrementHourGroup, Inc13Test) {
    tm test_tm;
    test_tm.tm_year = 2013;
    test_tm.tm_mon = 9;
    test_tm.tm_mday = 31;
    test_tm.tm_hour = 23;
    test_tm.tm_min = 0;
    test_tm.tm_sec = 0;

    tm_increment_hour(&test_tm);

    CHECK_EQUAL(2013, test_tm.tm_year);
    CHECK_EQUAL(10, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(0, test_tm.tm_hour);
    CHECK_EQUAL(0, test_tm.tm_min);
    CHECK_EQUAL(0, test_tm.tm_sec);
}


/*
 *  Tests function for November 30, 2013, 23:00. Should go to December 1,
 *  2013, 00:00.
 */

TEST(TmIncrementHourGroup, Inc14Test) {
    tm test_tm;
    test_tm.tm_year = 2013;
    test_tm.tm_mon = 10;
    test_tm.tm_mday = 30;
    test_tm.tm_hour = 23;
    test_tm.tm_min = 0;
    test_tm.tm_sec = 0;

    tm_increment_hour(&test_tm);

    CHECK_EQUAL(2013, test_tm.tm_year);
    CHECK_EQUAL(11, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(0, test_tm.tm_hour);
    CHECK_EQUAL(0, test_tm.tm_min);
    CHECK_EQUAL(0, test_tm.tm_sec);
}


/*
 *  Tests function for December 31, 2013, 23:00. Should go to January 1,
 *  2014, 23:00.
 */

TEST(TmIncrementHourGroup, Inc15Test) {
    tm test_tm;
    test_tm.tm_year = 2013;
    test_tm.tm_mon = 11;
    test_tm.tm_mday = 31;
    test_tm.tm_hour = 23;
    test_tm.tm_min = 0;
    test_tm.tm_sec = 0;

    tm_increment_hour(&test_tm);

    CHECK_EQUAL(2014, test_tm.tm_year);
    CHECK_EQUAL(0, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(0, test_tm.tm_hour);
    CHECK_EQUAL(0, test_tm.tm_min);
    CHECK_EQUAL(0, test_tm.tm_sec);
}


/*
 *  Tests function for December 1, 2013, 06:00. Should go to December 1,
 *  2013, 07:00.
 */

TEST(TmIncrementHourGroup, Inc16Test) {
    tm test_tm;
    test_tm.tm_year = 2013;
    test_tm.tm_mon = 11;
    test_tm.tm_mday = 1;
    test_tm.tm_hour = 6;
    test_tm.tm_min = 0;
    test_tm.tm_sec = 0;

    tm_increment_hour(&test_tm);

    CHECK_EQUAL(2013, test_tm.tm_year);
    CHECK_EQUAL(11, test_tm.tm_mon);
    CHECK_EQUAL(1, test_tm.tm_mday);
    CHECK_EQUAL(7, test_tm.tm_hour);
    CHECK_EQUAL(0, test_tm.tm_min);
    CHECK_EQUAL(0, test_tm.tm_sec);
}


/*
 *  Tests function for December 3, 2013, 23:00. Should go to December 4,
 *  2013, 00:00.
 */

TEST(TmIncrementHourGroup, Inc17Test) {
    tm test_tm;
    test_tm.tm_year = 2013;
    test_tm.tm_mon = 11;
    test_tm.tm_mday = 3;
    test_tm.tm_hour = 23;
    test_tm.tm_min = 0;
    test_tm.tm_sec = 0;

    tm_increment_hour(&test_tm);

    CHECK_EQUAL(2013, test_tm.tm_year);
    CHECK_EQUAL(11, test_tm.tm_mon);
    CHECK_EQUAL(4, test_tm.tm_mday);
    CHECK_EQUAL(0, test_tm.tm_hour);
    CHECK_EQUAL(0, test_tm.tm_min);
    CHECK_EQUAL(0, test_tm.tm_sec);
}


/*
 *  test_julian_date.cpp
 *  ====================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Unit tests for julian_date() function.
 *
 *  The test cases in this group were taken from:
 *
 *    http://aa.usno.navy.mil/data/docs/JulianDate.php
 *
 *  on or around June 2, 2013.
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include <ctime>
#include "../astrofunc.h"

using namespace astro;


TEST_GROUP(JulianDateGroup) {
};


/*
 *  Tests Julian date function for June 2, 2013, 00:00 UTC.
 */

TEST(JulianDateGroup, FirstDateTest) {
    tm test_time_tm;
    test_time_tm.tm_sec = 0;
    test_time_tm.tm_min = 0;
    test_time_tm.tm_hour = 0;
    test_time_tm.tm_mday = 2;
    test_time_tm.tm_mon = 5;
    test_time_tm.tm_year = 113;
    test_time_tm.tm_isdst = 142;        // julian_date() should zero this

    double jdate = julian_date(&test_time_tm);
    double accuracy = 0.000001;

    DOUBLES_EQUAL(2456445.5, jdate, accuracy);
}


/*
 *  Tests Julian date function for Jan 1, 1980, 00:00 UTC.
 */

TEST(JulianDateGroup, SecondDateTest) {
    tm test_time_tm;
    test_time_tm.tm_sec = 0;
    test_time_tm.tm_min = 0;
    test_time_tm.tm_hour = 0;
    test_time_tm.tm_mday = 1;
    test_time_tm.tm_mon = 0;
    test_time_tm.tm_year = 80;
    test_time_tm.tm_isdst = -368;       // julian_date() should zero this

    double jdate = julian_date(&test_time_tm);
    double accuracy = 0.000001;

    DOUBLES_EQUAL(2444239.5, jdate, accuracy);
}


/*
 *  Tests Julian date function for Nov 11, 1918, 11:11 UTC.
 */

TEST(JulianDateGroup, ThirdDateTest) {
    tm test_time_tm;
    test_time_tm.tm_sec = 0;
    test_time_tm.tm_min = 11;
    test_time_tm.tm_hour = 11;
    test_time_tm.tm_mday = 11;
    test_time_tm.tm_mon = 10;
    test_time_tm.tm_year = 18;
    test_time_tm.tm_isdst = 0;          // julian_date() should zero this

    double jdate = julian_date(&test_time_tm);
    double accuracy = 0.001;

    DOUBLES_EQUAL(2421908.9661, jdate, accuracy);
}

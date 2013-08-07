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
#include "../utc_time.h"

using namespace astro;


TEST_GROUP(JulianDateGroup) {
};


/*
 *  Tests Julian date function for June 2, 2013, 00:00 UTC.
 */

TEST(JulianDateGroup, FirstDateTest) {
    double jdate = julian_date(utctime::UTCTime(2013, 6, 2, 0 ,0 , 0));
    double accuracy = 0.000001;

    DOUBLES_EQUAL(2456445.5, jdate, accuracy);
}


/*
 *  Tests Julian date function for Jan 1, 1980, 00:00 UTC.
 */

TEST(JulianDateGroup, SecondDateTest) {
    double jdate = julian_date(utctime::UTCTime(1980, 1, 1, 0, 0, 0));
    double accuracy = 0.000001;

    DOUBLES_EQUAL(2444239.5, jdate, accuracy);
}


/*
 *  Tests Julian date function for Nov 11, 1918, 11:11 UTC.
 */

TEST(JulianDateGroup, ThirdDateTest) {
    double jdate = julian_date(utctime::UTCTime(1918, 11, 11, 11, 11, 0));
    double accuracy = 0.001;

    DOUBLES_EQUAL(2421908.9661, jdate, accuracy);
}

/*
 *  test_is_leap_year.cpp
 *  =====================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Unit tests for is_leap_year() function.
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include "../utc_time.h"

using namespace utctime;


TEST_GROUP(IsLeapYearGroup) {
};


/*
 *  Tests is_leap_year() function.
 */

TEST(IsLeapYearGroup, LeapYearTest) {
    CHECK(is_leap_year(2012));
    CHECK(is_leap_year(2008));
    CHECK(is_leap_year(2004));
    CHECK(is_leap_year(2003) == false);
    CHECK(is_leap_year(2002) == false);
    CHECK(is_leap_year(2001) == false);
    CHECK(is_leap_year(2000));
    CHECK(is_leap_year(1999) == false);
    CHECK(is_leap_year(1998) == false);
    CHECK(is_leap_year(1997) == false);
    CHECK(is_leap_year(1996));
    CHECK(is_leap_year(1600));
    CHECK(is_leap_year(1200));
    CHECK(is_leap_year(1300) == false);
    CHECK(is_leap_year(1400) == false);
    CHECK(is_leap_year(1500) == false);
    CHECK(is_leap_year(1700) == false);
    CHECK(is_leap_year(1800) == false);
    CHECK(is_leap_year(1900) == false);
}

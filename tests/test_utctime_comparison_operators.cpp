/*
 *  test_utctime_comparison_operators.cpp
 *  =====================================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Unit tests for UTCTime class comparison operators.
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include "../utc_time.h"

using namespace utctime;


TEST_GROUP(UTCTimeComparisonGroup) {
};


/*
 *  Tests truth of comparison operators.
 */

TEST(UTCTimeComparisonGroup, TrueTest) {
    const UTCTime low_utc(2013, 8, 10, 0, 34, 0);
    const UTCTime high_utc(2013, 9, 6, 4, 22, 3);
    const UTCTime high_utc2(2013, 9, 6, 4, 22, 3);

    CHECK(low_utc < high_utc);
    CHECK(low_utc <= high_utc);
    CHECK(high_utc > low_utc);
    CHECK(high_utc >= low_utc);
    CHECK(low_utc != high_utc);
    CHECK(high_utc == high_utc2);
    CHECK(high_utc >= high_utc2);
    CHECK(high_utc <= high_utc2);
}


/*
 *  Tests falsity of comparison operators.
 */

TEST(UTCTimeComparisonGroup, FalseTest) {
    const UTCTime low_utc(2013, 8, 10, 0, 34, 0);
    const UTCTime high_utc(2013, 9, 6, 4, 22, 3);
    const UTCTime high_utc2(2013, 9, 6, 4, 22, 3);

    CHECK((low_utc >= high_utc) == false);
    CHECK((low_utc > high_utc) == false);
    CHECK((high_utc <= low_utc) == false);
    CHECK((high_utc < low_utc) == false);
    CHECK((low_utc == high_utc) == false);
    CHECK((high_utc != high_utc2) == false);
    CHECK((high_utc < high_utc2) == false);
    CHECK((high_utc > high_utc2) == false);
}

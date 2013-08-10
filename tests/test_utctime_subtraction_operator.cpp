/*
 *  test_utctime_subtraction_operator.cpp
 *  =====================================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Unit tests for UTCTime class subtraction operator.
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include "../utc_time.h"

using namespace utctime;


TEST_GROUP(UTCTimeSubtractionGroup) {
};


/*
 *  Tests subtraction operator.
 */

TEST(UTCTimeSubtractionGroup, SubtractionTest) {
    static const double accuracy = 0.000001;
    const UTCTime low_utc(2013, 8, 10, 0, 34, 0);
    const UTCTime high_utc(2013, 8, 10, 0, 39, 0);
    const UTCTime high_utc2(2013, 8, 10, 0, 39, 0);

    double test_result = high_utc - low_utc;
    DOUBLES_EQUAL(300, test_result, accuracy);

    test_result = low_utc - high_utc;
    DOUBLES_EQUAL(-300, test_result, accuracy);

    test_result = high_utc2 - high_utc;
    DOUBLES_EQUAL(0, test_result, accuracy);
}

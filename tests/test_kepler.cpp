/*
 *  test_kepler.cpp
 *  ===============
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Unit tests for kepler() function.
 *
 *  Test cases were taken from:
 *
 *    http://www.jgiesen.de/kepler/kepler.html
 *
 *  on or around June 2, 2013.
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include "../astrofunc.h"

using namespace astro;


TEST_GROUP(KeplerGroup) {
};


/*
 *  Tests Julian date function for June 2, 2013, 00:00 UTC.
 */

TEST(KeplerGroup, KeplerTest) {
    double accuracy = 0.00001;

    double expected_result = radians(37.40006);
    double test_result = kepler(radians(20), 0.5);
    DOUBLES_EQUAL(expected_result, test_result, accuracy);

    expected_result = radians(48.43418);
    test_result = kepler(radians(27), 0.5);
    DOUBLES_EQUAL(expected_result, test_result, accuracy);

    expected_result = radians(226.66512);
    test_result = kepler(radians(235), 0.2);
    DOUBLES_EQUAL(expected_result, test_result, accuracy);

    expected_result = radians(0);
    test_result = kepler(radians(0), 0);
    DOUBLES_EQUAL(expected_result, test_result, accuracy);

    expected_result = radians(360);
    test_result = kepler(radians(360), 0);
    DOUBLES_EQUAL(expected_result, test_result, accuracy);

    expected_result = radians(300);
    test_result = kepler(radians(300), 0);
    DOUBLES_EQUAL(expected_result, test_result, accuracy);

    expected_result = radians(96.25884);
    test_result = kepler(radians(45), 0.9);
    DOUBLES_EQUAL(expected_result, test_result, accuracy);
}

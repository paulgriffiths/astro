/*
 *  test_normalize_degrees.cpp
 *  ==========================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Unit tests for normalize_degrees() function.
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include "../astrofunc.h"

using namespace astro;


TEST_GROUP(NormalizeDegreesGroup) {
};


/*
 *  Tests normalize_degrees() function
 */

TEST(NormalizeDegreesGroup, NormalizeDegreesTest) {
    double accuracy = 0.00001;

    double test_result = normalize_degrees(50);
    DOUBLES_EQUAL(50, test_result, accuracy);

    test_result = normalize_degrees(400);
    DOUBLES_EQUAL(40, test_result, accuracy);

    test_result = normalize_degrees(-60);
    DOUBLES_EQUAL(300, test_result, accuracy);

    test_result = normalize_degrees(-460);
    DOUBLES_EQUAL(260, test_result, accuracy);

    test_result = normalize_degrees(500);
    DOUBLES_EQUAL(140, test_result, accuracy);

    test_result = normalize_degrees(360);
    DOUBLES_EQUAL(0, test_result, accuracy);

    test_result = normalize_degrees(0);
    DOUBLES_EQUAL(0, test_result, accuracy);
}

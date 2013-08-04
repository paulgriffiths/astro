/*
 *  test_rasc_to_zodiac.cpp
 *  =======================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Unit tests for rasc_to_zodiac() function.
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include "../astrofunc.h"

using namespace astro;


TEST_GROUP(RascToZodiacGroup) {
};


/*
 *  Tests rasc_to_zodiac() function
 */

TEST(RascToZodiacGroup, RascToZodiacTest) {
    std::string expected_result;
    std::string test_result;

    test_result = rasc_to_zodiac(0);
    expected_result = "00AR00";
    CHECK_EQUAL(expected_result, test_result);

    test_result = rasc_to_zodiac(30);
    expected_result = "00TA00";
    CHECK_EQUAL(expected_result, test_result);

    test_result = rasc_to_zodiac(65.5);
    expected_result = "05GE30";
    CHECK_EQUAL(expected_result, test_result);

    test_result = rasc_to_zodiac(145.7);
    expected_result = "25LE42";
    CHECK_EQUAL(expected_result, test_result);

    test_result = rasc_to_zodiac(325.2);
    expected_result = "25AQ12";
    CHECK_EQUAL(expected_result, test_result);
}

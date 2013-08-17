/*
 *  test_moon.cpp
 *  =============
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Unit test for moon position.
 *
 *  Test cases were taken from:
 *
 *    http://ssd.jpl.nasa.gov/?horizons
 *
 *  on August 4, 2013.
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include <paulgrif/utctime.h>
#include "../astro.h"

using namespace astro;


TEST_GROUP(MoonGroup) {
};


/*
 *  Tests position of the Moon for August 10, 1988, 00:00 UTC
 *
 *  Note: distance is not assessed in this test, as it is returned
 *  in earth radii rather than astronomical units, and no reliable
 *  test data could be found.
 */

TEST(MoonGroup, MoonTest) {
    SphCoords cds;
    double expected_result, test_result;
    const double ra_accuracy = 0.3;
    const double de_accuracy = 0.1;

    Moon moon(utctime::UTCTime(1988, 8, 10, 0, 0, 0));
    rec_to_sph(moon.geo_equ_coords(), cds);

    expected_result = 112.130708333333;
    test_result = normalize_degrees(cds.right_ascension);
    DOUBLES_EQUAL(expected_result, test_result, ra_accuracy);

    expected_result = 26.1949444444444;
    test_result = normalize_degrees(cds.declination);
    DOUBLES_EQUAL(expected_result, test_result, de_accuracy);
}

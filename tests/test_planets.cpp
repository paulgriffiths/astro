/*
 *  test_planets.cpp
 *  ================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Unit tests for planetary positions.
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
#include "../astro.h"
#include "../utc_time.h"

using namespace astro;


TEST_GROUP(PlanetsGroup) {
};


/*
 *  Tests position of Mercury for May 5, 1980, 20:23 UTC.
 */

TEST(PlanetsGroup, MercuryTest) {
    SphCoords cds;
    double expected_result, test_result;
    const double ra_accuracy = 0.1;
    const double de_accuracy = 0.01;
    const double di_accuracy = 0.0001;

    Mercury mercury(utctime::UTCTime(1980, 5, 5, 20, 23, 0));
    rec_to_sph(mercury.geo_equ_coords(), cds);

    expected_result = 35.0765;
    test_result = normalize_degrees(cds.right_ascension);
    DOUBLES_EQUAL(expected_result, test_result, ra_accuracy);

    expected_result = 12.7926666666667;
    test_result = normalize_degrees(cds.declination);
    DOUBLES_EQUAL(expected_result, test_result, de_accuracy);

    expected_result = 1.30377991344909;
    test_result = cds.distance;
    DOUBLES_EQUAL(expected_result, test_result, di_accuracy);
}


/*
 *  Tests position of Venus for June 14, 1982, 08:30 UTC
 */

TEST(PlanetsGroup, VenusTest) {
    SphCoords cds;
    double expected_result, test_result;
    const double ra_accuracy = 0.01;
    const double de_accuracy = 0.01;
    const double di_accuracy = 0.001;

    Venus venus(utctime::UTCTime(1982, 6, 14, 8, 30, 0));
    rec_to_sph(venus.geo_equ_coords(), cds);

    expected_result = 45.2389583333333;
    test_result = normalize_degrees(cds.right_ascension);
    DOUBLES_EQUAL(expected_result, test_result, ra_accuracy);

    expected_result = 15.0340277777778;
    test_result = normalize_degrees(cds.declination);
    DOUBLES_EQUAL(expected_result, test_result, de_accuracy);

    expected_result = 1.23214680691694;
    test_result = cds.distance;
    DOUBLES_EQUAL(expected_result, test_result, di_accuracy);
}


/*
 *  Tests position of Mars for June 21, 1997, 00:00 UTC.
 */

TEST(PlanetsGroup, MarsTest) {
    SphCoords cds;
    double expected_result, test_result;
    const double ra_accuracy = 0.01;
    const double de_accuracy = 0.01;
    const double di_accuracy = 0.0001;

    Mars mars(utctime::UTCTime(1997, 6, 21, 0, 0, 0));
    rec_to_sph(mars.geo_equ_coords(), cds);

    expected_result = 180.840541666667;
    test_result = normalize_degrees(cds.right_ascension);
    DOUBLES_EQUAL(expected_result, test_result, ra_accuracy);

    expected_result = 0.03566666666667;
    test_result = normalize_degrees(cds.declination);
    DOUBLES_EQUAL(expected_result, test_result, de_accuracy);

    expected_result = 1.18174124286972;
    test_result = cds.distance;
    DOUBLES_EQUAL(expected_result, test_result, di_accuracy);
}


/*
 *  Tests position of Jupiter for June 17, 1991, 00:00 UTC
 */

TEST(PlanetsGroup, JupiterTest) {
    SphCoords cds;
    double expected_result, test_result;
    const double ra_accuracy = 0.01;
    const double de_accuracy = 0.01;
    const double di_accuracy = 0.01;

    Jupiter jupiter(utctime::UTCTime(1991, 6, 17, 0, 0, 0));
    rec_to_sph(jupiter.geo_equ_coords(), cds);

    expected_result = 134.511875;
    test_result = normalize_degrees(cds.right_ascension);
    DOUBLES_EQUAL(expected_result, test_result, ra_accuracy);

    expected_result = 17.9471666666667;
    test_result = normalize_degrees(cds.declination);
    DOUBLES_EQUAL(expected_result, test_result, de_accuracy);

    expected_result = 5.9852047799159;
    test_result = cds.distance;
    DOUBLES_EQUAL(expected_result, test_result, di_accuracy);
}


/*
 *  Tests position of Saturn for December 1, 1947, 12:00 UTC
 */

TEST(PlanetsGroup, SaturnTest) {
    SphCoords cds;
    double expected_result, test_result;
    const double ra_accuracy = 0.02;
    const double de_accuracy = 0.01;
    const double di_accuracy = 0.01;

    Saturn saturn(utctime::UTCTime(1947, 12, 1, 12, 0, 0));
    rec_to_sph(saturn.geo_equ_coords(), cds);

    expected_result = 146.079125;
    test_result = normalize_degrees(cds.right_ascension);
    DOUBLES_EQUAL(expected_result, test_result, ra_accuracy);

    expected_result = 14.6949444444444;
    test_result = normalize_degrees(cds.declination);
    DOUBLES_EQUAL(expected_result, test_result, de_accuracy);

    expected_result = 8.84280824210253;
    test_result = cds.distance;
    DOUBLES_EQUAL(expected_result, test_result, di_accuracy);
}


/*
 *  Tests position of Uranus for October 31, 1975, 08:00 UTC
 */

TEST(PlanetsGroup, UranusTest) {
    SphCoords cds;
    double expected_result, test_result;
    const double ra_accuracy = 0.02;
    const double de_accuracy = 0.01;
    const double di_accuracy = 0.01;

    Uranus uranus(utctime::UTCTime(1975, 10, 31, 8, 0, 0));
    rec_to_sph(uranus.geo_equ_coords(), cds);

    expected_result = 211.38025;
    test_result = normalize_degrees(cds.right_ascension);
    DOUBLES_EQUAL(expected_result, test_result, ra_accuracy);

    expected_result = -12.21186111111110;
    test_result = cds.declination;
    DOUBLES_EQUAL(expected_result, test_result, de_accuracy);

    expected_result = 19.4873488102392;
    test_result = cds.distance;
    DOUBLES_EQUAL(expected_result, test_result, di_accuracy);
}


/*
 *  Tests position of Neptune for September 15, 1966, 09:00 UTC
 */

TEST(PlanetsGroup, NeptuneTest) {
    SphCoords cds;
    double expected_result, test_result;
    const double ra_accuracy = 0.01;
    const double de_accuracy = 0.01;
    const double di_accuracy = 0.01;

    Neptune neptune(utctime::UTCTime(1966, 9, 15, 9, 0, 0));
    rec_to_sph(neptune.geo_equ_coords(), cds);

    expected_result = 228.44925;
    test_result = normalize_degrees(cds.right_ascension);
    DOUBLES_EQUAL(expected_result, test_result, ra_accuracy);

    expected_result = -16.2009444444444;
    test_result = cds.declination;
    DOUBLES_EQUAL(expected_result, test_result, de_accuracy);

    expected_result = 30.8457020366069;
    test_result = cds.distance;
    DOUBLES_EQUAL(expected_result, test_result, di_accuracy);
}


/*
 *  Tests position of Pluto for September 11, 2001, 14:00 UTC
 */

TEST(PlanetsGroup, PlutoTest) {
    SphCoords cds;
    double expected_result, test_result;
    const double ra_accuracy = 0.01;
    const double de_accuracy = 0.01;
    const double di_accuracy = 0.01;

    Pluto pluto(utctime::UTCTime(2001, 9, 11, 14, 0, 0));
    rec_to_sph(pluto.geo_equ_coords(), cds);

    expected_result = 252.494583333333;
    test_result = normalize_degrees(cds.right_ascension);
    DOUBLES_EQUAL(expected_result, test_result, ra_accuracy);

    expected_result = -12.1994722222222;
    test_result = cds.declination;
    DOUBLES_EQUAL(expected_result, test_result, de_accuracy);

    expected_result = 30.5130260187628;
    test_result = cds.distance;
    DOUBLES_EQUAL(expected_result, test_result, di_accuracy);
}


/*
 *  Tests position of the Sun for June 4, 2013, 01:15 UTC.
 */

TEST(PlanetsGroup, SunTest) {
    SphCoords cds;
    double expected_result, test_result;
    const double ra_accuracy = 0.01;
    const double de_accuracy = 0.01;
    const double di_accuracy = 0.0001;

    Sun sun(utctime::UTCTime(2013, 6, 4, 1, 15, 0));
    rec_to_sph(sun.geo_equ_coords(), cds);

    expected_result = 72.0135416666667;
    test_result = normalize_degrees(cds.right_ascension);
    DOUBLES_EQUAL(expected_result, test_result, ra_accuracy);

    expected_result = 22.4078888888889;
    test_result = cds.declination;
    DOUBLES_EQUAL(expected_result, test_result, de_accuracy);

    expected_result = 1.01447036664534;
    test_result = cds.distance;
    DOUBLES_EQUAL(expected_result, test_result, di_accuracy);
}

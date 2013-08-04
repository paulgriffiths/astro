/*
 *  test_zodiac_sign_short.cpp
 *  ==========================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Unit tests for zodiac_sign_short() function.
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include "../astrofunc.h"

using namespace astro;


TEST_GROUP(ZodiacSignShortGroup) {
};


/*
 *  Tests zodiac_sign_short() function
 */

TEST(ZodiacSignShortGroup, ZodiacSignShortTest) {
    STRCMP_EQUAL("AR", zodiac_sign_short(0));
    STRCMP_EQUAL("AR", zodiac_sign_short(15));
    STRCMP_EQUAL("AR", zodiac_sign_short(29.9));
    STRCMP_EQUAL("TA", zodiac_sign_short(30));
    STRCMP_EQUAL("TA", zodiac_sign_short(45));
    STRCMP_EQUAL("TA", zodiac_sign_short(59.9));
    STRCMP_EQUAL("GE", zodiac_sign_short(60));
    STRCMP_EQUAL("GE", zodiac_sign_short(75));
    STRCMP_EQUAL("GE", zodiac_sign_short(89.9));
    STRCMP_EQUAL("CN", zodiac_sign_short(90));
    STRCMP_EQUAL("CN", zodiac_sign_short(105));
    STRCMP_EQUAL("CN", zodiac_sign_short(119.9));
    STRCMP_EQUAL("LE", zodiac_sign_short(120));
    STRCMP_EQUAL("LE", zodiac_sign_short(135));
    STRCMP_EQUAL("LE", zodiac_sign_short(149.9));
    STRCMP_EQUAL("VI", zodiac_sign_short(150));
    STRCMP_EQUAL("VI", zodiac_sign_short(165));
    STRCMP_EQUAL("VI", zodiac_sign_short(179.9));
    STRCMP_EQUAL("LI", zodiac_sign_short(180));
    STRCMP_EQUAL("LI", zodiac_sign_short(195));
    STRCMP_EQUAL("LI", zodiac_sign_short(209.9));
    STRCMP_EQUAL("SC", zodiac_sign_short(210));
    STRCMP_EQUAL("SC", zodiac_sign_short(225));
    STRCMP_EQUAL("SC", zodiac_sign_short(239.9));
    STRCMP_EQUAL("SG", zodiac_sign_short(240));
    STRCMP_EQUAL("SG", zodiac_sign_short(255));
    STRCMP_EQUAL("SG", zodiac_sign_short(269.9));
    STRCMP_EQUAL("CP", zodiac_sign_short(270));
    STRCMP_EQUAL("CP", zodiac_sign_short(285));
    STRCMP_EQUAL("CP", zodiac_sign_short(299.9));
    STRCMP_EQUAL("AQ", zodiac_sign_short(300));
    STRCMP_EQUAL("AQ", zodiac_sign_short(315));
    STRCMP_EQUAL("AQ", zodiac_sign_short(329.9));
    STRCMP_EQUAL("PI", zodiac_sign_short(330));
    STRCMP_EQUAL("PI", zodiac_sign_short(345));
    STRCMP_EQUAL("PI", zodiac_sign_short(359.9));
}

/*
 *  test_zodiac_sign.cpp
 *  ====================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Unit tests for zodiac_sign() function.
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include "../astrofunc.h"

using namespace astro;


TEST_GROUP(ZodiacSignGroup) {
};


/*
 *  Tests zodiac_sign() function
 */

TEST(ZodiacSignGroup, ZodiacSignTest) {
    STRCMP_EQUAL("Aries", zodiac_sign(0));
    STRCMP_EQUAL("Aries", zodiac_sign(15));
    STRCMP_EQUAL("Aries", zodiac_sign(29.9));
    STRCMP_EQUAL("Taurus", zodiac_sign(30));
    STRCMP_EQUAL("Taurus", zodiac_sign(45));
    STRCMP_EQUAL("Taurus", zodiac_sign(59.9));
    STRCMP_EQUAL("Gemini", zodiac_sign(60));
    STRCMP_EQUAL("Gemini", zodiac_sign(75));
    STRCMP_EQUAL("Gemini", zodiac_sign(89.9));
    STRCMP_EQUAL("Cancer", zodiac_sign(90));
    STRCMP_EQUAL("Cancer", zodiac_sign(105));
    STRCMP_EQUAL("Cancer", zodiac_sign(119.9));
    STRCMP_EQUAL("Leo", zodiac_sign(120));
    STRCMP_EQUAL("Leo", zodiac_sign(135));
    STRCMP_EQUAL("Leo", zodiac_sign(149.9));
    STRCMP_EQUAL("Virgo", zodiac_sign(150));
    STRCMP_EQUAL("Virgo", zodiac_sign(165));
    STRCMP_EQUAL("Virgo", zodiac_sign(179.9));
    STRCMP_EQUAL("Libra", zodiac_sign(180));
    STRCMP_EQUAL("Libra", zodiac_sign(195));
    STRCMP_EQUAL("Libra", zodiac_sign(209.9));
    STRCMP_EQUAL("Scorpio", zodiac_sign(210));
    STRCMP_EQUAL("Scorpio", zodiac_sign(225));
    STRCMP_EQUAL("Scorpio", zodiac_sign(239.9));
    STRCMP_EQUAL("Sagittarius", zodiac_sign(240));
    STRCMP_EQUAL("Sagittarius", zodiac_sign(255));
    STRCMP_EQUAL("Sagittarius", zodiac_sign(269.9));
    STRCMP_EQUAL("Capricorn", zodiac_sign(270));
    STRCMP_EQUAL("Capricorn", zodiac_sign(285));
    STRCMP_EQUAL("Capricorn", zodiac_sign(299.9));
    STRCMP_EQUAL("Aquarius", zodiac_sign(300));
    STRCMP_EQUAL("Aquarius", zodiac_sign(315));
    STRCMP_EQUAL("Aquarius", zodiac_sign(329.9));
    STRCMP_EQUAL("Pisces", zodiac_sign(330));
    STRCMP_EQUAL("Pisces", zodiac_sign(345));
    STRCMP_EQUAL("Pisces", zodiac_sign(359.9));
}

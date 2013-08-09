/*
 *  test_validate_date.cpp
 *  ======================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Unit tests for validate_date() function.
 *
 *  Uses CppUTest unit testing framework.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <CppUTest/CommandLineTestRunner.h>
#include "../utc_time.h"

using namespace utctime;


TEST_GROUP(ValidateDateGroup) {
};


/*
 *  Test valid and invalid years.
 */

TEST(ValidateDateGroup, ValidateYearTest) {
    try {
        bool valid = validate_date(100, 1, 1, 1, 1, 1);
        CHECK(valid);
    } catch(...) {
        FAIL("Valid year threw exception");
    }

    try {
        bool valid = validate_date(-100, 1, 1, 1, 1, 1);
        CHECK(valid);
    } catch(...) {
        FAIL("Valid year threw exception");
    }

    try {
        validate_date(0, 1, 1, 1, 1, 1);
        FAIL("Invalid year did not throw exception");
    } catch (invalid_date& e) {
        CHECK(true);
    } catch(...) {
        FAIL("Valid year threw exception");
    }
}


/*
 *  Test valid and invalid months.
 */

TEST(ValidateDateGroup, ValidateMonthTest) {
    try {
        bool valid = validate_date(100, 1, 1, 1, 1, 1);
        CHECK(valid);
    } catch(...) {
        FAIL("Valid month threw exception");
    }

    try {
        bool valid = validate_date(-100, 12, 1, 1, 1, 1);
        CHECK(valid);
    } catch(...) {
        FAIL("Valid month threw exception");
    }

    try {
        validate_date(100, 0, 1, 1, 1, 1);
        FAIL("Invalid month did not throw exception");
    } catch (invalid_date& e) {
        CHECK(true);
    } catch(...) {
        FAIL("Valid month threw exception");
    }

    try {
        validate_date(100, 13, 1, 1, 1, 1);
        FAIL("Invalid month did not throw exception");
    } catch (invalid_date& e) {
        CHECK(true);
    } catch(...) {
        FAIL("Valid month threw exception");
    }

    try {
        validate_date(100, -5, 1, 1, 1, 1);
        FAIL("Invalid month did not throw exception");
    } catch (invalid_date& e) {
        CHECK(true);
    } catch(...) {
        FAIL("Valid month threw exception");
    }

}


/*
 *  Test valid and invalid days.
 */

TEST(ValidateDateGroup, ValidateDayTest) {
    try {
        bool valid = validate_date(100, 1, 1, 1, 1, 1);
        CHECK(valid);
    } catch(...) {
        FAIL("Valid day threw exception");
    }

    try {
        bool valid = validate_date(-100, 12, 31, 1, 1, 1);
        CHECK(valid);
    } catch(...) {
        FAIL("Valid day threw exception");
    }

    try {
        bool valid = validate_date(-100, 11, 30, 1, 1, 1);
        CHECK(valid);
    } catch(...) {
        FAIL("Valid day threw exception");
    }

    try {
        bool valid = validate_date(-100, 10, 31, 1, 1, 1);
        CHECK(valid);
    } catch(...) {
        FAIL("Valid day threw exception");
    }

    try {
        bool valid = validate_date(-100, 9, 30, 1, 1, 1);
        CHECK(valid);
    } catch(...) {
        FAIL("Valid day threw exception");
    }

    try {
        bool valid = validate_date(-100, 8, 31, 1, 1, 1);
        CHECK(valid);
    } catch(...) {
        FAIL("Valid day threw exception");
    }

    try {
        bool valid = validate_date(-100, 7, 31, 1, 1, 1);
        CHECK(valid);
    } catch(...) {
        FAIL("Valid day threw exception");
    }

    try {
        bool valid = validate_date(-100, 6, 30, 1, 1, 1);
        CHECK(valid);
    } catch(...) {
        FAIL("Valid day threw exception");
    }

    try {
        bool valid = validate_date(-100, 5, 31, 1, 1, 1);
        CHECK(valid);
    } catch(...) {
        FAIL("Valid day threw exception");
    }

    try {
        bool valid = validate_date(-100, 4, 30, 1, 1, 1);
        CHECK(valid);
    } catch(...) {
        FAIL("Valid day threw exception");
    }

    try {
        bool valid = validate_date(-100, 3, 31, 1, 1, 1);
        CHECK(valid);
    } catch(...) {
        FAIL("Valid day threw exception");
    }

    try {
        bool valid = validate_date(101, 2, 28, 1, 1, 1);
        CHECK(valid);
    } catch(...) {
        FAIL("Valid day threw exception");
    }

    try {
        bool valid = validate_date(-100, 1, 31, 1, 1, 1);
        CHECK(valid);
    } catch(...) {
        FAIL("Valid day threw exception");
    }

    try {
        validate_date(100, 1, 0, 1, 1, 1);
        FAIL("Invalid day did not throw exception");
    } catch (invalid_date& e) {
        CHECK(true);
    } catch(...) {
        FAIL("Valid day threw exception");
    }

    try {
        validate_date(100, 7, -5, 1, 1, 1);
        FAIL("Invalid day did not throw exception");
    } catch (invalid_date& e) {
        CHECK(true);
    } catch(...) {
        FAIL("Valid day threw exception");
    }

    try {
        validate_date(100, 1, 32, 1, 1, 1);
        FAIL("Invalid day did not throw exception");
    } catch (invalid_date& e) {
        CHECK(true);
    } catch(...) {
        FAIL("Valid day threw exception");
    }

    try {
        validate_date(100, 2, 29, 1, 1, 1);
        FAIL("Invalid day did not throw exception");
    } catch (invalid_date& e) {
        CHECK(true);
    } catch(...) {
        FAIL("Valid day threw exception");
    }

    try {
        bool valid = validate_date(104, 2, 29, 1, 1, 1);
        CHECK(valid);
    } catch(...) {
        FAIL("Valid day threw exception");
    }

    try {
        bool valid = validate_date(2000, 2, 29, 1, 1, 1);
        CHECK(valid);
    } catch(...) {
        FAIL("Valid day threw exception");
    }

    try {
        validate_date(104, 2, 30, 1, 1, 1);
        FAIL("Invalid day did not throw exception");
    } catch (invalid_date& e) {
        CHECK(true);
    } catch(...) {
        FAIL("Valid day threw exception");
    }

    try {
        validate_date(400, 2, 30, 1, 1, 1);
        FAIL("Invalid day did not throw exception");
    } catch (invalid_date& e) {
        CHECK(true);
    } catch(...) {
        FAIL("Valid day threw exception");
    }

    try {
        validate_date(104, 3, 32, 1, 1, 1);
        FAIL("Invalid day did not throw exception");
    } catch (invalid_date& e) {
        CHECK(true);
    } catch(...) {
        FAIL("Valid day threw exception");
    }

    try {
        validate_date(104, 4, 31, 1, 1, 1);
        FAIL("Invalid day did not throw exception");
    } catch (invalid_date& e) {
        CHECK(true);
    } catch(...) {
        FAIL("Valid day threw exception");
    }

    try {
        validate_date(104, 5, 32, 1, 1, 1);
        FAIL("Invalid day did not throw exception");
    } catch (invalid_date& e) {
        CHECK(true);
    } catch(...) {
        FAIL("Valid day threw exception");
    }

    try {
        validate_date(104, 6, 31, 1, 1, 1);
        FAIL("Invalid day did not throw exception");
    } catch (invalid_date& e) {
        CHECK(true);
    } catch(...) {
        FAIL("Valid day threw exception");
    }

    try {
        validate_date(104, 7, 32, 1, 1, 1);
        FAIL("Invalid day did not throw exception");
    } catch (invalid_date& e) {
        CHECK(true);
    } catch(...) {
        FAIL("Valid day threw exception");
    }

    try {
        validate_date(104, 8, 32, 1, 1, 1);
        FAIL("Invalid day did not throw exception");
    } catch (invalid_date& e) {
        CHECK(true);
    } catch(...) {
        FAIL("Valid day threw exception");
    }

    try {
        validate_date(104, 9, 31, 1, 1, 1);
        FAIL("Invalid day did not throw exception");
    } catch (invalid_date& e) {
        CHECK(true);
    } catch(...) {
        FAIL("Valid day threw exception");
    }

    try {
        validate_date(104, 10, 32, 1, 1, 1);
        FAIL("Invalid day did not throw exception");
    } catch (invalid_date& e) {
        CHECK(true);
    } catch(...) {
        FAIL("Valid day threw exception");
    }

    try {
        validate_date(104, 11, 31, 1, 1, 1);
        FAIL("Invalid day did not throw exception");
    } catch (invalid_date& e) {
        CHECK(true);
    } catch(...) {
        FAIL("Valid day threw exception");
    }

    try {
        validate_date(104, 12, 32, 1, 1, 1);
        FAIL("Invalid day did not throw exception");
    } catch (invalid_date& e) {
        CHECK(true);
    } catch(...) {
        FAIL("Valid day threw exception");
    }
}


/*
 *  Test valid and invalid hours
 */

TEST(ValidateDateGroup, ValidateHourTest) {
    try {
        bool valid = validate_date(100, 1, 1, 0, 1, 1);
        CHECK(valid);
    } catch(...) {
        FAIL("Valid hour threw exception");
    }

    try {
        bool valid = validate_date(-100, 12, 1, 12, 1, 1);
        CHECK(valid);
    } catch(...) {
        FAIL("Valid hour threw exception");
    }

    try {
        validate_date(100, 6, 1, -1, 1, 1);
        FAIL("Invalid hour did not throw exception");
    } catch (invalid_date& e) {
        CHECK(true);
    } catch(...) {
        FAIL("Valid hour threw exception");
    }

    try {
        validate_date(100, 12, 1, 24, 1, 1);
        FAIL("Invalid hour did not throw exception");
    } catch (invalid_date& e) {
        CHECK(true);
    } catch(...) {
        FAIL("Valid hour threw exception");
    }
}


/*
 *  Test valid and invalid minutes
 */

TEST(ValidateDateGroup, ValidateMinuteTest) {
    try {
        bool valid = validate_date(100, 1, 1, 1, 0, 1);
        CHECK(valid);
    } catch(...) {
        FAIL("Valid minute threw exception");
    }

    try {
        bool valid = validate_date(100, 1, 1, 1, 59, 1);
        CHECK(valid);
    } catch(...) {
        FAIL("Valid minute threw exception");
    }

    try {
        validate_date(100, 1, 1, 1, -1, 1);
        FAIL("Invalid minute did not throw exception");
    } catch (invalid_date& e) {
        CHECK(true);
    } catch(...) {
        FAIL("Valid minute threw exception");
    }

    try {
        validate_date(100, 1, 1, 1, 60, 1);
        FAIL("Invalid minute did not throw exception");
    } catch (invalid_date& e) {
        CHECK(true);
    } catch(...) {
        FAIL("Valid minute threw exception");
    }
}

/*
 *  Test valid and invalid seconds
 */

TEST(ValidateDateGroup, ValidateSecondTest) {
    try {
        bool valid = validate_date(100, 1, 1, 1, 1, 0);
        CHECK(valid);
    } catch(...) {
        FAIL("Valid second threw exception");
    }

    try {
        bool valid = validate_date(100, 1, 1, 1, 1, 59);
        CHECK(valid);
    } catch(...) {
        FAIL("Valid second threw exception");
    }

    try {
        validate_date(100, 1, 1, 1, 1, -1);
        FAIL("Invalid second did not throw exception");
    } catch (invalid_date& e) {
        CHECK(true);
    } catch(...) {
        FAIL("Valid second threw exception");
    }

    try {
        validate_date(100, 1, 1, 1, 1, 60);
        FAIL("Invalid second did not throw exception");
    } catch (invalid_date& e) {
        CHECK(true);
    } catch(...) {
        FAIL("Valid second threw exception");
    }
}

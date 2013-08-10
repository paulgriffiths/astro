/*
 *  utc_time.cpp
 *  ============
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Implementation of UTCTime() class and functions.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <sstream>
#include <ctime>
#include <cassert>
#include "utc_time.h"

using namespace utctime;

/********************************************************************
 *
 * UTCTime class member function definitions.
 *
 ********************************************************************/


/*
 *  Default constructor, initializes to current time.
 *
 *  Throws bad_time_init() if cannot get the current time.
 */

UTCTime::UTCTime() :
        m_year(0), m_month(0), m_day(0),
        m_hour(0), m_minute(0), m_second(0),
        m_timestamp(0) {
    m_timestamp = std::time(0);
    if ( m_timestamp == -1 ) {
        throw bad_time_init();
    }

    tm* ptm = gmtime(&m_timestamp);
    if ( ptm == 0 ) {
        throw bad_time_init();
    }

    m_year = ptm->tm_year + 1900;
    m_month = ptm->tm_mon + 1;
    m_day = ptm->tm_mday;
    m_hour = ptm->tm_hour;
    m_minute = ptm->tm_min;
    m_second = ptm->tm_sec;
}


/*
 *  Constructor initializing with a tm struct
 */

UTCTime::UTCTime(const tm& utc_tm) :
        m_year(utc_tm.tm_year + 1900), m_month(utc_tm.tm_mon + 1),
        m_day(utc_tm.tm_mday), m_hour(utc_tm.tm_hour),
        m_minute(utc_tm.tm_min), m_second(utc_tm.tm_sec),
        m_timestamp(0) {
    try {
        validate_date(m_year, m_month, m_day, m_hour, m_minute, m_second);
    } catch(invalid_date) {
        throw;
    }

    try {
        m_timestamp = get_utc_timestamp(m_year, m_month, m_day,
                                        m_hour, m_minute, m_second);
    } catch(bad_time) {
        throw bad_time_init();
    }
}


/*
 *  Constructor for initializing to specified date & time.
 *
 *  Throws bad_time_init() if cannot get the current time.
 */

UTCTime::UTCTime(const int year, const int month,
                 const int day, const int hour,
                 const int minute, const int second) :
        m_year(year), m_month(month), m_day(day),
        m_hour(hour), m_minute(minute), m_second(second),
        m_timestamp(0) {
    try {
        validate_date(m_year, m_month, m_day, m_hour, m_minute, m_second);
    } catch(invalid_date) {
        throw;
    }

    try {
        m_timestamp = get_utc_timestamp(m_year, m_month, m_day,
                                        m_hour, m_minute, m_second);
    } catch(bad_time) {
        throw bad_time_init();
    }
}


/*
 *  Returns a struct tm containing the date representation.
 */

std::tm UTCTime::get_tm() const {
    tm ret_tm;
    ret_tm.tm_year = m_year - 1900;
    ret_tm.tm_mon = m_month - 1;
    ret_tm.tm_mday = m_day;
    ret_tm.tm_hour = m_hour;
    ret_tm.tm_min = m_minute;
    ret_tm.tm_sec = m_second;

    return ret_tm;
}


/*
 *  Returns a string representation of the time
 *
 *  Throws bad_time() if cannot get the current time.
 */

std::string UTCTime::time_string() const {
    tm* utc_tm = gmtime(&m_timestamp);
    if ( utc_tm == 0 ) {
        throw bad_time();
    }
    char tstring[100];
    strftime(tstring, 1000, "%A %B %d, %Y %H:%M:%S UTC", utc_tm);
    return tstring;
}


/*
 *  Returns a string representation of the time in internet
 *  RFC 3339 format
 *
 *  Throws bad_time() if cannot get the current time.
 */

std::string UTCTime::time_string_inet() const {
    tm* utc_tm = gmtime(&m_timestamp);
    if ( utc_tm == 0 ) {
        throw bad_time();
    }
    char tstring[100];
    strftime(tstring, 1000, "%Y-%m-%dT%H:%M:%SZ", utc_tm);
    return tstring;
}


/*
 *  Returns the timestamp.
 */

time_t UTCTime::timestamp() const {
    return m_timestamp;
}


/********************************************************************
 *
 * Standalone function definitions.
 *
 ********************************************************************/


/*
 *  Checks whether a supplied date is valid, and throws invalid_date()
 *  if it isn't.
 */

bool utctime::validate_date(const int year, const int month,
                            const int day, const int hour,
                            const int minute, const int second) {
    static const int days_in_month[] = {31, 28, 31, 30, 31, 30,
                                        31, 31, 30, 31, 30, 31};
    static const char* month_names[] = {"January", "February", "March",
                                        "April", "May", "June", "July",
                                        "August", "September", "October",
                                        "November", "December"};

    if ( year == 0 ) {
        std::ostringstream oss;
        oss << "Invalid year: " << year;
        throw invalid_date(oss.str());
    } else if ( month < 1 || month > 12 ) {
        std::ostringstream oss;
        oss << "Invalid month: " << month;
        throw invalid_date(oss.str());
    } else if ( day < 1 ) {
        std::ostringstream oss;
        oss << "Invalid day: " << day;
        throw invalid_date(oss.str());
    } else if ( day > days_in_month[month - 1] &&
                !(month == 2 && day == 29 && is_leap_year(year)) ) {
        std::ostringstream oss;
        oss << "Invalid day: " << day << " of " << month_names[month - 1]
            << ", " << year;
        throw invalid_date(oss.str());
    } else if ( hour < 0 || hour > 23 ) {
        std::ostringstream oss;
        oss << "Invalid hour: " << hour;
        throw invalid_date(oss.str());
    } else if ( minute < 0 || minute > 59 ) {
        std::ostringstream oss;
        oss << "Invalid minute: " << minute;
        throw invalid_date(oss.str());
    } else if ( second < 0 || second > 59 ) {
        std::ostringstream oss;
        oss << "Invalid second: " << second;
        throw invalid_date(oss.str());
    }

    return true;
}


/*
 *  Checks whether the provided time_t timestamp yields a UTC
 *  date corresponding with the date and time information provided
 *  when gmtime() is called with it.
 *
 *  The function modifies the second argument, 'secs_diff', to contain
 *  the difference in seconds between the time we're checking, and
 *  the time gmtime() actually gives us. 
 *
 *  Throws bad_time() if cannot get the current time.
 */

bool utctime::check_utc_timestamp(const time_t check_time, int& secs_diff,
                                  const int year, const int month,
                                  const int day, const int hour,
                                  const int minute, const int second) {
    tm* ptm = gmtime(&check_time);
    if ( ptm == 0 ) {
        throw bad_time();
    }

    tm check_tm = *ptm;
    bool agrees = false;
    if ( check_tm.tm_year + 1900 == year &&
         check_tm.tm_mon + 1 == month &&
         check_tm.tm_mday == day &&
         check_tm.tm_hour == hour &&
         check_tm.tm_min == minute &&
         check_tm.tm_sec == second ) {
        agrees = true;
    }

    if ( agrees == false ) {
        tm utc_tm;
        utc_tm.tm_year = year - 1900;
        utc_tm.tm_mon = month - 1;
        utc_tm.tm_mday = day;
        utc_tm.tm_hour = hour;
        utc_tm.tm_min = minute;
        utc_tm.tm_sec = second;

        secs_diff = tm_intraday_secs_diff(utc_tm, check_tm);
    } else {
        secs_diff = 0;
    }

    return agrees;
}


/*
 *  Calculate a time_t value which represents a difference of
 *  one day. The C standard does not define the units in which
 *  a time_t value is measured. On most UNIX systems it's measured
 *  in seconds, but we can't assume this, so we find out for
 *  sure by setting up two struct tms a day apart and calculating
 *  the difference between the values that mktime() yields.
 *
 *  We've picked January 2 and January 3 as the dates to use, since
 *  we're likely clear of any DST or other weirdness on these dates.
 *  Since mktime() will modify the struct we pass to it if it represents
 *  a bad date, and since we reuse it, it should be good anyway.
 *
 *  Throws bad_time() if cannot get the current time.
 */

time_t utctime::get_day_diff() {
    tm datum_day;
    datum_day.tm_sec = 0;
    datum_day.tm_min = 0;
    datum_day.tm_hour = 12;
    datum_day.tm_mday = 2;
    datum_day.tm_mon = 0;
    datum_day.tm_year = 30;
    datum_day.tm_isdst = -1;

    const time_t datum_time = mktime(&datum_day);
    if ( datum_time == -1 ) {
        throw bad_time();
    }

    datum_day.tm_mday += 1;
    const time_t tomorrow_time = mktime(&datum_day);
    if ( tomorrow_time == -1 ) {
        throw bad_time();
    }

    return (tomorrow_time - datum_time);
}


/*
 *  Calculate a time_t value which represents a difference of
 *  one hour. The C standard does not define the units in which
 *  a time_t value is measured. On most UNIX systems it's measured
 *  in seconds, but we can't assume this, so we find out for
 *  sure by setting up two struct tms a second apart and calculating
 *  the difference between the values that mktime() yields.
 *
 *  We've picked January 2 as the date to use, since we're likely clear
 *  of any DST or other weirdness on these dates. Since mktime() will
 *  modify the struct we pass to it if it represents a bad date, and
 *  since we reuse it, it should be good anyway.
 *
 *  Throws bad_time() if cannot get the current time.
 */

time_t utctime::get_hour_diff() {
    tm datum_day;
    datum_day.tm_sec = 0;
    datum_day.tm_min = 0;
    datum_day.tm_hour = 12;
    datum_day.tm_mday = 2;
    datum_day.tm_mon = 0;
    datum_day.tm_year = 30;
    datum_day.tm_isdst = -1;

    const time_t datum_time = mktime(&datum_day);
    if ( datum_time == -1 ) {
        throw bad_time();
    }

    datum_day.tm_hour += 1;
    const time_t next_hour_time = mktime(&datum_day);
    if ( next_hour_time == -1 ) {
        throw bad_time();
    }

    return (next_hour_time - datum_time);
}


/*
 *  Calculate a time_t value which represents a difference of
 *  one second. The C standard does not define the units in which
 *  a time_t value is measured. On most UNIX systems it's measured
 *  in seconds, but we can't assume this, so we find out for
 *  sure by setting up two struct tms a second apart and calculating
 *  the difference between the values that mktime() yields.
 *
 *  We've picked January 2 as the date to use, since we're likely clear
 *  of any DST or other weirdness on these dates. Since mktime() will
 *  modify the struct we pass to it if it represents a bad date, and
 *  since we reuse it, it should be good anyway.
 *
 *  Throws bad_time() if cannot get the current time.
 */

time_t utctime::get_sec_diff() {
    tm datum_day;
    datum_day.tm_sec = 0;
    datum_day.tm_min = 0;
    datum_day.tm_hour = 12;
    datum_day.tm_mday = 2;
    datum_day.tm_mon = 0;
    datum_day.tm_year = 30;
    datum_day.tm_isdst = -1;

    const time_t datum_time = mktime(&datum_day);
    if ( datum_time == -1 ) {
        throw bad_time();
    }

    datum_day.tm_sec += 1;
    const time_t next_sec_time = mktime(&datum_day);
    if ( next_sec_time == -1 ) {
        throw bad_time();
    }

    return (next_sec_time - datum_time);
}


/*
 *  Compares two struct tms. Returns -1 is the first struct tm is
 *  smaller than the second, 1 if the first struct tm is greater
 *  than the second, and 0 if they are equal.
 *
 *  The function only compares the year, month, day, hour, minute
 *  and second. Any timezone or DST information is ignored.
 */

int utctime::tm_compare(const tm& first, const tm& second) {
    int compare_result;

    if ( first.tm_year != second.tm_year ) {
        compare_result = first.tm_year > second.tm_year ? 1 : -1;
    } else if ( first.tm_mon != second.tm_mon ) {
        compare_result = first.tm_mon > second.tm_mon ? 1 : -1;
    } else if ( first.tm_mday != second.tm_mday ) {
        compare_result = first.tm_mday > second.tm_mday ? 1 : -1;
    } else if ( first.tm_hour != second.tm_hour ) {
        compare_result = first.tm_hour > second.tm_hour ? 1 : -1;
    } else if ( first.tm_min != second.tm_min ) {
        compare_result = first.tm_min > second.tm_min ? 1 : -1;
    } else if ( first.tm_sec != second.tm_sec ) {
        compare_result = first.tm_sec > second.tm_sec ? 1 : -1;
    } else {
        compare_result = 0;
    }

    return compare_result;
}


/*
 *  Returns the difference in seconds between two times which are
 *  assumed to be within 24 hours of each other. 
 *
 *  If they are not within 24 hours of each other, the result is
 *  returned as if they were. For instance, comparing 10am on one day
 *  to 2pm on the next day will yield a difference of 4 hours, not
 *  28 hours.
 *
 *  The value returned is positive if 'second' is later than 'first',
 *  and negative if 'second' is earlier than 'first'.
 */

int utctime::tm_intraday_secs_diff(const tm& first, const tm& second) {
    static const int secs_in_day = 86400;
    static const int secs_in_hour = 3600;
    static const int secs_in_min = 60;

    const int time_comp = tm_compare(first, second);
    int difference = 0;

    if ( time_comp == 0 ) {
        difference = 0;
    } else {
        difference = (second.tm_hour - first.tm_hour) * secs_in_hour;
        difference += (second.tm_min - first.tm_min) * secs_in_min;
        difference += (second.tm_sec - first.tm_sec);

        if ( time_comp == 1 && difference > 0 ) {
            difference -= secs_in_day;
        } else if ( time_comp == -1 && difference < 0 ) {
            difference += secs_in_day;
        }
    }
    
    return difference;
}


/*
 *  Returns true if the supplied year is a leap year.
 */

bool utctime::is_leap_year(const int year) {
    bool leap_year;
    if ( year % 4 == 0 &&
         (year % 100 != 0 ||
          year % 400 == 0) ) {
        leap_year = true;
    } else {
        leap_year = false;
    }
    return leap_year;
}


/*
 *  Adds a day to a supplied tm struct.
 */

tm* utctime::tm_increment_day(tm * changing_tm, const int quantity) {
    enum months {january, february, march, april, may, june, july,
                 august, september, october, november, december};

    if ( quantity < 0 ) {
        tm_decrement_day(changing_tm, -quantity);
    } else {
        int num_days = quantity;

        while ( num_days-- ) {
            changing_tm->tm_mday += 1;
            switch ( changing_tm->tm_mon ) {
                case january:
                case march:
                case may:
                case july:
                case august:
                case october:
                    if ( changing_tm->tm_mday > 31 ) {
                        changing_tm->tm_mday = 1;
                        changing_tm->tm_mon += 1;
                    }
                    break;

                case december:
                    if ( changing_tm->tm_mday > 31 ) {
                        changing_tm->tm_mday = 1;
                        changing_tm->tm_mon = 0;
                        if ( changing_tm->tm_year == -1 ) {
                            changing_tm->tm_year = 1;
                        } else {
                            changing_tm->tm_year += 1;
                        }
                    }
                    break;

                case april:
                case june:
                case september:
                case november:
                    if ( changing_tm->tm_mday > 30 ) {
                        changing_tm->tm_mday = 1;
                        changing_tm->tm_mon +=1;
                    }
                    break;

                case 1:
                    if ( changing_tm->tm_mday > 29 ) {
                        changing_tm->tm_mday = 1;
                        changing_tm->tm_mon += 1;
                    } else if ( changing_tm->tm_mday > 28 &&
                                !is_leap_year(changing_tm->tm_year) ) {
                        changing_tm->tm_mday = 1;
                        changing_tm->tm_mon += 1;
                    }
                    break;

                default:
                    assert(false);
                    break;
            }
        }
    }

    return changing_tm;
}


/*
 *  Adds an hour to a supplied tm struct.
 */

tm* utctime::tm_increment_hour(tm * changing_tm, const int quantity) {
    static const int hours_in_day = 24;

    if ( quantity < 0 ) {
        tm_decrement_hour(changing_tm, -quantity);
    } else {
        int num_hours = quantity;

        if ( num_hours >= hours_in_day ||
             num_hours >= hours_in_day - changing_tm->tm_hour ) {
            int num_days = quantity / hours_in_day;
            num_hours -= num_days * hours_in_day;
            if ( num_hours >= hours_in_day - changing_tm->tm_hour ) {
                ++num_days;
                num_hours -= hours_in_day - changing_tm->tm_hour;
                changing_tm->tm_hour = num_hours;
            }
            tm_increment_day(changing_tm, num_days);
        }

        changing_tm->tm_hour += num_hours;
    }

    return changing_tm;
}


/*
 *  Adds a minute to a supplied tm struct.
 */

tm* utctime::tm_increment_minute(tm * changing_tm, const int quantity) {
    static const int mins_in_hour = 60;

    if ( quantity < 0 ) {
        tm_decrement_minute(changing_tm, -quantity);
    } else {
        int num_mins = quantity;

        if ( num_mins >= mins_in_hour ||
             num_mins >= mins_in_hour - changing_tm->tm_min ) {
            int num_hours = quantity / mins_in_hour;
            num_mins -= num_hours * mins_in_hour;
            if ( num_mins >= mins_in_hour - changing_tm->tm_min ) {
                ++num_hours;
                changing_tm->tm_min += num_mins - mins_in_hour;
                num_mins = 0;
            }
            tm_increment_hour(changing_tm, num_hours);
        }

        changing_tm->tm_min += num_mins;
    }
    return changing_tm;
}


/*
 *  Adds a second to a supplied tm struct.
 */

tm* utctime::tm_increment_second(tm * changing_tm, const int quantity) {
    static const int secs_in_min = 60;

    if ( quantity < 0 ) {
        tm_decrement_second(changing_tm, -quantity);
    } else {
        int num_secs = quantity;

        if ( num_secs >= secs_in_min ||
             num_secs >= secs_in_min - changing_tm->tm_sec ) {
            int num_mins = quantity / secs_in_min;
            num_secs -= num_mins * secs_in_min;
            if ( num_secs >= secs_in_min - changing_tm->tm_sec ) {
                ++num_mins;
                changing_tm->tm_sec += num_secs - secs_in_min;
                num_secs = 0;
            }
            tm_increment_minute(changing_tm, num_mins);
        }

        changing_tm->tm_sec += num_secs;
    }

    return changing_tm;
}


/*
 *  Deducts a day from a supplied tm struct.
 */

tm* utctime::tm_decrement_day(tm * changing_tm, const int quantity) {
    enum months {january, february, march, april, may, june, july,
                 august, september, october, november, december};

    if ( quantity < 0 ) {
        tm_increment_day(changing_tm, -quantity);
    } else {
        int num_days = quantity;

        while ( num_days-- ) {
            if ( changing_tm->tm_mday > 1 ) {
                changing_tm->tm_mday -= 1;
            } else {
                switch ( changing_tm->tm_mon ) {
                    case january:
                        changing_tm->tm_mday = 31;
                        changing_tm->tm_mon = 11;
                        if ( changing_tm->tm_year == 1 ) {
                            changing_tm->tm_year = -1;
                        } else {
                            changing_tm->tm_year -= 1;
                        }
                        break;

                    case february: 
                    case april:
                    case june:
                    case august:
                    case september:
                    case november:
                        changing_tm->tm_mday = 31;
                        changing_tm->tm_mon -= 1;
                        break;

                    case may:
                    case july:
                    case october:
                    case december:
                        changing_tm->tm_mday = 30;
                        changing_tm->tm_mon -= 1;
                        break;

                    case march:
                        if ( is_leap_year(changing_tm->tm_year) ) {
                            changing_tm->tm_mday = 29;
                        } else {
                            changing_tm->tm_mday = 28;
                        }
                        changing_tm->tm_mon -= 1;
                        break;

                    default:
                        assert(false);
                        break;
                }
            }
        }
    }

    return changing_tm;
}


/*
 *  Deducts an hour from a supplied tm struct.
 */

tm* utctime::tm_decrement_hour(tm * changing_tm, const int quantity) {
    static const int hours_in_day = 24;

    if ( quantity < 0 ) {
        tm_increment_hour(changing_tm, -quantity);
    } else {
        int num_hours = quantity;

        if ( num_hours >= hours_in_day || num_hours > changing_tm->tm_hour ) {
            int num_days = quantity / hours_in_day;
            num_hours -= num_days * hours_in_day;
            if ( num_hours > changing_tm->tm_hour ) {
                ++num_days;
                num_hours -= changing_tm->tm_hour;
                changing_tm->tm_hour = hours_in_day;
            }
            tm_decrement_day(changing_tm, num_days);
        }

        changing_tm->tm_hour -= num_hours;
    }

    return changing_tm;
}


/*
 *  Deducts a minute from a supplied tm struct.
 */

tm* utctime::tm_decrement_minute(tm * changing_tm, const int quantity) {
    static const int mins_in_hour = 60;

    if ( quantity < 0 ) {
        tm_increment_minute(changing_tm, -quantity);
    } else {
        int num_mins = quantity;

        if ( num_mins >= mins_in_hour || num_mins > changing_tm->tm_min ) {
            int num_hours = quantity / mins_in_hour;
            num_mins -= num_hours * mins_in_hour;
            if ( num_mins > changing_tm->tm_min ) {
                ++num_hours;
                num_mins -= changing_tm->tm_min;
                changing_tm->tm_min = mins_in_hour;
            }
            tm_decrement_hour(changing_tm, num_hours);
        }

        changing_tm->tm_min -= num_mins;
    }
    return changing_tm;
}


/*
 *  Deducts a second from a supplied tm struct.
 */

tm* utctime::tm_decrement_second(tm * changing_tm, const int quantity) {
    static const int secs_in_min = 60;

    if ( quantity < 0 ) {
        tm_increment_second(changing_tm, -quantity);
    } else {
        int num_secs = quantity;

        if ( num_secs >= secs_in_min || num_secs > changing_tm->tm_sec ) {
            int num_mins = quantity / secs_in_min;
            num_secs -= num_mins * secs_in_min;
            if ( num_secs > changing_tm->tm_sec ) {
                ++num_mins;
                num_secs -= changing_tm->tm_sec;
                changing_tm->tm_sec = secs_in_min;
            }
            tm_decrement_minute(changing_tm, num_mins);
        }

        changing_tm->tm_sec -= num_secs;
    }

    return changing_tm;
}


/*
 *  Returns a time_t timestamp for the given arguments
 *  representing a UTC time.
 *
 *  Throws bad_time() if cannot get the current time.
 */

time_t utctime::get_utc_timestamp(const int year, const int month,
                                  const int day, const int hour,
                                  const int minute, const int second) {

    //  Create a struct tm containing the desired UTC time.

    tm local_tm;
    local_tm.tm_sec = second;
    local_tm.tm_min = minute;
    local_tm.tm_hour = hour;
    local_tm.tm_mday = day;
    local_tm.tm_mon = month - 1;        // Months start at 0 for tm
    local_tm.tm_year = year - 1900;     // Years since 1900 for tm

    //  Get a timestamp close to (i.e. within 24 hours of) the
    //  desired UTC time.

    time_t utc_ts = mktime(&local_tm);
    if ( utc_ts == -1 ) {
        throw bad_time();
    }

    //  Compute the difference with the desired UTC time...

    int secs_diff = get_utc_timestamp_sec_diff(utc_ts, year, month,
                                               day, hour, minute, second);

    //  ...and adjust the timestamp, if needed.

    if ( secs_diff ) {
        const time_t one_sec = get_sec_diff();
        utc_ts -= one_sec * secs_diff;

        secs_diff = get_utc_timestamp_sec_diff(utc_ts, year, month, day,
                                               hour, minute, second);

        if ( secs_diff ) {

            //  We're pretty unlucky if we get here, but let's check
            //  for a leap second on either side, and give up if not.

            if ( get_utc_timestamp_sec_diff(utc_ts + one_sec, year, month,
                                            day, hour, minute, second) == 0 ) {
               utc_ts += one_sec;
            } else if ( get_utc_timestamp_sec_diff(utc_ts - one_sec, year,
                                     month, day, hour, minute, second) == 0 ) {
               utc_ts -= one_sec;
            } else { 
                throw bad_time();
            }
        }
    }

    return utc_ts;
}


/*
 *  Returns the difference, in seconds, between the UTC time
 *  calculated by calling gmtime() with the provided timestamp,
 *  and the UTC time desired, specified in the other arguments.
 *
 *  This function only returns a good value if the timestamp is less
 *  than 24 hours away from the desired time, so the caller should
 *  make sure it is.
 *
 *  This function may also return a value off by one second if
 *  you're unlucky enough to both have a leap second fall between
 *  the desired UTC time and the provided time stamp, and if you're
 *  on a system which implements leap seconds.
 */

int utctime::get_utc_timestamp_sec_diff(const time_t check_time,
                                        const int year, const int month,
                                        const int day, const int hour,
                                        const int minute, const int second) {

    //  Get a struct tm representing UTC time for the provided
    //  timestamp.

    tm* ptm = gmtime(&check_time);
    if ( ptm == 0 ) {
        throw bad_time();
    }
    tm check_tm = *ptm;

    //  Create a second struct tm representing the desired UTC time.

    tm utc_tm;
    utc_tm.tm_year = year - 1900;
    utc_tm.tm_mon = month - 1;
    utc_tm.tm_mday = day;
    utc_tm.tm_hour = hour;
    utc_tm.tm_min = minute;
    utc_tm.tm_sec = second;

    //  Compare the two and return the difference.

    return tm_intraday_secs_diff(utc_tm, check_tm);
}


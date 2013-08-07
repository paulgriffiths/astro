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
        m_timestamp = get_utc_timestamp(year, month, day,
                                        hour, minute, second);
    } catch(bad_time) {
        throw bad_time_init();
    }
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
 *  Checks whether the provided time_t timestamp yields a UTC
 *  date corresponding with the date and time information provided
 *  when gmtime() is called with it.
 *
 *  Throws bad_time() if cannot get the current time.
 */

bool utctime::check_utc_timestamp(const time_t check_time,
                                  const int year, const int month,
                                  const int day, const int hour,
                                  const int minute, const int second) {
    tm* check_tm = gmtime(&check_time);
    if ( check_tm == 0 ) {
        throw bad_time();
    }

    bool agrees = false;
    if ( check_tm->tm_year + 1900 == year &&
         check_tm->tm_mon + 1 == month &&
         check_tm->tm_mday == day &&
         check_tm->tm_hour == hour &&
         check_tm->tm_min == minute &&
         check_tm->tm_sec == second ) {
        agrees = true;
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

    time_t datum_time = mktime(&datum_day);
    if ( datum_time == -1 ) {
        throw bad_time();
    }

    datum_day.tm_mday += 1;
    time_t tomorrow_time = mktime(&datum_day);
    if ( tomorrow_time == -1 ) {
        throw bad_time();
    }

    return (tomorrow_time - datum_time);
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
 *  Adds an hour to a supplied tm struct.
 */

tm* utctime::tm_increment_hour(tm * changing_tm) {
    if ( changing_tm->tm_hour < 23 ) {
        changing_tm->tm_hour += 1;
    } else {
        changing_tm->tm_hour = 0;
        changing_tm->tm_mday += 1;
        switch ( changing_tm->tm_mon ) {
            case 0:
            case 2:
            case 4:
            case 6:
            case 7:
            case 9:
                if ( changing_tm->tm_mday > 31 ) {
                    changing_tm->tm_mday = 1;
                    changing_tm->tm_mon += 1;
                }
                break;

            case 11:
                if ( changing_tm->tm_mday > 31 ) {
                    changing_tm->tm_mday = 1;
                    changing_tm->tm_mon = 0;
                    changing_tm->tm_year += 1;
                }
                break;

            case 3:
            case 5:
            case 8:
            case 10:
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

    return changing_tm;
}


/*
 *  Deducts an hour from a supplied tm struct.
 */

tm* utctime::tm_decrement_hour(tm * changing_tm) {
    if ( changing_tm->tm_hour > 0 ) {
        changing_tm->tm_hour -= 1;
    } else {
        changing_tm->tm_hour = 23;
        if ( changing_tm->tm_mday > 1 ) {
            changing_tm->tm_mday -= 1;
        } else {
            switch ( changing_tm->tm_mon ) {
                case 0:
                    changing_tm->tm_mday = 31;
                    changing_tm->tm_mon = 11;
                    changing_tm->tm_year -= 1;
                    break;

                case 1:
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                    changing_tm->tm_mday = 31;
                    changing_tm->tm_mon -= 1;
                    break;

                case 4:
                case 6:
                case 9:
                case 11:
                    changing_tm->tm_mday = 30;
                    changing_tm->tm_mon -= 1;
                    break;

                case 2:
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

    return changing_tm;
}


/*
 *  Returns a time_t value which *might* represent the datetime
 *  contained within the supplied struct tm. 
 *
 *  The procedure is:
 *
 *  1. Call mktime() on the supplied struct tm to get a time_t
 *     value for the *local* time using the struct tm supplied.
 *  2. Call gmtime() on that time_t to get a struct tm corresponding
 *     to the UTC date for that time_t.
 *  3. Call mktime() again on the new struct tm, to get a time_t
 *     value.
 *  4. Subtract the second time_t value from the first time_t value
 *     to give a *possible* UTC offset.
 *  5. Add the offset to the first (local) time_t value and return
 *     a *possible* UTC time_t value.
 *
 *  The reason that the result only *may* be right is because the C
 *  standard gives us no way to get a time_t value for a specified
 *  UTC date time, so we have to calculate an offset *at the local
 *  time that matches it*, not at the actual UTC time we're interested
 *  in. While these two offsets will *usually* be the same, they
 *  won't be if DST begins or ends in between the two times.
 *
 *  For instance, DST began in the Eastern United States on March 10,
 *  2013 at what would have been 2:00 local time if the clocks hadn't
 *  jumped straight from 01:59:59 to 03:00:00. Suppose we want to find
 *  the time_t for 06:00 UTC on March 10, 2013. At 06:00 UTC, local
 *  time was 01:00 EST, a five hour offset. At 10:00 UTC, for instance,
 *  local was was 06:00 EDT, only a four hour offset. To calculate the
 *  time_t for 06:00 UTC, this function would:
 *
 *  1. Calculate the time_t for 06:00 *local* time. 
 *  2. Call gmtime() on that time_t, and find that UTC was 10:00, a
 *     four hour offset.
 *  3. Apply that four hour offset in the opposite direction,
 *     and return a time_t corresponding to 06:00 less four hours,
 *     or 02:00 local.
 *
 *  This is not the correct answer, because the UTC offset at
 *  06:00 UTC was four hours, but the UTC offset at 06:00 *local*
 *  was *five* hours. This will only be an issue for somewhere
 *  between 2 and 24 hours each year, depending on location, but
 *  it's enough to be annoying. The caller of this function should
 *  check whether the timestamp actually agrees using the
 *  check_utc_timestamp() function, and take remedial action if
 *  necessary.
 *
 *  Throws bad_time() if cannot get the current time.
 */

time_t utctime::get_fuzzy_utc_timestamp(const tm* const local_tm) {
    tm local_tm_copy = *local_tm; 
    local_tm_copy.tm_isdst = -1;
    time_t l_time = mktime(&local_tm_copy);
    if ( l_time == -1 ) {
        throw bad_time();
    }

    tm* ptm = gmtime(&l_time);
    if ( ptm == 0 ) {
        throw bad_time();
    }

    tm utc_tm = *ptm;
    utc_tm.tm_isdst = local_tm_copy.tm_isdst;
    time_t utc_wrong_way = mktime(&utc_tm);
    if ( utc_wrong_way == -1 ) {
        throw bad_time();
    }
    
    time_t utc_offset = l_time - utc_wrong_way;
    return (l_time + utc_offset);
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

    //  Create a struct tm for the local time using the provided
    //  inputs as if local time equals UTC.

    tm local_tm;
    local_tm.tm_sec = second;
    local_tm.tm_min = minute;
    local_tm.tm_hour = hour;
    local_tm.tm_mday = day;
    local_tm.tm_mon = month - 1;        // Months start at 0 for tm
    local_tm.tm_year = year - 1900;     // Years since 1900 for tm

    //  Using that struct we just created, get a UTC timestamp
    //  for the corresponding UTC time which will *usually* be right.
    //  See comments to get_fuzzy_utc_timestamp() for more information
    //  on when it might *not* be right.

    time_t utc_maybe = get_fuzzy_utc_timestamp(&local_tm);

    //  Check if it actually is right

    if ( !check_utc_timestamp(utc_maybe, year, month,
                              day, hour, minute, second) ) {

        //  The datetime is not what we expected. The standard
        //  library doesn't make it all that easy for us to deal
        //  with times, so we'll resort to a few quick
        //  brute-force calculations.

        bool error = true;

        //  First try the immediately preceding and following hours
        //  for the local time, this should almost always work.

        tm last_hour_tm = local_tm;
        tm_decrement_hour(&last_hour_tm);

        tm next_hour_tm = local_tm;
        tm_increment_hour(&next_hour_tm);

        //  And now loop through them, doing the same calculation
        //  that we tried originally.

        tm* hours[] = {&last_hour_tm, &local_tm, &next_hour_tm};
        for ( int i = 0; i < 3 && error; ++i ) {
            utc_maybe = get_fuzzy_utc_timestamp(hours[i]);
            if ( check_utc_timestamp(utc_maybe, year, month,
                                     day, hour, minute, second) ) {
                error = false;
            }
        }

        if ( error ) {

            //  We still don't have a match. This could happen if
            //  the DST offset is not a whole number of hours. This
            //  is pretty much a doomsday scenario, and the user is
            //  going to pay for living in such a weird place, but
            //  let's loop through each minute to see if we can find
            //  the answer, here. This is worst case 3 * 24 * 60 =
            //  4,320 tests.

            //  We need struct tms for yesterday, today, and tomorrow,
            //  and we need to get a time_t value corresponding to a
            //  single day in order to do it.

            time_t day_t_diff = get_day_diff();

            tm today_tm = local_tm;
            time_t today_time = mktime(&today_tm);
            if ( today_time == -1 ) {
                throw bad_time();
            }

            time_t yes_time = today_time - day_t_diff;
            tm* ptm = localtime(&yes_time);
            if ( ptm == 0 ) {
                throw bad_time();
            }
            tm yesterday_tm = *ptm;

            time_t tom_time = today_time + day_t_diff;
            ptm = localtime(&tom_time);
            if ( ptm == 0 ) {
                throw bad_time();
            }
            tm tomorrow_tm = *ptm;

            //  Since time_t doesn't have to be an integral value,
            //  and possibly because of leap seconds or some other
            //  weirdness, it's conceivable that the seconds and
            //  maybe the minutes in our new struct tms might differ
            //  from the original input, so let's reset them just
            //  to be on the safe side.

            yesterday_tm.tm_min = minute;
            yesterday_tm.tm_sec = second;

            tomorrow_tm.tm_min = minute;
            tomorrow_tm.tm_sec = second;

            //  Now loop through all the minutes in each of the
            //  24 hours in each of the 3 days.

            tm* days[] = {&yesterday_tm, &today_tm, &tomorrow_tm};
            for ( int i = 0; i < 3 && error; ++i ) {
                for ( int hour = 0; hour < 24 && error; ++hour ) {
                    for ( int minute = 0; minute < 60 && error; ++minute ) {
                        days[i]->tm_hour = hour;
                        days[i]->tm_min = minute;

                        utc_maybe = get_fuzzy_utc_timestamp(days[i]);
                        if ( check_utc_timestamp(utc_maybe, year, month,
                                                 day, hour, minute, second) ) {
                            error = false;
                        }
                    }
                }
            }

            if ( error ) {

                //  Well, we tried. We can't find it, so thrown an
                //  exception.

                throw bad_time_init();
            }
        }
    }

    time_t utc_definitely = utc_maybe;
    return utc_definitely;
}
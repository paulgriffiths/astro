/*
 *  utc_time.h
 *  ==========
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to UTCTime() class and associated functions.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_UTC_TIME_H
#define PG_UTC_TIME_H

#include <string>

namespace utctime {

//  Base exception, all custom exceptions thrown by this module
//  are derived from UTCTimeException

class UTCTimeException {
    private:
        std::string m_error_message;

    public:
        explicit UTCTimeException(const std::string& msg =
                                  "No error message")
            : m_error_message(msg) {}
        virtual ~UTCTimeException() {}

        const std::string& what() const { return m_error_message; }
};

//  Thrown when the time cannot be initialized.

class bad_time_init : public UTCTimeException {
    public:
        explicit bad_time_init() :
            UTCTimeException("Couldn't initialize time") {};
};

//  Thrown when the time cannot be obtained.

class bad_time : public UTCTimeException {
    public:
        explicit bad_time() :
            UTCTimeException("Couldn't get time") {};
};


/*
 *  Standalone functions.
 */

time_t get_day_diff();
int tm_compare(const tm& first, const tm& second);
bool is_leap_year(const int year);
tm * tm_increment_day(tm * changing_tm, const int quantity = 1);
tm * tm_increment_hour(tm * changing_tm, const int quantity = 1);
tm * tm_increment_minute(tm * changing_tm, const int quantity = 1);
tm * tm_increment_second(tm * changing_tm, const int quantity = 1);
tm * tm_decrement_day(tm * changing_tm, const int quantity = 1);
tm * tm_decrement_hour(tm * changing_tm, const int quantity = 1);
tm * tm_decrement_minute(tm * changing_tm, const int quantity = 1);
tm * tm_decrement_second(tm * changing_tm, const int quantity = 1);
time_t get_fuzzy_utc_timestamp(const tm* const local_tm);
bool check_utc_timestamp(const time_t check_time,
                         const int year, const int month,
                         const int day, const int hour,
                         const int minute, const int second);
time_t get_utc_timestamp(const int year, const int month,
                         const int day, const int hour,
                         const int minute, const int second);


/*
 *  UTCTime class.
 */

class UTCTime {
    public:
        UTCTime();
        UTCTime(const int year, const int month,
                const int day, const int hour,
                const int minute, const int second);

        std::string time_string() const;
        std::string time_string_inet() const;
        time_t timestamp() const;

    private:
        int m_year;
        int m_month;
        int m_day;
        int m_hour;
        int m_minute;
        int m_second;
        time_t m_timestamp;
};

}           //  namespace utctime

#endif          // PG_UTC_TIME_H

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
#include <ctime>

namespace utctime {

//  Base exception, all custom exceptions thrown by this module
//  are derived from UTCTimeException

class UTCTimeException {
    private:
        std::string m_error_message;

    public:
        explicit UTCTimeException(const std::string msg =
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

//  Thrown when an invalid date is provided to the constructor

class invalid_date : public UTCTimeException {
    public:
        explicit invalid_date(const std::string& msg) :
            UTCTimeException(msg) {};
};


/*
 *  Standalone functions.
 */

bool validate_date(const int year, const int month,
                   const int day, const int hour,
                   const int minute, const int second);
time_t get_day_diff();
time_t get_hour_diff();
time_t get_sec_diff();
int tm_compare(const std::tm& first, const tm& second);
int tm_intraday_secs_diff(const tm& first, const tm& second);
bool is_leap_year(const int year);
std::tm* tm_increment_day(std::tm* changing_tm, const int quantity = 1);
std::tm* tm_increment_hour(std::tm* changing_tm, const int quantity = 1);
std::tm* tm_increment_minute(std::tm* changing_tm, const int quantity = 1);
std::tm* tm_increment_second(std::tm* changing_tm, const int quantity = 1);
std::tm* tm_decrement_day(std::tm* changing_tm, const int quantity = 1);
std::tm* tm_decrement_hour(std::tm* changing_tm, const int quantity = 1);
std::tm* tm_decrement_minute(std::tm* changing_tm, const int quantity = 1);
std::tm* tm_decrement_second(std::tm* changing_tm, const int quantity = 1);
bool check_utc_timestamp(const time_t check_time, int& secs_diff,
                         const int year, const int month,
                         const int day, const int hour,
                         const int minute, const int second);
time_t get_utc_timestamp(const int year, const int month,
                         const int day, const int hour,
                         const int minute, const int second);
int get_utc_timestamp_sec_diff(const time_t check_time,
                               const int year, const int month,
                               const int day, const int hour,
                               const int minute, const int second);


/*
 *  UTCTime class.
 */

class UTCTime {
    public:
        explicit UTCTime();
        explicit UTCTime(const std::tm& utc_tm);
        explicit UTCTime(const int year, const int month,
                         const int day, const int hour,
                         const int minute, const int second);

        std::tm get_tm() const;
        std::string time_string() const;
        std::string time_string_inet() const;
        time_t timestamp() const;

        bool operator<(const UTCTime& rhs) const;
        bool operator>=(const UTCTime& rhs) const;
        bool operator>(const UTCTime& rhs) const;
        bool operator<=(const UTCTime& rhs) const;
        bool operator==(const UTCTime& rhs) const;
        bool operator!=(const UTCTime& rhs) const;

        double operator-(const UTCTime& rhs) const;

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

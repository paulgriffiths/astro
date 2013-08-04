// astrofunc.cpp
// Copyright 2013 Paul Griffiths

#include <sstream>
#include <iomanip>
#include <string>

#include <cmath>
#include <cassert>
#include <ctime>

#include "astrofunc.h"

void deg_to_hms(const double degrees, HMS& hmsout) {
    double norm_degs = normalize_degrees(degrees);
    int total_seconds = floor((norm_degs / 360) * 86400);

    hmsout.hours = total_seconds / 3600;
    hmsout.minutes = (total_seconds - hmsout.hours * 3600) / 60;
    hmsout.seconds = total_seconds - hmsout.hours * 3600 - hmsout.minutes * 60;

    assert(hmsout.hours >= 0);
    assert(hmsout.hours < 24);
    assert(hmsout.minutes >= 0);
    assert(hmsout.minutes < 60);
    assert(hmsout.seconds >= 0);
    assert(hmsout.seconds < 60);
}

void deg_to_dms(const double degrees, DMS& dmsout) {
    int total_seconds = degrees > 0 ? floor(degrees * 3600) :
                                      ceil(degrees * 3600);

    dmsout.degrees = total_seconds / 3600;
    dmsout.minutes = (total_seconds - dmsout.degrees * 3600) / 60;
    dmsout.seconds = total_seconds - dmsout.degrees * 3600 -
                                     dmsout.minutes * 60;
    
    assert(dmsout.minutes > -60);
    assert(dmsout.minutes < 60);
    assert(dmsout.seconds > -60);
    assert(dmsout.seconds < 60);
}

void get_zodiac_info(const double rasc, ZodiacInfo& zInfo) {
    double norm_degs = normalize_degrees(rasc);
    DMS dms;
    deg_to_dms(norm_degs, dms);

    zInfo.right_ascension = norm_degs;
    zInfo.sign_index = dms.degrees / 30;

    assert(zInfo.sign_index >= 0);
    assert(zInfo.sign_index < 12);

    zInfo.sign_name = ZODIAC_SIGNS[zInfo.sign_index];
    zInfo.sign_short_name = ZODIAC_SIGNS_SHORT[zInfo.sign_index];
    zInfo.degrees = dms.degrees % 30;

    assert(zInfo.degrees >= 0);
    assert(zInfo.degrees < 30);

    zInfo.minutes = dms.minutes;
    zInfo.seconds = dms.seconds;
}

double julian_date(const time_t * in_time) {
    double epoch_jdate = 2451545;              // Jan 1 2000 12:00 UTC
    time_t epoch_cal_time = 946728000;         // Jan 1 2000 12:00 UTC

    time_t calc_cal_time = in_time == NULL ? time(NULL) : *in_time;

    double seconds_since_epoch = difftime(calc_cal_time, epoch_cal_time);
    double days_since_epoch = seconds_since_epoch / 86400;

    return epoch_jdate + days_since_epoch;
}

double kepler(const double m_anom, const double ecc) {
    double desired_accuracy = 1e-6;
    double e_anom = m_anom;
    double diff;

    do {
        diff = e_anom - ecc * sin(e_anom) - m_anom;
        e_anom -= diff / (1 - ecc * cos(e_anom));
    } while ( fabs(diff) > desired_accuracy );

    return e_anom;
}

void rec_to_sph(const RectCoords& rcd, SphCoords& scd) {
    scd.right_ascension = degrees(atan2(rcd.y, rcd.x));
    scd.declination = degrees(atan(rcd.z / sqrt(pow(rcd.x, 2) +
                                                pow(rcd.y, 2))));
    scd.distance = sqrt(pow(rcd.x, 2) + pow(rcd.y, 2) + pow(rcd.z, 2));
}

const char * zodiac_sign(const double rasc) {
    ZodiacInfo zInfo;
    get_zodiac_info(rasc, zInfo);
    return zInfo.sign_name;
}

const char * zodiac_sign_short(const double rasc) {
    ZodiacInfo zInfo;
    get_zodiac_info(rasc, zInfo);
    return zInfo.sign_short_name;
}

std::string rasc_to_zodiac(const double rasc) {
    ZodiacInfo zInfo;
    get_zodiac_info(rasc, zInfo);

    std::ostringstream oStream;
    oStream << std::setfill('0');
    oStream << std::setw(2) << zInfo.degrees << zInfo.sign_short_name
            << std::setw(2) << zInfo.minutes;
    
    return oStream.str();
}

std::string rasc_string(const double rasc) {
    HMS hms;
    deg_to_hms(rasc, hms);

    std::ostringstream oStream;
    oStream << std::setfill('0');
    oStream << std::setw(2) << hms.hours << "h "
            << std::setw(2) << hms.minutes << "m "
            << std::setw(2) << hms.seconds << "s";
    
    return oStream.str();
}

std::string decl_string(const double decl) {
    DMS dms;
    deg_to_dms(decl, dms);

    std::ostringstream oStream;
    oStream << std::setfill('0');
    oStream << (decl >= 0 ? "+" : "")
            << std::setw(2) << dms.degrees << "d "
            << std::setw(2) << dms.minutes << "m "
            << std::setw(2) << dms.seconds << "s";
    
    return oStream.str();
}


#include <iostream>
#include <cstdio>

#include "astrofunc.h"
#include "astro.h"

int main(void) {

    double angle = -462.62;

    //  Test normalize_degrees()
    
    normalize_degrees(360.0);
    normalize_degrees(0.0);

    std::cout << "Angle before is: " << angle << std::endl;

    angle = normalize_degrees(angle);

    std::cout << "Angle after is: " << angle << std::endl;

    //  Test deg_to_hms()

    HMS hms;
    deg_to_hms(angle, hms);

    std::cout << "Which is " << hms.hours << " hours, "
              << hms.minutes << " minutes, and " << hms.seconds
              << " seconds." << std::endl;

    //  Test deg_to_dms()

    DMS dms;
    angle = 180.999999999;
    deg_to_dms(angle, dms);

    std::cout << "Angle is now " << angle << " degrees." << std::endl;
    std::cout << "Which is " << dms.degrees << " degrees, "
              << dms.minutes << " minutes, and " << dms.seconds
              << " seconds." << std::endl;

    //  Test get_zodiac_info()

    angle = 98.234;
    deg_to_dms(angle, dms);
    ZodiacInfo zInfo;
    get_zodiac_info(angle, zInfo);

    std::cout << "Angle is now " << angle << " degrees." << std::endl;
    std::cout << "Which is " << dms.degrees << " degrees, "
              << dms.minutes << " minutes, and " << dms.seconds
              << " seconds." << std::endl;
    std::cout << "Sign of " << zInfo.sign_name << " (" << zInfo.sign_short_name
              << ")" << std::endl;
    std::cout << "Zodiac date: " << zInfo.degrees << zInfo.sign_short_name
              << zInfo.minutes << std::endl;

    //  Test julian_date()

    double jdate = julian_date(NULL);
    char temp_char[100] = {0};
    sprintf(temp_char, "%0.5f", jdate);

    std::cout << "Current Julian Date is " << temp_char << std::endl;

    //  Test kepler()

    double m = 27;
    double e = 0.5;
    double e_anom = degrees(kepler(radians(m), e));

    std::cout << "Kepler's solution is " << e_anom << " for 27, 0.5"
              << std::endl;

    //  Test rec_to_sph()

    RectCoords rcd = {5, 7, 3};
    SphCoords scd;
    rec_to_sph(rcd, scd);

    //  Test zodiac_sign()

    angle = 135;

    std::cout << "Zodiac sign for angle " << angle << " is "
              << zodiac_sign(angle) << ", or "
              << zodiac_sign_short(angle)<< " for short." << std::endl;

    // Test rasc_to_zodiac

    std::cout << "Zodiac date for 135 degrees is "
              << rasc_to_zodiac(135) << std::endl;
    std::cout << "Zodiac date for 241.52 degrees is "
              << rasc_to_zodiac(241.51) << std::endl;
    std::cout << "Zodiac date for 423.89 degrees is "
              << rasc_to_zodiac(423.89) << std::endl;

    //  Test rasc_string

    std::cout << "rasc string for 257.38 degrees is "
              << rasc_string(257.38) << std::endl;

    //  Test decl_string

    std::cout << "decl string for 132.91 degrees is "
              << decl_string(132.91) << std::endl;
    std::cout << "decl string for -71.32 degrees is "
              << decl_string(-71.32) << std::endl;

    // Test planet

    Mars myplanet;

    return 0;
}

# C++ astronomical library
# ========================
# Copyright 2013 Paul Griffiths
# Email: mail@paulgriffiths.net
#
# Distributed under the terms of the GNU General Public License.
# http://www.gnu.org/licenses/


# Variables section
# =================

# Executable names
OUT=astro
TESTOUT=unittests

# Compiler executable name
CXX=g++

# Compiler flags
CXXFLAGS=-std=c++98 -pedantic -Wall -Wextra -Weffc++
CXX_POSIX_FLAGS=-Wall -Wextra -Weffc++
CXX_DEBUG_FLAGS=-ggdb -DDEBUG -DDEBUG_ALL
CXX_RELEASE_FLAGS=-O3 -DNDEBUG

# Linker flags
LDFLAGS=
LD_TEST_FLAGS=-lCppUTest -lCppUTestExt

# Object code files
MAINOBJ=main.o
TESTMAINOBJ=tests/unittests.o

OBJS=major_body.o planet.o planets.o astrofunc.o planet_func.o moon.o
OBJS+=utc_time.o

TESTOBJS=tests/test_julian_date.o
TESTOBJS+=tests/test_kepler.o
TESTOBJS+=tests/test_normalize_degrees.o
TESTOBJS+=tests/test_rasc_to_zodiac.o
TESTOBJS+=tests/test_zodiac_sign.o
TESTOBJS+=tests/test_zodiac_sign_short.o
TESTOBJS+=tests/test_planets.o
TESTOBJS+=tests/test_moon.o
TESTOBJS+=tests/test_tm_decrement_hour.o
TESTOBJS+=tests/test_tm_increment_hour.o
TESTOBJS+=tests/test_is_leap_year.o
TESTOBJS+=tests/test_get_utc_timestamp.o
TESTOBJS+=tests/test_get_utc_timestamp_gb.o
TESTOBJS+=tests/test_get_utc_timestamp_eet.o
TESTOBJS+=tests/test_get_utc_timestamp_nsw.o
TESTOBJS+=tests/test_get_utc_timestamp_xxx.o

# Source and clean files and globs
SRCS=$(wildcard *.cpp *.h)
SRCS+=$(wildcard tests/*.cpp)

SRCGLOB=*.cpp *.h
SRCGLOB+=tests/*.cpp

CLNGLOB=astro unittests
CLNGLOB+=*~ *.o *.gcov *.out *.gcda *.gcno
CLNGLOB+=tests/*~ tests/*.o tests/*.gcov tests/*.out tests/*.gcda tests/*.gcno


# Build targets section
# =====================

default: debug

# debug - builds objects with debugging info
.PHONY: debug
debug: CXXFLAGS+=$(CXX_DEBUG_FLAGS)
debug: main

# release - builds with optimizations and without debugging info
.PHONY: release
release: CXXFLAGS+=$(CXX_RELEASE_FLAGS)
release: main

# tests - builds unit tests
.PHONY: tests
tests: CXXFLAGS+=$(CXX_DEBUG_FLAGS)
tests: LDFLAGS+=$(LD_TEST_FLAGS)
tests: testmain

# clean - removes ancilliary files from working directory
.PHONY: clean
clean:
	-@rm $(CLNGLOB) 2>/dev/null

# lint - runs cpplint with specified options
.PHONY: lint
lint:
	@cpplint --verbose=5 --filter=-runtime/references,-build/header_guard,\
-readability/streams,-build/include,-legal/copyright,\
-runtime/threadsafe_fn,-whitespace/blank_line,-runtime/int,\
-build/namespaces \
$(SRCGLOB)

# check - runs cppcheck with specified options
.PHONY: check
check:
	@cppcheck --enable=all $(SRCGLOB)


# Executable targets section
# ==========================

# Main executable
main: $(MAINOBJ) $(OBJS)
	$(CXX) -o $(OUT) $(MAINOBJ) $(OBJS) $(LDFLAGS) 

# Unit tests executable
testmain: $(TESTMAINOBJ) $(TESTOBJS) $(OBJS)
	$(CXX) -o $(TESTOUT) $(TESTMAINOBJ) $(TESTOBJS) $(OBJS) $(LDFLAGS) 


# Object files targets section
# ============================

# Main program

main.o: main.cpp astro.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

major_body.o: major_body.cpp major_body.h astrofunc.h astro_common_types.h \
		planets.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

planets.o: planets.cpp planets.h astro_common_types.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

planet.o: planet.cpp planet.h astro_common_types.h major_body.h astrofunc.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

moon.o: moon.cpp moon.h astrofunc.h astro_common_types.h planet.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

planet_func.o: planet_func.cpp planet_func.h astrofunc.h moon.h planets.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

astrofunc.o: astrofunc.cpp astro_common_types.h astrofunc.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

utc_time.o: utc_time.cpp utc_time.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<


# Unit tests

tests/unittests.o: tests/testmain.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_julian_date.o: tests/test_julian_date.cpp \
	astrofunc.cpp astrofunc.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_kepler.o: tests/test_kepler.cpp \
	astrofunc.cpp astrofunc.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_normalize_degrees.o: tests/test_normalize_degrees.cpp \
	astrofunc.cpp astrofunc.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_rasc_to_zodiac.o: tests/test_rasc_to_zodiac.cpp \
	astrofunc.cpp astrofunc.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_zodiac_sign.o: tests/test_zodiac_sign.cpp \
	astrofunc.cpp astrofunc.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_zodiac_sign_short.o: tests/test_zodiac_sign_short.cpp \
	astrofunc.cpp astrofunc.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_planets.o: tests/test_planets.cpp \
	astrofunc.cpp astrofunc.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_moon.o: tests/test_moon.cpp \
	astrofunc.cpp astrofunc.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_tm_decrement_hour.o: tests/test_tm_decrement_hour.cpp \
	utc_time.cpp utc_time.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_tm_increment_hour.o: tests/test_tm_increment_hour.cpp \
	utc_time.cpp utc_time.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_is_leap_year.o: tests/test_is_leap_year.cpp \
	utc_time.cpp utc_time.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_get_utc_timestamp.o: tests/test_get_utc_timestamp.cpp \
	utc_time.cpp utc_time.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_get_utc_timestamp_gb.o: tests/test_get_utc_timestamp_gb.cpp \
	utc_time.cpp utc_time.h
	$(CXX) $(CXX_POSIX_FLAGS) -c -o $@ $<

tests/test_get_utc_timestamp_eet.o: tests/test_get_utc_timestamp_eet.cpp \
	utc_time.cpp utc_time.h
	$(CXX) $(CXX_POSIX_FLAGS) -c -o $@ $<

tests/test_get_utc_timestamp_nsw.o: tests/test_get_utc_timestamp_nsw.cpp \
	utc_time.cpp utc_time.h
	$(CXX) $(CXX_POSIX_FLAGS) -c -o $@ $<

tests/test_get_utc_timestamp_xxx.o: tests/test_get_utc_timestamp_xxx.cpp \
	utc_time.cpp utc_time.h
	$(CXX) $(CXX_POSIX_FLAGS) -c -o $@ $<


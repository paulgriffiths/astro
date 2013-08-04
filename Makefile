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
CXXFLAGS=-ansi -pedantic -Wall -Wextra -Weffc++
CXX_DEBUG_FLAGS=-ggdb -DDEBUG -DDEBUG_ALL
CXX_RELEASE_FLAGS=-O3 -DNDEBUG

# Linker flags
LDFLAGS=
LD_TEST_FLAGS=-lCppUTest -lCppUTestExt

# Object code files
MAINOBJ=main.o
TESTMAINOBJ=tests/unittests.o

OBJS=base_planet.o planets.o astrofunc.o planet_func.o

TESTOBJS=tests/test_julian_date.o
TESTOBJS+=tests/test_kepler.o
TESTOBJS+=tests/test_normalize_degrees.o
TESTOBJS+=tests/test_rasc_to_zodiac.o
TESTOBJS+=tests/test_zodiac_sign.o
TESTOBJS+=tests/test_zodiac_sign_short.o
TESTOBJS+=tests/test_planets.o

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

base_planet.o: base_planet.cpp base_planet.h astrofunc.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

planets.o: planets.cpp planets.h astrofunc.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

planet_func.o: planet_func.cpp planet_func.h astrofunc.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

astrofunc.o: astrofunc.cpp astrofunc.h
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


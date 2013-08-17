# C++ astronomical library
# ========================
# Copyright 2013 Paul Griffiths
# Email: mail@paulgriffiths.net
#
# Distributed under the terms of the GNU General Public License.
# http://www.gnu.org/licenses/


# Variables section
# =================

# Library and executable names
OUT=libastro.a
TESTOUT=unittests
SAMPLEOUT=sample

# Install paths
LIB_INSTALL_PATH=/home/paul/lib/cpp
INC_INSTALL_PATH=/home/paul/include
HEADERS=astro.h astro_common_types.h astrofunc.h major_body.h
HEADERS+=moon.h planet_func.h planet.h planets.h

# Compiler and archiver executable names
AR=ar
CXX=g++

# Archiver flags
ARFLAGS=rcs

# Compiler flags
UTC_INC_PATH=/home/paul/include
UTC_LIB_PATH=/home/paul/lib/cpp
CXXFLAGS=-std=c++98 -pedantic -Wall -Wextra -Weffc++ -I$(UTC_INC_PATH)
CXX_POSIX_FLAGS=-Wall -Wextra -Weffc++
CXX_DEBUG_FLAGS=-ggdb -DDEBUG -DDEBUG_ALL
CXX_RELEASE_FLAGS=-O3 -DNDEBUG

# Linker flags
LDFLAGS=
LD_TEST_FLAGS=-lCppUTest -lCppUTestExt -lutctime -L$(UTC_LIB_PATH)
LD_TEST_FLAGS+=-lastro -L$(CURDIR)

# Object code files
MAINOBJ=main.o
TESTMAINOBJ=tests/unittests.o

OBJS=major_body.o planet.o planets.o astrofunc.o planet_func.o moon.o

TESTOBJS=tests/test_julian_date.o
TESTOBJS+=tests/test_kepler.o
TESTOBJS+=tests/test_normalize_degrees.o
TESTOBJS+=tests/test_rasc_to_zodiac.o
TESTOBJS+=tests/test_zodiac_sign.o
TESTOBJS+=tests/test_zodiac_sign_short.o
TESTOBJS+=tests/test_planets.o
TESTOBJS+=tests/test_moon.o

# Source and clean files and globs
SRCS=$(wildcard *.cpp *.h)
SRCS+=$(wildcard tests/*.cpp)

SRCGLOB=*.cpp *.h
SRCGLOB+=tests/*.cpp

CLNGLOB=$(OUT) $(TESTOUT) $(SAMPLEOUT)
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

# install - installs library and headers
.PHONY: install
install:
	@if [ ! -d $(INC_INSTALL_PATH)/paulgrif ]; then \
		mkdir $(INC_INSTALL_PATH)/paulgrif; fi
	@echo "Copying library to $(LIB_INSTALL_PATH)..."
	@cp $(OUT) $(LIB_INSTALL_PATH)
	@echo "Copying headers to $(INC_INSTALL_PATH)..."
	@cp $(HEADERS) $(INC_INSTALL_PATH)/paulgrif
	@echo "Done."

# sample - makes sample program
.PHONY: sample
sample: LDFLAGS+=-L$(UTC_LIB_PATH) -L$(LIB_INSTALL_PATH) -lutctime -lastro
sample: main.o
	@echo "Linking sample program..."
	@$(CXX) -o $(SAMPLEOUT) main.o $(LDFLAGS)
	@echo "Done."

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

# Main library
main: $(OBJS)
	@echo "Building library..."
	@$(AR) $(ARFLAGS) $(OUT) $(OBJS)
	@echo "Done."

# Unit tests executable
testmain: $(TESTMAINOBJ) $(TESTOBJS) $(OBJS)
	@echo "Linking unit tests..."
	@$(CXX) -o $(TESTOUT) $(TESTMAINOBJ) $(TESTOBJS) $(OBJS) $(LDFLAGS) 
	@echo "Done."


# Object files targets section
# ============================

# Sample program

main.o: main.cpp
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -I$(INC_INSTALL_PATH) -c -o $@ $<

# Object files for library

major_body.o: major_body.cpp major_body.h astrofunc.h astro_common_types.h \
		planets.h planet.h
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

planets.o: planets.cpp planets.h astro_common_types.h major_body.h planet.h
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

planet.o: planet.cpp planet.h astro_common_types.h astrofunc.h
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

moon.o: moon.cpp moon.h astrofunc.h astro_common_types.h planet.h
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

planet_func.o: planet_func.cpp planet_func.h astrofunc.h moon.h planets.h \
	planet.h astro_common_types.h major_body.h
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

astrofunc.o: astrofunc.cpp astro_common_types.h astrofunc.h
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c -o $@ $<


# Unit tests

tests/unittests.o: tests/testmain.cpp
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_julian_date.o: tests/test_julian_date.cpp astrofunc.h \
	astro_common_types.h
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_kepler.o: tests/test_kepler.cpp astrofunc.h \
	astro_common_types.h
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_normalize_degrees.o: tests/test_normalize_degrees.cpp astrofunc.h \
	astro_common_types.h
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_rasc_to_zodiac.o: tests/test_rasc_to_zodiac.cpp astrofunc.h \
	astro_common_types.h
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_zodiac_sign.o: tests/test_zodiac_sign.cpp astrofunc.h \
	astro_common_types.h
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_zodiac_sign_short.o: tests/test_zodiac_sign_short.cpp astrofunc.h \
	astro_common_types.h
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_planets.o: tests/test_planets.cpp astrofunc.h astro_common_types.h \
	planet.h major_body.h planets.h
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_moon.o: tests/test_moon.cpp astrofunc.h astro_common_types.h \
	planet.h moon.h
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

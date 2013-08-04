/*
 *
 *  testmain.cpp
 *  ============
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Unit test runner for Prisoners' Dilemma simulation.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#include <iostream>
#include <CppUTest/CommandLineTestRunner.h>

int main(int argc, char ** argv) {
    MemoryLeakWarningPlugin::turnOffNewDeleteOverloads();
    return CommandLineTestRunner::RunAllTests(argc, argv);
}

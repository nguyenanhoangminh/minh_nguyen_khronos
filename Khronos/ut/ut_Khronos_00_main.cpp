/** @file ut_khronos_00_main.cpp
	@author Garth Santor
	@date 2016-09-30
	@version 1.1.0
	@note C++ 11/vc14
	@brief Khronos library unit test main module.
*/

#define BOOST_TEST_MODULE square_list_unit_test
#include "ut_Khronos.hpp"
#include <iostream>
#include <iomanip>
using namespace std;



/** Unit test build info. */
BOOST_AUTO_TEST_CASE(ut_build_info) {
	double mscVersion = _MSC_VER / 100.0;
	cout << "ut-khronos version " UT_VERSION "\n"
		"TEST PHASE = " << TEST_PHASES << "\n"
		"MSC Version: " << fixed << setprecision(2) << mscVersion << "\n"
		"Last Build: " __DATE__ " - " __TIME__ "\n" << endl;

	PhaseList<>::set_phases(TEST_PHASES);
}


/*============================================================================

Revision History

Version 1.1.0: 2016-09-30
Updated: Phase List

Version 1.0.0: 2015-09-21

==============================================================================
Copyright Garth Santor, 2015

The copyright to the computer program(s) herein
is the property of Garth Santor, Canada.
The program(s) may be used and/or copied only with
the written permission of Garth Santor
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
============================================================================*/
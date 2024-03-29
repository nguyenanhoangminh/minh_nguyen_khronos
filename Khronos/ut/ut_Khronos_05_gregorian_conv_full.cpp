/** @file ut_khronos_05_gregorian_conv_full.cpp

	@author Garth Santor
	@date 2016-09-30
	@version 1.1.0
	@note C++ 11/vc14
	@brief Khronos library jd to Gregorian functions unit test.
*/

#include <khronos.hpp>
#include "ut_Khronos.hpp"
using namespace std;



#if defined(FULL_TEST)
#if PHASE_115 && TEST_PHASES>=115
/**	Check all conversions from the lowest Proleptic Gregorian date, until a day well in the future. */
BEGIN_PHASE(115, test_gregorian_full) {
	using namespace khronos;

	cout << "Starting Gregorian FULL_TEST: ";
	auto low = gregorian_to_jd(4800_BCE, January, 1);
	auto high = gregorian_to_jd(4800_CE, January, 1);
	for (auto jd = low; jd <= high; jd += 0.125) {
		year_t year;
		month_t month;
		day_t day;
		jd_to_gregorian(jd, year, month, day);
		auto result = gregorian_to_jd(year, month, day);
		BOOST_CHECK_EQUAL(jd_to_jdn(jd)-0.5, result);
		hour_t hours;
		minute_t minutes;
		second_t seconds;
		jd_to_gregorian(jd, year, month, day, hours, minutes, seconds);
		result = gregorian_to_jd(year, month, day, hours, minutes, seconds);
		BOOST_CHECK_CLOSE(jd, result,0.000'01);
	}
	cout << "... completed\n";
} END_PHASE()
#endif
#endif



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

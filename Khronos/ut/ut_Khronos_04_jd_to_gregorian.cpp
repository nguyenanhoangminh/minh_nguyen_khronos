/** @file ut_khronos_04_jd_to_gregorian.cpp

	@author Garth Santor
	@date 2016-09-30
	@version 1.1.0
	@note C++ 11/vc14
	@brief Khronos library jd to Gregorian functions unit test.
	*/

#include <khronos.hpp>
#include "ut_Khronos.hpp"

#include <iomanip>
#include <sstream>
using namespace std;

#if TEST_PHASES>=9
using namespace khronos;
#endif





#if PHASE_9 && TEST_PHASES>=9
/**	Test known JD to Gregorian conversions. */
BEGIN_PHASE(9, test_jd_to_gregorian) {

	auto test = [](year_t year, month_t month, day_t day, jd_t jd, int line) {
		year_t y;
		month_t m;
		day_t d;
		jd_to_gregorian(jd, y, m, d);

		ostringstream ossY;
		ossY << "y(" << y << ") != year(" << year << " from line: " << line;
		BOOST_CHECK_MESSAGE(y == year, ossY.str());

		ostringstream ossM;
		ossM << "m(" << m << ") != month(" << month << " from line: " << line;
		BOOST_CHECK_MESSAGE(m == month, ossM.str());

		ostringstream ossD;
		ossD << "d(" << d << ") != day(" << day << " from line: " << line;
		BOOST_CHECK_MESSAGE(d == day, ossD.str());
	};

	test(4714_BCE, November, 24, -0.5, __LINE__);			// beginning of the Julian Epoch
	test(1_CE, January, 1, GREGORIAN_EPOCH, __LINE__);		// January 1, 1 CE
	test(1582_CE, October, 15, 2'299'160.5, __LINE__);		// Gregorian adoption date Spain, Portugal, Polish-Lithuanian Commonwealth, Papal
	test(1582_CE, December, 20, 2'299'226.5, __LINE__);		// Gregorian adoption date France
	test(1752_CE, September, 14, 2'361'221.5, __LINE__);		// Gregorian adoption date British Empire
	test(1858_CE, November, 16, 2'400'000 - 0.5, __LINE__);
	test(2012_CE, September, 14, 2'456'184.5, __LINE__);
	test(2132_CE, August, 31, 2'500'000 - 0.5, __LINE__);


	auto test2 = [](year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second, jd_t jd, int line) {
		year_t y;
		month_t m;
		day_t d;
		hour_t h;
		minute_t mi;
		second_t s;
		jd_to_gregorian(jd, y, m, d, h, mi, s);

		ostringstream ossY;
		ossY << "y(" << y << ") != year(" << year << " from line: " << line;
		BOOST_CHECK_MESSAGE(y == year, ossY.str());

		ostringstream ossM;
		ossM << "m(" << m << ") != month(" << month << " from line: " << line;
		BOOST_CHECK_MESSAGE(m == month, ossM.str());

		ostringstream ossD;
		ossD << "d(" << d << ") != day(" << day << " from line: " << line;
		BOOST_CHECK_MESSAGE(d == day, ossD.str());

		ostringstream ossH;
		ossH << "h(" << h << ") != hour(" << hour << " from line: " << line;
		BOOST_CHECK_MESSAGE(h == hour, ossH.str());

		ostringstream ossMi;
		ossMi << "mi(" << mi << ") != minute(" << minute << " from line: " << line;
		BOOST_CHECK_MESSAGE(mi == minute, ossMi.str());

		ostringstream ossS;
		ossS << "s(" << s << ") != second(" << second << " from line: " << line;
		BOOST_CHECK_MESSAGE(s == second, ossS.str());
	};
	test2(2132_CE, August, 31, 12, 0, 0, 2'500'000, __LINE__);
	test2(2132_CE, August, 31, 6, 0, 0, 2'500'000 - 0.25, __LINE__);
	test2(2132_CE, August, 31, 18, 0, 0, 2'500'000 + 0.25, __LINE__);
	test2(2132_CE, August, 31, 12, 0, 1, 2'500'000 + 1.0 / (24 * 60 * 60), __LINE__);
} END_PHASE()
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

/**	@file Julian_to_jd.cpp
	@author Minh Nguyen
	@date 2019-10-14

	Date and time library Julian conversion implementations.
	*/

#include <khronos/julian_calendar.hpp>

namespace khronos {
	// convert jd to julian
	void  jd_to_julian(jd_t jd, year_t& year, month_t& month, day_t& day)
	{
		int a = (int)(floor(jd + 0.5));
		int b = a + 1524;
		int c = (int)(floor((b - 122.1) / 365.25));
		int d = (int)(floor(365.25 * c));
		int e = (int)(floor(((double)(b) - d) / 30.6001));
		if (e < 14)
		{
			month = e - 1;
		}
		else
		{
			month = e - 13;
		}
		if (month > 2)
		{
			year = (year_t)(c) - 4716;
		}
		else
		{
			year = (year_t)(c) - 4715;
		}
		day = b - d - (int)(floor(30.6001 * e));
	}
	// convert jd to julian with hms
	void  jd_to_julian(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second)
	{
		jd_to_julian(jd, year, month, day);
		tod_t tod = (jd + 0.5) - floor(jd + 0.5);
		hms(tod, hour, minute, second);	
	}

}
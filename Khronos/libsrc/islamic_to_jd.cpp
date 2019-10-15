/**	@file Islamic_to_jd.cpp
	@author Minh Nguyen
	@date 2019-10-14

	Islamic calendar conversion implementations.
	*/

#include <khronos/islamic_calendar.hpp>
namespace khronos {

	// convert islamic to jd
	jd_t  islamic_to_jd(year_t year, month_t month, day_t day)
	{
		return day +//16
			ceil(29.5 * (month - 1.0)) +//206.5==207
			(year - 1) * 354 +//-1-5498//-5499//-1946646
			floor((3 + (11 * year)) / 30.0) +//-2016
			ISLAMIC_EPOCH - 1;//
	}
	//convert islamic to jd with (hms)
	jd_t  islamic_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second)
	{
		jd_t jdv = islamic_to_jd(year, month, day);
		tod_t todv = tod(hour, minute, second);
		if (todv >= 0.5)
			todv = todv - 1;
		return jdv + todv;
	}
	void  jd_to_islamic(jd_t jd, year_t& year, month_t& month, day_t& day)
	{
		jd = floor(jd) + 0.5;
		year = (int)(floor((30 * (jd - ISLAMIC_EPOCH) + 10646) / 10631));
		month = std::min(12, (int)(ceil((jd - (29 + islamic_to_jd(year, 1, 1))) / 29.5)) + 1);
		day = (int)(jd - islamic_to_jd(year, month, 1) + 1);
	}
	void  jd_to_islamic(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second)
	{
		jd_to_islamic(jd, year, month, day);
		tod_t tod = (jd + 0.5) - floor(jd + 0.5);
		hms(tod, hour, minute, second);
	}
}
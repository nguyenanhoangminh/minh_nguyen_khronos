/**	@file Hebrew_to_jd.cpp
	@author Minh Nguyen
	@date 2019-10-14

	Hebrew calendar conversion implementations.
	*/

#include <khronos/hebrew_calendar.hpp>

namespace khronos {
	// convert hebrew to jd
	jd_t  hebrew_to_jd(year_t year, month_t month, day_t day)
	{
		jd_t jdn = hebrewEpoch + delayOfWeek(year) + delayAdjacentYear(year) + day + 1;
		if (month < 7)
		{
			for (month_t mon = 7; mon <= hebrew_months_in_year(year); mon++) {
				jdn += hebrew_days_in_month(year, mon);
			}
			for (month_t mon = 1; mon < month; mon++) {
				jdn += hebrew_days_in_month(year, mon);
			}
		}
		else
		{
			for (month_t mon = 7; mon < month; mon++) {
				jdn += hebrew_days_in_month(year, mon);
			}
		}
		return jdn;
	}
	//convert hebrew to jd with (hms)
	jd_t  hebrew_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second)
	{
		jd_t jdv = hebrew_to_jd(year, month, day);
		tod_t todv = tod(hour, minute, second);
		if (todv >= 0.5)
			todv--;
		return jdv + todv;
	}
	// convert jd to hebrew
	void  jd_to_hebrew(jd_t jd, year_t& year, month_t& month, day_t& day)
	{
		jd = floor(jd) + 0.5;
		int count = (int)(floor(((jd - hebrewEpoch) * 98496.0) / 35975351.0));
		year = (year_t)(count)-1;
		int i = count;
		day = day_t((jd - hebrew_to_jd(year, month, 1))) + 1;
		while (jd >= hebrew_to_jd(i, 7, 1))
		{
			year++;
			i++;
		}
		int first = (jd < hebrew_to_jd(year, 1, 1)) ? 7 : 1;
		month = first;
		i = first;
		while (jd > hebrew_to_jd(year, i, hebrew_days_in_month(year, i)))
		{
			month++;
			i++;
		}
		day = (int)(floor(jd - hebrew_to_jd(year, month, 1) + 1));
	}
	// convert jd to hebrew with (hms)
	void  jd_to_hebrew(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second)
	{
		jd_to_hebrew(jd, year, month, day);
		tod_t tod = (jd + 0.5) - floor(jd + 0.5);
		hms(tod, hour, minute, second);
	}
}
/*
khronos\gregorian_to_jdn.cpp
(c) Minh Nguyen
Last Updated:  2019-10-13

Khronos library 'gregorian::to_jdn' implementation.
*/


#include <khronos/gregorian_calendar.hpp>
namespace khronos {
	//convet gregorian to jd
	jd_t gregorian_to_jd(year_t year, month_t month, day_t day)
	{
		int a = (int)((14 - month) / 12);
		int y = (int)(year + 4800 - a);
		int m = (int)(month + 12 * a - 3);
		return (static_cast<jd_t>(day) + (153 * m + 2) / 5 + 365.0 * y + y / 4 - y / 100 + y / 400 - 32045.5);
	}
	//convet gregorian to jd with hms
	jd_t gregorian_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second)
	{
		return gregorian_to_jd(year, month, day) + tod(hour, minute, second);
	}
}
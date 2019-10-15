/**	@file Jdn.cpp
	@author Garth Santor
	@date 2012-09-16

	Date and time library to_string method implementations.
	*/


#include <khronos/julian_day.hpp>
#include <khronos/gregorian_calendar.hpp>
#include <ctime>
#include <sstream>
using namespace std;

namespace khronos {
	jd_t jd_to_jdn(jd_t jd)
	{
		return floor(jd + 0.5);
	}
	/**	Jd default constructor.  Initialize to the current local time. */
	Jd::Jd() {
		time_t nowTime = time(NULL);
		struct tm tmNow;
		localtime_s(&tmNow, &nowTime);
		jd_ = gregorian_to_jd(
			year_t(tmNow.tm_year) + 1900, month_t(tmNow.tm_mon + 1), day_t(tmNow.tm_mday),
			hour_t(tmNow.tm_hour), minute_t(tmNow.tm_min), second_t(tmNow.tm_sec));
	}
	Jd::Jd(now_t t)
	{
		time_t nowTime = time(NULL);
		struct tm tmNow;
		localtime_s(&tmNow, &nowTime);
		if (t == 0)
		{
			jd_ = gregorian_to_jd(year_t(tmNow.tm_year) + 1900, month_t(tmNow.tm_mon + 1), day_t(tmNow.tm_mday));
		}
		else
		{
			jd_ = gregorian_to_jd(
				year_t(tmNow.tm_year) + 1900, month_t(tmNow.tm_mon + 1), day_t(tmNow.tm_mday),
				hour_t(tmNow.tm_hour), minute_t(tmNow.tm_min), second_t(tmNow.tm_sec));
		}
	}
	/** Print the Julian Day as a string. */
	std::string Jd::to_string() const {
		ostringstream oss;
		oss << "JD " <<jd_;
		return oss.str();
	}

	void jd_to_gregorian(jd_t jd, year_t& year, month_t& month, day_t& day) 
	{
		jd = floor(jd - 0.5) + 0.5;
		long long a = static_cast<long long>(jd + 0.5) + 32044;
		long long b = (4 * a + 3) / 146097;
		long long c = a - b * 146097 / 4;
		long long d = (4 * c + 3) / 1461;
		long long e = c - 1461 * d / 4;
		long long m = (5 * e + 2) / 153;
		day = static_cast<day_t>(e - (153 * m + 2) / 5 + 1);
		month = static_cast<month_t>(m + 3 - 12 * (m / 10));
		year = b * 100 + d - 4800 + m / 10;
	}
	void jd_to_gregorian(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second)
	{
		jd_to_gregorian(jd, year, month, day);
		tod_t tod = (jd + 0.5) - floor(jd + 0.5);
		hms(tod, hour, minute, second);
		return;
	}
	void hms(tod_t tod,hour_t& hour, minute_t& minute, second_t& second)
	{
		int secondsInDay = (int)(floor(tod * SECONDS_PER_DAY + 0.5));
		hour = (int)(secondsInDay / 3600);
		minute = (int)(secondsInDay / 60 % 60);
		second = (int)(secondsInDay % 60);
	}

} // end-of-namespace khronos
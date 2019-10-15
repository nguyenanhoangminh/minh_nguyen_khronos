/**	@file Hebrew.cpp
	@author Minh Nguyen
	@date 2019-10-12

	Hebrew calendar class implementation.
	*/

#include <khronos/hebrew_calendar.hpp>
#include<iostream>
#include <sstream>
namespace khronos
{
	//constructor and hebrew function
	// generate current time and day 
	Hebrew::Hebrew(now_t t)
	{
		//call gregogrian current date and time 
		Gregorian g(t);
		from_jd(g.to_jd());//convert to jd and from jd convert to hebrew

	}
	// generate current time and day 
	Hebrew::Hebrew()
	{
		//call gregogrian current date and time 
		Gregorian g;
		from_jd(g.to_jd());//convert to jd and from jd convert to hebrew
	}
	// constructor convert jd to hebrew
	Hebrew::Hebrew(Jd const& jd) 
	{
		from_jd(jd.jd());
	}
	// check whether the year is a leap year
	bool is_hebrew_leapyear(year_t year)
	{
		return utility::mod((int)((year * 7) + 1), 19) < 7;
	}
	// caculate the delay by week
	day_t  delayOfWeek(year_t year)
	{
		int months, day, parts;
		jd_t temp = floor(((235.0 * year) - 234.0) / 19.0);
		months = (int)(temp);
		parts = 12084 + (13753 * months);
		//
		day = (months * 29) + (int)(floor(parts / 25920.0));

		if (3 * (day + 1)% 7 < 3) 
		{
			day++;
		}
		return day;
	}
	day_t  delayAdjacentYear(year_t year)
	{
		day_t last, present, next;

		last = delayOfWeek(year - 1);
		present = delayOfWeek(year);
		next = delayOfWeek(year + 1);

		return ((next - present) == 356) ? 2 :
			(((present - last) == 382) ? 1 : 0);
	}
	// find how many month in a specific year
	month_t hebrew_months_in_year(year_t year)
	{
	     return is_hebrew_leapyear(year) ? 13 : 12;
	}
	// find how many day in a specific month
	day_t hebrew_days_in_month(year_t year, month_t month)
	{
		//  First of all, dispose of fixed-length 29 day months
		if (month == 2 || month == 4 || month == 6 || month == 10 || month == 13)
			return 29;
		//  If it's not a leap year, Adar has 29 days
	    if (month == 12 && !is_hebrew_leapyear(year))
			return 29;
		//  If it's Heshvan, days depend on length of year
	    if (month == 8 && hebrew_days_in_year(year)% 10 != 5)
			return 29;
		//  Similarly, Kislev varies with the length of year
	    if (month == 9 && hebrew_days_in_year(year)% 10 == 3)
			return 29;
		//30 day month
			return 30;
	}
	//find out how many day in a spicific year
	day_t hebrew_days_in_year(year_t year)
	{
		return (int)(hebrew_to_jd(year + 1, 7, 1) - hebrew_to_jd(year, 7, 1));
	}
	// print out hebrew calendar
	std::string Hebrew::to_string() const {
		std::ostringstream oss;
		// day of week
		oss << hebrew_month_name(month_) << ' ' << (unsigned)day_ << ' ';
		oss << year_;
		if (hour_ == 0 && minute_ == 0 && second_ == 0)
		{
			oss << ", 12:00:00 am";
		}
		else
		{
			if (hour_ > 12)
			{
				oss << ", " << hour_ - 12 << ":";
				if (minute_ < 10)
					oss << 0 << minute_ << ":";
				else
					oss << minute_ << ":";
				if (second_ < 10)
					oss << 0 << second_;
				else
					oss << second_;
				oss << " pm";
			}
			else if (hour_ < 12)
			{
				oss << ", " << hour_ << ":";
				if (minute_ < 10)
					oss << 0 << minute_ << ":";
				else
					oss << minute_ << ":";
				if (second_ < 10)
					oss << 0 << second_;
				else
					oss << second_;
				oss << " am";

			}
			else
			{
				oss << ", " << hour_ << ":";
				if (minute_ < 10)
					oss << 0 << minute_ << ":";
				else
					oss << minute_ << ":";
				if (second_ < 10)
					oss << 0 << second_;
				else
					oss << second_;
				oss << " pm";
			}
		}

		return oss.str();
	}

}
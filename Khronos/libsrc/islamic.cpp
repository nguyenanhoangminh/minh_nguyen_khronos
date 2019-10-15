/**	@file Islamic.cpp
	@author Garth Santor
	@date 2013-09-20

	Islamic calendar class implementation.
	*/
#include <ctime>
#include <khronos/islamic_calendar.hpp>
#include<iostream> 
#include <sstream>
namespace khronos
{
	// islamic constructor and function
	// generate current time and day 
	Islamic::Islamic(now_t t)
	{
		Gregorian g(t);		//call gregogrian current date and time 
		from_jd(g.to_jd());//convert it to jd and from jd convert to islamic
	}
	// generate current time and day 
	Islamic::Islamic()
	{
		Gregorian g;//call gregogrian current date and time 
		from_jd(g.to_jd());//convert it to jd and from jd convert to islamic
	}
	// constructor convert Jd obj to Islamic
	Islamic::Islamic(Jd const& jd) {
		from_jd(jd.jd());
	}
	// print out islamic calander
	std::string Islamic::to_string() const {
		std::ostringstream oss;
		// day of week
		oss << civil::islamic_day_name(day_of_week(to_jd())+1) << ", ";
		oss << islamic_month_name(month_) << ' ' << (unsigned)day_ << ' ';
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


	// check whether the year is a leap year
	bool is_islamic_leapyear(year_t year)
	{
		return  ((11 * year + 14)% 30) < 11;
	}


}
/**	@file Julian.cpp
	@author Garth Santor
	@date 2013-09-19

	Julian calendar class implementation.
	*/

#include <ctime>
#include <sstream>
#include <khronos/julian_calendar.hpp>
namespace khronos
{
	// julian constructor and function
	//generate current date and time
	Julian::Julian(now_t t)
	{
		Gregorian g(t);// generate current date and time in gregogrian calandar
		from_jd(g.to_jd());//convert it to jd and from jd convert to julian
	
	}
	//generate current date and time
	Julian::Julian()
	{
		Gregorian g;// generate current date and time in gregogrian calandar
		from_jd(g.to_jd());//convert it to jd and from jd convert to julian
	}
	//constructo convert jd objec to julian
	Julian::Julian(Jd const& jd) {
		
		from_jd(jd.jd());
	}
	// print out julian calandar
	std::string Julian::to_string() const {
		std::ostringstream oss;
		// day of week
		oss << civil::day_name(day_of_week(to_jd())) << ", ";
		oss << gregorian_month_name(month_) << ' ' << (unsigned)day_ << ' ';
		if (year_ <= 0)
			oss << (-year_ + 1) << " BC";
		else
			oss << year_ << " AD";
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
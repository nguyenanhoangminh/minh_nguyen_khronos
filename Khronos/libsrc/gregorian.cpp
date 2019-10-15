/**	@file gregorian.cpp
	@author Minh Nguyen
	@date 2019-14-10

	Gregorian calendar class implementation.
	*/
#include <ctime>
#include <sstream>

#include <khronos/gregorian_calendar.hpp>
namespace khronos {
	//class Gregorian constructor and function
	// constructor with Jd as a parameter
	Gregorian::Gregorian(Jd const& jd) {
		from_jd(jd.jd());
	}
	// constructor generate current date and time
	Gregorian::Gregorian(now_t t) 
	{
		time_t nowTime = time(NULL);
		struct tm tmNow;
		localtime_s(&tmNow, &nowTime);
		if (t == 0)
		{
			year_ = year_t(tmNow.tm_year) + 1900;
			month_ = month_t(tmNow.tm_mon) + 1;
			day_ = day_t(tmNow.tm_mday);

		}
		else
		{
			year_ = year_t(tmNow.tm_year) + 1900;
			month_ = month_t(tmNow.tm_mon) + 1;
			day_ = day_t(tmNow.tm_mday);
			hour_ = hour_t(tmNow.tm_hour);
			minute_ = minute_t(tmNow.tm_min);
			second_ = second_t(tmNow.tm_sec);
		}
	}
	// constructor generate current date and time
	Gregorian::Gregorian()
	{
		time_t nowTime = time(NULL);
		struct tm tmNow;
		localtime_s(&tmNow, &nowTime);
		
			year_ = year_t(tmNow.tm_year) + 1900;
			month_ = month_t(tmNow.tm_mon) + 1;
			day_ = day_t(tmNow.tm_mday);
			hour_ = hour_t(tmNow.tm_hour);
			minute_ = minute_t(tmNow.tm_min);
			second_ = second_t(tmNow.tm_sec);
	}
	// print out gregorian calandar
	std::string Gregorian::to_string() const {
		std::ostringstream oss;
		// day of week
		oss << civil::day_name(day_of_week(to_jd())) << ", ";
		//oss << civil_weekday_codes_long(to_jd())<<", ";
		oss << gregorian_month_name(month_) << ' ' << (unsigned)day_ << ' ';
		if (year_ <= 0)
			oss << (-year_ + 1) << " BCE";
		else
			oss << year_ << " CE";
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
					oss  << second_;
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
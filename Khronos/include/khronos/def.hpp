#pragma once

/** @file: def.hpp
@author Minh Nguyen
 @date 2019-10-12
 @version 0.1
@note Developed for Visual C++ 7.0/GCC 3.2
@brief Implementation of …
 */
/*
khronos\def.hpp
(c) Garth Santor
Created: 2015-09-22
Last Updated: 2015-09-22

Khronos library definitions.
*/

namespace khronos {
	// Note: fundamental data types are signed to simplifies subtractions. * /
	using second_t = double;
	using minute_t = int;
	using hour_t = int;
	using jd_t = double;		// Julian date (JD)

	using tod_t = double;

	using day_t = int;
	using month_t = int;
	using year_t = long long;

	/** Indicates the 'now' type used by default constructors. */
	enum now_t { NOTIMEOFDAY = 0, WTIMEOFDAY };

	// VALUES
	double constexpr EARTH_ORBITAL_PERIOD_DAYS = 365.256'363'004;

	
	/* UDL - converts am hour to 24 base hour . */
	constexpr hour_t operator ""_am(unsigned long long hour) { //h_am, h = {0, 12}

		//logic
		if (hour == 12)
			return 0;
		else
			return static_cast<hour_t>(hour);
	}
	/* UDL - converts pm hour to 24 base hour . */
	constexpr hour_t operator ""_pm(unsigned long long hour) { //h_pm

		//logic
		if (hour == 12)
			return 12;
		else
			return static_cast<hour_t>(hour + 12);
	}
	// class for day
	class days {
	private:
		day_t day_;
	public:
		constexpr days(day_t day) : day_(day) {}
		constexpr day_t day() const { return day_; }

	};
	// class for week
	class weeks {
	private:
		day_t week_;
	public:
		constexpr weeks(day_t week) : week_(week) {}
		constexpr day_t week() const { return week_; }
	};
	//class for month
	class months {
	private:
		month_t month_;
	public:
		constexpr months(month_t month) : month_(month) {}
		constexpr month_t month() const { return month_; }
	};
	// class for year
	class years {
	private:
		double year_;
	public:
		constexpr years(double year) : year_(year) {}
		constexpr double year() const { return year_; }

	};
} // end-of-namespace khronos

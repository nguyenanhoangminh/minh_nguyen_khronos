#pragma once
#include <khronos/def.hpp>
#include <khronos/calendar.hpp>
#include <khronos/timeofday.hpp>

#include <khronos/gregorian_calendar.hpp>
/** @file: julian_calendar.hpp
@author Minh Nguyen
 @date 2019-10-12
 @version 0.1
@brief Implementation of Julian calendar functions and class declaration.
 */

namespace khronos {
	jd_t constexpr JULIAN_EPOCH = 1'721'423.5;
	/* UDL - converts a Julian year BC to an astronomical Julian year. */
	constexpr year_t operator ""_BC(unsigned long long year)
	{
		return 1 - year;
	}
	//calculate jd by julian
	constexpr jd_t  julian_to_jd(year_t year, month_t month, day_t day)
	{
		int a = (14 - month) / 12;
		int	y = (int)(year)+4800 - a;
		int	m = month + 12 * a - 3;
		return ((double)(day)+(153 * m + 2) / 5 + 365.0 * y + y / 4 - 32083.5);
	}
	//calculate jd by julian with (hms)
	constexpr jd_t  julian_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second)
	{
		jd_t jdv = julian_to_jd(year, month, day);
		tod_t todv = tod(hour, minute, second);
		return jdv + todv;
	}
	// calculate julian by jd
	void  jd_to_julian(jd_t jd, year_t& year, month_t& month, day_t& day);
	void  jd_to_julian(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second);
	// class Julian
	class Julian {
	private:
		// class properties 
		year_t year_ = 0;
		month_t month_ = 0;
		day_t day_ = 0;
		hour_t   hour_ = 0;
		minute_t minute_ = 0;
		second_t second_ = 0;
	//constructor
	public:
		constexpr Julian(year_t year, month_t month, day_t day) : year_(year), month_(month), day_(day) {}
		constexpr Julian(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second) : year_(year),
			month_(month), day_(day), hour_(hour), minute_(minute), second_(second) {}
		Julian(now_t t);
		Julian();
		Julian(Jd const& d);
		//method
		void from_jd(jd_t jd) { jd_to_julian(jd, year_, month_, day_); }
		jd_t to_jd() const { return julian_to_jd(year_, month_, day_); }
	public:
		constexpr year_t year() const { return year_; }
		constexpr month_t month() const { return month_; }
		constexpr day_t day() const { return day_; }
		constexpr hour_t hour() const { return hour_; }
		constexpr minute_t minute() const { return minute_; }
		constexpr second_t second() const { return second_; }
		/**	Assign and convert from Jd type to Gregorian type. */
		Julian& operator = (Jd const& jd) {
			this->hour_ = 0;
			this->minute_ = 0;
			this->second_ = 0;
			from_jd(jd.jd());
			return *this;
		}
		/**	Implicit cast to Jd class. */
		operator Jd () const { return Jd(to_jd()); } //test case 24
		std::string to_string() const;
	};
	// overloading << operator
	inline std::ostream& operator << (std::ostream& os, Julian const& g) {
		return os << g.to_string();
	}
	// compare Gregorian and julian
	inline bool operator == (Gregorian const& lhs, Julian const& rhs)
	{
		 return(julian_to_jd(rhs.year(),rhs.month(),rhs.day())== lhs.to_jd());
	}
	// compare julian and Gregorian
	inline bool operator == (Julian const& lhs, Gregorian const& rhs)
	{
		return(julian_to_jd(lhs.year(), lhs.month(), lhs.day()) == rhs.to_jd());
	}
	//add day
	inline Julian operator + (Julian const& date, days const& day)
	{
		year_t y = date.year();
		month_t m = date.month();
		day_t d = date.day() + day.day();
		day_t dom = civil::days_in_month(m, is_julian_leapyear(y));
		while (d > dom) {
			d -= dom;
			if (++m > 12) {
				++y;
				m = 1;
			}
			dom = civil::days_in_month(m, is_julian_leapyear(y));
		}
		return Julian(y, m, d, date.hour(), date.minute(), date.second());
	}
	//subtract day
	inline Julian operator - (Julian const& date, days const& day)
	{
		year_t y = date.year();
		month_t m = date.month();
		day_t d = date.day() - day.day();
		day_t dom = civil::days_in_month(m, is_julian_leapyear(y));
		while (d < 1) {
			d += dom;
			if (--m < 1) {
				--y;
				m = 12;
			}
			dom = civil::days_in_month(m, is_julian_leapyear(y));
		}
		return Julian(y, m, d, date.hour(), date.minute(), date.second());
	}
	//add week
	inline Julian operator + (Julian const& date, weeks const& week)
	{
		year_t y = date.year();
		month_t m = date.month();
		day_t d = date.day() + week.week() * 7;
		day_t dom = civil::days_in_month(m, is_gregorian_leapyear(y));
		while (d > dom) {
			d -= dom;
			if (++m > 12) {
				++y;
				m = 1;
			}
			dom = civil::days_in_month(m, is_gregorian_leapyear(y));
		}
		return Julian(y, m, d, date.hour(), date.minute(), date.second());
	}
	//subtract week
	inline Julian operator - (Julian const& date, weeks const& week)
	{
		year_t y = date.year();
		month_t m = date.month();
		day_t d = date.day() - week.week() * 7;
		day_t dom = civil::days_in_month(m, is_gregorian_leapyear(y));
		while (d < 1) {
			d += dom;
			if (--m < 1) {
				--y;
				m = 12;
			}
			dom = civil::days_in_month(m, is_gregorian_leapyear(y));
		}
		return Julian(y, m, d, date.hour(), date.minute(), date.second());
	}

	//add month
	inline Julian operator + (Julian const& dt, months const& month)
	{
		year_t yearsToAdd = month.month() / 12;
		month_t monthsToAdd = month.month() % 12;

		year_t y = dt.year() + yearsToAdd;
		month_t m = dt.month() + monthsToAdd;


		int adjustment = (m - 1) / 12 + (m - 12) / 12;
		y += adjustment;
		m -= month_t(adjustment * 12);
		day_t d = std::min(dt.day(), gregorian_days_in_month(m, is_julian_leapyear(y)));

		return Julian(y, m, d, dt.hour(), dt.minute(), dt.second());
	}
	//subtract month
	inline Julian operator - (Julian const& dt, months const& month)
	{
		year_t yearsToAdd = -month.month() / 12;
		month_t monthsToAdd = -month.month() % 12;
		year_t y = dt.year() + yearsToAdd;
		month_t m = dt.month() + monthsToAdd;

		int adjustment = (m - 1) / 12 + (m - 12) / 12;
		y += adjustment;
		m -= month_t(adjustment * 12);

		day_t d = std::min(dt.day(), gregorian_days_in_month(m, is_julian_leapyear(y)));
		return Julian(y, m, d, dt.hour(), dt.minute(), dt.second());

	}

	/** add year. */
	inline	Julian operator + (Julian const& dt, years const& year) {
		year_t y = dt.year() + (year_t)(year.year());
		month_t m = dt.month();
		day_t d = dt.day();

		if (m == 2 && d == 29 && !is_julian_leapyear(y))
			d = 28;

		return Julian(y, m, d, dt.hour(), dt.minute(), dt.second());
	}
	/** subtract year */
	inline	Julian operator - (Julian const& dt, years const& year) {
		year_t y = dt.year() - (year_t)(year.year());
		month_t m = dt.month();
		day_t d = dt.day();

		if (m == 2 && d == 29 && !is_julian_leapyear(y))
			d = 28;

		return Julian(y, m, d, dt.hour(), dt.minute(), dt.second());
	}

	// operator overloading
	//relational julian
	inline bool operator == (Julian const& lhs, Julian const& rhs) {
		return lhs.to_jd() == rhs.to_jd();
	}
	inline bool operator <= (Julian const& lhs, Julian const& rhs) {
		return lhs.to_jd() <= rhs.to_jd();
	}
	inline bool operator >= (Julian const& lhs, Julian const& rhs) {
		return lhs.to_jd() >= rhs.to_jd();

	}
	inline bool operator < (Julian const& lhs, Julian const& rhs) {
		return lhs.to_jd() < rhs.to_jd();
	}
	inline bool operator > (Julian const& lhs, Julian const& rhs) {
		return lhs.to_jd() > rhs.to_jd();
	}
	//count total leap year from year to year y
	constexpr year_t countLeapYears(Julian const& date)
	{
		year_t years = date.year();

		// Check if the current year needs to be considered 
		// for the count of leap years or not 
		if (date.month() <= 2)
			years--;

		// An year is a leap year if it is a multiple of 4, 
		// multiple of 400 and not a multiple of 100. 
		return years / 4;
	}
	inline long operator - (Julian const& lhs, Julian const& rhs) {
		// COUNT TOTAL NUMBER OF DAYS BEFORE FIRST DATE 'dt1' 

	// initialize count using years and day 
		long int n1 = (long int)(lhs.year()) * 365 + lhs.day();

		// Add days for months in given date 
		for (int i = 0; i < lhs.month() - 1; i++)
			n1 += civil::days_in_month(i, 0);
		civil::days_in_month(7, 0);
		// Since every leap year is of 366 days, 
		// Add a day for every leap year 
		n1 += (long int)(countLeapYears(lhs));

		// SIMILARLY, COUNT TOTAL NUMBER OF DAYS BEFORE 'dt2' 

		long int n2 = (long int)(rhs.year()) * 365 + rhs.day();

		for (int i = 0; i < rhs.month() - 1; i++)
			n2 += civil::days_in_month(i, 0);

		n2 += (long int)(countLeapYears(rhs));

		// return difference between two counts 
		return (n1 - n2);
	}
	inline long operator + (Julian const& lhs, Julian const& rhs)
	{
		// COUNT TOTAL NUMBER OF DAYS BEFORE FIRST DATE 'dt1' 

// initialize count using years and day 
		long int n1 = (long int)(lhs.year()) * 365 + lhs.day();

		// Add days for months in given date 
		for (int i = 0; i < lhs.month() - 1; i++)
			n1 += civil::days_in_month(i, 0);

		// Since every leap year is of 366 days, 
		// Add a day for every leap year 
		n1 += (long int)(countLeapYears(lhs));

		// SIMILARLY, COUNT TOTAL NUMBER OF DAYS BEFORE 'dt2' 

		long int n2 = (long int)(rhs.year()) * 365 + rhs.day();

		for (int i = 0; i < rhs.month() - 1; i++)
			n2 += civil::days_in_month(i, 0);

		n2 += (long int)(countLeapYears(rhs));

		// return difference between two counts 
		return (n1 + n2);
	}
	//get element function 
	constexpr year_t year(Julian const& g) { return g.year(); }
	constexpr month_t month(Julian const& g) { return g.month(); }
	constexpr day_t day(Julian const& g) { return g.day(); }
	constexpr hour_t hour(Julian const& g) { return g.hour(); }
	constexpr minute_t minute(Julian const& g) { return g.minute(); }
	constexpr second_t second(Julian const& g) { return g.second(); }
	// overloading operator Jd and Julian
	inline bool operator == (Jd const& lhs, Julian const& rhs) {
		return lhs.jd() == rhs.to_jd();
	}
	// overloading operator Julian and Jd
	inline bool operator == (Julian const& lhs, Jd const& rhs) {
		return rhs.jd() == lhs.to_jd();
	}

}

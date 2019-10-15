#pragma once
/*
khronos\gregorian_calendar.hpp
(c) Garth Santor
Created: 2015-09-22
Last Updated: 2015-09-22

Khronos library 'Gregorian calendar' declarations.
*/
/** @file: julian_day.hpp
@author Minh Nguyen
 @date 2019-10-12
 @version 0.1
@brief Implementation of …
 */

#include <khronos/def.hpp>
#include <khronos/calendar.hpp>
#include <khronos/julian_day.hpp>
#include <string>

namespace khronos {
	//convert jd to gregorian
	void jd_to_gregorian(jd_t jd, year_t& year, month_t& month, day_t& day);
	//convert jd to gregorian with hms
	void jd_to_gregorian(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second);
	// LITERALS
	/* UDL - converts a Gregorian year CE to an astronomical Gregorian year. */
	constexpr year_t operator ""_CE(unsigned long long year)
	{
		return year;
	}
	/* UDL - converts a Gregorian year BCE to an astronomical Gregorian year. */
	constexpr year_t operator ""_BCE(unsigned long long year)
	{
		return 1 - year;
	}

	/*!	JD of the start of the Gregorian epoch. */
	jd_t constexpr GREGORIAN_EPOCH = 1'721'425.5;
	// VALUES



	// OPERATIONS
	/*!Leap year test for Proleptic Gregorian Calendar.
		\return 'true' if leap year, 'false' if not.
		\param year[in] Astronomical year(1 CE = 1, 1 BCE = 0, 2 BCE = -1, etc.)*/
	constexpr bool is_gregorian_leapyear(year_t year)
	{
		return (year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0);
	}
	// caculate jd by using gregorian
	jd_t gregorian_to_jd(year_t year, month_t month, day_t day);
	
	// caculate jd by using gregorian
	jd_t gregorian_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second);

	/** Provide the number of days in the month of the Gregorian Calendar. */
	constexpr day_t gregorian_days_in_month(month_t month, bool isLeapYear) {
		return civil::days_in_month(month, isLeapYear);
	}


	/** Provide the name of the given month in the Gregorian calendar. */
	constexpr char const * gregorian_month_name(month_t month) {
		return civil::month_name_long(month);
	}
	
	
	/** Provide the short name of the given month in the Gregorian calendar. */
	constexpr char const * gregorian_short_month_name(month_t month) {
		return civil::month_name_short(month);
	}




	// CLASSES
	// --------------------------------------------------------------------------------------
	class Gregorian {
	private:
		year_t year_ = 0;
		month_t month_ = 0;
		day_t day_ = 0;
		hour_t   hour_ = 0;
		minute_t minute_ = 0;
		second_t second_ = 0;

	public:
		//constructor
		constexpr Gregorian(year_t year, month_t month, day_t day) : year_(year), month_(month), day_(day) {}
		constexpr Gregorian(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second) : year_(year),
			month_(month), day_(day), hour_(hour), minute_(minute), second_(second) {}
		Gregorian(now_t t);
		Gregorian(Jd const& d);
		Gregorian();

	public:
		// function to get element
		constexpr year_t year() const { return year_; }
		constexpr month_t month() const { return month_; }
		constexpr day_t day() const { return day_; }
		constexpr hour_t hour() const { return hour_; }
		constexpr minute_t minute() const { return minute_; }
		constexpr second_t second() const { return second_; }
		void from_jd(jd_t jd) { jd_to_gregorian(jd, year_, month_, day_); }
		jd_t to_jd() const { return gregorian_to_jd(year_, month_, day_); }
		/** Construct a Gregorian date from Julian Day Number object.
		@param jd [in] Jd object.
		*/
		/**	Assign and convert from Jd type to Gregorian type. */
		Gregorian& operator = (Jd const& jd) {
			this->hour_ = 0;
			this->minute_ = 0;
			this->second_ = 0;
			from_jd(jd.jd());
			return *this;
		}
		/**	Implicit cast to Jd class. */
		operator Jd () const { return Jd(to_jd()); } //test case 24
		//print out calendar
		std::string to_string() const;


	};
	//overloading << operator
	inline std::ostream& operator << (std::ostream& os, Gregorian const& g) {
		return os << g.to_string();
	}
	//get element function 
	constexpr year_t year(Gregorian const&g)  { return g.year(); }
	constexpr month_t month(Gregorian const& g)  { return g.month(); }
	constexpr day_t day(Gregorian const& g)  { return g.day(); }
	constexpr hour_t hour(Gregorian const& g)  { return g.hour(); }
	constexpr minute_t minute(Gregorian const& g)  { return g.minute(); }
	constexpr second_t second(Gregorian const& g)  { return g.second(); }
	
	constexpr year_t countLeapYears(Gregorian const& date)
	{
		year_t years = date.year();

		// Check if the current year needs to be considered 
		// for the count of leap years or not 
		if (date.month() <= 2)
			years--;

		// An year is a leap year if it is a multiple of 4, 
		// multiple of 400 and not a multiple of 100. 
		return years / 4 - years / 100 + years / 400;
	}

	inline bool operator == (Gregorian const& lhs, Gregorian const& rhs) {
		return lhs.to_jd() == rhs.to_jd();
	}
	inline long operator - (Gregorian const& lhs, Gregorian const& rhs) {
		// COUNT TOTAL NUMBER OF DAYS BEFORE FIRST DATE 'dt1' 

	// initialize count using years and day 
		long int n1 = (long int)(lhs.year()) * 365 + lhs.day();

		// Add days for months in given date 
		for (int i = 0; i < lhs.month() - 1; i++)
			n1 += civil::days_in_month(i, 0);
		civil::days_in_month(7,0);
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
	inline long operator + (Gregorian const& lhs, Gregorian const& rhs)
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
	inline bool operator != (Gregorian const& lhs, Gregorian const& rhs) {
		return lhs.to_jd() != rhs.to_jd();
	}
	inline bool operator <= (Gregorian const& lhs, Gregorian const& rhs) {
		return lhs.to_jd()<=rhs.to_jd();
	}
	inline bool operator >= (Gregorian const& lhs, Gregorian const& rhs) {
		return lhs.to_jd() >= rhs.to_jd();

	}
	inline bool operator < (Gregorian const& lhs, Gregorian const& rhs) {
		return lhs.to_jd() < rhs.to_jd();
	}
	inline bool operator > (Gregorian const& lhs, Gregorian const& rhs) {
		return lhs.to_jd() > rhs.to_jd();
	}

	// adding day
	inline Gregorian operator + (Gregorian const& date, days const& day)
	{
		year_t y = date.year();
		month_t m = date.month();
		day_t d = date.day() + day.day();
		day_t dom = civil::days_in_month(m, is_gregorian_leapyear(y));
		while (d > dom) {
			d -= dom;
			if (++m > 12) {
				++y;
				m = 1;
			}
			dom = civil::days_in_month(m, is_gregorian_leapyear(y));
		}
		return Gregorian(y, m, d, date.hour(), date.minute(), date.second());
	}
	// substract day
	inline Gregorian operator - (Gregorian const& date, days const& day)
	{
		year_t y = date.year();
		month_t m = date.month();
		day_t d = date.day() - day.day();
		day_t dom = civil::days_in_month(m, is_gregorian_leapyear(y));
		while (d < 1) {
			d += dom;
			if (--m < 1) {
				--y;
				m = 12;
			}
			dom = civil::days_in_month(m, is_gregorian_leapyear(y));
		}
		return Gregorian(y, m, d, date.hour(), date.minute(), date.second());
	}
	//add week
	inline Gregorian operator + (Gregorian const& date, weeks const& week)
	{
		year_t y = date.year();
		month_t m = date.month();
		day_t d = date.day() + week.week()*7;
		day_t dom = civil::days_in_month(m, is_gregorian_leapyear(y));
		while (d > dom) {
			d -= dom;
			if (++m > 12) {
				++y;
				m = 1;
			}
			dom = civil::days_in_month(m, is_gregorian_leapyear(y));
		}
		return Gregorian(y, m, d, date.hour(), date.minute(), date.second());
	}
	//subtract week
	inline Gregorian operator - (Gregorian const& date, weeks const& week)
	{
		year_t y = date.year();
		month_t m = date.month();
		day_t d = date.day() - week.week()*7;
		day_t dom = civil::days_in_month(m, is_gregorian_leapyear(y));
		while (d < 1) {
			d += dom;
			if (--m < 1) {
				--y;
				m = 12;
			}
			dom = civil::days_in_month(m, is_gregorian_leapyear(y));
		}
		return Gregorian(y, m, d, date.hour(), date.minute(), date.second());
	}
	//add month
	inline Gregorian operator + (Gregorian const& dt, months const& month)//13
	{
		//g 2000, JAN, 1
		year_t yearsToAdd = month.month() / 12;//1
		month_t monthsToAdd = month.month() % 12;//1

		year_t y = dt.year() + yearsToAdd;//2000+1=2001
		month_t m = dt.month() + monthsToAdd;//2
		

		int adjustment = (m - 1) / 12 + (m - 12) / 12;//
		y += adjustment;
		m -= month_t(adjustment * 12);
		day_t d = std::min(dt.day(), gregorian_days_in_month(m, is_gregorian_leapyear(y)));

		return Gregorian(y, m, d,dt.hour(),dt.minute(),dt.second());
	}
	//subtract month
	inline Gregorian operator - (Gregorian const& dt, months const& month)
	{
		year_t yearsToAdd = -month.month() / 12;
		month_t monthsToAdd = -month.month() % 12;
		year_t y = dt.year() + yearsToAdd;
		month_t m = dt.month() + monthsToAdd;

		int adjustment = (m - 1) / 12 + (m - 12) / 12;
		y += adjustment;
		m -= month_t(adjustment * 12);

		day_t d = std::min(dt.day(), gregorian_days_in_month(m, is_gregorian_leapyear(y)));
		return Gregorian(y, m, d, dt.hour(), dt.minute(), dt.second());

	}
	/** Gregorian + (integer year) operator. */
	inline	Gregorian operator + (Gregorian const& dt, years const& year) {
		year_t y = dt.year() + (year_t)(year.year());
		month_t m = dt.month();
		day_t d = dt.day();

		if (m == 2 && d == 29 && !is_gregorian_leapyear(y))
			d = 28;

		return Gregorian(y, m, d, dt.hour(), dt.minute(), dt.second());
	}
	/** Gregorian + (integer year) operator. */
	inline	Gregorian operator - (Gregorian const& dt, years const& year) {
		year_t y = dt.year() - (year_t)(year.year());
		month_t m = dt.month();
		day_t d = dt.day();

		if (m == 2 && d == 29 && !is_gregorian_leapyear(y))
			d = 28;

		return Gregorian(y, m, d, dt.hour(), dt.minute(), dt.second());
	}
	// get day of week // Mon , thur, Wed, ...
	inline civil_weekday_codes_long day_of_week(Gregorian const& g) 
	{ 
		return civil_weekday_codes_long(day_of_week(gregorian_to_jd(g.year(), g.month(), g.day())));
	}
	// get max day of each month
	constexpr day_t julian_days_in_month(month_t month, bool isLeapYear)
	{
		return civil::days_in_month(month, isLeapYear);
	}
	/** Provide the name of the given month in the Gregorian calendar. */
	constexpr char const* julian_month_name(month_t month) 
	{
		return civil::month_name_long(month);
	}

	/** Provide the short name of the given month in the Gregorian calendar. */
	constexpr char const* julian_short_month_name(month_t month) 
	{
		return civil::month_name_short(month);
	}
	// OPERATORS
	// ====================
		// overloading operator Jd and Gregorion
	inline long operator - (Jd const& lhs, Gregorian const& rhs) {
		Gregorian temp(lhs);
		return temp - rhs;
	}
	inline long operator + (Jd const& lhs, Gregorian const& rhs) {
		Gregorian temp(lhs);
		return temp + rhs;
	}
	inline bool operator > (Jd const& lhs, Gregorian const& rhs) {
		Gregorian temp(lhs);
		return temp > rhs;
	}
	inline bool operator < (Jd const& lhs, Gregorian const& rhs) {
		Gregorian temp(lhs);
		return temp < rhs;
	}
	inline bool operator >= (Jd const& lhs, Gregorian const& rhs) {
		Gregorian temp(lhs);
		return temp >= rhs;
	}
	inline bool operator <= (Jd const& lhs, Gregorian const& rhs) {
		Gregorian temp(lhs);
		return temp <= rhs;
	}
	inline bool operator == (Jd const& lhs, Gregorian const& rhs) {
		Gregorian temp(lhs);
		return temp == rhs;
	}
	inline bool operator != (Jd const& lhs, Gregorian const& rhs) {
		Gregorian temp(lhs);
		return temp != rhs;
	}

	// overloading operator Gregorian and Jd
	inline long operator - (Gregorian const& lhs, Jd const& rhs) {
		Gregorian temp(rhs);
		return lhs-temp;
	}
	
	inline long operator + (Gregorian const& lhs, Jd const& rhs) {
		Gregorian temp(rhs);
		return lhs + temp;
	}
	inline bool operator > (Gregorian const& lhs, Jd const& rhs) {
		Gregorian temp(rhs);
		return lhs > temp;
	}
	inline bool operator < (Gregorian const& lhs, Jd const& rhs) {
		Gregorian temp(rhs);
		return lhs < temp;
	}
	inline bool operator >= (Gregorian const& lhs, Jd const& rhs) {
		Gregorian temp(rhs);
		return lhs >= temp;
	}
	inline bool operator <= (Gregorian const& lhs, Jd const& rhs) {
		Gregorian temp(rhs);
		return lhs <= temp;
	}
	inline bool operator == (Gregorian const& lhs, Jd const& rhs) {
		Gregorian temp(rhs);
		return lhs == temp;
	}
	inline bool operator != (Gregorian const& lhs, Jd const& rhs) {
		Gregorian temp(rhs);
		return lhs != temp;
	}

} // end-of-namespace khronos

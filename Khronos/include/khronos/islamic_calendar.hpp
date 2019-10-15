#pragma once
#include <iostream>
#include <khronos/julian_calendar.hpp>
//#include <khronos/utility.hpp>

/**	@file khronos/Islamic_calendar.hpp
	@author Minh Nguyen
	@date 2019-10-13

	Islamic calendar class and functions.
	*/
namespace khronos
{
	/** Provide the name of the given month in the islamic calendar. */
	constexpr char const* islamic_month_name(month_t month) {
		return civil::islamic_month_name(month);
	}
	/*!Leap year test for Islamic Calendar.
		\return 'true' if leap year, 'false' if not.
		\param year[in] Astronomical year*/
	bool is_islamic_leapyear(year_t year);
	jd_t constexpr ISLAMIC_EPOCH = 1'948'439.5;//constant
	// convert islamic to jd
	jd_t  islamic_to_jd(year_t year, month_t month, day_t day);
	//convert islamic to jd with (hms)
	jd_t  islamic_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second);
	
	// convert jd to islamic
	void  jd_to_islamic(jd_t jd, year_t& year, month_t& month, day_t& day);
	void  jd_to_islamic(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second);
	inline day_t islamic_days_in_month(month_t month, bool is_islamic_leapyear)
	{
		if (month % 2 == 1 || month == 12 && is_islamic_leapyear)
			return 30;
		else
			return 29;

	}
	// CLASSES
	// --------------------------------------------------------------------------------------
	class Islamic {
	private:
		year_t year_ = 0;
		month_t month_ = 0;
		day_t day_ = 0;
		hour_t   hour_ = 0;
		minute_t minute_ = 0;
		second_t second_ = 0;

	public:
		//constructor
		constexpr Islamic(year_t year, month_t month, day_t day) : year_(year), month_(month), day_(day) {}
		constexpr Islamic(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second) : year_(year),
			month_(month), day_(day), hour_(hour), minute_(minute), second_(second) {}
		Islamic(now_t t);
		Islamic(Jd const& d);
		Islamic();

	public:
		constexpr year_t year() const { return year_; }
		constexpr month_t month() const { return month_; }
		constexpr day_t day() const { return day_; }
		constexpr hour_t hour() const { return hour_; }
		constexpr minute_t minute() const { return minute_; }
		constexpr second_t second() const { return second_; }
		void from_jd(jd_t jd) { jd_to_islamic(jd, year_, month_, day_,hour_,minute_, second_); }
		jd_t to_jd() const { return islamic_to_jd(year_, month_, day_,hour_,minute_, second_); }
		/** Construct a Islamic date from Julian Day Number object.
		@param jd [in] Jd object.
		*/
		/**	Assign and convert from Jd type to Islamic type. */
		Islamic& operator = (Jd const& jd) {
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
	inline std::ostream& operator << (std::ostream& os, Islamic const& g) {
		return os << g.to_string();
	}
	// adding day
	inline Islamic operator + (Islamic const& date, days const& day)
	{
		year_t y = date.year();
		month_t m = date.month();
		day_t d = date.day() + day.day();
		day_t dom = islamic_days_in_month(m, is_islamic_leapyear(y));
		while (d > dom) {
			d -= dom;
			if (++m > 12) {
				++y;
				m = 1;
			}
			dom = islamic_days_in_month(m, is_islamic_leapyear(y));
		}
		return Islamic(y, m, d, date.hour(), date.minute(), date.second());
	}
	// substract day
	inline Islamic operator - (Islamic const& date, days const& day)
	{
		year_t y = date.year();
		month_t m = date.month();
		day_t d = date.day() - day.day();
		day_t dom = islamic_days_in_month(m, is_islamic_leapyear(y));
		while (d < 1) {
			d += dom;
			if (--m < 1) {
				--y;
				m = 12;
			}
			dom = islamic_days_in_month(m, is_islamic_leapyear(y));
		}
		return Islamic(y, m, d, date.hour(), date.minute(), date.second());
	}
	//add 

	inline Islamic operator + (Islamic const& date, weeks const& week)
	{
		year_t y = date.year();
		month_t m = date.month();
		day_t d = date.day() + week.week() * 7;
		day_t dom = islamic_days_in_month(m, is_islamic_leapyear(y));
		while (d > dom) {
			d -= dom;
			if (++m > 12) {
				++y;
				m = 1;
			}
			dom = islamic_days_in_month(m, is_islamic_leapyear(y));
		}
		return Islamic(y, m, d, date.hour(), date.minute(), date.second());
	}
	//subtract week
	inline Islamic operator - (Islamic const& date, weeks const& week)
	{
		year_t y = date.year();
		month_t m = date.month();
		day_t d = date.day() - week.week() * 7;
		day_t dom = islamic_days_in_month(m, is_islamic_leapyear(y));
		while (d < 1) {
			d += dom;
			if (--m < 1) {
				--y;
				m = 12;
			}
			dom = islamic_days_in_month(m, is_islamic_leapyear(y));
		}
		return Islamic(y, m, d, date.hour(), date.minute(), date.second());
	}
	//add month
	inline Islamic operator + (Islamic const& dt, months const& month)//13
	{
		year_t y = dt.year() + month.month() / 12;
		month_t m = dt.month() + month.month() % 12;

		int adjustment = (m - 1) / 12 + (m - 12) / 12;
		y += adjustment;
		m -= month_t(adjustment * 12);

		day_t d = std::min(dt.day(), islamic_days_in_month(m, is_islamic_leapyear(y)));
		return Islamic(y, m, d, dt.hour(), dt.minute(), dt.second());
	}
	//subtract month
	inline Islamic operator - (Islamic const& dt, months const& month)
	{
		year_t y = dt.year() - month.month()/12;
		month_t m = dt.month() - month.month()%12;

		int adjustment = (m - 1) / 12 + (m - 12) / 12;
		y += adjustment;
		m -= month_t(adjustment * 12);

		day_t d = std::min(dt.day(), islamic_days_in_month(m, is_islamic_leapyear(y)));
		return Islamic(y, m, d, dt.hour(), dt.minute(), dt.second());

	}
	/** Islamic + (integer year) operator. */
	inline	Islamic operator + (Islamic const& dt, years const& year) {
		year_t y = dt.year() + (year_t)(year.year());
		month_t m = dt.month();
		day_t d = dt.day();

		if (m == 12 && d == 30 && !is_islamic_leapyear(y))
			d = 29;

		return Islamic(y, m, d, dt.hour(), dt.minute(), dt.second());
	}
	/** Islamic + (integer year) operator. */
	inline	Islamic operator - (Islamic const& dt, years const& year) {
		year_t y = dt.year() - (year_t)(year.year());
		month_t m = dt.month();
		day_t d = dt.day();

		if (m == 12 && d == 30 && !is_islamic_leapyear(y))
			d = 29;

		return Islamic(y, m, d, dt.hour(), dt.minute(), dt.second());
	}
	//overloading operator
	inline bool operator == (Islamic const& lhs, Islamic const& rhs) {
		return lhs.to_jd() == rhs.to_jd();
	}
	inline bool operator != (Islamic const& lhs, Islamic const& rhs) {
		return lhs.to_jd() != rhs.to_jd();
	}
	inline bool operator <= (Islamic const& lhs, Islamic const& rhs) {
		return lhs.to_jd() <= rhs.to_jd();
	}
	inline bool operator >= (Islamic const& lhs, Islamic const& rhs) {
		return lhs.to_jd() >= rhs.to_jd();

	}
	inline bool operator < (Islamic const& lhs, Islamic const& rhs) {
		return lhs.to_jd() < rhs.to_jd();
	}
	inline bool operator > (Islamic const& lhs, Islamic const& rhs) {
		return lhs.to_jd() > rhs.to_jd();
	}
}
#pragma once

/**	@file khronos/hebrew_calendar.hpp
	@author Garth Santor
	@date 2013-09-26

	Hebrew calendar class.
	*/
	/** @file: hebrew_calendar.hpp
	@author Minh Nguyen
	 @date 2019-10-12
	 @version 0.1
	@brief Implementation of …
	 */
#include <khronos/islamic_calendar.hpp>


namespace khronos
{
	/*!Leap year test for hebrew Calendar.
		\return 'true' if leap year, 'false' if not.
		\param year[in] Astronomical year*/
	bool is_hebrew_leapyear(year_t year);
	jd_t constexpr hebrewEpoch = 347'995.5;//constant
	//caculate delate
	day_t  delayOfWeek(year_t year);
	day_t  delayAdjacentYear(year_t year);
	// caculate total months in a specific year
	month_t hebrew_months_in_year(year_t year);
	// caculate total days in a specific month
	day_t hebrew_days_in_month(year_t year,month_t month);
	// caculate total days in a specific year
	day_t hebrew_days_in_year(year_t year);

	// convert hebrew to jd
	jd_t  hebrew_to_jd(year_t year, month_t month, day_t day);
	//convert hebrew to jd with (hms)
	jd_t  hebrew_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second);

	// convert jd to hebrew
	void  jd_to_hebrew(jd_t jd, year_t& year, month_t& month, day_t& day);
	void  jd_to_hebrew(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second);

	// CLASSES
	// --------------------------------------------------------------------------------------
	class Hebrew {
	private:
		year_t year_ = 0;
		month_t month_ = 0;
		day_t day_ = 0;
		hour_t   hour_ = 0;
		minute_t minute_ = 0;
		second_t second_ = 0;

	public:
		//constructor
		constexpr Hebrew(year_t year, month_t month, day_t day) : year_(year), month_(month), day_(day) {}
		constexpr Hebrew(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second) : year_(year),
			month_(month), day_(day), hour_(hour), minute_(minute), second_(second) {}
		Hebrew(now_t t);
		Hebrew(Jd const& d);
		Hebrew();

	public:
		// function to get element of class
		constexpr year_t year() const { return year_; }
		constexpr month_t month() const { return month_; }
		constexpr day_t day() const { return day_; }
		constexpr hour_t hour() const { return hour_; }
		constexpr minute_t minute() const { return minute_; }
		constexpr second_t second() const { return second_; }
		void from_jd(jd_t jd) { jd_to_hebrew(jd, year_, month_, day_,hour_,minute_,second_); }
		jd_t to_jd() const { return hebrew_to_jd(year_, month_, day_,hour_, minute_, second_); }
		/** Construct a Hebrew date from Julian Day Number object.
		@param jd [in] Jd object.
		*/
		/**	Assign and convert from Jd type to Hebrew type. */
		Hebrew& operator = (Jd const& jd) {
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
	inline std::ostream& operator << (std::ostream& os, Hebrew const& g) {
		return os << g.to_string();
	}
	// adding day
	inline Hebrew operator + (Hebrew const& date, days const& day)
	{
		Jd dummy(date.to_jd());
		Jd ret = dummy + day;
		return Hebrew(ret);
	}
	// substract day
	inline Hebrew operator - (Hebrew const& date, days const& day)
	{
		Jd dummy(date.to_jd());
		Jd ret = dummy - day;
		return Hebrew(ret);
	}
	//add week
	inline Hebrew operator + (Hebrew const& date, weeks const& week)
	{
		year_t y = date.year();
		month_t m = date.month();
		day_t d = date.day() + week.week() * 7;
		day_t dom = hebrew_days_in_month(m, is_hebrew_leapyear(y));
		while (d > dom) {
			d -= dom;
			if (++m > 12) {
				++y;
				m = 1;
			}
			dom = hebrew_days_in_month(m, is_hebrew_leapyear(y));
		}
		return Hebrew(y, m, d, date.hour(), date.minute(), date.second());
	}
	//subtract week
	inline Hebrew operator - (Hebrew const& date, weeks const& week)
	{
		year_t y = date.year();
		month_t m = date.month();
		day_t d = date.day() - week.week() * 7;
		day_t dom = hebrew_days_in_month(m, is_hebrew_leapyear(y));
		while (d < 1) {
			d += dom;
			if (--m < 1) {
				--y;
				m = 12;
			}
			dom = hebrew_days_in_month(m, is_hebrew_leapyear(y));
		}
		return Hebrew(y, m, d, date.hour(), date.minute(), date.second());
	}

	//relational
	//overloading operator
	inline bool operator == (Hebrew const& lhs, Hebrew const& rhs) {
		return lhs.to_jd() == rhs.to_jd();
	}
	inline bool operator != (Hebrew const& lhs, Hebrew const& rhs) {
		return lhs.to_jd() != rhs.to_jd();
	}
	inline bool operator <= (Hebrew const& lhs, Hebrew const& rhs) {
		return lhs.to_jd() <= rhs.to_jd();
	}
	inline bool operator >= (Hebrew const& lhs, Hebrew const& rhs) {
		return lhs.to_jd() >= rhs.to_jd();

	}
	inline bool operator < (Hebrew const& lhs, Hebrew const& rhs) {
		return lhs.to_jd() < rhs.to_jd();
	}
	inline bool operator > (Hebrew const& lhs, Hebrew const& rhs) {
		return lhs.to_jd() > rhs.to_jd();
	}
	// get month name
		constexpr char const* hebrew_month_name(month_t month) {
		return civil::hebrew_month_name(month);
	}
}
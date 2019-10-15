#pragma once
/** @file: julian_day.hpp
@author Minh Nguyen
 @date 2019-10-12
 @version 0.1
@brief Implementation of julian calendar class
 */
#include <cmath>
#include <string>

#include <khronos/def.hpp>
#include <khronos/timeofday.hpp>
#include <khronos/utility.hpp>
//#include <khronos/gregorian_calendar.hpp>



namespace khronos {

	// class for Julian_day calendar
	class Jd {
	private:
		jd_t jd_;
	public:
		Jd();
		Jd(now_t t);
		/**	Constructor from real number. */
		constexpr Jd(jd_t jd) : jd_(jd) { }

		/**	Get the number of days. */
		constexpr jd_t jd() const { return jd_; }

		std::string to_string() const;
	};

	/** stream insertion operator. */
	inline std::ostream& operator << (std::ostream& os, Jd const& jd) {
		return os << jd.to_string();
	}
	// get name day of week [monday ,thur...]
	namespace civil {
		inline day_t day_of_week(jd_t jd) { return (int)(jd + 0.5)% 7; }
	}
	// get name day of week [monday ,thur...]
	inline day_t day_of_week(Jd const& jd) { return civil::day_of_week(jd.jd()); }
	// check the year is the leap year or not
	constexpr bool is_julian_leapyear(year_t year)
	{
		return year % 4 == 0;
	}
	// convert jd to jdn
	jd_t jd_to_jdn(jd_t jd);
	// OPERATORS
	// --------------------------------------------------------------------------------------

	/** Jd relational operators. */
	inline bool operator == (Jd const& lhs, Jd const& rhs) {
		return lhs.jd() == rhs.jd();
	}
	inline Jd operator - (Jd const& lhs, Jd const& rhs) {
		return lhs.jd() - rhs.jd();
	}
	inline Jd operator + (Jd const& lhs, Jd const& rhs) 
	{
		return lhs.jd() + rhs.jd();
	}
	inline bool operator != (Jd const& lhs, Jd const& rhs) {
		return lhs.jd() != rhs.jd();
	}
	inline bool operator <= (Jd const& lhs, Jd const& rhs) {
		return lhs.jd() <= rhs.jd();
	}
	inline bool operator >= (Jd const& lhs, Jd const& rhs) {
		return lhs.jd() >= rhs.jd();
	}
	inline bool operator < (Jd const& lhs, Jd const& rhs) {
		return lhs.jd() < rhs.jd();
	}
	inline bool operator > (Jd const& lhs, Jd const& rhs) {
		return lhs.jd() > rhs.jd();
	}

	//subtract day
	inline Jd operator - (Jd const& lhs, days const& rhs) {
		return lhs.jd() - rhs.day();
	}
	//add day
	inline Jd operator + (Jd const& lhs, days const& rhs)
	{
		return Jd(lhs.jd() + rhs.day());
	}
	//add week
	inline Jd operator - (Jd const& lhs, weeks const& rhs)
	{
		return lhs.jd() - rhs.week() * 7.0;
	}
	//subtract week
	inline Jd operator + (Jd const& lhs, weeks const& rhs)
	{
		return lhs.jd() + rhs.week() * 7.0;
	}
	//subtract year
	inline Jd operator - (Jd const& lhs, years const& rhs)
	{
		return lhs.jd() - rhs.year() * EARTH_ORBITAL_PERIOD_DAYS;
	}
	//add year
	inline Jd operator + (Jd const& lhs, years const& rhs)
	{
		return lhs.jd() + rhs.year() * EARTH_ORBITAL_PERIOD_DAYS;
	}
	// caculate hms
	void hms(tod_t tod, hour_t& hour, minute_t& minute, second_t& second);

} // end-of-namespace khronos
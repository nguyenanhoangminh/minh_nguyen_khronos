#pragma once
/** @file: calendar.hpp
@author Minh Nguyen
 @date 2019-10-12
 @version 0.1
@brief Implementation of 
Khronos library 'civil' declarations.
 */
/*
khronos\calendar.hpp
(c) Garth Santor
Created: 2015-09-22
Last Updated: 2015-09-22

Khronos library 'civil' declarations.
*/


#include <khronos/def.hpp>
#include <array>
#include <cassert>

namespace khronos {

	namespace civil {

		namespace detail {
			constexpr std::array<std::array<day_t, 13>, 2> daysInMonth = {
				0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
				0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
			};
			//** Month addition/subtraction. */
			
		}


		/** Get the full name of the civil day of 
		.
			@return pointer to the day name as a c-string.
			@param day [in] day number [0..6], where 0 = Monday
		*/
		constexpr char const* day_name(day_t day) {
			constexpr char const* names[7] = {
				"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
			};
			assert(day >= 0);
			assert(day < 7);
			return names[day];
		}
		/** Get the full name of the Hebrew Month.
			@return pointer to the day name as a c-string.
			@param day [in] day number [0..6], where 0 = Monday
		*/
		constexpr char
			const* hebrew_month_name(month_t month) {
			constexpr char const* names[14] = { "",
		"Nisan", "Iyyar", "Sivan", "Tammuz",
		"Av", "Elul", "Tishri", "Heshvan",
		"Kislev", "Teveth", "Shevat", "Adar", "Veadar" };
		assert(month >= 0);
		assert(month < 14);
		return names[month];
		}
		/** Get the full name of the islamic day of
		.
			@return pointer to the day name as a c-string.
			@param day [in] day number [0..6], where 0 = Monday
		*/
		constexpr char const* islamic_day_name(day_t day) {
			constexpr char const* names[7] = {
				"al-'ahad", "al-'ithnayn", "alth-thalatha", "al-'arb`a'", "al-khamis", "al-jum`a", "as-sabt"
			};
			assert(day >= 0);
			assert(day < 7);
			return names[day];
		}

		/**	Returns the number of days in the given month of the civil calendar.
			@return The number of days in the given month.
			@param month [in] month number [1..12]
			@param isLeapYear [in] 'true' for leap year, 'false' otherwise.
			*/
		constexpr day_t days_in_month(month_t month, bool isLeapYear) {
			return detail::daysInMonth[isLeapYear][month];
		}

		// month functions

		/** Get the full name of the civil month.
			@return pointer to the month name as a c-string.
			@param month [in] month number [1..12]
		*/
		constexpr char const* vulcan_month_name(month_t month) {
			constexpr char const* const names[13] = {"","Z'at", "D'ruh", "K'riBrax", "re'T'Khutai", "T'keKhuti", "Khuti",
		"Ta'Krat", "K'ri'lior", "et'khior", "T'lakht", "T'ke'Tas", "Tasmeen"};
			assert(month > 0);
			assert(month < 13);
			return names[month];
		};
		constexpr char const* islamic_month_name(month_t month) {
			constexpr char const* const names[13] = { "", "Muharram", "Safar", "Rabi'al-Awwal",
			"Rabi'ath-Thani", "Jumada I-Ula", "Jumada t-Tania", "Rajab", "Sha'ban", "Ramadan", "Shawwal",
			"Dhu I-Qa'da", "Dhu I-Hijja" };

			assert(month > 0);
			assert(month < 13);
			return names[month];
		};

		constexpr char const* month_name_long(month_t month) {
			constexpr char const* const names[13] = {
				"",
				"January", "February", "March", "April", "May", "June",
				"July", "August", "September", "October", "November", "December"
			};

			assert(month > 0);
			assert(month < 13);
			return names[month];
		}




		/** Get the short name of the civil month.
			@return pointer to the 3-letter month name as a c-string.
			@param month [in] month number [1..12]
		*/
		constexpr char const* month_name_short(month_t month) {
			constexpr char const* const names[13] = {
				"",
				"JAN", "FEB", "MAR", "APR", "MAY", "JUN",
				"JUL", "AUG", "SEP", "OCT", "NOV", "DEC"
			};

			assert(month > 0);
			assert(month < 13);
			return names[month];
		}
	}

	// VALUES
	enum civil_month_codes_long { January = 1, February, March, April, May, June, July, August, September, October, November, December };
	enum civil_month_codes_short { JAN = January, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };
	enum civil_weekday_codes_long { Monday = 0, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };
	enum civil_weekday_codes_short { MON = Monday, TUE, WED, THU, FRI, SAT, SUN };
	enum civil_islamic_month_name {	Muharram = 1, Safar, RabialAwwal, RabiathThani ,  JumadaIUla ,  JumadatTania ,
		Rajab ,  Shaban ,  Ramadan ,  Shawwal , DhulQadah, DhulHijja
	};
	enum civil_habrew_month_name { Nisan = 1, Iyar, Sivan, Tammuz, Av, Elul, Tishri, Heshvan, Kislev, Teveth, Shevat, AdarI,Veadar};

	



} // end-of-namespace khronos

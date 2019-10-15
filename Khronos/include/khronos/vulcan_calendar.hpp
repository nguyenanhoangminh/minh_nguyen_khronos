#pragma once
#include <khronos/hebrew_calendar.hpp>

/**	@file vulcan.hpp
	@author Minh Nguyen
	@date 2019-10-12

	Vulcan calendar class and functions.
	*/
namespace khronos {
	/** Provide the name of the given month in the vulcan calendar. */
	constexpr char const* vulcan_month_name(month_t month) {
		return civil::vulcan_month_name(month);
	}
	constexpr day_t vulcan_days_in_month() {
		return 21;
	}
}

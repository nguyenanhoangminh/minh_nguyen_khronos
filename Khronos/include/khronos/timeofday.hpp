#pragma once

/*
khronos\timeofday.hpp
(c) Minh Nguyen
Last Updated: 2019-10-14

Khronos library 'time-of-day' declarations.
*/

namespace khronos {
	// const total second in one day
	unsigned long long constexpr SECONDS_PER_DAY = 24 * 60 * 60;
	// caculate time of day with hms
	constexpr tod_t tod(hour_t hour, minute_t minute, second_t second)
	{
		return (second + 60 * (static_cast<tod_t>(minute) + 60 * static_cast<tod_t>(hour))) / SECONDS_PER_DAY;
	}
}


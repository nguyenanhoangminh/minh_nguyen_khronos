#pragma once

#include <cmath>
/**	@file vulcan.hpp
	@author Minh Nguyen
	@date 2019-10-12
	utility class and function
	*/

namespace khronos {

	namespace utility {
		inline double mod(double a, double b) { return a - b * floor(a / b); }
		inline double mod(int a, int b) { return a - (b * floor(a / b)); }
		inline double jwday(double j) { return mod(floor(j + 1.5), 7.0); }
	}

} // end-of-namespace khronos
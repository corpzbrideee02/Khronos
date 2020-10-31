/**	@file Jdn.cpp
	@author Garth Santor
	@date 2012-09-16

	Date and time library to_string method implementations.
	*/


#include <khronos/julian_day.hpp>
#include <sstream>
#include <ctime>
#include "gregorian_to_jd.cpp"
using namespace std;
	/**	Jd default constructor.  Initialize to the current local time. */
/**	Jd default constructor.  Initialize to the current local time. */

namespace khronos {
	Jd::Jd()
		: jd_(0)
	{
		time_t nowTime = time(NULL);
		struct tm tmNow;
		localtime_s(&tmNow, &nowTime);
		jd_ = gregorian_to_jd(
			year_t(tmNow.tm_year) + 1900,
			month_t(tmNow.tm_mon) + 1,
			day_t(tmNow.tm_mday)
		);
	}


	/** Print the Julian Day as a string. */
	std::string Jd::to_string() const {
		ostringstream oss;
		oss << "JD " << jd_;
		return oss.str();
	}

}

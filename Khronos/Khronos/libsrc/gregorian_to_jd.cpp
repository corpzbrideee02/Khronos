/*
khronos\gregorian_to_jdn.cpp
(c) Garth Santor
Created: 2015-09-22
Last Updated: 2015-09-22

Khronos library 'gregorian::to_jdn' implementation.
*/
#include <khronos/gregorian_calendar.hpp>


//#include <cassert>
//using namespace detail;
//using namespace khronos;

//* !Convert a Proleptic Gregorian Calendar date to a Julian Day Number
//\param year[in] Astronomical year(1 CE = 1, 1 BCE = 0, 2 BCE = -1, etc.)
//\param month[in] 1..12
//\param day[in] 1..31
//* /
namespace khronos {

	namespace detail {
		/**	Real-number implementation. */
		inline jd_t greg2jd_real(year_t year, month_t month, day_t dayOfMonth) {
			long long y = year - 1;
			return
				GREGORIAN_EPOCH - 1
				+ 365 * y
				+ floor(y / 4.0)
				- floor(y / 100.0)
				+ floor(y / 400.0)
				+ floor(((367.0 * month - 362.0) / 12.0)
					+ ((month <= 2)
						? 0
						: (is_gregorian_leapyear(year) ? -1 : -2)))
				+ dayOfMonth;
		}

		constexpr inline jd_t greg2jd_integer(year_t year, month_t month, day_t dayOfMonth) {
			long long a = (14 - month) / 12;
			long long y = year + 4800 - a;
			long long m = month + 12 * a - 3;
			return dayOfMonth + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045 - 0.5;
		}

	

	};
	
	inline jd_t gregorian_to_jd(year_t year, month_t month, day_t day) {
		assert(year > -4800 && "Minimum year is 4800 BCE");
		assert(month >= 1 && "Minumum month is January = 1");
		assert(month <= 12 && "Maximum month is December = 12");
		assert(day >= 1 && "Minumum day is 1");
		assert(day <= 31 && "Maximum day is 31");
		assert(detail::greg2jd_integer(year, month, day) == detail::greg2jd_real(year, month, day));
		return detail::greg2jd_integer(year, month, day);
	}


	inline jd_t gregorian_to_jd(year_t year, month_t month, day_t day, hour_t hr, minute_t min, second_t sec)
	{
		 tod_t tt = tod((double)hr, min,  (unsigned long long)sec);
		//return gregorian_to_jd(year, month, day) + tod((unsigned long long)sec,min,(double)hr);
		 return gregorian_to_jd(year, month, day) + tt;
	}


	
	//inline void jd_to_gregorian(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hr, minute_t& min, second_t& sec) {
		//jd_to_gregorian(jd, year, month, day);
		//hms(hr, min, sec);
	//}

}


	




	
	

	
	











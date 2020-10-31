#pragma once

#include <cmath>
#include <string>

#include <khronos/def.hpp>
#include <khronos/timeofday.hpp>
#include <khronos/utility.hpp>
#include <ostream>


namespace khronos {
	/**	Julian Date (JN) class. */
	class Jd {
		jd_t jd_;
	public:
		Jd();

		// Constructor from real number
		constexpr Jd(jd_t jd) :jd_(jd) {}

		// Accessor
		constexpr jd_t jd() const { return jd_; }

		std::string to_string() const;
	};

	/** stream insertion operator. */
	inline std::ostream& operator << (std::ostream& os, Jd const& jd) {
		return os << jd.to_string();
	}


	// OPERATORS
	// --------------------------------------------------------------------------------------

	/** Jd relational operators. */
	inline bool operator == (Jd const& lhs, Jd const& rhs) { return lhs.jd() == rhs.jd(); }
	inline bool operator != (Jd const& lhs, Jd const& rhs) { return lhs.jd() != rhs.jd(); }
	inline bool operator < (Jd const& lhs, Jd const& rhs) { return lhs.jd() < rhs.jd(); }
	inline bool operator > (Jd const& lhs, Jd const& rhs) { return lhs.jd() > rhs.jd(); }
	inline bool operator <= (Jd const& lhs, Jd const& rhs) { return lhs.jd() <= rhs.jd(); }
	inline bool operator >= (Jd const& lhs, Jd const& rhs) { return lhs.jd() >= rhs.jd(); }





	/**Jd difference operator. */
	inline jd_t operator - (Jd const& lhs, Jd const& rhs) { return lhs.jd() - rhs.jd(); }


	/**	Day of the week. */
	inline day_t day_of_week(Jd const& jd) { return civil::day_of_week(jd.jd()); }


	/** Day addition/subtraction. */
	namespace detail {
		struct package_day {
			day_t nDays_;
			constexpr package_day(day_t d) :nDays_(d) {}
		};
	};
	constexpr inline detail::package_day days(day_t d) { return detail::package_day(d); }
	inline Jd operator + (Jd const& jdn, detail::package_day days) { return Jd(jdn.jd() + days.nDays_); }
	inline Jd operator - (Jd const& jdn, detail::package_day days) { return Jd(jdn.jd() - days.nDays_); }

	/** Week addition/subtraction. */
	namespace detail {
		struct package_week {
			day_t nWeeks_;
			constexpr package_week(day_t w) :nWeeks_(w) {}
		};
	};
	constexpr inline detail::package_week weeks(day_t w) { return detail::package_week(w); }
	inline Jd operator + (Jd const& jdn, detail::package_week weeks) { return Jd(jdn.jd() + weeks.nWeeks_ * 7.0); }
	inline Jd operator - (Jd const& jdn, detail::package_week weeks) { return Jd(jdn.jd() - weeks.nWeeks_ * 7.0); }


	//** Month addition/subtraction. */
	namespace detail {
		struct packaged_month_integer {
			month_t nMonths_;
			packaged_month_integer(month_t m) : nMonths_(m) { }
		};
		struct packaged_month_real {
			double nMonths_;
			packaged_month_real(double m) : nMonths_(m) { }
		};
	};
	inline detail::packaged_month_real months(double m) { return detail::packaged_month_real(m); }
	inline detail::packaged_month_real months(float m) { return detail::packaged_month_real(m); }
	template <typename T> inline detail::packaged_month_integer months(T m) { return detail::packaged_month_integer(month_t(m)); }


	//** Year addition/subtraction. */
	namespace detail {
		/** Year as integer number wrapper. */
		struct packaged_year_integer {
			year_t nYears_;
			packaged_year_integer(year_t y) : nYears_(y) { }
		};
		/** Year as real number wrapper. */
		struct packaged_year_real {
			double nYears_;
			packaged_year_real(double y) : nYears_(y) { }
		};
	};
	/** Wrap a double literal into a real year package. */
	inline detail::packaged_year_real years(double y) { return detail::packaged_year_real(y); }

	/** Wrap a float literal into a real year package. */
	inline detail::packaged_year_real years(float y) { return detail::packaged_year_real(y); }

	/** Wrap all other literals into an integer year package (if possible). */
	template<typename T> inline detail::packaged_year_integer years(T y) { return detail::packaged_year_integer(static_cast<year_t>(y)); }

	/**	JD + (real years) */
	inline Jd operator + (Jd const& dt, detail::packaged_year_real const& year) {
		return Jd(dt.jd() + year.nYears_ * EARTH_ORBITAL_PERIOD_DAYS);
	}

	/**	JD - (real years) */
	inline Jd operator - (Jd const& dt, detail::packaged_year_real const& year) { return dt + detail::packaged_year_real(-year.nYears_); }

	/**	JD + (integer year) */
	inline Jd operator + (Jd const& dt, detail::packaged_year_integer const& year) { return dt + detail::packaged_year_real((double)year.nYears_); }

	/**	JD - (integer year) */
	inline Jd operator - (Jd const& dt, detail::packaged_year_integer const& year) { return dt + detail::packaged_year_integer(-year.nYears_); }




} // end-of-namespace khronos

// CLASSES
// --------------------------------------------------------------------------------------


/** @file ut_khronos_17_hebrew_conv.cpp
	@author Garth Santor
	@date 2016-09-30
	@version 1.1.0
	@note C++ 11/vc14
	@brief Khronos library Hebrew Calendar conversion unit test.
*/

#include <khronos.hpp>
#include "ut_Khronos.hpp"
#include <random>
#include <chrono>
using namespace std;

#if TEST_PHASES>=87
using namespace khronos;
#endif



/** Test known Hebrew to JD conversions. */
#if PHASE_87 && TEST_PHASES>=87
BEGIN_PHASE(87, test_hebrew_to_jd) {

	auto test = [](year_t year, month_t month, day_t day, jd_t jd)->bool {
		return hebrew_to_jd(year, month, day) == jd;
	};

	BOOST_CHECK(test(-952, Teveth, 20, -0.5));				// beginning of the Julian Epoch
	BOOST_CHECK(test(1, Nisan, 1, 348'175.5));			// January 1, 1
	BOOST_CHECK(test(5343, Tishri, 19, 2'299'160.5));			// Gregorian adoption date Spain, Portugal, Polish-Lithuanian Commonwealth, Papal
	BOOST_CHECK(test(5343, Kislev, 25, 2'299'226.5));			// Gregorian adoption date France
	BOOST_CHECK(test(5513, Tishri, 6, 2'361'221.5));		// Gregorian adoption date British Empire
	BOOST_CHECK(test(5619, Kislev, 9, 2'400'000 - 0.5));
	BOOST_CHECK(test(5772, Elul, 27, 2'456'184.5));
	BOOST_CHECK(test(5892, Elul, 19, 2'500'000 - 0.5));


	auto test2 = [](year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t seconds, jd_t jd) {
		auto result = hebrew_to_jd(year, month, day, hour, minute, seconds);
		BOOST_CHECK_EQUAL(result, jd);
	};
	test2(5892, Elul, 20, 12, 0, 0, 2'500'000);
	test2(5892, Elul, 19, 6, 0, 0, 2'500'000 - 0.25);
	test2(5892, Elul, 20, 18, 0, 0, 2'500'000 + 0.25);
	test2(5892, Elul, 20, 12, 0, 1, 2'500'000 + 1.0 / (24 * 60 * 60));
} END_PHASE()
#endif



#if PHASE_88 && TEST_PHASES>=88
/**	Test known JD to Hebrew conversions. */
BEGIN_PHASE(88, test_jd_to_hebrew) {

	auto test = [](year_t year, month_t month, day_t day, jd_t jd)->bool {
		year_t y;
		month_t m;
		day_t d;
		jd_to_hebrew(jd, y, m, d);
		return y == year && m == month && d == day;
	};

	BOOST_CHECK(test(-952, Teveth, 20, -0.5));				// beginning of the Julian Epoch
	BOOST_CHECK(test(1, Nisan, 1, 348'175.5));			// January 1, 1
	BOOST_CHECK(test(5343, Tishri, 19, 2'299'160.5));			// Gregorian adoption date Spain, Portugal, Polish-Lithuanian Commonwealth, Papal
	BOOST_CHECK(test(5343, Kislev, 25, 2'299'226.5));			// Gregorian adoption date France
	BOOST_CHECK(test(5513, Tishri, 6, 2'361'221.5));		// Gregorian adoption date British Empire
	BOOST_CHECK(test(5619, Kislev, 9, 2'400'000 - 0.5));
	BOOST_CHECK(test(5772, Elul, 27, 2'456'184.5));
	BOOST_CHECK(test(5892, Elul, 19, 2'500'000 - 0.5));


	auto test2 = [](year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t seconds, jd_t jd) {
		year_t y;
		month_t m;
		day_t d;
		hour_t h;
		minute_t mi;
		second_t s;
		jd_to_hebrew(jd, y, m, d, h, mi, s);
		BOOST_CHECK_EQUAL(y, year);
		BOOST_CHECK_EQUAL(m, month);
		BOOST_CHECK_EQUAL(d, day);
		BOOST_CHECK_EQUAL(h, hour);
		BOOST_CHECK_EQUAL(mi, minute);
		BOOST_CHECK_EQUAL(s, seconds);
	};
	auto start = 2'499'999.5;
	test2(5892, Elul, 19, 0, 0, 0, start);
	test2(5892, Elul, 19, 6, 0, 0, start + 0.25);
	test2(5892, Elul, 20, 12, 0, 0, start + 0.5);
	test2(5892, Elul, 20, 12, 0, 1, start + 0.5 + 1.0 / (24 * 60 * 60));
} END_PHASE()
#endif



#if PHASE_118 && TEST_PHASES>=118
#if defined( FULL_TEST )
/**	Check all conversions from the lowest Proleptic Gregorian date, until a day well in the future. */
BEGIN_PHASE(118, test_hebrew_full) {

	cout << "Starting Hebrew FULL_TEST: ";
	mt19937 engine((unsigned int)std::chrono::system_clock::now().time_since_epoch().count());

	uniform_int_distribution<int> yearDist(-2000, 10'000);
	auto yearGen = bind(yearDist, engine);
	for (auto iY = 0; iY < 20; ++iY) {
		year_t year = yearGen();
		uniform_int_distribution<int> monthDist(1, hebrew_months_in_year(year));
		auto monthGen = bind(monthDist, engine);
		for (auto iMon = 0; iMon < 10; ++iMon) {
			month_t month = (month_t)monthGen();
			uniform_int_distribution<int> dayDist(1, hebrew_days_in_month(year, month));
			auto dayGen = bind(dayDist, engine);
			for (auto iDay = 0; iDay < 10; ++iDay) {
				day_t day = (day_t)dayGen();
				uniform_int_distribution<int> hourDist(0, 23);
				auto hourGen = bind(hourDist, engine);
				for (auto iH = 0; iH < 10; ++iH) {
					hour_t hour = (hour_t)hourGen();
					uniform_int_distribution<int> minSecDist(0, 59);
					auto minSecGen = bind(minSecDist, engine);
					for (auto iMin = 0; iMin < 10; ++iMin) {
						minute_t minute = (minute_t)minSecGen();
						for (auto iSec = 0; iSec < 10; ++iSec) {
							second_t second = (second_t)minSecGen();

							jd_t jd = hebrew_to_jd(year, month, day);
							year_t ye;
							month_t mo;
							day_t da;
							jd_to_hebrew(jd, ye, mo, da);
							BOOST_CHECK_EQUAL(year, ye);
							BOOST_CHECK_EQUAL(month, mo);
							BOOST_CHECK_EQUAL(day, da);

							jd = hebrew_to_jd(year, month, day, hour, minute, second);
							hour_t ho;
							minute_t mi;
							second_t se;
							jd_to_hebrew(jd, ye, mo, da, ho, mi, se);
							BOOST_CHECK_EQUAL(year, ye);
							BOOST_CHECK_EQUAL(month, mo);
							BOOST_CHECK_EQUAL(day, da);
							BOOST_CHECK_EQUAL(hour, ho);
							BOOST_CHECK_EQUAL(minute, mi);
							BOOST_CHECK_EQUAL(second, se);
						}
					}
				}
			}
		}
	}
	cout << "... completed\n";
} END_PHASE()
#endif
#endif



/*============================================================================

Revision History

Version 1.1.0: 2016-09-30
Updated: Phase List

Version 1.0.0: 2015-09-21

==============================================================================
Copyright Garth Santor, 2015

The copyright to the computer program(s) herein
is the property of Garth Santor, Canada.
The program(s) may be used and/or copied only with
the written permission of Garth Santor
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
============================================================================*/

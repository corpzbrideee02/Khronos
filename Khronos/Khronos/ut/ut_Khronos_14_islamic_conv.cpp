/** @file ut_khronos_14_islamic_conv.cpp
	@author Garth Santor
	@date 2016-09-30
	@version 1.1.0
	@note C++ 11/vc14
	@brief Khronos library Islamic Calendar conversions unit test.
*/

#include <khronos.hpp>
#include "ut_Khronos.hpp"
using namespace std;

#if TEST_PHASES>=71
using namespace khronos;
#endif



/** Test known Islamic to JDN conversions. */
#if PHASE_71 && TEST_PHASES>=71
BEGIN_PHASE(71, test_islamic_to_jd) {

	auto test = [](year_t year, month_t month, day_t day, jd_t jdn)->bool {
		return islamic_to_jd(year, month, day) == jdn;
	};

	BOOST_CHECK(test(-5498, Shaban, 16, -0.5));			// beginning of the Julian Epoch
	BOOST_CHECK(test(1, Muharram, 1, ISLAMIC_EPOCH));	// Muharram 1, 1 A.H.
	BOOST_CHECK(test(990, Ramadan, 17, 2'299'160.5));		// Gregorian adoption date Spain, Portugal, Polish-Lithuanian Commonwealth, Papal
	BOOST_CHECK(test(990, DhulQadah, 24, 2'299'226.5));		// Gregorian adoption date France
	BOOST_CHECK(test(1165, DhulQadah, 5, 2'361'221.5));		// Gregorian adoption date British Empire
	BOOST_CHECK(test(1275, RabiathThani, 9, 2'400'000 - 0.5));
	BOOST_CHECK(test(1433, Shawwal, 27, 2'456'184.5));
	BOOST_CHECK(test(1557, JumadatTania, 18, 2'500'000 - 0.5));


	auto test2 = [](year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t seconds, jd_t jdn) {
		auto jd = islamic_to_jd(year, month, day, hour, minute, seconds);
		BOOST_CHECK_EQUAL(jd, jdn);
	};
	test2(1557, JumadatTania, 19, 12, 0, 0, 2'500'000);
	test2(1557, JumadatTania, 18, 6, 0, 0, 2'500'000 - 0.25);
	test2(1557, JumadatTania, 19, 18, 0, 0, 2'500'000 + 0.25);
	test2(1557, JumadatTania, 19, 12, 0, 1, 2'500'000 + 1.0 / (24 * 60 * 60));
} END_PHASE()
#endif



#if PHASE_72 && TEST_PHASES>=72
/**	Test known JDN to Islamic conversions. */
BEGIN_PHASE(72, test_jd_to_islamic) {

	auto test = [](year_t year, month_t month, day_t day, jd_t jd)->bool {
		year_t y;
		month_t m;
		day_t d;
		jd_to_islamic(jd, y, m, d);
		return y == year && m == month && d == day;
	};

	BOOST_CHECK(test(-5498, Shaban, 16, -0.5));				// beginning of the Julian Epoch
	BOOST_CHECK(test(1, Muharram, 1, ISLAMIC_EPOCH));		// January 1, 1 CE
	BOOST_CHECK(test(990, Ramadan, 17, 2'299'160.5));			// Gregorian adoption date Spain, Portugal, Polish-Lithuanian Commonwealth, Papal
	BOOST_CHECK(test(990, DhulQadah, 24, 2'299'226.5));		// Gregorian adoption date France
	BOOST_CHECK(test(1165, DhulQadah, 5, 2'361'221.5));		// Gregorian adoption date British Empire
	BOOST_CHECK(test(1275, RabiathThani, 9, 2'400'000 - 0.5));
	BOOST_CHECK(test(1433, Shawwal, 27, 2'456'184.5));
	BOOST_CHECK(test(1557, JumadatTania, 18, 2'500'000 - 0.5));


	auto test2 = [](year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t seconds, jd_t jd) {
		year_t y;
		month_t m;
		day_t d;
		hour_t h;
		minute_t mi;
		second_t s;
		jd_to_islamic(jd, y, m, d, h, mi, s);
		BOOST_CHECK_EQUAL(y, year);
		BOOST_CHECK_EQUAL(m, month);
		BOOST_CHECK_EQUAL(d, day);
		BOOST_CHECK_EQUAL(h, hour);
		BOOST_CHECK_EQUAL(mi, minute);
		BOOST_CHECK_EQUAL(s, seconds);
	};
	test2(1557, JumadatTania, 19, 12, 0, 0, 2'500'000);
	test2(1557, JumadatTania, 18, 6, 0, 0, 2'500'000 - 0.25);
	test2(1557, JumadatTania, 19, 18, 0, 0, 2'500'000 + 0.25);
	test2(1557, JumadatTania, 19, 12, 0, 1, 2'500'000 + 1.0 / (24 * 60 * 60));
} END_PHASE()
#endif



/**	Check all conversions from the lowest Proleptic Islamic date, until a day well in the future. */
#if PHASE_117 && TEST_PHASES>=117
#if defined( FULL_TEST )
BEGIN_PHASE(117, test_islamic_full) {
	cout << "Starting Islamic FULL_TEST: ";
	jd_t low = islamic_to_jd(-4799, 1, 1);
	jd_t high = islamic_to_jd(4800, 1, 1);
	for (jd_t jdn = low; jdn <= high; jdn += 1.0) {
		year_t year;
		month_t month;
		day_t day;
		jd_to_islamic(jdn, year, month, day);
		jd_t result = islamic_to_jd(year, month, day);
		BOOST_CHECK_EQUAL(jdn, result);
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

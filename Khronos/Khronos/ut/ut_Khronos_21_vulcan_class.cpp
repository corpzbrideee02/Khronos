/** @file ut_khronos_21_vulcan_class.cpp
	@author Garth Santor
	@date 2016-09-30
	@version 1.1.0
	@note C++ 11/vc14
	@brief Khronos library Vulcan Calendar class unit test.
*/

#include <khronos.hpp>
#include "ut_Khronos.hpp"
#include <ctime>
using namespace std;

#include "ut_utilities.hpp"

#if TEST_PHASES>=103
using namespace khronos;
#endif



/* Default constructor initializes to current time. */
#if PHASE_103 && TEST_PHASES>=103
BEGIN_PHASE(103, test_Vulcan_ctor_default) {
	time_t utcTime = time(NULL);
	Vulcan const	now;
	struct tm tmLocal;
	localtime_s(&tmLocal, &utcTime);

	Gregorian		localDateTime(
		year_t(tmLocal.tm_year) + 1900,
		month_t(tmLocal.tm_mon + 1),
		day_t(tmLocal.tm_mday),
		hour_t(tmLocal.tm_hour),
		minute_t(tmLocal.tm_min),
		second_t(tmLocal.tm_sec)
		);

	auto v = ((Jd)now).jd();
	auto g = ((Jd)localDateTime).jd();

	BOOST_CHECK_CLOSE(v, g, 0.000'01);
} END_PHASE()
#endif



#if PHASE_104 && TEST_PHASES>=104
BEGIN_PHASE(104, test_Vulcan_ctor_literal) {
	Vulcan const epochVulcan(-4712, Zat, 1);
	BOOST_CHECK(-4712 == epochVulcan.year());
	BOOST_CHECK(January == epochVulcan.month());
	BOOST_CHECK(1 == epochVulcan.day());

	Vulcan const greatWar(1918, October, 29, 11, 11, 11);
	BOOST_CHECK(1918 == greatWar.year());
	BOOST_CHECK(October == greatWar.month());
	BOOST_CHECK(29 == greatWar.day());
	BOOST_CHECK(11 == greatWar.hour());
	BOOST_CHECK(11 == greatWar.minute());
	BOOST_CHECK(11 == greatWar.second());
} END_PHASE()
#endif



#if PHASE_105 && TEST_PHASES>=105
BEGIN_PHASE(105, test_Vulcan_ctor_from_Jd) {
	Jd jd = VULCAN_EPOCH;
	Vulcan v(jd);
	BOOST_CHECK_EQUAL(v.year(), 1);
	BOOST_CHECK_EQUAL(v.month(), Zat);
	BOOST_CHECK_EQUAL(v.day(), 1);
	BOOST_CHECK_EQUAL(v.hour(), 0);
	BOOST_CHECK_EQUAL(v.minute(), 0);
	BOOST_CHECK_EQUAL(v.second(), 0);
} END_PHASE()
#endif



#if PHASE_106 && TEST_PHASES>=106
BEGIN_PHASE(106, test_Vulcan_cast_to_Jd) {
	Vulcan const	vulcanEpoch(1, Zat, 1);
	Jd je = vulcanEpoch;
	BOOST_CHECK_EQUAL(je.jd(), VULCAN_EPOCH);
} END_PHASE()
#endif



#if PHASE_107 && TEST_PHASES>=107
BEGIN_PHASE(107, test_Vulcan_assignment_from_Jd) {
	Vulcan g;
	g = Jd(VULCAN_EPOCH);
	BOOST_CHECK_EQUAL(g.year(), 1);
	BOOST_CHECK_EQUAL(g.month(), Zat);
	BOOST_CHECK_EQUAL(g.day(), 1);
	BOOST_CHECK_EQUAL(g.hour(), 0);
	BOOST_CHECK_EQUAL(g.minute(), 0);
	BOOST_CHECK_EQUAL(g.second(), 0);
} END_PHASE()
#endif



#if PHASE_108 && TEST_PHASES>=108
BEGIN_PHASE(108, test_Vulcan_add_days) {
	Vulcan d(1, Zat, 1);
	Vulcan res = d + days(10);
	BOOST_CHECK(res == Vulcan(1, Zat, 11));
	res = res - days(10);
	BOOST_CHECK(res == d);
} END_PHASE()
#endif



#if PHASE_109 && TEST_PHASES>=109
BEGIN_PHASE(109, test_Vulcan_add_days_with_time) {
	Vulcan d(2000, January, 1, 12, 13, 14);
	Vulcan res = d + days(10);
	BOOST_CHECK(res == Vulcan(2000, January, 11, 12, 13, 14));
	res = res - days(10);
	BOOST_CHECK(res == d);
} END_PHASE()
#endif



#if PHASE_110 && TEST_PHASES>=110
BEGIN_PHASE(110, test_Vulcan_add_months) {
	{	Vulcan start(2000, JAN, 1);
	Vulcan end(2000, FEB, 1);
	Vulcan res = start + months(1);
	BOOST_CHECK(end == res);
	res = end - months(1);
	BOOST_CHECK(res == start);
	}
	{	Vulcan start(2000, JAN, 1, 12, 13, 14);
	Vulcan end(2001, FEB, 1, 12, 13, 14);
	Vulcan res = start + months(13);
	BOOST_CHECK(end == res);
	res = end - months(13);
	BOOST_CHECK(res == start);
	}

	// shouldn't compile
	//start + months(1.2);
} END_PHASE()
#endif



#if PHASE_111 && TEST_PHASES>=111
BEGIN_PHASE(111, test_Vulcan_add_years) {
	Vulcan date(2000, January, 1);
	Vulcan result = date + years(10);
	BOOST_CHECK(Vulcan(2010, January, 1) == result);
	result = result - years(10);
	BOOST_CHECK(result == date);

	// The following won't compile (we made the operator private)
	//result = date + years(10.4);
} END_PHASE()
#endif



#if PHASE_112 && TEST_PHASES>=112
BEGIN_PHASE(112, test_Vulcan_relational) {
	Vulcan low(2009, 1, 1);
	Vulcan high(2009, 12, 31);
	Vulcan copyLow(low);

	BOOST_CHECK(low == copyLow);
	BOOST_CHECK(low < high);
	BOOST_CHECK(low <= copyLow);
	BOOST_CHECK(high >= low);
	BOOST_CHECK(high > low);
	BOOST_CHECK(high != low);
} END_PHASE()
#endif



#if PHASE_113 && TEST_PHASES>=113
BEGIN_PHASE(113, test_Vulcan_to_string) {
	BOOST_CHECK_EQUAL(Vulcan(1000, Zat, 1).to_string(), std::string("Z'at 1, 1000 0:00:00"));
	BOOST_CHECK_EQUAL(Vulcan(2000, reTKhutai, 21, 12, 30, 11).to_string(), std::string("re'T'Khutai 21, 2000 12:30:11"));
	BOOST_CHECK_EQUAL(Vulcan(2010, Tlakht, 12, 17, 45, 8).to_string(), std::string("T'lakht 12, 2010 17:45:08"));
	BOOST_CHECK_EQUAL(Vulcan(-100, Tasmeen, 1, 6, 7, 8).to_string(), std::string("Tasmeen 1, -100 6:07:08"));

	std::ostringstream oss;
	oss << Vulcan(2010, TaKrat, 12, 11, 45, 8);
	BOOST_CHECK_EQUAL(oss.str(), std::string("Ta'Krat 12, 2010 11:45:08"));
} END_PHASE()
#endif



#if PHASE_114 && TEST_PHASES>=114
BEGIN_PHASE(114, test_Vulcan_element_functions) {
	Vulcan g(2010, Tasmeen, 12, 23, 45, 8);
	BOOST_CHECK_EQUAL(year(g), 2010);
	BOOST_CHECK_EQUAL(month(g), Tasmeen);
	BOOST_CHECK_EQUAL(day(g), 12);
	BOOST_CHECK_EQUAL(hour(g), 23);
	BOOST_CHECK_EQUAL(minute(g), 45);
	BOOST_CHECK_EQUAL(second(g), 8);
} END_PHASE()
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

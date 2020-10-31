/** @file ut_khronos_15_islamic_class.cpp
	@author Garth Santor
	@date 2016-09-30
	@version 1.1.0
	@note C++ 11/vc14
	@brief Khronos library Islamic Calendar class unit test.
*/

#include <khronos.hpp>
#include "ut_Khronos.hpp"
#include <ctime>
using namespace std;

#if TEST_PHASES>=73
using namespace khronos;
#endif




#if PHASE_73 && TEST_PHASES>=73
/* Default constructor initializes to current time. */
BEGIN_PHASE(73, Islamic_ctor_default) {
	time_t utcTime = time(NULL);
	Islamic const now;
	Islamic const today(NOTIMEOFDAY);
	struct tm tmLocal;
	localtime_s(&tmLocal, &utcTime);

	Gregorian localDateTime(
		year_t(tmLocal.tm_year) + 1900,
		month_t(tmLocal.tm_mon) + 1,
		day_t(tmLocal.tm_mday),
		hour_t(tmLocal.tm_hour),
		minute_t(tmLocal.tm_min),
		second_t(tmLocal.tm_sec)
		);

	Gregorian localDate(
		year_t(tmLocal.tm_year) + 1900,
		month_t(tmLocal.tm_mon) + 1,
		day_t(tmLocal.tm_mday)
		);

	BOOST_CHECK(localDateTime == now);
	BOOST_CHECK(localDate == today);
} END_PHASE()
#endif



#if PHASE_74 && TEST_PHASES>=74
BEGIN_PHASE(74, test_Islamic_ctor_literal) {
	Islamic const	islamicEpoch(1, Muharram, 1);
	BOOST_CHECK(1 == islamicEpoch.year());
	BOOST_CHECK(Muharram == islamicEpoch.month());
	BOOST_CHECK(1 == islamicEpoch.day());

	Islamic const aDay(1434, DhulHijja, 1, 12, 30, 45);
	BOOST_CHECK(1434 == aDay.year());
	BOOST_CHECK(DhulHijja == aDay.month());
	BOOST_CHECK(1 == aDay.day());
	BOOST_CHECK(12 == aDay.hour());
	BOOST_CHECK(30 == aDay.minute());
	BOOST_CHECK(45 == aDay.second());
} END_PHASE()
#endif



#if PHASE_75 && TEST_PHASES>=75
BEGIN_PHASE(75, test_Islamic_ctor_from_Jd) {
	Islamic i(Jd(0.0));
	BOOST_CHECK_EQUAL(i.year(), -5498);
	BOOST_CHECK_EQUAL(i.month(), Shaban);
	BOOST_CHECK_EQUAL(i.day(), 17);
	BOOST_CHECK_EQUAL(i.hour(), 12);
	BOOST_CHECK_EQUAL(i.minute(), 0);
	BOOST_CHECK_EQUAL(i.second(), 0);
} END_PHASE()
#endif



#if PHASE_76 && TEST_PHASES>=76
BEGIN_PHASE(76, test_Islamic_cast_to_Jd) {
	Islamic const	i(-5498, Shaban, 17, 12, 0, 0);
	Jd je = i;
	BOOST_CHECK_EQUAL(je.jd(), 0.0);
} END_PHASE()
#endif



#if PHASE_77 && TEST_PHASES>=77
BEGIN_PHASE(77, test_Islamic_assignment_from_Jd) {
	Islamic i;
	i = Jd(0.0);
	BOOST_CHECK_EQUAL(i.year(), -5498);
	BOOST_CHECK_EQUAL(i.month(), Shaban);
	BOOST_CHECK_EQUAL(i.day(), 17);
	BOOST_CHECK_EQUAL(i.hour(), 12);
	BOOST_CHECK_EQUAL(i.minute(), 0);
	BOOST_CHECK_EQUAL(i.second(), 0);
} END_PHASE()
#endif



#if PHASE_78 && TEST_PHASES>=78
BEGIN_PHASE(78, test_Islamic_add_days) {
	Islamic date(1434, DhulHijja, 17);
	Islamic res = date + days(100);
	BOOST_CHECK(res == Islamic(1435, RabialAwwal, 28));
	res = res - days(100);
	BOOST_CHECK(res == date);
} END_PHASE()
#endif



#if PHASE_79 && TEST_PHASES>=79
BEGIN_PHASE(79, test_Islamic_add_weeks) {
	Islamic date(1400, Muharram, 1);
	Islamic res = date + weeks(10);
	BOOST_CHECK(date + days(70) == res);
	res = res - weeks(10);
	BOOST_CHECK(date == res);
} END_PHASE()
#endif



#if PHASE_80 && TEST_PHASES>=80
BEGIN_PHASE(80, test_Islamic_add_months) {
	Islamic start(1400, Muharram, 1);
	{
		Islamic end(1400, Safar, 1);
		Islamic res = start + months(1);
		BOOST_CHECK(end == res);
		res = end - months(1);
		BOOST_CHECK(res == start);
	}
	{	Islamic end(1401, Safar, 1);
	Islamic res = start + months(13);
	BOOST_CHECK_EQUAL(end, res);
	res = end - months(13);
	BOOST_CHECK_EQUAL(res, start);
	}

	// shouldn't compile
	// start + months(1.2);
} END_PHASE()
#endif



#if PHASE_81 && TEST_PHASES>=81
BEGIN_PHASE(81, test_Islamic_add_month_leap) {

	{	Islamic start(1401, Muharram, 30);
	Islamic forward(1401, Safar, 29);
	Islamic back(1401, Muharram, 29);

	auto result = start + months(1);
	BOOST_CHECK(result == forward);
	result = forward - months(1);
	BOOST_CHECK(result == back);
	}

	{	Islamic start(1434, DhulQadah, 30, 6, 7, 8);
	Islamic forward(1434, DhulHijja, 30, 6, 7, 8);
	Islamic back(1434, DhulQadah, 30, 6, 7, 8);

	auto result = start + months(1);
	BOOST_CHECK(result == forward);
	result = forward - months(1);
	BOOST_CHECK(result == back);
	}

	{	Islamic start(1435, DhulQadah, 30, 12, 13, 14);
	Islamic forward(1435, DhulHijja, 29, 12, 13, 14);
	Islamic back(1435, DhulQadah, 29, 12, 13, 14);

	auto result = start + months(1);
	BOOST_CHECK(result == forward);
	result = forward - months(1);
	BOOST_CHECK(result == back);
	}
} END_PHASE()
#endif



#if PHASE_82 && TEST_PHASES>=82
BEGIN_PHASE(82, test_Islamic_add_years) {
	Islamic date(1433, Muharram, 1);
	Islamic res = date + years(10);
	BOOST_CHECK(Islamic(1443, Muharram, 1) == res);
	res = res - years(10);
	BOOST_CHECK(res == date);

	// The following won't compile (we made the operator private)
	//res = date + years(10.4);
} END_PHASE()
#endif



#if PHASE_83 && TEST_PHASES>=83
BEGIN_PHASE(83, test_Islamic_add_years_leapyear) {
	Islamic date(1434, DhulHijja, 30, 6, 7, 8);
	Islamic later = date + years(2);
	BOOST_CHECK(Islamic(1436, DhulHijja, 30, 6, 7, 8) == later);
	later = date + years(3);
	BOOST_CHECK(Islamic(1437, DhulHijja, 29, 6, 7, 8) == later);
} END_PHASE()
#endif



#if PHASE_84 && TEST_PHASES>=84
BEGIN_PHASE(84, test_Islamic_relational) {
	Islamic low(1400, Muharram, 1);
	Islamic high(1400, DhulHijja, 29);
	Islamic copyLow(low);

	BOOST_CHECK(low == copyLow);
	BOOST_CHECK(low < high);
	BOOST_CHECK(low <= copyLow);
	BOOST_CHECK(high >= low);
	BOOST_CHECK(high > low);
	BOOST_CHECK(high != low);
} END_PHASE()
#endif



#if PHASE_85 && TEST_PHASES>=85
BEGIN_PHASE(85, test_Islamic_to_string) {
	BOOST_CHECK_EQUAL(Islamic(1000, Muharram, 1).to_string(), std::string("as-sabt, Muharram 1 1000, 12:00:00 am"));
	BOOST_CHECK_EQUAL(Islamic(2000, Safar, 29, 12, 0, 0).to_string(), std::string("as-sabt, Safar 29 2000, 12:00:00 pm"));
	BOOST_CHECK_EQUAL(Islamic(2010, Rajab, 12, 23, 45, 8).to_string(), std::string("al-jum`a, Rajab 12 2010, 11:45:08 pm"));
	BOOST_CHECK_EQUAL(Islamic(-100, Muharram, 1, 6, 7, 8).to_string(), std::string("al-jum`a, Muharram 1 -100, 6:07:08 am"));

	std::ostringstream oss;
	oss << Islamic(2010, Shawwal, 12, 23, 45, 8);
	BOOST_CHECK_EQUAL(oss.str(), std::string("al-'arb`a', Shawwal 12 2010, 11:45:08 pm"));
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

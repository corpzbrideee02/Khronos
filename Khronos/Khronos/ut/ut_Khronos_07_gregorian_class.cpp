/** @file ut_khronos_07_gregorian_class.cpp
	@author Garth Santor
	@date 2016-09-30
	@version 1.1.0
	@note C++ 11/vc14
	@brief Khronos library Gregorian class unit test.
	*/

#include <khronos.hpp>
#include "ut_Khronos.hpp"
#include <ctime>

#if TEST_PHASES>=20
using namespace khronos;
#endif



#if PHASE_20 && TEST_PHASES>=20
BEGIN_PHASE(20, gregorian_differences) {
	Gregorian past(1858, 11, 16);
	Gregorian future(2132, 8, 31);

	BOOST_CHECK(future - past == 100'000);
	BOOST_CHECK(past - future == -100'000);

	Gregorian start(2000, 1, 1);
	Gregorian end(2001, 1, 1);

	BOOST_CHECK(end - start == 366);
	BOOST_CHECK(start - end == -366);
} END_PHASE()
#endif





#if PHASE_21 && TEST_PHASES>=21
/* Default constructor initializes to current time. */
BEGIN_PHASE(21, test_Gregorian_ctor_default) {
	time_t utcTime = time(NULL);
	Gregorian const now;
	Gregorian const today(NOTIMEOFDAY);
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



#if PHASE_22 && TEST_PHASES>=22
BEGIN_PHASE(22, test_gregorian_ctor_literal) {
	Gregorian const	julianEpoch(-4713, November, 24);
	BOOST_CHECK(-4713 == julianEpoch.year());
	BOOST_CHECK(November == julianEpoch.month());
	BOOST_CHECK(24 == julianEpoch.day());

	Gregorian const greatWar(1918, NOV, 11, 11, 11, 11);
	BOOST_CHECK(1918 == greatWar.year());
	BOOST_CHECK(November == greatWar.month());
	BOOST_CHECK(11 == greatWar.day());
	BOOST_CHECK(11 == greatWar.hour());
	BOOST_CHECK(11 == greatWar.minute());
	BOOST_CHECK(11 == greatWar.second());
} END_PHASE()
#endif



#if PHASE_23 && TEST_PHASES>=23
BEGIN_PHASE(23, test_Gregorian_ctor_from_Jd) {
	Gregorian g(Jd(-0.5));
	BOOST_CHECK_EQUAL(g.year(), -4713);
	BOOST_CHECK_EQUAL(g.month(), November);
	BOOST_CHECK_EQUAL(g.day(), 24);
	BOOST_CHECK_EQUAL(g.hour(), 0);
	BOOST_CHECK_EQUAL(g.minute(), 0);
	BOOST_CHECK_EQUAL(g.second(), 0);
} END_PHASE()
#endif



#if PHASE_24 && TEST_PHASES>=24
BEGIN_PHASE(24, test_Gregorian_cast_to_Jd) {
	Gregorian const	julianEpoch(-4713, November, 24);
	Jd je = julianEpoch;
	BOOST_CHECK_EQUAL(je.jd(), -0.5);
} END_PHASE()
#endif



#if PHASE_25 && TEST_PHASES>=25
BEGIN_PHASE(25, test_Gregorian_assignment_from_Jd) {
	Gregorian g;
	g = Jd(-0.5);
	BOOST_CHECK_EQUAL(g.year(), -4713);
	BOOST_CHECK_EQUAL(g.month(), November);
	BOOST_CHECK_EQUAL(g.day(), 24);
	BOOST_CHECK_EQUAL(g.hour(), 0);
	BOOST_CHECK_EQUAL(g.minute(), 0);
	BOOST_CHECK_EQUAL(g.second(), 0);
} END_PHASE()
#endif



#if PHASE_26 && TEST_PHASES>=26
BEGIN_PHASE(26, test_Gregorian_add_days) {
	Gregorian date(2000, January, 1);
	Gregorian res = date + days(10);
	BOOST_CHECK(res == Gregorian(2000, January, 11));
	res = res - days(10);
	BOOST_CHECK(res == date);
} END_PHASE()
#endif



#if PHASE_27 && TEST_PHASES>=27
BEGIN_PHASE(27, test_Gregorian_add_days_with_time) {
	Gregorian date(2000, January, 1, 12, 13, 14);
	Gregorian res = date + days(10);
	BOOST_CHECK(res == Gregorian(2000, January, 11, 12, 13, 14));
	res = res - days(10);
	BOOST_CHECK(res == date);
} END_PHASE()
#endif



#if PHASE_28 && TEST_PHASES>=28
BEGIN_PHASE(28, test_Gregorian_add_weeks) {
	Gregorian date(2000, JAN, 1);
	Gregorian res = date + weeks(10);
	BOOST_CHECK(date + days(70) == res);
	res = res - weeks(10);
	BOOST_CHECK(date == res);
} END_PHASE()
#endif



#if PHASE_29 && TEST_PHASES>=29
BEGIN_PHASE(29, test_Gregorian_add_weeks_with_time) {
	Gregorian date(2000, JAN, 1, 6, 7, 8);
	Gregorian res = date + weeks(10);
	BOOST_CHECK(date + days(70) == res);
	res = res - weeks(10);
	BOOST_CHECK(date == res);
} END_PHASE()
#endif



#if PHASE_30 && TEST_PHASES>=30
BEGIN_PHASE(30, test_Gregorian_add_months) {
	{	Gregorian start(2000, JAN, 1);
	Gregorian end(2000, FEB, 1);
	Gregorian res = start + months(1);
	BOOST_CHECK(end == res);
	res = end - months(1);
	BOOST_CHECK(res == start);
	}
	{	Gregorian start(2000, JAN, 1, 12, 13, 14);
	Gregorian end(2001, FEB, 1, 12, 13, 14);
	Gregorian res = start + months(13);
	BOOST_CHECK(end == res);
	res = end - months(13);
	BOOST_CHECK(res == start);
	}

	// shouldn't compile
	// start + months(1.2);
} END_PHASE()
#endif



#if PHASE_31 && TEST_PHASES>=31
BEGIN_PHASE(31, test_Gregorian_add_months_w_carry) {

	{	Gregorian start(2000, OCT, 1);
	Gregorian end(2001, FEB, 1);
	Gregorian res = start + months(4);
	BOOST_CHECK(end == res);
	res = end - months(4);
	BOOST_CHECK(res == start);
	}
	{	Gregorian start(2000, OCT, 1, 6, 7, 8);
	Gregorian end(2003, FEB, 1, 6, 7, 8);
	Gregorian res = start + months(28);
	BOOST_CHECK(end == res);
	res = end - months(28);
	BOOST_CHECK(res == start);
	}
} END_PHASE()
#endif



#if PHASE_32 && TEST_PHASES>=32
BEGIN_PHASE(32, test_Gregorian_add_month_leap) {

	{	Gregorian start(2000, February, 29, 12, 13, 14);
	Gregorian end(2000, March, 29, 12, 13, 14);
	Gregorian res = start + months(1);
	BOOST_CHECK(end == res);
	res = end - months(1);
	BOOST_CHECK(res == start);
	}
	{	Gregorian start(2000, January, 31, 6, 7, 8);
	Gregorian end(2000, February, 29, 6, 7, 8);
	Gregorian res = start + months(1);
	BOOST_CHECK(end == res);
	res = end - months(1);
	BOOST_CHECK(res == Gregorian(2000, January, 29, 6, 7, 8));
	}
} END_PHASE()
#endif



#if PHASE_33 && TEST_PHASES>=33
BEGIN_PHASE(33, test_Gregorian_add_years) {
	Gregorian date(2000, January, 1, 6, 7, 8);
	Gregorian res = date + years(10);
	BOOST_CHECK(Gregorian(2010, January, 1, 6, 7, 8) == res);
	res = res - years(10);
	BOOST_CHECK(res == date);

	// The following won't compile (we made the operator private)
	//res = date + years(10.4);
} END_PHASE()
#endif



#if PHASE_34 && TEST_PHASES>=34
BEGIN_PHASE(34, test_Gregorian_add_years_leapyear) {
	Gregorian date(2000, February, 29, 12, 13, 14);
	Gregorian later = date + years(2);
	BOOST_CHECK(Gregorian(2002, February, 28, 12, 13, 14) == later);
} END_PHASE()
#endif



#if PHASE_35 && TEST_PHASES>=35
BEGIN_PHASE(35, test_Gregorian_relational) {
	Gregorian low(2009, January, 1);
	Gregorian high(2009, December, 31);
	Gregorian copyLow(low);

	BOOST_CHECK(low == copyLow);
	BOOST_CHECK(low < high);
	BOOST_CHECK(low <= copyLow);
	BOOST_CHECK(high >= low);
	BOOST_CHECK(high > low);
	BOOST_CHECK(high != low);
} END_PHASE()
#endif



#if PHASE_36 && TEST_PHASES>=36
BEGIN_PHASE(36, test_Gregorian_element_functions) {
	Gregorian g(2010, September, 12, 23, 45, 8);
	BOOST_CHECK_EQUAL(year(g), 2010);
	BOOST_CHECK_EQUAL(month(g), September);
	BOOST_CHECK_EQUAL(day(g), 12);
	BOOST_CHECK_EQUAL(hour(g), 23);
	BOOST_CHECK_EQUAL(minute(g), 45);
	BOOST_CHECK_EQUAL(second(g), 8);
} END_PHASE()
#endif




#if PHASE_37 && TEST_PHASES>37
BEGIN_PHASE(37, test_Gregorian_to_string) {
	BOOST_CHECK_EQUAL(Gregorian(1000, January, 1).to_string(), std::string("Wednesday, January 1 1000 CE, 12:00:00 am"));
	BOOST_CHECK_EQUAL(Gregorian(2000, February, 29, 12, 30, 11).to_string(), std::string("Tuesday, February 29 2000 CE, 12:30:11 pm"));
	BOOST_CHECK_EQUAL(Gregorian(2010, September, 12, 23, 45, 8).to_string(), std::string("Sunday, September 12 2010 CE, 11:45:08 pm"));
	BOOST_CHECK_EQUAL(Gregorian(101_BCE, January, 1, 6, 7, 8).to_string(), std::string("Monday, January 1 101 BCE, 6:07:08 am"));

	std::ostringstream oss;
	oss << Gregorian(2010, September, 12, 23, 45, 8);
	BOOST_CHECK_EQUAL(oss.str(), std::string("Sunday, September 12 2010 CE, 11:45:08 pm"));
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

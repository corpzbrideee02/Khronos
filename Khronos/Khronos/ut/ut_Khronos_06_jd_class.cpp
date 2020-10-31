/** @file ut_khronos_06_jd_class.cpp
	@author Garth Santor
	@date 2016-09-30
	@version 1.1.0
	@note C++ 11/vc14
	@brief Khronos library Julian Day unit test.
	*/

#include <khronos.hpp>
#include "ut_Khronos.hpp"
#include <ctime>
using namespace std;

#if TEST_PHASES>=10
using namespace khronos;
#endif



#if PHASE_10 && TEST_PHASES>=10
BEGIN_PHASE(10, Jdn_differences) {
	Jd past(1000);
	Jd future(2000);

	BOOST_CHECK(future - past == 1000);
	BOOST_CHECK(past - future == -1000);
} END_PHASE()
#endif



/* Default constructor initializes to current time. */
#if PHASE_11 && TEST_PHASES>=11
BEGIN_PHASE(11, test_Jd_ctor_default) {
	time_t utcTime = time(NULL);
	Jd const nowJD;

	struct tm tmLocal;
	localtime_s(&tmLocal, &utcTime);
	jd_t jd = gregorian_to_jd(
		year_t(tmLocal.tm_year) + 1900, month_t(tmLocal.tm_mon + 1), day_t(tmLocal.tm_mday),
		hour_t(tmLocal.tm_hour), minute_t(tmLocal.tm_min), second_t(tmLocal.tm_sec));

	BOOST_CHECK_EQUAL(nowJD, jd);
} END_PHASE()
#endif



/* Default constructor initializes to current time suppressing time of day. */
#if PHASE_12 && TEST_PHASES>=12
BEGIN_PHASE(12, test_Jd_ctor_default_no_time_of_day) {
	time_t utcTime = time(NULL);
	struct tm tmLocal;
	localtime_s(&tmLocal, &utcTime);
	Jd const nowJD(WTIMEOFDAY);
	Jd const nowJDN(NOTIMEOFDAY);

	jd_t jdn = gregorian_to_jd(year_t(tmLocal.tm_year) + 1900, month_t(tmLocal.tm_mon + 1), day_t(tmLocal.tm_mday));
	BOOST_CHECK_EQUAL(nowJDN.jd(), jdn);

	jd_t jd = gregorian_to_jd(
		year_t(tmLocal.tm_year) + 1900, month_t(tmLocal.tm_mon + 1), day_t(tmLocal.tm_mday),
		hour_t(tmLocal.tm_hour), minute_t(tmLocal.tm_min), second_t(tmLocal.tm_sec));
	BOOST_CHECK_EQUAL(nowJD, jd);
} END_PHASE()
#endif



/** Test literal constructors. */
#if PHASE_13 && TEST_PHASES>=13
BEGIN_PHASE(13, test_Jd_ctor_literal) {
	Jd const epochJdn(-0.5);
	BOOST_CHECK(-0.5 == epochJdn);
} END_PHASE()
#endif // TEST_PHASES 11



#if PHASE_14 && TEST_PHASES>=14
BEGIN_PHASE(14, test_Jd_add_days) {
	Jd d(2000);
	Jd res = d + days(10);
	BOOST_CHECK(res.jd() == 2010);
	res = res - days(10);
	BOOST_CHECK(res.jd() == 2000);
} END_PHASE()
#endif



#if PHASE_15 && TEST_PHASES>=15
BEGIN_PHASE(15, test_Jd_add_weeks) {
	Jd d(2000);
	Jd res = d + weeks(10);
	BOOST_CHECK(d + days(70) == res);
	res = res - weeks(10);
	BOOST_CHECK(d == res);
} END_PHASE()
#endif



#if PHASE_16 && TEST_PHASES>=16
BEGIN_PHASE(16, test_Jd_add_years) {
	Jd d = 2000;
	double const astroYears = 10.4;
	Jd res = d + years(astroYears);
	BOOST_CHECK(2000 + EARTH_ORBITAL_PERIOD_DAYS * astroYears == res);
	res = d - years(astroYears);
	BOOST_CHECK(2000 - EARTH_ORBITAL_PERIOD_DAYS * astroYears == res);
} END_PHASE()
#endif



#if PHASE_17 && TEST_PHASES>=17
BEGIN_PHASE(17, test_Jd_day_of_week) {
	Gregorian g(2012, September, 24);  // a monday

	BOOST_CHECK(day_of_week(g) == Monday);
} END_PHASE()
#endif



#if PHASE_18 && TEST_PHASES>=18
BEGIN_PHASE(18, Test_Jd_relational) {
	Jd low(2009);
	Jd high(2010);
	Jd copyLow(low);

	BOOST_CHECK(low == copyLow);
	BOOST_CHECK(low < high);
	BOOST_CHECK(low <= copyLow);
	BOOST_CHECK(high >= low);
	BOOST_CHECK(high > low);
	BOOST_CHECK(high != low);
} END_PHASE()
#endif



#if PHASE_19 && TEST_PHASES>=19
BEGIN_PHASE(19, test_Jd_to_string) {
	BOOST_CHECK_EQUAL(Jd(0).to_string(), std::string("JD 0"));
	BOOST_CHECK_EQUAL(Jd(10'000).to_string(), std::string("JD 10000"));
	BOOST_CHECK_EQUAL(Jd(-10).to_string(), std::string("JD -10"));

	std::ostringstream oss;
	oss << Jd(0.5);
	BOOST_CHECK_EQUAL(oss.str(), std::string("JD 0.5"));
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

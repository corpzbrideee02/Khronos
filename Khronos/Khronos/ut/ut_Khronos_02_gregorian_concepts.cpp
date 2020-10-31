/** @file ut_khronos_02_gregorian_concepts.cpp
	@author Garth Santor
	@date 2016-09-30
	@version 1.1.0
	@note C++ 11/vc14
	@brief Khronos library Gregorian to Jd functions unit test.
	*/

#include <khronos.hpp>
#include "ut_Khronos.hpp"
#include <array>
#include <string>

#if TEST_PHASES>=4
using namespace khronos;
#endif


#if PHASE_4 && TEST_PHASES>=4
BEGIN_PHASE(4, test_Gregorian_leapyear_test) {
	BOOST_CHECK_EQUAL(is_gregorian_leapyear(2000_CE), true);
	BOOST_CHECK_EQUAL(is_gregorian_leapyear(1999_CE), false);
	BOOST_CHECK_EQUAL(is_gregorian_leapyear(1996_CE), true);
	BOOST_CHECK_EQUAL(is_gregorian_leapyear(2001_CE), false);
	BOOST_CHECK_EQUAL(is_gregorian_leapyear(2004_CE), true);
	BOOST_CHECK_EQUAL(is_gregorian_leapyear(1900_CE), false);
	BOOST_CHECK_EQUAL(is_gregorian_leapyear(1600_CE), true);
	BOOST_CHECK_EQUAL(is_gregorian_leapyear(4_CE), true);
	BOOST_CHECK_EQUAL(is_gregorian_leapyear(1_CE), false);
	BOOST_CHECK_EQUAL(is_gregorian_leapyear(1_BCE), true);
	BOOST_CHECK_EQUAL(is_gregorian_leapyear(2_BCE), false);
	BOOST_CHECK_EQUAL(is_gregorian_leapyear(4_BCE), false);
	BOOST_CHECK_EQUAL(is_gregorian_leapyear(5_BCE), true);
	BOOST_CHECK_EQUAL(is_gregorian_leapyear(6_BCE), false);
} END_PHASE()
#endif



#if PHASE_5 && TEST_PHASES>=5
BEGIN_PHASE(5, test_Gregorian_days_of_month) {
	BOOST_CHECK_EQUAL(gregorian_days_in_month(JAN, false), 31);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(FEB, false), 28);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(MAR, false), 31);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(APR, false), 30);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(MAY, false), 31);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(JUN, false), 30);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(JUL, false), 31);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(AUG, false), 31);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(SEP, false), 30);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(OCT, false), 31);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(NOV, false), 30);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(DEC, false), 31);

	BOOST_CHECK_EQUAL(gregorian_days_in_month(JAN, true), 31);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(FEB, true), 29);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(MAR, true), 31);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(APR, true), 30);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(MAY, true), 31);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(JUN, true), 30);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(JUL, true), 31);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(AUG, true), 31);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(SEP, true), 30);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(OCT, true), 31);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(NOV, true), 30);
	BOOST_CHECK_EQUAL(gregorian_days_in_month(DEC, true), 31);
} END_PHASE()
#endif



#if PHASE_6 && TEST_PHASES>=6
BEGIN_PHASE(6, test_Gregorian_month_name) {
	static std::array<std::string const, 13> const names = { "", "January", "February", "March",
		"April", "May", "June", "July", "August", "September", "October",
		"November", "December" };

	for (month_t i = JAN; i <= DEC; ++i)
		BOOST_CHECK(gregorian_month_name(i) == names[i]);

	for (month_t i = JAN; i <= DEC; ++i) {
		auto s = names[i].substr(0, 3);
		s[1] = (char)toupper(s[1]);
		s[2] = (char)toupper(s[2]);
		BOOST_CHECK(gregorian_short_month_name(i) == s);
	}
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

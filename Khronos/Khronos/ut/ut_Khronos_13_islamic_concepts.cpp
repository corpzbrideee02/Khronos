/** @file ut_khronos_13_islamic_concepts.cpp
	@author Garth Santor
	@date 2016-09-30
	@version 1.1.0
	@note C++ 11/vc14
	@brief Khronos library Islamic Calendar concepts unit test.
*/

#include <khronos.hpp>
#include "ut_Khronos.hpp"
#include <array>
using namespace std;

#if TEST_PHASES>=68
using namespace khronos;
#endif



#if PHASE_68 && TEST_PHASES>=68
BEGIN_PHASE(68, test_Islamic_leapyear_test) {
	BOOST_CHECK_EQUAL(is_islamic_leapyear(1400), false);
	BOOST_CHECK_EQUAL(is_islamic_leapyear(1401), true);
	BOOST_CHECK_EQUAL(is_islamic_leapyear(1402), false);
	BOOST_CHECK_EQUAL(is_islamic_leapyear(1403), false);
	BOOST_CHECK_EQUAL(is_islamic_leapyear(1404), true);
	BOOST_CHECK_EQUAL(is_islamic_leapyear(1405), false);
	BOOST_CHECK_EQUAL(is_islamic_leapyear(0), false);
	BOOST_CHECK_EQUAL(is_islamic_leapyear(-1), true);
} END_PHASE()
#endif



#if PHASE_69 && TEST_PHASES>=69
/** Check islamic leap years. */
BEGIN_PHASE(69, test_islamic_leapyear) {
	BOOST_CHECK_EQUAL(is_islamic_leapyear(-5498), true);				// beginning of the Julian Epoch
	BOOST_CHECK_EQUAL(is_islamic_leapyear(1), false);					// Muharram 1, 1 A.H.
	BOOST_CHECK_EQUAL(is_islamic_leapyear(990), false);					// Gregorian adoption date Spain, Portugal, Polish-Lithuanian Commonwealth, Papal
	BOOST_CHECK_EQUAL(is_islamic_leapyear(1165), false);				// Gregorian adoption date British Empire
	BOOST_CHECK_EQUAL(is_islamic_leapyear(1275), false);
	BOOST_CHECK_EQUAL(is_islamic_leapyear(1433), false);
	BOOST_CHECK_EQUAL(is_islamic_leapyear(1434), true);
	BOOST_CHECK_EQUAL(is_islamic_leapyear(1557), false);
} END_PHASE()
#endif



#if PHASE_70 && TEST_PHASES>=70
BEGIN_PHASE(70, test_Islamic_month_name) {
	std::array<std::string, 13> const names = { "", "Muharram", "Safar", "Rabi'al-Awwal",
		"Rabi'ath-Thani", "Jumada I-Ula", "Jumada t-Tania", "Rajab", "Sha'ban", "Ramadan", "Shawwal",
		"Dhu I-Qa'da", "Dhu I-Hijja" };

	for (month_t i = 1; i <= 12; ++i)
		BOOST_CHECK(islamic_month_name(i) == names[i]);
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

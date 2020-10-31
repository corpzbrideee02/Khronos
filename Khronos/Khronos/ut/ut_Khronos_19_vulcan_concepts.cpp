/** @file ut_khronos_19_vulcan_concepts.cpp
	@author Garth Santor
	@date 2016-09-30
	@version 1.1.0
	@note C++ 11/vc14
	@brief Khronos library Vulcan Calendar concepts unit test.
*/

#include <khronos.hpp>
#include "ut_Khronos.hpp"
#include "ut_utilities.hpp"
#include <array>

#if TEST_PHASES>=98
using namespace khronos;
#endif




#if PHASE_98 && TEST_PHASES>=98
BEGIN_PHASE(98, test_vulcan_days_of_month) {
	BOOST_CHECK_EQUAL(vulcan_days_in_month(), 21);
} END_PHASE()
#endif



#if PHASE_99 && TEST_PHASES>=99
BEGIN_PHASE(99, test_Vulcan_month_name) {
	static std::array<char const *, 13> const names = {
		"",
		"Z'at",
		"D'ruh",
		"K'riBrax",
		"re'T'Khutai",
		"T'keKhuti",
		"Khuti",
		"Ta'Krat",
		"K'ri'lior",
		"et'khior",
		"T'lakht",
		"T'ke'Tas",
		"Tasmeen",
	};

	for (month_t i = 1; i <= 12; ++i)
		BOOST_CHECK(vulcan_month_name(i) == names[i]);
} END_PHASE()
#endif



#if PHASE_100 && TEST_PHASES>=100
/** Test Vulcan month names. */
BEGIN_PHASE(100, test_vulcan_month_names) {
	BOOST_CHECK(boost_compare("Z'at", vulcan_month_name(1)));
	BOOST_CHECK(boost_compare("D'ruh", vulcan_month_name(2)));
	BOOST_CHECK(boost_compare("K'riBrax", vulcan_month_name(3)));
	BOOST_CHECK(boost_compare("re'T'Khutai", vulcan_month_name(4)));
	BOOST_CHECK(boost_compare("T'keKhuti", vulcan_month_name(5)));
	BOOST_CHECK(boost_compare("Khuti", vulcan_month_name(6)));
	BOOST_CHECK(boost_compare("Ta'Krat", vulcan_month_name(7)));
	BOOST_CHECK(boost_compare("K'ri'lior", vulcan_month_name(8)));
	BOOST_CHECK(boost_compare("et'khior", vulcan_month_name(9)));
	BOOST_CHECK(boost_compare("T'lakht", vulcan_month_name(10)));
	BOOST_CHECK(boost_compare("T'ke'Tas", vulcan_month_name(11)));
	BOOST_CHECK(boost_compare("Tasmeen", vulcan_month_name(12)));
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

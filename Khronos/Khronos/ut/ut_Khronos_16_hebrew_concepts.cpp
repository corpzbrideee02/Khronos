/** @file ut_khronos_16_hebrew_concepts.cpp
	@author Garth Santor
	@date 2016-09-30
	@version 1.1.0
	@note C++ 11/vc14
	@brief Khronos library Hebrew Calendar concepts unit test.
*/

#include <khronos.hpp>
#include "ut_Khronos.hpp"
#include <array>

#if TEST_PHASES>=86
using namespace khronos;
#endif




#if PHASE_86 && TEST_PHASES>=86
BEGIN_PHASE(86, test_Hebrew_month_name) {
	static std::array<std::string, 14> const names = { "",
		"Nisan", "Iyyar", "Sivan", "Tammuz",
		"Av", "Elul", "Tishri", "Heshvan",
		"Kislev", "Teveth", "Shevat", "Adar", "Veadar" };

	for (month_t i = 1; i <= 13; ++i)
		BOOST_CHECK(hebrew_month_name(i) == names[i]);
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

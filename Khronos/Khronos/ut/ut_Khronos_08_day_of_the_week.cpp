/** @file ut_khronos_08_day_of_the_week.cpp

	@author Garth Santor
	@date 2016-09-30
	@version 1.1.0
	@note C++ 11/vc14
	@brief Khronos library day-of-the-week unit test.
	*/

#include <khronos.hpp>
#include "ut_Khronos.hpp"

#if TEST_PHASES>=38
using namespace khronos;
#endif



#if PHASE_38 && TEST_PHASES>=38
/** Day-of-week from JD. */
BEGIN_PHASE(38, day_of_week_base_func_test) {
	Gregorian g(2012_CE, September, 24);  // a monday
	Jd jd = g;

	for (double offset = 0.0; offset < 1.0; offset += 0.01)
		BOOST_CHECK(day_of_week(jd.jd() + offset) == Monday);

	BOOST_CHECK(day_of_week(jd.jd() + 1.0) == Tuesday);
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

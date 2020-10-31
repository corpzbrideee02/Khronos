/** @file ut_khronos_01_concepts.cpp
	@author Garth Santor
	@date 2016-09-30
	@version 1.1.0
	@note C++ 11/vc14
	@brief Khronos library concepts unit test.
	*/

#include <khronos.hpp>
#include "ut_Khronos.hpp"



#if PHASE_1 && TEST_PHASES>=1
BEGIN_PHASE(1, concept_am_pm_UDL) {
	using namespace khronos;
	BOOST_CHECK_EQUAL(12_am, 0);
	BOOST_CHECK_EQUAL(1_am, 1);
	BOOST_CHECK_EQUAL(12_pm, 12);
	BOOST_CHECK_EQUAL(1_pm, 13);
} END_PHASE()
#endif



#if PHASE_2 && TEST_PHASES>=2
BEGIN_PHASE(2, concept_time_of_day) {
	using namespace khronos;
	BOOST_CHECK_EQUAL(SECONDS_PER_DAY, 24 * 60 * 60);
	BOOST_CHECK_EQUAL(tod(12_am, 0, 0), 0.0);
	BOOST_CHECK_EQUAL(tod(12_pm, 1, 1.5), ((12*60+1)*60+1.5)/SECONDS_PER_DAY);
} END_PHASE()
#endif



#if PHASE_3 && TEST_PHASES>=3
BEGIN_PHASE(3, concept_CE_BCE_to_Gregorian_astro) {
	using namespace khronos;
	BOOST_CHECK_EQUAL(1975_CE, 1975);
	BOOST_CHECK_EQUAL(1975_BCE, -1974);
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

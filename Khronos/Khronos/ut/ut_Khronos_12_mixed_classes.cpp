/** @file ut_khronos_12_mixed_classes.cpp
	@author Garth Santor
	@date 2016-09-30
	@version 1.1.0
	@note C++ 11/vc14
	@brief Khronos library mixed classes unit test.
	*/

#include <khronos.hpp>
#include "ut_Khronos.hpp"

#if TEST_PHASES>=62
using namespace khronos;
#endif


#if PHASE_62 && TEST_PHASES>=62
BEGIN_PHASE(62, mixed_differences) {
	using namespace khronos;
	Gregorian low(2000);
	Jd high = Jd(low).jd() + 1;
	Julian copyLow(low);

	BOOST_CHECK(high - low == 1);
	BOOST_CHECK(low - high == -1);
	BOOST_CHECK(low - copyLow == 0);
	BOOST_CHECK(copyLow - low == 0);
} END_PHASE()
#endif



#if PHASE_63 && TEST_PHASES>=63
BEGIN_PHASE(63, mixed_relational) {
	using namespace khronos;
	Gregorian low(2000);
	Jd high = Jd(low).jd() + 1;
	Julian copyLow(low);

	BOOST_CHECK(low == copyLow);
	BOOST_CHECK(low < high);
	BOOST_CHECK(low <= copyLow);
	BOOST_CHECK(high >= low);
	BOOST_CHECK(high > low);
	BOOST_CHECK(high != low);
} END_PHASE()
#endif



/**	Base objects. */
#if TEST_PHASES>=64
khronos::Jd const			epochJdn(-0.5);
khronos::Julian const		epochJulian(4713_BC, 1, 1);
khronos::Gregorian const	epochGregorian(4714_BCE, 11, 24);
#endif



#if PHASE_64 && TEST_PHASES>=64
/** Test assignment to Jd conversions. */
BEGIN_PHASE(64, assignment_conversion_to_jdn_tests) {
	using namespace khronos;

	{	Jd jdn;
	jdn = epochJulian;
	BOOST_CHECK(jdn == epochJulian);
	}
	{	Jd jdn;
	jdn = epochGregorian;
	BOOST_CHECK(jdn == epochGregorian);
	}
	{	Jd jdn;
	jdn = epochJdn;
	BOOST_CHECK(jdn == epochJdn);
	}
} END_PHASE()
#endif



#if PHASE_65 && TEST_PHASES>=65
/** Test assignment to Gregorian conversions. */
BEGIN_PHASE(65, assignment_conversion_to_gregorian_tests) {
	using namespace khronos;
	Gregorian greg;

	{	Gregorian greg;
	greg = epochJulian;
	BOOST_CHECK(greg == epochJulian);
	}
	{	Gregorian greg;
	greg = epochGregorian;
	BOOST_CHECK(greg == epochGregorian);
	}
	{	Gregorian greg;
	greg = epochJdn;
	BOOST_CHECK(greg == epochJdn);
	}
} END_PHASE()
#endif



#if PHASE_66 && TEST_PHASES>=66
/** Test assignment to Julian conversions. */
BEGIN_PHASE(66, assignment_conversion_to_julian_tests) {
	using namespace khronos;

	Julian julian;

	{	Julian julian;
	julian = epochJulian;
	BOOST_CHECK(julian == epochJulian);
	}
	{	Julian julian;
	julian = epochGregorian;
	BOOST_CHECK(julian == epochGregorian);
	}
	{	Julian julian;
	julian = epochJdn;
	BOOST_CHECK(julian == epochJdn);
	}
} END_PHASE()
#endif



#if PHASE_67 && TEST_PHASES>=67
/** Test now */
BEGIN_PHASE(67, test_defaults) {
	using namespace khronos;

	Gregorian gNow(NOTIMEOFDAY);
	Julian jNow(NOTIMEOFDAY);
	Islamic iNow(NOTIMEOFDAY);
	Hebrew hNow(NOTIMEOFDAY);
	Jd now(NOTIMEOFDAY);

	BOOST_CHECK(gNow == jNow);
	BOOST_CHECK(iNow == hNow);
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

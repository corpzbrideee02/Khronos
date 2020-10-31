/** @file ut_khronos_20_vulcan_conv.cpp
	@author Garth Santor
	@date 2016-09-30
	@version 1.1.0
	@note C++ 11/vc14
	@brief Khronos library Vulcan Calendar conversion unit test.
*/

#include <khronos.hpp>
#include "ut_Khronos.hpp"
#include <sstream>
#include <iomanip>
using namespace std;

#include "ut_utilities.hpp"

#if TEST_PHASES>=101
using namespace khronos;
#endif




/** Test known Vulcan to JD conversions. */
#if PHASE_101 && TEST_PHASES>=101
BEGIN_PHASE(101, test_vulcan_to_jd) {

	auto test = [](year_t year, month_t month, day_t day, jd_t jd, int line) {
		auto jg = vulcan_to_jd(year, month, day);
		jg = round(jg, 4);
		jd = round(jd, 4);
		ostringstream oss;
		oss << fixed << setprecision(15) << "jg(" << jg << ") != jd(" << jd << ") from line: " << line;
		BOOST_CHECK_MESSAGE(jg == jd, oss.str());
	};

	test(1, Zat, 1, VULCAN_EPOCH, __LINE__);
	test(-651, Druh, 18, -1.028'571'4, __LINE__);					// beginning of the Julian Epoch


	auto test2 = [](year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t seconds, jd_t jd, int line) {
		auto jg = vulcan_to_jd(year, month, day, hour, minute, seconds);
		jg = round(jg, 4);
		jd = round(jd, 4);
		ostringstream oss;
		oss << fixed << setprecision(10) << "jg(" << jg << ") != jd(" << jd << ") from line: " << line;
		BOOST_CHECK_MESSAGE(jg == jd, oss.str());
	};
	test2(1, Zat, 1, 0, 0, 0, VULCAN_EPOCH, __LINE__);
	test2(8733, TaKrat, 10, 15, 4, 20, 2'500'000, __LINE__);
} END_PHASE()
#endif



#if PHASE_102 && TEST_PHASES>=102
/**	Test known JD to Vulcan conversions. */
BEGIN_PHASE(102, test_jd_to_vulcan) {

	auto test = [](year_t year, month_t month, day_t day, jd_t jd, int line) {
		year_t y;
		month_t m;
		day_t d;
		jd_to_vulcan(jd, y, m, d);

		ostringstream ossY;
		ossY << "y(" << y << ") != year(" << year << " from line: " << line;
		BOOST_CHECK_MESSAGE(y == year, ossY.str());

		ostringstream ossM;
		ossM << "m(" << m << ") != month(" << month << " from line: " << line;
		BOOST_CHECK_MESSAGE(m == month, ossM.str());

		ostringstream ossD;
		ossD << "d(" << d << ") != day(" << day << " from line: " << line;
		BOOST_CHECK_MESSAGE(d == day, ossD.str());
	};

	test(-651, Druh, 18, 0, __LINE__);						// beginning of the Julian Epoch
	test(1, Zat, 1, VULCAN_EPOCH, __LINE__);


	auto test2 = [](year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second, jd_t jd, int line) {
		year_t y;
		month_t m;
		day_t d;
		hour_t h;
		minute_t mi;
		second_t s;
		jd_to_vulcan(jd, y, m, d, h, mi, s);

		ostringstream ossY;
		ossY << "y(" << y << ") != year(" << year << ") from line: " << line;
		BOOST_CHECK_MESSAGE(y == year, ossY.str());

		ostringstream ossM;
		ossM << "m(" << m << ") != month(" << month << ") from line: " << line;
		BOOST_CHECK_MESSAGE(m == month, ossM.str());

		ostringstream ossD;
		ossD << "d(" << d << ") != day(" << day << ") from line: " << line;
		BOOST_CHECK_MESSAGE(d == day, ossD.str());

		ostringstream ossH;
		ossH << "h(" << h << ") != hour(" << hour << ") from line: " << line;
		BOOST_CHECK_MESSAGE(h == hour, ossH.str());

		ostringstream ossMi;
		ossMi << "mi(" << mi << ") != minute(" << minute << ") from line: " << line;
		BOOST_CHECK_MESSAGE(mi == minute, ossMi.str());

		ostringstream ossS;
		ossS << "s(" << s << ") != second(" << second << ") from line: " << line;
		BOOST_CHECK_MESSAGE(round(s) == second, ossS.str());
	};
	test2(1, Zat, 1, 0, 0, 0, VULCAN_EPOCH, __LINE__);
	test2(8733, TaKrat, 10, 15, 4, 20, 2'500'000, __LINE__);
} END_PHASE()
#endif


#if PHASE_119 && TEST_PHASES>=119
/**	Check all conversions from the lowest Proleptic Vulcan date, until a day well in the future. */
#if defined( FULL_TEST )
BEGIN_PHASE(119, test_vulcan_to_jd_full) {

	cout << "Starting Vulcan FULL_TEST: ";
	auto increment = 0.1;
	jd_t low = vulcan_to_jd(1, Zat, 1);
	jd_t high = vulcan_to_jd(10'000, Tasmeen, 21);
	for (jd_t jd = low; jd <= high; jd += increment) {
		year_t year;
		month_t month;
		day_t day;
		hour_t hours;
		minute_t minutes;
		second_t seconds;
		jd_to_vulcan(jd, year, month, day, hours, minutes, seconds);
		jd_t result = vulcan_to_jd(year, month, day, hours, minutes, seconds);
		BOOST_CHECK_CLOSE(jd, result, 0.000'000'1);
	}
	cout << "... completed\n";
} END_PHASE()
#endif
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

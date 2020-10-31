#pragma once

#include <cmath>
#include <khronos\utility.hpp>
#include <khronos\calendar.hpp>
/*
khronos\timeofday.hpp
(c) Garth Santor
Created: 2015-09-22
Last Updated: 2015-09-22

Khronos library 'time-of-day' declarations.
*/

namespace khronos {

	//seconds in day

	inline tod_t SECONDS_PER_DAY= 24 * 60 * 60;
	
	inline tod_t sec_in_day = 24.0 * 60.0 * 60.0;

	constexpr int operator ""_am(unsigned long long timeAM) {
		if (timeAM == 12)
			return static_cast<int>(VAL_OF_AM);
		else if (timeAM < 12)
			return static_cast<int>(timeAM);
	}
	constexpr int operator ""_pm(unsigned long long timePM) {
		if (timePM == 12)
			return static_cast<int>(VAL_OF_PM);
		else if (timePM < 12)
			return static_cast<int>(timePM + 12);
	}


	/*constexpr int tod(second_t sec, minute_t min, hour_t hr)
	{
		return utility::mod(sec + 60 * (min + 60 + hr), 24 * 60 * 60);

	}*/



	//-----------------------------------------------------------------------------------------------
	inline tod_t tod(unsigned long long sec, minute_t min, double hr)
	{
		//double frst = (sec + 60.0 * (min + 60.0 * hr)) / sec_in_day;
		//sec = sec * 60.0;
		//return (sec + 60.0 * (min + (60.0 * hr)))/ SECONDS_PER_DAY;
		return ((sec * 60.0 + min) * 60.0 + hr) / SECONDS_PER_DAY;

	}


	//inline tod_t tod(double hr, minute_t min,unsigned long long sec )
	//{
	//	//double frst = (sec + 60.0 * (min + 60.0 * hr)) / sec_in_day;
	//	//sec = sec * 60.0;
	//	//return (sec + 60.0 * (min + (60.0 * hr)))/ seconds_per_day;
	//	return ((sec * 60.0 + min) * 60.0 + hr) / SECONDS_PER_DAY;

	//}

	inline void hms(hour_t& hr, minute_t& min, second_t& sec)
	{
		sec_in_day = floor((tod((unsigned long long)sec, min, hr))* SECONDS_PER_DAY +0.5);
		hr = (int)sec_in_day / (60 * 60);
		min = (int)utility::mod((sec_in_day / 60), 60);
		sec = utility::mod(sec_in_day, 60);
	}

	//-----------------------------------------------------------------------------------------------




	//void tod(unsigned int sec, minute_t min, double hr)
	//{
	//	//static_cast<double>((12.0 * 60.0 + 1) * 60.0 + 1.5)) / SECONDS_PER_DAY();
	//}
	
	//inline tod_t tod(hour_t hr,minute_t min, second_t sec  )
	//{
	//	return (sec + 60.0 * (min + 60.0 * (double)hr)) / (double)SECONDS_PER_DAY();
	////	//static_cast<tod_t>(min, hr, sec);
	////	static_cast<tod_t>(sec);
	////	static_cast<tod_t>(min);
	////	static_cast<tod_t>(hr);
	////	//long long numerator= static_cast<long long>(sec + 60 * (min + 60 * hr));
	////	double numm=sec + 60.0 * (min + 60.0 * hr);
	////	double denom = SECONDS_PER_DAY();
	////	return utility::mod(numm, denom);
	////	//long long denominator = static_cast<long long>(SECONDS_PER_DAY());
	////	//return utility::mod(numerator, denominator);
	//
	//}

	/*inline tod_t tod(hour_t hr, minute_t min, second_t sec)
	{
	
	}*/

	//BOOST_CHECK_EQUAL(SECONDS_PER_DAY, 24 * 60 * 60);
	//BOOST_CHECK_EQUAL(tod(12_am, 0, 0), 0.0);
	//BOOST_CHECK_EQUAL(tod(12_pm, 1, 1.5), ((12 * 60 + 1) * 60 + 1.5) / SECONDS_PER_DAY);

	

}

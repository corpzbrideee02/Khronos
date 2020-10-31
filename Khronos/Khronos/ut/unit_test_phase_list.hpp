#pragma once
/** @file unit_test_phase_list.hpp
	@author Garth Santor
	@date 2017-04-30
	@version 2.1.0
	@note Visual C++ 14.1
	@brief Unit test phase reporting.
	*/

#include <set>
#include <memory>
#include <iostream>


/** PhaseList <<singleton>>

	Tracks which unit test phases have been attempted and reports the list of
	phases missing from the unit test.
	*/
template <typename SIZE_T = std::size_t>
class PhaseList {
	SIZE_T								nPhases;
	std::set<SIZE_T>					phases;
	static std::unique_ptr<PhaseList>	pInstance;


	/** <<constructor>> sets the phase list to [1..nPhases] */
	PhaseList(SIZE_T _nPhases) : nPhases(_nPhases) {
		for (SIZE_T i = 1; i <= _nPhases; ++i)
			phases.insert(i);
	}

public:
	/** <<destructor>> reports phase incompletions to stdout. */
	~PhaseList() {
		if (phases.empty())
			std::cout << "\nAll "<< nPhases << " phases implemented." << std::endl;
		else {
			std::cout << "\nPhases not implemented: ";
			auto it = phases.begin();
			std::cout << *it;
			while (++it != phases.end())
				std::cout << ", " << *it;
			std::cout << std::endl;
		}
	}

	/** Set the total number of phases in the unit test. */
	static void set_phases(SIZE_T _nPhases) {
		if (!pInstance)
			pInstance.reset(new PhaseList(_nPhases));
	}


	/** Record that a phase has been implemented. */
	static void implements(SIZE_T _phase) {
		pInstance->phases.erase(_phase);
	}
};


/** <<singleton>> member variable instance. */
template <typename SIZE_T>
std::unique_ptr<PhaseList<SIZE_T>> PhaseList<SIZE_T>::pInstance;



/*============================================================================

Revision History

Version 2.1.0: 2017-04-30
Validated for VC++ 14.1

Version 2.0.0: 2016-05-09
Changed to a template to remove the need of explicitly instantiating the static member.

Version 1.0.0: 2014-05-02
Initial version.

==============================================================================
Copyright Garth Santor, 2014-2017

The copyright to the computer program(s) herein
is the property of Garth Santor, Canada.
The program(s) may be used and/or copied only with
the written permission of Garth Santor
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
============================================================================*/

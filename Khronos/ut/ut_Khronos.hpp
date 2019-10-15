#pragma once

/** @file ut_khronos_00_main.cpp
	@author Garth Santor
	@date 2016-09-30
	@version 1.1.0
	@note C++ 11/vc14
	@brief Khronos unit test common declarations.
	*/


#include "unit_test_phase_list.hpp"
#include <boost/test/unit_test.hpp>
#define BEGIN_PHASE(num,name) BOOST_AUTO_TEST_CASE(name) { auto phaseNumber = num;
#define END_PHASE() PhaseList<>::implements(phaseNumber); }


#define UT_VERSION "1.1.0"


// set 'TEST_PHASES' to the maximum test phase attempted
#define TEST_PHASES 119


// set 'PHASE_dd' to 'true' for any test phase you wish to skip
#define PHASE_1 true
#define PHASE_2 true
#define PHASE_3 true
#define PHASE_4 true
#define PHASE_5 true
#define PHASE_6 true
#define PHASE_7 true
#define PHASE_8 true
#define PHASE_9 true

#define PHASE_10 true
#define PHASE_11 true
#define PHASE_12 true
#define PHASE_13 true
#define PHASE_14 true
#define PHASE_15 true
#define PHASE_16 true
#define PHASE_17 true
#define PHASE_18 true
#define PHASE_19 true

#define PHASE_20 true
#define PHASE_21 true
#define PHASE_22 true
#define PHASE_23 true
#define PHASE_24 true
#define PHASE_25 true
#define PHASE_26 false
#define PHASE_27 true
#define PHASE_28 false
#define PHASE_29 true

#define PHASE_30 true
#define PHASE_31 true
#define PHASE_32 true
#define PHASE_33 true
#define PHASE_34 true
#define PHASE_35 true
#define PHASE_36 true
#define PHASE_37 true
#define PHASE_38 true
#define PHASE_39 true

#define PHASE_40 true
#define PHASE_41 true
#define PHASE_42 true
#define PHASE_43 true
#define PHASE_44 true
#define PHASE_45 true
#define PHASE_46 true
#define PHASE_47 true
#define PHASE_48 true
#define PHASE_49 true

#define PHASE_50 true
#define PHASE_51 true
#define PHASE_52 true
#define PHASE_53 true
#define PHASE_54 true
#define PHASE_55 true
#define PHASE_56 true
#define PHASE_57 true
#define PHASE_58 true
#define PHASE_59 true

#define PHASE_60 true
#define PHASE_61 true
#define PHASE_62 true
#define PHASE_63 true
#define PHASE_64 true
#define PHASE_65 true
#define PHASE_66 true
#define PHASE_67 true
#define PHASE_68 true
#define PHASE_69 true

#define PHASE_70 true
#define PHASE_71 true
#define PHASE_72 true
#define PHASE_73 true
#define PHASE_74 true
#define PHASE_75 true
#define PHASE_76 true
#define PHASE_77 true
#define PHASE_78 true
#define PHASE_79 true

#define PHASE_80 true
#define PHASE_81 true
#define PHASE_82 true
#define PHASE_83 true
#define PHASE_84 true
#define PHASE_85 true
#define PHASE_86 true
#define PHASE_87 true
#define PHASE_88 true
#define PHASE_89 true

#define PHASE_90 true
#define PHASE_91 true
#define PHASE_92 true
#define PHASE_93 true
#define PHASE_94 true
#define PHASE_95 true
#define PHASE_96 true
#define PHASE_97 true
#define PHASE_98 true
#define PHASE_99 true

#define PHASE_100 true
#define PHASE_101 false
#define PHASE_102 false
#define PHASE_103 false
#define PHASE_104 false
#define PHASE_105 false
#define PHASE_106 false
#define PHASE_107 false
#define PHASE_108 false
#define PHASE_109 false

#define PHASE_110 false
#define PHASE_111 false
#define PHASE_112 false
#define PHASE_113 false
#define PHASE_114 false
#define PHASE_115 true
#define PHASE_116 true
#define PHASE_117 true
#define PHASE_118 true
#define PHASE_119 false



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
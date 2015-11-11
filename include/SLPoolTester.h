/*!
	<PRE>
	SOURCE FILE : SLPoolTester.h
	DESCRIPTION.: SLPoolTester class - with implementation.
	AUTHORS.....: Igor A. Brandão and Leandro F. Silva
	CONTRIBUTORS: Igor A. Brandão and Leandro F. Silva
	LOCATION....: IMD/UFRN.
	SATARTED ON.: OCT/2015
	CHANGES.....: Functions implemented.

	TO COMPILE..: Use makefile.
	OBS.........: Part of the LP1/EDB Project.

	LAST UPDATE.: October 27th, 2015.
	LAST UPDATE.: November 1st, 2015.
	LAST UPDATE.: November 10th, 2015.
	</PRE>
*/

#ifndef SLPoolTester_H_
#define SLPoolTester_H_

#include <iostream>
#include <queue>		// std::priority_queue
#include <vector>		// std::vector

/*! Custom classes */
#include "StoragePool.h"
#include "Event.h"

using namespace std;

// ******************PUBLIC OPERATIONS*********************
// void StoragePoolTest( const StoragePool, time_t ) 	--> Test the SLPool efficiency
// size_t getRandomForSize( int, int ) 					--> Generate a randomic memory size
// time_t getRandomTimeInterval( int, int ) 			--> Generate a randomic time interval

/*! SLPoolTester class */
class SLPoolTester
{
	/*!
     * Public section
    */
	public:

		/*! Basic members */
		void StoragePoolTest( StoragePool & _pool, time_t );
		size_t getRandomForSize( int, int ) const;
		time_t getRandomTimeInterval( int, int ) const;

};

#endif

/* --------------------- [ End of the SLPoolTester.h header ] ------------------- */
/* ========================================================================= */
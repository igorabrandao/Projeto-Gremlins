/*! \file */ 
/*! \brief SLPoolTester.cpp.
 *
 *  Implements the functions from SLPoolTester class.
*/

#include "SLPoolTester.h"

/********************************************//**
* Test the SLPool efficiency.
***********************************************/
void
SLPoolTester::StoragePoolTest ( StoragePool & _pool, time_t _timeLimit ) 
{
	// [1] Setup random numbers generator for memory size, say [100, 2000] bytes.
	// [2] Setup random numbers generator for time intervals, say [1, 100] units.
	// [3] Create the pirority queue std::priority_queue ‘pq ’ and
	// insert some events comprising the simulation.
	// Assuming there is a class Event that creates a pair address/time-stamp.

	priority_queue<Event, vector<Event>, Compare> pq;

	// Run simulation fot the time set by the client .
	for ( time_t t(0); t < _timeLimit; ++ t )
	{
		/*! Run while we have events pending or time to run. */
		while ( !pq.empty() )
		{
			//!* Access the event with the smallest time - stamp .
			Event ev = pq.top();

			//!* Still some time left ....
			if ( ev.getTimeStamp() > t ) break;

			//!* When we got here, the top event has run out of time .
			pq.pop(); //!*< Remove event from priority queue .
			_pool.Free( ev.getMemoryPtr() ); //!*< Calling free operator .
			//delete ev;
		}

		auto memSize = getRandomForSize(100, 2000);
		void * const add = _pool.Allocate(memSize);

		auto elapsedTime = getRandomTimeInterval(1, 100);
		time_t releaseTime = t + elapsedTime; //!*< Set time stamp some time from now.

		cout << "xxx memSize: " << memSize << " xxx" << endl << endl;
		cout << "xxx releaseTime: " << releaseTime << " xxx" << endl << endl;

		Event ev2(add, releaseTime);
		pq.push( ev2 ); //!*< Creating a new simulation event.

		// Here you might want to show the memory map on the screen ,
		// or write it to a log file, for debugging purpose.
	}
}

/********************************************//**
* Generate a randomic memory size
***********************************************/
size_t
SLPoolTester::getRandomForSize ( int _min, int _max ) const
{
	return (size_t)( rand() % _max + _min );
}

/********************************************//**
* Generate a randomic time interval
***********************************************/
time_t
SLPoolTester::getRandomTimeInterval ( int _min, int _max ) const
{
	return (time_t)( rand() % _max + _min );
}
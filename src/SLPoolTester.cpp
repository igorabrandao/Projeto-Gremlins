/*! \file */ 
/*! \brief SLPoolTester.cpp.
 *
 *  Implements the functions from SLPoolTester class.
*/

#include "SLPoolTester.h"

/********************************************//**
* Test the SLPool efficiency.
* @param _pool - 
***********************************************/
void
SLPoolTester::StoragePoolTest( SLPool & _pool, time_t _timeLimit ) 
{
	// [1] Setup random numbers generator for memory size, say [100, 2000] bytes.
	// [2] Setup random numbers generator for time intervals, say [1, 100] units.
	// [3] Create the pirority queue std::priority_queue ‘pq ’ and
	// insert some events comprising the simulation.
	// Assuming there is a class Event that creates a pair address/time-stamp.

	priority_queue<Event, vector<Event>, Compare> pq;

	// Run simulation fot the time set by the client .
	for ( time_t t(0); t < _timeLimit; ++t )
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

			cout << endl << "<<< Deleting... " << ev.getMemoryPtr() << " >>>" << endl << endl;
			_pool.Free( ev.getMemoryPtr() ); //!*< Calling free operator.
			//delete ev;

			_pool.Debug();
		}

		/*! Initialize random seed: */
        srand (time(NULL));

		auto memSize = getRandomForSize(10, 100);
		void * const add = _pool.Allocate(memSize);

		auto elapsedTime = getRandomTimeInterval(1, 5);
		time_t releaseTime = t + elapsedTime; //!*< Set time stamp some time from now.

		cout << "xxx memAddress: " << add << " xxx" << endl;
		cout << "xxx memSize: " << memSize << " xxx" << endl;
		cout << "xxx releaseTime: " << releaseTime << " xxx" << endl << endl;

		if ( add != nullptr )
		{
			Event ev2(add, releaseTime);
			pq.push( ev2 ); //!*< Creating a new simulation event.
		}

		// Here you might want to show the memory map on the screen ,
		_pool.Debug();

		// or write it to a log file, for debugging purpose.
	}
}

/********************************************//**
* Generate a randomic memory size
***********************************************/
size_t
SLPoolTester::getRandomForSize( int _min, int _max ) const
{
	return (size_t)( rand() % _max + _min );
}

/********************************************//**
* Generate a randomic time interval
***********************************************/
time_t
SLPoolTester::getRandomTimeInterval( int _min, int _max ) const
{
	return (time_t)( rand() % _max + _min );
}

/********************************************//**
* Counts the time interval
***********************************************/
double
SLPoolTester::getTickCount()
{
	struct timespec now;

 	if ( clock_gettime(CLOCK_MONOTONIC, &now) )
		return 0;

  	return now.tv_sec * 1000.0 + now.tv_nsec / 1000000.0;
}
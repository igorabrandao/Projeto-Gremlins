/*!
	<PRE>
	SOURCE FILE : Event.h
	DESCRIPTION.: Event class - with implementation.
	AUTHORS.....: Igor A. Brandão and Leandro F. Silva
	CONTRIBUTORS: Igor A. Brandão and Leandro F. Silva
	LOCATION....: IMD/UFRN.
	SATARTED ON.: NOV/2015
	CHANGES.....: Functions implemented.

	TO COMPILE..: Use makefile.
	OBS.........: Part of the LP1/EDB Project.

	LAST UPDATE.: November 9th, 2015.
	LAST UPDATE.: November 10th, 2015.
	</PRE>
*/

#ifndef EVENT_H_
#define EVENT_H_

#include <iostream>
#include <ctime>

using namespace std;

// ******************PUBLIC OPERATIONS*********************
// time_t getTimeStamp( void ) 	--> Return the timeStamp
// void* getMemoryPtr( void ) 	--> Return the memoryPointer 

/*! Event class */
class Event
{
	/*!
     * Public section
    */
	public:

		/*! Basic members */
		explicit Event( void* _adress = nullptr, time_t _time = 10 );
		virtual ~Event();

		time_t getTimeStamp();
		void * getMemoryPtr();

	/*!
     * Private section
    */
	private:

		/*! Private attributes */
		void * e_adress;
		time_t e_time;
};

/*! Compare class */
class Compare
{
	/*!
     * Public section
    */
	public:

	    bool operator() (Event & _a, Event & _b) const
	    {
	    	if ( _a.getTimeStamp() < _b.getTimeStamp() )
	        	return true;
	        else
	        	return false;
	    }
};

#endif

/* --------------------- [ End of the Event.h header ] ------------------- */
/* ========================================================================= */
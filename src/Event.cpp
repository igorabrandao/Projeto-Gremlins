/*! \file */ 
/*! \brief Event.cpp.
 *
 *  Implements the functions from Event class.
*/

#include "Event.h"

/********************************************//**
* constructor
***********************************************/
Event::Event( void * _adress, time_t _time )
{
	/*! Initialize the attributes with parameters */
	e_adress = _adress;
	e_time = _time;
}

/********************************************//**
* destructor
***********************************************/
Event::~Event()
{
	//delete e_adress;
}

/********************************************//**
* Return the timeStamp
***********************************************/
time_t
Event::getTimeStamp()
{
	return e_time;
}

/********************************************//**
* Return the memoryPointer
***********************************************/
void*
Event::getMemoryPtr()
{
	return e_adress;
}
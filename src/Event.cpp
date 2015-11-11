/*! \file */ 
/*! \brief Event.cpp.
 *
 *  Implements the functions from Event class.
*/

#include "Event.h"

/********************************************//**
* constructor
***********************************************/
Event::Event()
{
	/*! Initialize the attributes with defafult */
	e_adress = nullptr;
	e_time = 10;
}

/********************************************//**
* constructor overload
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
	//delete[] e_adress;
}

/********************************************//**
* Return the timeStamp
***********************************************/
time_t
Event::getTimeStamp() const
{
	return e_time;
}

/********************************************//**
* Return the memoryPointer
***********************************************/
void*
Event::getMemoryPtr() const
{
	return e_adress;
}
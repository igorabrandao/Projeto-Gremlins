/*!
	<PRE>
	SOURCE FILE : StoragePool.h
	DESCRIPTION.: StoragePool class - with implementation.
	AUTHORS.....: Igor A. Brandão and Leandro F. Silva
	CONTRIBUTORS: Igor A. Brandão and Leandro F. Silva
	LOCATION....: IMD/UFRN.
	SATARTED ON.: OCT/2015
	CHANGES.....: Functions implemented.

	TO COMPILE..: Use makefile.
	OBS.........: Part of the LP1/EDB Project.

	LAST UPDATE.: October 27th, 2015.
	</PRE>
*/

#ifndef StoragePool_H_
#define StoragePool_H_

#include <iostream>
#include <stdexcept>

/*! Custom classes */
#include "MempoolCommon.h"

using namespace std;

// ******************PUBLIC OPERATIONS*********************
// queue<string> infixToPostfix( _exp )			--> Convert infix to postfix expressions
// int hasPriority( _exp1, _exp2 )				--> Check wich operator has a higher precedence
// int isRightAssociative( _operator )			--> Check whether an operator is right associative
// int getOperatorPrecedence( _operator )		--> Get the operator precedence

// ***********************ERRORS****************************
// std::underflow_error thrown if needed.

/*! StoragePool class */
class StoragePool
{
	/*!
     * Public section
    */
	public:

		/*! Functions */
		virtual ~StoragePool();					/*!< Virtual destructor */
		virtual void* Allocate( size_t ) = 0;
		virtual void Free( void * ) = 0;

		/*! Basic members */

	/*!
     * Private section
    */
	private:

		/*! Attributes */

		/*! Disable copy constructor */
};

#endif

/* --------------------- [ End of the StoragePool.h header ] ------------------- */
/* ========================================================================= */
/*!
	<PRE>
	SOURCE FILE : SLPool.h
	DESCRIPTION.: SLPool class - with implementation.
	AUTHORS.....: Igor A. Brandão and Leandro F. Silva
	CONTRIBUTORS: Igor A. Brandão and Leandro F. Silva
	LOCATION....: IMD/UFRN.
	SATARTED ON.: OCT/2015
	CHANGES.....: Functions implemented.

	TO COMPILE..: Use makefile.
	OBS.........: Part of the LP1/EDB Project.

	LAST UPDATE.: October 27th, 2015.
	LAST UPDATE.: November 1st, 2015.
	</PRE>
*/

#ifndef SLPool_H_
#define SLPool_H_

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <math.h>
#include <stdexcept>

/*! Custom classes */
#include "StoragePool.h"

using namespace std;

// ******************PUBLIC OPERATIONS*********************
// void * Allocate( size_t )	--> Allocates a volume of memory defined by the argument in bytes
// void Free( void * )			--> Receive a pointer to the reserved area and free this area to be used later

// ***********************ERRORS****************************
// std::underflow_error thrown if needed.

/*! SLPool class */
class SLPool : public StoragePool
{
	/*!
     * Public section
    */
	public:

		/*! Header node */
		struct Header
		{
			unsigned int mui_Length;
			Header() : mui_Length(0u) { /* empty */ };
		};

		/*! Block node - inherits from Header node */
		struct Block : public Header
		{
			enum { BlockSize = 16 }; //!< Each block has 16 bytes .
			union
			{
				/*! Pointer to the next block */
				Block * mp_Next;

				/*! Space allocated to the client area */
				char mc_RawArea [ BlockSize - sizeof ( Header ) ];
			};

			Block () : Header () , mp_Next ( nullptr ) { /* Empty */ };
		};

	/*!
     * Public section
    */
	public:

		/*! Basic members */
		explicit SLPool( size_t );	//!< Constructor
		~SLPool();					//!< Destructor

		void * Allocate( size_t );
		void Free( void * );

	/*!
     * Private section
    */
	private:

		/*! Private attributes */
		unsigned int mui_NumberOfBlocks;
		Block *mp_Pool;			//!< Head of the list
		Block *mr_Sentinel;		//!< End of the list

};

#endif

/* --------------------- [ End of the SLPool.h header ] ------------------- */
/* ========================================================================= */
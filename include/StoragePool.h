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
	LAST UPDATE.: November 1st, 2015.
	</PRE>
*/

#ifndef StoragePool_H_
#define StoragePool_H_

/*! Custom classes */
//#include "MempoolCommon.h"

using namespace std;

// ******************PUBLIC OPERATIONS*********************
// void * Allocate( size_t )	--> Allocates a volume of memory defined by the argument in bytes
// void Free( void * )			--> Receive a pointer to the reserved area and free this area to be used later

/*! StoragePool class */
class StoragePool
{
	/*!
     * Public section
    */
	public:

		/*! Functions */
		virtual ~StoragePool(){};	/*!< Virtual destructor */
		virtual void* Allocate( size_t ) = 0;
		virtual void Free( void * ) = 0;
};

#endif

/* --------------------- [ End of the StoragePool.h header ] ------------------- */
/* ========================================================================= */
/*!
	<PRE>
	SOURCE FILE : MempoolCommon.h
	DESCRIPTION.: MempoolCommon class - with implementation.
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

#ifndef MempoolCommon_H_
#define MempoolCommon_H_

#include "SLPool.h"

using namespace std;

// ******************PUBLIC OPERATIONS*********************

// ***********************ERRORS****************************

/*! MempoolCommon class */
class MempoolCommon
{
	/*!
     * Public section
    */
	public:

		/*! Tag node */
		//struct Tag { StoragePool * pool; };

		/*! Basic members */

		/*! Operators */

		/*! Overloaded new */
		/*void * operator new ( size_t bytes, StoragePool & p )
		{
			Tag* const tag = reinterpret_cast <Tag *>( p.Allocate(bytes + sizeof(Tag)) );
			tag->pool = &p;
			return tag + 1U; //!< skip sizeof tag to get the raw data-block
		}*/

		/*! Regular new */
		/*void * operator new ( size_t bytes, StoragePool & p )
		{
			Tag* const tag = reinterpret_cast <Tag *>( std::malloc(bytes + sizeof(Tag)) );
			tag->pool = nullptr;
			return ( reinterpret_cast <void *>(tag + 1U) );
		}*/

		/*! Delete */
		/*void operator delete ( void * arg ) noexcept
		{*/
			/*! We need subtract 1U (in fact, pointer arithmetics), because
			 * arg points to the raw data (second block of information).
			 * The pool id (tag) is located 'sizeof(Tag)' bytes before.
			*/
			/*Tag * const tag = reinterpret_cast <Tag *>(arg) - 1U;

			if ( nullptr != tag->pool ) //!< Memory block belongs to a particular GM
				tag->pool->Free(tag);
			else
				std::free(tag); //!< Memory block belongs to the operational system
		}*/

	/*!
     * Private section
    */
	private:

		/*! Attributes */

};

#endif

/* --------------------- [ End of the MempoolCommon.h header ] ------------------- */
/* ========================================================================= */
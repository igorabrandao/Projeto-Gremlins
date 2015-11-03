#ifndef M_POOL_H
#define M_POOL_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <math.h>
using namespace std;


class StoragePool {
	public:
		virtual ~StoragePool ();
		virtual void * Allocate ( size_t ) = 0;
		virtual void Free ( void * ) = 0;
};

class SLPool {
	public:
		struct Header {
			unsigned int mui_Length;
			Header () : mui_Length ( 0u ) { /* Empty */ };
		};

		struct Block: public Header {
			enum { BlockSize = 16 }; // Each block has 16 bytes.
				union {
					Block *mp_Next;
					char mc_RawArea [ BlockSize - sizeof( Header ) ];
				};
			Block (): Header(), mp_Next ( nullptr ) { /* Empty */ };
		};
		public:
		explicit SLPool ( size_t bytes );
		~SLPool ();
		void * Allocate ( size_t bytes );
		void Free ( void * );

	private:
		unsigned int mui_NumberOfBlocks;
		Block *mp_Pool;	//! < Head of list.
		Block *mr_Sentinel;	//! < End of the list.


};


#endif

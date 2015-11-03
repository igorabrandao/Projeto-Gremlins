/*! \file */ 
/*! \brief Class main.cpp.
 *
 *  Contains the menu function and starts the program.
*/
#include <iostream>
#include "StoragePool.h"

using namespace std;

int main( int argc, char const *argv[] )
{
	/*! Create an instance from Storage Pool class */
	StoragePool p;

	/*! Allocates 100 bytes of memory */
	void *ptr = p.Allocate(100);

	/*! Free the memory */
	p.Free(ptr);

	/*
		StoragePool p, q;

		// Instanciando ’T’ diretamente com o Sistema Operacional
		T * ptr0 = new T;

		// Instanciando ’T’ no GM ’p ’.
		T * ptr1 = new (p ) T;

		// Instanciando ’T’ no GM ’q ’.
		T * ptr2 = new (q ) T;

		delete ptr0 ;
		delete ptr1 ;
		delete ptr2 ;
	*/

	/*! Main return */
	return 0;
}
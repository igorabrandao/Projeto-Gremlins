/*! \file */ 
/*! \brief main.cpp.
 *
 *  Contains the menu function and starts the program.
*/
#include <iostream>
#include "SLPool.h"
#include "MempoolCommon.h"

using namespace std;

int main( int argc, char const *argv[] )
{
	/********************************************//**
	* Test with new overload
	***********************************************/

	/*! Create an instance from Storage Pool class */
	/*SLPool p(200);
	SLPool q(300);

	// Instanciando ’ptr0’ diretamente com o Sistema Operacional
	int * ptr0 = new int(100) ;

	// Instanciando ’T’ no GM ’p ’.
	int * ptr1 = new (p) int;

	// Instanciando ’T’ no GM ’q ’.
	int * ptr2 = new (q) int;

	delete ptr0;
	delete ptr1;
	delete ptr2;*/

	/********************************************//**
	* Test without new overload
	***********************************************/

	void* x;
    void* y;
    void* s;

    SLPool pool( 100 );
    pool.Debug();
    x = pool.Allocate(25);

    pool.Debug();
    cout << "<<< X: " << x << " >>> " << endl;
    //delete x;

    int * z = new (pool) int;
    pool.Debug();
    cout << "<<< Z: " << z << " >>> " << endl;
    //delete z;

    y = pool.Allocate(25);
    pool.Debug();
    cout << "<<< Y: " << y << " >>> " << endl;
    //delete y;

    s = pool.Allocate(15);
    pool.Debug();
    cout << "<<< S: " << s << " >>> " << endl;
    //delete s;

    cout << "<<< Finish with success! >>>" << endl;

	/*! Main return */
	return 0;
}
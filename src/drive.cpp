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
	* Test without new overload
	***********************************************/

	void * x;
    void * y;

    cout << endl << "--------------------[CONSTRUCTOR]-------------------" << endl;
    SLPool pool( 100 );
    pool.Debug();
    cout << "----------------------------------------------------" << endl << endl;

    cout << "------------------[WITHOUT OVERLOAD]----------------" << endl;
    x = pool.Allocate(25);
    pool.Debug();
    cout << "<<< X: " << x << " >>> " << endl;
    pool.Free(x);
    pool.Debug();
    cout << "----------------------------------------------------" << endl;

    cout << "----------------------------------------------------" << endl;
    y = pool.Allocate(25);
    pool.Debug();
    cout << "<<< Y: " << y << " >>> " << endl;
    pool.Free(y);
    pool.Debug();
    cout << "----------------------------------------------------" << endl << endl;

    /********************************************//**
	* Test with new overload
	***********************************************/

    cout << "-------------------[WITH OVERLOAD]------------------" << endl;
    int * z = new (pool) int;
    pool.Debug();
    cout << "<<< Z: " << z << " >>> " << endl;
    delete z;
    pool.Debug();
    cout << "----------------------------------------------------" << endl << endl;

    cout << "<<< Finish with success! >>>" << endl;

	/*! Main return */
	return 0;
}
/*! \file */ 
/*! \brief main.cpp.
 *
 *  Contains the menu function and starts the program.
*/
#include <iostream>
#include "SLPool.h"
#include "MempoolCommon.h"
#include "SLPoolTester.h"

using namespace std;

int main( int argc, char const *argv[] )
{
    void * x;
    SLPoolTester slPoolTest;
    SLPool pool(2000);

	/********************************************//**
	* Testing
	***********************************************/
    for ( auto i(1); i < 5; ++i )
    {
        cout << endl << "------------------[TESTE " << i << "]----------------" << endl;
        cout << "<<< S.O >>>" << endl << endl;

        cout << "Allocate..." << endl;
        x = pool.Allocate(slPoolTest.getRandomForSize(100, 2000));
        pool.Debug();

        cout << "Free..." << endl;
        pool.Free(x);
        pool.Debug();

        cout << "<<< MEU TESTE >>>" << endl << endl;

        int * z = new (pool) int;
        cout << "Allocate..." << endl;
        //z = pool.Allocate(slPoolTest.getRandomForSize(100, 2000));
        pool.Debug();

        cout << "Free..." << endl;
        delete z;
        pool.Debug();

        cout << "-----------------------------------------------------" << endl << endl;
    }

    cout << "<<< Finish with success! >>>" << endl;

	/*! Main return */
	return 0;
}
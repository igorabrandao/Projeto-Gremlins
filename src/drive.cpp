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

void return_to_menu();

/********************************************//**
* Run a simple test of GM
***********************************************/
void simpleTest( unsigned int n_instances )
{
    /*! Instance of test class */
    SLPoolTester poolTest;

    /*! Running a simple test */
    cout << endl << "----------------------------------------------" << endl;
    cout << "<<< Simple test execution >>>" << endl;
    cout << "----------------------------------------------" << endl << endl;

    /*! Info */
    cout << "Number of instances: " << n_instances << endl << endl;

    /*! Sistema operacional (SO) */
    cout << "<<< Sistema operacional (SO) >>>" << endl;
    double count = poolTest.getTickCount();    
    for ( unsigned int i = 0; i < n_instances; i++ )
    {
        int *ptr0 = new int;
        delete ptr0;
    }
    cout << "Interval SO = " << poolTest.getTickCount()-count << " ms" << endl << endl;

    /*! Gerenciador de memória (GM) */
    cout << "<<< Gerenciador de memória (GM) >>>" << endl;
    double count2 = poolTest.getTickCount();    
    SLPool poolGM( 256 );
    for ( unsigned int i=0; i<10; i++ )
    {
        int *ptr1 = new (poolGM) int;
        //poolGM.Debug();
        delete ptr1;
        //poolGM.Debug();
    }
    cout << "Interval GM = " << poolTest.getTickCount()-count2 << " ms" << endl << endl;

    cout << "----------------------------------------------" << endl << endl;

    return_to_menu();   
}

/********************************************//**
* Menu application
***********************************************/
void menu()
{
    int op = 0;

    /*! Clear the screen */
    cout << string(50, '\n');

    cout << endl << "----------------------------------------------" << endl;
    cout << "<<< Gremlins - Memory manager >>>" << endl;
    cout << "----------------------------------------------" << endl << endl;
    cout << "Choose and option below: " << endl << endl;
    cout << "1) Simple test " << endl;
    cout << "2) Simple test and log file (batch) " << endl;
    cout << "3) Advanced test " << endl;
    cout << "4) Advanced test and log file (batch) " << endl;
    cout << "5) Exit " << endl << endl;
    cout << "----------------------------------------------" << endl << endl;    

    cout << "Inform the menu option: ";
    cin >> op;

    /*! Check if the option is valid */
    if ( op < 0 || op > 5 )
    {
        menu(); //!< invalid option
    }
    else
    {
        /*! Check the option */
        switch ( op )
        {
            /*! Simple test */
            case 1:
                unsigned int n;
                cout << endl << "Inform the number of instances: ";
                cin >> n;
                simpleTest(n);
                break;

            /*! Simple test and log file (batch) */
            case 2:
                menu();
                break;

            /*! Exit */
            default:
              exit(0);
              break;
        }
    }
}

/********************************************//**
* Menu application
***********************************************/
void return_to_menu()
{
    char opt;
    cout << endl << "Would you like to return? (y or n): ";
    cin >> opt;

    if ( opt == 'y' || opt == 'Y' )
        menu();
    else
        exit(0);
}

int main( int argc, char const *argv[] )
{
    /*! Call menu function */    
    menu();

    /*
        Using test class
        SLPool poolGM( 1000000 );
        poolTest.StoragePoolTest(poolGM, 5);
    */

    cout << "<<< Finish with success! >>>" << endl;

	/*! Main return */
	return 0;
}
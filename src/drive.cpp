/*! \file */ 
/*! \brief main.cpp.
 *
 *  Contains the menu function and starts the program.
*/
#include <iostream>
#include "SLPool.h"
#include "MempoolCommon.h"
#include "SLPoolTester.h"
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

void return_to_menu();

/********************************************//**
* Save the output file
***********************************************/
void saveFile( string _filename, string _content )
{
    std::ofstream ofs;
    std::string localFile = "assets/" + _filename + ".txt";

    ofs.open(localFile);

    if ( !ofs.is_open() )
    {
        ofs.open(localFile, std::fstream::in | std::fstream::out | std::fstream::app);
    }

    ofs << _content;
    ofs.close();
}

/********************************************//**
* Run a simple test of GM
***********************************************/
void simpleTest( unsigned int n_instances, size_t bytes )
{
    /*! Instance of test class */
    SLPoolTester poolTest;
    string filename = "";

    string out = "";

    /*! Running a simple test */
    cout << endl << "----------------------------------------------" << endl;
    cout << "<<< Sistema operacional (SO) >>>" << endl;
    cout << "----------------------------------------------" << endl << endl;

    filename = "outSO" + std::to_string(bytes);

    for ( unsigned int i = 0; i < n_instances; i++ )
    {
        double count = poolTest.getTickCount();

            long *ptrSO1 = new long[5];
            char *ptrSO2 = new char[2];
            long long *ptrSO3 = new long long;
            string *ptrSO4 = new string;
            float *ptrSO5 = new float[25];
            delete ptrSO1;
            delete ptrSO2;
            ptrSO2 = new char[8];
            delete ptrSO4;
            ptrSO1 = new long[2];
            ptrSO4 = new string;

        /*! Print the time */
        cout << "Interval SO = " << poolTest.getTickCount()-count << " ms" << endl;

        out += std::to_string( (poolTest.getTickCount()-count) ) + '\n';
    }

    /*! Save the time in the output file */
    saveFile(filename, out);

    cout << endl << "----------------------------------------------" << endl;

    /*! Running a simple test */
    cout << endl << "----------------------------------------------" << endl;
    cout << "<<< Gerenciador de memória (GM) - First Fit >>>" << endl;
    cout << "----------------------------------------------" << endl << endl;

    filename = "outGMFF" + std::to_string(bytes);

    for ( unsigned int i = 0; i < n_instances; i++ )
    {
        double count2 = poolTest.getTickCount();    
        SLPoolFF poolGM( bytes );

            long *ptrGM1 = new long[5];
            //poolGM.Debug();

            char *ptrGM2 = new char[2];
            //poolGM.Debug();

            long long *ptrGM3 = new long long;
            //poolGM.Debug();

            string *ptrGM4 = new string;
            //poolGM.Debug();

            float *ptrGM5 = new float[25];
            //poolGM.Debug();

            delete ptrGM1;
            //poolGM.Debug();

            delete ptrGM2;
            //poolGM.Debug();

            ptrGM2 = new char[8];
            //poolGM.Debug();

            delete ptrGM4;
            //poolGM.Debug();

            ptrGM1 = new long[2];
            //poolGM.Debug();

            ptrGM4 = new string;
            //poolGM.Debug();

        /*! Print the time */
        cout << "Interval GM FF = " << poolTest.getTickCount()-count2 << " ms" << endl;

        out += std::to_string( (poolTest.getTickCount()-count2) ) + '\n';
    }

    /*! Save the time in the output file */
    saveFile(filename, out);

    cout << endl << "----------------------------------------------" << endl;

    /*! Running a simple test */
    cout << endl << "----------------------------------------------" << endl;
    cout << "<<< Gerenciador de memória (GM) - Best Fit >>>" << endl;
    cout << "----------------------------------------------" << endl << endl;

    filename = "outGMBF" + std::to_string(bytes);

    for ( unsigned int i = 0; i < n_instances; i++ )
    {
        double count2 = poolTest.getTickCount();    
        SLPoolBF poolGM( bytes );

            long *ptrGM1 = new long[5];
            //poolGM.Debug();

            char *ptrGM2 = new char[2];
            //poolGM.Debug();

            long long *ptrGM3 = new long long;
            //poolGM.Debug();

            string *ptrGM4 = new string;
            //poolGM.Debug();

            float *ptrGM5 = new float[25];
            //poolGM.Debug();

            delete ptrGM1;
            //poolGM.Debug();

            delete ptrGM2;
            //poolGM.Debug();

            ptrGM2 = new char[8];
            //poolGM.Debug();

            delete ptrGM4;
            //poolGM.Debug();

            ptrGM1 = new long[2];
            //poolGM.Debug();

            ptrGM4 = new string;
            //poolGM.Debug();

        /*! Print the time */
        cout << "Interval GM BF = " << poolTest.getTickCount()-count2 << " ms" << endl;

        out += std::to_string( (poolTest.getTickCount()-count2) ) + '\n';
    }

    /*! Save the time in the output file */
    saveFile(filename, out);

    cout << endl << "----------------------------------------------" << endl << endl;

    //return_to_menu();   
}

/********************************************//**
* Run an advanced test from Test class
***********************************************/
void advancedTest( time_t _time )
{
    /*! Instance from SLPoolTester */
    SLPoolTester poolTest;
    SLPoolFF poolGM( 256 );
    poolGM.Debug();
    poolTest.StoragePoolTest(poolGM, _time);

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
    cout << "2) Automatic test " << endl;
    cout << "3) Exit " << endl << endl;
    cout << "----------------------------------------------" << endl << endl;    

    cout << "Inform the menu option: ";
    cin >> op;

    /*! Check if the option is valid */
    if ( op < 0 || op > 3 )
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
                /*unsigned int n;
                size_t memSize;
                cout << endl << "Inform the number of instances: ";
                cin >> n;
                cout << endl << "Inform the allocation block in bytes: ";
                cin >> memSize;
                simpleTest(n, memSize);*/

                for (auto i(1); i <= 20; ++i)
                {
                    simpleTest(100, (50 * i));
                }

                cout << endl << "<<< Output files generated with success >>> " << endl;
                break;

            /*! Advanced test */
            case 2:
                time_t time_test;
                cout << endl << "Inform the time limit in seconds: ";
                cin >> time_test;
                advancedTest(time_test);
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

/********************************************//**
* Main
***********************************************/
int main( int argc, char const *argv[] )
{
    /*! Call menu function */    
    menu();

    cout << "<<< Finish with success! >>>" << endl;

	/*! Main return */
	return 0;
}
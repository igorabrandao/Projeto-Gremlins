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
    string filename2 = "";

    string out = "";
    string out2 = "";

    /*! Running a simple test */
    out2 += "\n----------------------------------------------\n";
    out2 += "<<< Sistema operacional (SO) >>>\n";
    out2 += "----------------------------------------------\n\n";

    filename = "outSO" + std::to_string(bytes);
    filename2 = "Output";

    for ( unsigned int i = 0; i < n_instances; i++ )
    {
        double count = poolTest.getTickCount();
        SLPoolFF poolGM( bytes );

            int *ptrSO1 = new int[5];
            poolGM.Debug();

            int *ptrSO2 = new int[2];
            poolGM.Debug();

            int *ptrSO3 = new int;
            poolGM.Debug();

            int *ptrSO4 = new int;
            poolGM.Debug();

            int *ptrSO5 = new int[25];
            poolGM.Debug();

            delete ptrSO1;
            poolGM.Debug();

            delete ptrSO2;
            poolGM.Debug();

            ptrSO2 = new int[8];
            poolGM.Debug();

            delete ptrSO4;
            poolGM.Debug();

            ptrSO1 = new int[2];
            poolGM.Debug();

            ptrSO4 = new int;
            poolGM.Debug();

        /*! Print the time */
        cout << "Interval SO = " << poolTest.getTickCount()-count << " ms" << endl;

        out += std::to_string( (poolTest.getTickCount()-count) ) + '\n';
    }

    /*! Save the time in the output file */
    saveFile(filename, out);

    out2 += "\n----------------------------------------------\n";

    /*! Running a simple test */
    out2 += "\n----------------------------------------------\n";
    out2 += "<<< Memory Manager (GM) - First Fit >>>\n";
    out2 += "----------------------------------------------\n\n";

    filename = "outGMFF" + std::to_string(bytes);

    for ( unsigned int i = 0; i < n_instances; i++ )
    {
        double count2 = poolTest.getTickCount();    
        SLPoolFF poolGM( bytes );

            int *ptrGM1 = new int[5];
            poolGM.Debug();

            int *ptrGM2 = new int[2];
            poolGM.Debug();

            int *ptrGM3 = new int;
            poolGM.Debug();

            int *ptrGM4 = new int;
            poolGM.Debug();

            int *ptrGM5 = new int[25];
            poolGM.Debug();

            delete ptrGM1;
            poolGM.Debug();

            delete ptrGM2;
            poolGM.Debug();

            ptrGM2 = new int[8];
            poolGM.Debug();

            delete ptrGM4;
            poolGM.Debug();

            ptrGM1 = new int[2];
            poolGM.Debug();

            ptrGM4 = new int;
            poolGM.Debug();

        /*! Print the time */
        out2 += "Interval GM FF = " + std::to_string( (poolTest.getTickCount()-count2) ) + " ms\n";

        out += std::to_string( (poolTest.getTickCount()-count2) ) + '\n';
    }

    /*! Save the time in the output file */
    saveFile(filename, out);

    out2 += "\n----------------------------------------------\n";

    /*! Running a simple test */
    out2 += "\n----------------------------------------------\n";
    out2 += "<<< Memory Manager (GM) - Best Fit >>>\n";
    out2 += "----------------------------------------------\n\n";

    filename = "outGMBF" + std::to_string(bytes);

    for ( unsigned int i = 0; i < n_instances; i++ )
    {
        double count2 = poolTest.getTickCount();    
        SLPoolBF poolGM( bytes );

            int *ptrGM1 = new int[5];
            poolGM.Debug();

            int *ptrGM2 = new int[2];
            poolGM.Debug();

            int *ptrGM3 = new int;
            poolGM.Debug();

            int *ptrGM4 = new int;
            poolGM.Debug();

            int *ptrGM5 = new int[25];
            poolGM.Debug();

            delete ptrGM1;
            poolGM.Debug();

            delete ptrGM2;
            poolGM.Debug();

            ptrGM2 = new int[8];
            poolGM.Debug();

            delete ptrGM4;
            poolGM.Debug();

            ptrGM1 = new int[2];
            poolGM.Debug();

            ptrGM4 = new int;
            poolGM.Debug();

        /*! Print the time */
        //cout << "Interval GM BF = " << poolTest.getTickCount()-count2 << " ms" << endl;

        out += std::to_string( (poolTest.getTickCount()-count2) ) + '\n';
    }

    /*! Save the time in the output file */
    saveFile(filename, out);

    out += "\n----------------------------------------------\n\n";

    /*! Save the time in the output file */
    saveFile(filename2, out2);

    //return_to_menu();
}

/********************************************//**
* Run an advanced test from Test class
***********************************************/
void advancedTest( time_t _time )
{
    cout << endl << "----------------------------------------------" << endl;
    cout << "<<< Memory Manager (GM) - First Fit >>>" << endl;
    cout << "----------------------------------------------" << endl << endl;

    /*! Instance from SLPoolTester */
    SLPoolTester poolTest;
    SLPoolFF poolGM( 256 );
    poolGM.Debug();
    poolTest.StoragePoolTest(poolGM, _time);

    /*cout << endl << "----------------------------------------------" << endl;
    cout << "<<< Memory Manager (GM) - Best Fit >>>" << endl;
    cout << "----------------------------------------------" << endl << endl;*/

    /*! Instance from SLPoolTester */
    /*SLPoolTester poolTest2;
    SLPoolBF poolGM2( 256 );
    poolGM2.Debug();
    poolTest2.StoragePoolTest(poolGM2, _time);*/

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
                int n;
                size_t memSize;
                cout << endl << "Inform the number of instances: ";
                cin >> n;
                cout << endl << "Inform the allocation block in bytes: ";
                cin >> memSize;
                //simpleTest(n, memSize);

                for ( auto i(1); i <= n; ++i )
                {
                    simpleTest(100, (memSize * i));
                }

                cout << endl << "<<< Output files generated with success >>> " << endl;
                break;

            /*! Advanced test */
            case 2:
                time_t time_test;
                cout << endl << "Inform the time limit: ";
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
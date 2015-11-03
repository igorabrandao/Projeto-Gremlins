#include <iostream>
#include "m_pool.h"

using namespace std;

int main()
{
    void* x;
    void* y;
    void* s;

    cout << x << endl;
    cout << y << endl;
    cout << s << endl;

    SLPool pool( 100 );
    x = pool.Allocate( 12);
    cout << x << endl;

    y = pool.Allocate( 65 );
    cout << y << endl;


    s = pool.Allocate( 30 );
    cout << s << endl;


    cout << "Hello world!" << endl;
    return 0;
}

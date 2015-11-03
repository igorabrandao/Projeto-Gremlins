/*! \file */ 
/*! \brief SLPool.inl.
 *
 *  Implements the functions from SLPool class.
*/

#include "SLPool.h"

/********************************************//**
* constructor
***********************************************/
SLPool::SLPool( size_t bytes )
{
    double leop = bytes + sizeof (Header);
	double riop = sizeof (Block);
	double op = leop/riop;

	mui_NumberOfBlocks = ceil(op);
	cout << mui_NumberOfBlocks << endl;

	Block *aux = new Block[ mui_NumberOfBlocks+1 ];
    mp_Pool = aux;
	mp_Pool->mui_Length = ( mui_NumberOfBlocks );
	mp_Pool->mp_Next = nullptr;
	mr_Sentinel=&mp_Pool[mui_NumberOfBlocks+1];
	mr_Sentinel->mp_Next = mp_Pool;

	cout << " primeiro: " << &mp_Pool[0] << "  ultimo " << &mp_Pool[mui_NumberOfBlocks] << endl;
    cout << " Sentinel  " << &mp_Pool[mui_NumberOfBlocks+1] << endl;
    cout << " funfando  " << mr_Sentinel->mp_Next << endl;
}

/********************************************//**
* destructor
***********************************************/
SLPool::~SLPool()
{
	delete mp_Pool;
}

/********************************************//**
* Allocates a volume of memory defined by 
* the argument in bytes.
***********************************************/
void * 
SLPool::Allocate( size_t bytes )
{
    double leop= bytes + sizeof (Header);
	double riop=sizeof (Block);
	double op=leop/riop;
    unsigned int N_Blocks =ceil(op);
    cout << "N blocks " << N_Blocks << endl;

    Block * aux;
    aux = mr_Sentinel;
    Block * aux1;
    Block * aux3;

    if ( mr_Sentinel->mp_Next == mp_Pool && mp_Pool[0].mui_Length >= N_Blocks )
    {
        if( aux->mp_Next->mui_Length == N_Blocks )
        {
            aux=mr_Sentinel->mp_Next;
            aux->mui_Length=N_Blocks;
            aux->mp_Next=nullptr;
            mr_Sentinel->mp_Next = nullptr;
            cout<<endl<<"chegou mizeravi "<< aux->mp_Next<<endl;
            ;

            //return aux;
        }
        cout<<"test3 : "<<aux<<endl;

        aux=aux->mp_Next;
        aux->mui_Length=N_Blocks;

        cout<<"test4 : "<<aux<<endl;

        aux3=aux+N_Blocks;
        aux3->mui_Length=mui_NumberOfBlocks-N_Blocks;
        aux->mp_Next = aux3;
        aux3->mp_Next=nullptr;

        cout<<"test2 :  ."<<aux3<<endl;
        cout<<"test5 :   "<<mp_Pool[1].mui_Length<<endl;
        cout<<"test6 :   "<<mp_Pool[0].mp_Next<<endl;


        mr_Sentinel->mp_Next = aux;
        cout<<"test: "<<aux<<endl;


        //return aux;
    }

    while( aux->mp_Next== nullptr && aux->mui_Length < N_Blocks )
    {
        aux = aux->mp_Next;
    }

    if( aux->mp_Next != nullptr )
    {
        aux1 = aux->mp_Next;
        if( aux1->mui_Length == N_Blocks )
        {

            if( aux1->mp_Next != nullptr )
                aux = aux1->mp_Next;
                aux1->mp_Next = nullptr;
                aux1->mui_Length = N_Blocks;
                //return aux1;
            }

             else if( aux->mp_Next->mui_Length > N_Blocks )
            {
                Block * aux2 = aux->mp_Next;
                aux = aux2 + N_Blocks;
                aux->mp_Next = aux2->mp_Next;
                aux2->mp_Next = nullptr;
                //return aux2;
            }

    }
    else
    {
       cout << "There is not suficient space!" << endl;
       return nullptr;
    }
}

/********************************************//**
* Allocates a volume of memory defined by 
* the argument in bytes.
***********************************************/
void
SLPool::Free( void * )
{
	/* Empty */
}
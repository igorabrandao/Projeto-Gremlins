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
	/*! Calculate the minimum number of blocks */
	double aux_blocks = ( (double)(bytes + sizeof(Header)) / (double)sizeof(Block) );
	mui_NumberOfBlocks = ceil(aux_blocks);
	cout << "<<< Number of blocks: " << mui_NumberOfBlocks << " >>>" << endl;
	cout << "<<< Sizeof of blocks: " << sizeof(Block) << " >>>" << endl;

	/*! Create the new block */
	Block * newBlock = new Block[(mui_NumberOfBlocks + 1)];

	/*! Receive the new block pointer */
    mp_Pool = newBlock;

    /*! Define the number of blocks in the tag area */
	mp_Pool->mui_Length = ( mui_NumberOfBlocks );
	mp_Pool[0].mui_Length = ( mui_NumberOfBlocks );

	/*! Indicate that exists another node in the free area */
	mp_Pool->mp_Next = nullptr;

	/*! Define the sentinel as the last block of the memory */
	mr_Sentinel = &mp_Pool[(mui_NumberOfBlocks + 1)];

	/*! Points the sentinel next node to the begin */
	mr_Sentinel->mp_Next = mp_Pool;
}

/********************************************//**
* destructor
***********************************************/
SLPool::~SLPool()
{
	//delete[] mp_Pool;
}

/********************************************//**
* Allocates a volume of memory defined by 
* the argument in bytes.
***********************************************/
void * 
SLPool::Allocate( size_t bytes )
{
	/*! Calculate the minimum number of blocks */
	double aux_blocks = ( (double)(bytes + sizeof(Header)) / (double)sizeof(Block) );

	/*! Round to above ceil(math.h) */
    unsigned int N_Blocks = ceil(aux_blocks);
    cout << "<<< N blocks: " << N_Blocks << " >>>" << endl;

    /*! Pointer to the block */
    Block * newBlock;
    Block * newBlock2;

    /*! Receive the block's head */
    newBlock = mr_Sentinel->mp_Next; // Keeps the header
    newBlock2 = mr_Sentinel;

    /*! Check if the sentinel points to a block */
    if ( mr_Sentinel->mp_Next != nullptr )
    {
    	/*! Run through the free area list and check if it has enough space */
	    while ( newBlock->mui_Length < N_Blocks && newBlock->mp_Next != nullptr )
	    {
	    	newBlock = newBlock->mp_Next;
	    	newBlock2 = newBlock2->mp_Next;
	    }

	    /*! 1º) Check if the area fits exactly */
	    if ( newBlock->mui_Length == N_Blocks )
	    {
	    	/*! The previous pointer jumps toward the "normal" one */
	    	newBlock2->mp_Next = newBlock->mp_Next;
	    	newBlock->mp_Next = nullptr;

	    	/*! Pointer to jump the header and return the raw area */
	    	void * space_pointer = newBlock;
	    	space_pointer += sizeof(Header);

	    	/*! Return the raw area */
	    	return ( space_pointer );
	    }

	    /*! 2º) Check if the area is bigger than necessary */
	    else if ( newBlock->mui_Length > N_Blocks )
	    {
	    	/*! Save the actually reserved area */
	    	Block * newBlock3 = newBlock;

	    	/*! Jump N_Blocks ahead (next free area) */
	    	newBlock += N_Blocks;

	    	/*! Define the next free area length */
	    	newBlock->mui_Length = (newBlock3->mui_Length - N_Blocks);

	    	/*! Update the reserved area length */
	    	newBlock3->mui_Length = N_Blocks;

	    	/*! The next free area header receives the next next one */
	    	newBlock->mp_Next = newBlock3->mp_Next;

	    	/*! Isolates the reserved area */
	    	newBlock3->mp_Next = nullptr;

	    	/*! Reconect the previous area with the next free one */
	    	newBlock2->mp_Next = newBlock;

	    	/*! Pointer to jump the header and return the raw area */
	    	void * space_pointer = newBlock3;
	    	space_pointer += sizeof(Header);

	    	/*! Return the raw area */
	    	return ( space_pointer );
	    }

	    /*! 3º) Check if the area is smaller than necessary */
	    else
	    {
	    	/*! throws not enough space exception */
	    	cout << "<<< There ins't enough space to be allocated! >>>" << endl;
	    }
    }
    else
    {
    	// throws bad alloc exception (it's full)
    	return nullptr;
    }
}

/********************************************//**
* Receive a pointer to the reserved area and 
* free this area to be used later
***********************************************/
void
SLPool::Free( void * p )
{
	/*! Pointer to the reserved area  */
    Block * ptReserved = (Block*)p;

    /*! Pointer to the previous reserved area  */
    Block * ptPrevReserved = mr_Sentinel;

    /*! Pointer to the next reserved area  */
    Block * ptPostReserved = mr_Sentinel->mp_Next;

    /*! Check if the reserved area is inside of memory pool */
    if ( ptReserved < &mp_Pool[0] || ptReserved > &mp_Pool[mui_NumberOfBlocks - 1] )
    {
    	/*! Out of range */
        cout << "<<< Invalid reference! >>>" << endl;
        return;
    }

    /*! Check if the block is full */
    if ( mr_Sentinel->mp_Next == nullptr )
    {
    	mr_Sentinel->mp_Next = ptReserved;
    	ptReserved->mp_Next = nullptr;
    	p = nullptr;
    	return;
    }
   	else
    {
	    while ( ptPostReserved < ptReserved && ptPostReserved != nullptr )
	    {
	    	ptPostReserved = ptPostReserved->mp_Next;
	    	ptPrevReserved = ptPrevReserved->mp_Next;
	    }

	   	if ( ( ptPostReserved - ptReserved->mui_Length ) == ptReserved )
	   	{
	   		ptReserved->mp_Next = ptPostReserved->mp_Next;

	   		ptReserved->mui_Length += ptPostReserved->mui_Length;
	   		ptPostReserved->mui_Length = 0;
	   		ptPostReserved->mp_Next = nullptr;
	    }
	    else
	    {
            ptReserved->mp_Next = ptPostReserved;
        }

	    if ( ( ptPrevReserved + ptPrevReserved->mui_Length ) == ptReserved )
	    {
	    	ptPrevReserved->mp_Next = ptReserved->mp_Next;
	    	ptReserved->mp_Next = nullptr;
	    	ptPrevReserved->mui_Length += ptReserved->mui_Length;
	    	ptReserved->mui_Length = 0;
	    }
	    else
	    {
            ptPrevReserved->mp_Next = ptReserved;
        }
	}
}

void
SLPool::Debug()
{
	cout << endl;
    Block *test[ mui_NumberOfBlocks ];
    Block *aux = mr_Sentinel->mp_Next;
    cout << "aux: " << aux << endl;
    //cout<<"aux-mui_Length: "<<aux->mui_Length<<endl;


    int nb[ mui_NumberOfBlocks ];
    int i = 0;
    int j = 0;

    cout << endl;
    for( unsigned int lok( 0 ); lok < mui_NumberOfBlocks;lok++ ){
        if( &mp_Pool[ lok ]== aux )
        {
            j = 0;
            for( unsigned int k = 0;k < mp_Pool[ lok ].mui_Length; k++ )
            {
                cout << "0" << " ";
            	j++;
            }
            lok = lok + j - 1;
            aux = aux->mp_Next;
        }
        
        else
        {
        	cout << "*" << " ";
        }
    }
    cout << endl;
    return;
}
/*! \file */ 
/*! \brief SLPool.cpp.
 *
 *  Implements the functions from SLPool class.
*/

#include "SLPool.h"

/********************************************//**
* constructor SLPool
***********************************************/
SLPool::SLPool( size_t bytes )
{
	/*! Calculate the minimum number of blocks */
	double aux_blocks = ( (double)(bytes + sizeof(Header)) / (double)sizeof(Block) );
	mui_NumberOfBlocks = ceil(aux_blocks);

	cout << "<<< Creating new Memory Pool... >>>" << endl;
    cout << "<<< Number of blocks:\t " << mui_NumberOfBlocks << " >>>" << endl;
    cout << "<<< Blocks sizeof:\t " << sizeof(Block) << " >>>" << endl << endl << endl;

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
	mr_Sentinel = &mp_Pool[mui_NumberOfBlocks];

	/*! Points the sentinel next node to the begin */
	mr_Sentinel->mp_Next = mp_Pool;
}

/********************************************//**
* constructor SLPoolFF
***********************************************/
SLPoolFF::SLPoolFF( size_t bytes ) : SLPool(bytes)
{
	/*! Call base class constructor */
}

/********************************************//**
* constructor SLPoolBF
***********************************************/
SLPoolBF::SLPoolBF( size_t bytes ) : SLPool(bytes)
{
	/*! Call base class constructor */
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
* the argument in bytes (First-Fit).
***********************************************/
void * 
SLPoolFF::Allocate( size_t bytes )
{
	/*! Calculate the minimum number of blocks */
	double aux_blocks = ( (double)(bytes + sizeof(Header)) / (double)sizeof(Block) );

	/*! Round to above ceil(math.h) */
    unsigned int N_Blocks = ceil(aux_blocks);

    cout << "<<< Allocating... >>>" << endl;
    cout << "<<< Number of blocks:\t " << N_Blocks << " >>>" << endl;
    cout << "<<< Blocks sizeof:\t " << sizeof(Block) << " >>>" << endl;

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
	    	//newBlock->mp_Next = newBlock3->mp_Next;
	    	newBlock2->mp_Next = newBlock;

	    	newBlock->mp_Next = newBlock3->mp_Next;
	    	/*! Isolates the reserved area */
	    	//newBlock3->mp_Next = nullptr;

	    	/*! Reconect the previous area with the next free one */
	    	//newBlock2->mp_Next = newBlock;
	    	newBlock -= N_Blocks;
	    	newBlock->mp_Next = nullptr;

	    	/*! Pointer to jump the header and return the raw area */
	    	void * space_pointer = newBlock;
	    	space_pointer += sizeof(Header);

	    	/*! Return the raw area */
	    	return ( space_pointer );
	    }
	    /*! 3º) Check if the area is smaller than necessary */
	    else
	    {
	    	/*! throws bad_alloc exception */
	    	cout << endl << "<<< Insufficient space to be allocated! >>>" << endl << endl;
	    	//throw std::bad_alloc();
	    	return nullptr;
	    }
    }
    else
    {
		/*! throws bad_alloc exception */
    	cout << endl << "<<< Insufficient space to be allocated! >>>" << endl << endl;
    	//throw std::bad_alloc();
    	return nullptr;
    }
}

/********************************************//**
* Allocates a volume of memory defined by 
* the argument in bytes (First-Fit).
***********************************************/
void * 
SLPoolBF::Allocate( size_t bytes )
{
	/*! Variables */
	int diff = 0; //!< store the difference between N_Blocks and free area size
	int occurrence = 0;

	/*! Calculate the minimum number of blocks */
	double aux_blocks = ( (double)(bytes + sizeof(Header)) / (double)sizeof(Block) );

	/*! Round to above ceil(math.h) */
    unsigned int N_Blocks = ceil(aux_blocks);

    cout << "<<< Allocating... >>>" << endl;
    cout << "<<< Number of blocks:\t " << N_Blocks << " >>>" << endl;
    cout << "<<< Blocks sizeof:\t " << sizeof(Block) << " >>>" << endl;

    /*! Pointer to the block */
    Block * newBlock;
    Block * newBlock2;
    Block * newBlock_bestfit;

    /*! Receive the block's head */
    newBlock = mr_Sentinel->mp_Next; // Keeps the header
    newBlock2 = mr_Sentinel;
    newBlock_bestfit = mr_Sentinel;

	/*! Check if the sentinel points to a block */
	if ( mr_Sentinel->mp_Next != nullptr )
	{
    	/*! Run through the free area list and check if it has enough space */
	    while ( newBlock->mp_Next != nullptr )
	    {
	    	diff = (newBlock->mui_Length - N_Blocks);

	    	/*! Check if the area fits exactly */
			if ( diff == 0 )
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
			/*! Check if the area is bigger than necessary */
			else if ( diff > 0 )
			{
				if ( occurrence != 0 )
				{
					if ( diff < (newBlock_bestfit->mp_Next->mui_Length - N_Blocks) )
					{
						newBlock_bestfit = newBlock2;
					}
				}
				else
				{
					/*! First occurence */
					newBlock_bestfit = newBlock2;
				}

				occurrence += 1;
			}
			/*! Check if the area is smaller than necessary */
			else
			{
				/*newBlock = newBlock->mp_Next;
	    		newBlock2 = newBlock2->mp_Next;*/
			}

	    	newBlock = newBlock->mp_Next;
	    	newBlock2 = newBlock2->mp_Next;

	    } // End while

	    newBlock = newBlock_bestfit;
	    newBlock = newBlock->mp_Next;
	    newBlock2 = newBlock_bestfit;

 		if ( newBlock->mui_Length > N_Blocks )
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
	    	//newBlock->mp_Next = newBlock3->mp_Next;
	    	newBlock2->mp_Next = newBlock;

	    	newBlock->mp_Next = newBlock3->mp_Next;
	    	/*! Isolates the reserved area */
	    	//newBlock3->mp_Next = nullptr;

	    	/*! Reconect the previous area with the next free one */
	    	//newBlock2->mp_Next = newBlock;
	    	newBlock -= N_Blocks;
	    	newBlock->mp_Next = nullptr;

	    	/*! Pointer to jump the header and return the raw area */
	    	void * space_pointer = newBlock;
	    	space_pointer += sizeof(Header);

	    	/*! Return the raw area */
	    	return ( space_pointer );
	    }
		else
	    {
	    	/*! throws bad_alloc exception */
	    	cout << endl << "<<< Insufficient space to be allocated! >>>" << endl << endl;
	    	throw std::bad_alloc();
	    	//return nullptr;
	    }
    }
    else
    {
		/*! throws bad_alloc exception */
    	cout << endl << "<<< Insufficient space to be allocated! >>>" << endl << endl;
    	throw std::bad_alloc();
    	//return nullptr;
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
	p -= sizeof(Header);
    Block * ptReserved = (Block*)p;

    /*! Pointer to the previous reserved area  */
    Block * ptPrevReserved = mr_Sentinel;

    /*! Pointer to the next reserved area  */
    Block * ptPostReserved = mr_Sentinel->mp_Next;

    /*! Check if the reserved area is inside of memory pool */
    if ( ptReserved < &mp_Pool[0] || ptReserved > &mp_Pool[(mui_NumberOfBlocks - 1)] )
    {
    	/*! Out of range */
        cout << "<<< Invalid reference! >>>" << endl;
        return;
    }

    /*! Check if the pool is full */
    if ( mr_Sentinel->mp_Next == nullptr )
    {
    	/*! Reconect to the free block of the list */
    	mr_Sentinel->mp_Next = ptReserved;

    	/*! Remove the reference to the new free block */
    	p = nullptr;
    	return;
    }
   	else
    {
    	/*! Run through free area list */
	    while ( ptPostReserved != nullptr && ptPostReserved < ptReserved )
	    {
	    	/*! The ptPostReserved needs to be after the ptReserved */
	    	ptPostReserved = ptPostReserved->mp_Next;

	    	/*! The ptPrevReserved needs to be before the ptReserved */
	    	ptPrevReserved = ptPrevReserved->mp_Next;
	    }

	    /*! 1) The previous and the next area are free 
		 *  Check if the next area minus the block size is
		 *  equal to the actual area (pointer arithmetics).
	    */
	   	if ( ( ptPostReserved - ptReserved->mui_Length ) == ptReserved )
	   	{
	   		/*! Combine the 3 areas in a single one */
	   		ptReserved->mp_Next = ptPostReserved->mp_Next;

	   		/*! Combine the nodes in ptReserved and sum the areas */
	   		ptReserved->mui_Length += ptPostReserved->mui_Length;

	   		/*! Isolates the ptPostReserved pointer */
	   		ptPostReserved->mui_Length = 0;
	   		ptPostReserved->mp_Next = nullptr;
	    }
	    /*! 2) Add the free area to the list without merging the others
		 *  The previous and next area are reserved.
	    */
	    else
	    {
            ptReserved->mp_Next = ptPostReserved;
        }

        /*! 3) The previous area is reserved and the next one is free 
		 *  Check if the previous area plus the block size is
		 *  equal to the actual area (pointer arithmetics).
	    */
	    if ( ( ptPrevReserved + ptPrevReserved->mui_Length ) == ptReserved )
	    {
	    	ptPrevReserved->mp_Next = ptReserved->mp_Next;
	    	ptReserved->mp_Next = nullptr;
	    	ptPrevReserved->mui_Length += ptReserved->mui_Length;
	    	ptReserved->mui_Length = 0;
	    }
	    /*! 4) The previous area is free and the next one is reserved 
		 *  Combine the actual with the previous one.
	    */
	    else
	    {
            ptPrevReserved->mp_Next = ptReserved;
        }
	}
}

/********************************************//**
* Print the block list (debug)
* AUTHORS: José Carlos and Heraclito César
***********************************************/
void
SLPool::Debug()
{
	cout << "***************[MEMORY SITUATION]*****************" << endl;

    Block * test[mui_NumberOfBlocks];
    Block* aux=mr_Sentinel->mp_Next;

    Block *aux2 = mr_Sentinel->mp_Next;
    Block* aux3 =mr_Sentinel->mp_Next;

    int nb=mui_NumberOfBlocks/20;
    int dec=mui_NumberOfBlocks%20;
    int mb=mui_NumberOfBlocks/6;
    int mdec=mui_NumberOfBlocks%6;

    int i=0;
    int j=0;
    int k=0;
    int h=0;

    int lop;
    int lop2;
    
    int cs=0;
    int lk=0;

    char preenchido[mui_NumberOfBlocks];
    
    int livre=0;

    for ( lop=0; lop <mui_NumberOfBlocks; lop++)
    {
        if ( &mp_Pool[lop] == aux2 )
        {
            for ( lop2 = 0; lop2 < aux2->mui_Length; lop2++ )
            {
                preenchido[lop] = ' ';
                lop++;
            }
            lop--;

            aux2=aux2->mp_Next;
        }
        else
        {
            preenchido[lop]='-';
        }
    }

    for ( unsigned int lok( 0 ); lok <= nb; lok++)
    {
		for (; k < lok * 20; k++)
		{
			cout << mp_Pool[ k ].mui_Length << " ";
		}

		cout<<endl;

		for (; h < lok*20; h++ )
		{
			int ts = mp_Pool[h].mui_Length;

			cs = Casas(ts);

			if ( cs > 1 )
			{
				for ( lk = 0; lk < cs; lk++ )
				{
					cout << preenchido[ h ];
				}

                    cout<<" ";
                }
                else
                {
                    cout << preenchido[ h ]<<" ";
                }
            }
            cout << endl;
    }

    i=0;
    j=0;
    k=0;
    h=0;
    lk=0;

    for( k = nb*20; k < mui_NumberOfBlocks; k++ )
    {
		cout << mp_Pool[ k ].mui_Length << " ";
	}
	cout<<endl;

    for ( h = nb*20; h < mui_NumberOfBlocks; h++ )
    {
        cout << preenchido[ h ]<<" ";
	}
	cout << endl << endl;

    i = 0;
    j = 0;
    k = 0;
    h = 0;
    lk = 0;

    lop = 0;
    lop2;

    cout << endl << "Free areas from block: ";

    while ( aux3 != nullptr )
    {
        livre=aux3-&mp_Pool[0];
        livre++;
        cout<<livre<<" -> ";
        aux3=aux3->mp_Next;
    }
    cout << "nullptr" << endl;

    cout << endl << "**************************************************" << endl << endl;
    return;
}

/********************************************//**
* Calculates the number o blank spaces to put
* the underline sign
* AUTHORS: José Carlos and Heraclito César
***********************************************/
int
SLPool::Casas( int p )
{
    int i = 0;
    int k = p;

    while( k > 0 )
    {
        k = k / 10;
        i++;
    }

    return i;
}
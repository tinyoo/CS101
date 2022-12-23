#include<iostream>

using namespace std;

void MaxHeapify( long int * M, int index, int size );
void HeapSort( long int * M, int size );

int main(void)
{
    long int N, Memo, c, k = 0;
    cin >> N;
    long int M[N + 1], 
             C[N + 1], 
             comsumption[N + 1],
             heap[2 * N + 1];

    for ( int i = 1; i <= N; ++i )
    {
        cin >> Memo;
        M[i] = Memo;
    }
    for ( int i = 1; i <= N; ++i )
    {
        cin >> c;
        C[i] = c;
    }

    for ( int i = 1; i <= N; ++i )
    {
        comsumption[i] = 0;
    }
//--------------------------------------------
    for ( int i = 1; i <= N; ++i )
    {
        HeapSort( M, i + 1 );
        for ( int j = k + 1; j <= i; ++j )
        {
            if ( M[j] - C[i] > 0 )
            {
                comsumption[i] += C[i];
                M[j] -= C[i];
            }
            else
            {
                comsumption[i] += M[j];
                M[j] = 0;
                k ++;
            }
        }
    }

    for ( int i = 1; i <= N; ++i )
    {
        cout << comsumption[i] << " ";
    }

    return 0;

}

//*********************************************************************

void MaxHeapify( long int * M, int index, int size )
{
    while( ( index != 0 ) && ( 2 * index < size ) )
    {
        if ( 2 * index + 1 < size )
        {
            if ( ( M[index] >= M[2 * index] ) && ( M[index] >= M[2 * index + 1] ) )
                MaxHeapify( M, index--, size );
            else
            {
                if ( M[2 * index] >= M[2 * index + 1] )
                {
                    long int larger = M[2 * index];
                    M[2 * index] = M[index];
                    M[index] = larger;
                    MaxHeapify( M, 2 * index, size );
                }
                else
                {
                    long int larger = M[2 * index + 1];
                    M[2 * index + 1] = M[index];
                    M[index] = larger;
                    MaxHeapify( M, 2 * index + 1, size );            
                }
                MaxHeapify( M, index--, size );
            }
        }
        else
        {
            if ( ( M[index] < M[2 * index] ) )
            {
                    long int larger = M[2 * index];
                    M[2 * index] = M[index];
                    M[index] = larger;
                    MaxHeapify( M, 2 * index, size );
            }
        }
    }
}

//*************************************************************************

void HeapSort( long int * M, int size )
{
    while ( size != 1 )
    {
        MaxHeapify( M, ( size - 1 ) / 2, size );
        int temp = M[1];
        for ( int i = 1; i < size - 1; ++i )
        {
            M[i] = M[i + 1];
        }
        M[size - 1] = temp;
        size --;
        MaxHeapify( M, ( size - 1 ) / 2, size );
    }
}
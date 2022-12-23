#include<iostream>

using namespace std;

void MinHeapify( long int * M, int index );
void Pop( long int * M, int size );
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
        HeapSort( M, i );
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
            for( int m = 1; m <= k; ++m )
            {
                pop( M, N );
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

void MinHeapify( long int * M, int index )
{
    while( index != 0 )
    {
        if ( ( M[index] <= M[2 * index] ) && ( M[index] <= M[2 * index + 1] ) )
            MinHeapify( M, index-- );
        else
        {
            if ( M[2 * index] <= M[2 * index + 1] )
            {
                long int smaller = M[2 * index];
                M[2 * index] = M[index];
                M[index] = smaller;
            }
            else
            {
                long int smaller = M[2 * index + 1];
                M[2 * index + 1] = M[index];
                M[index] = smaller;               
            }
            MinHeapify( M, index-- );
        }
    }
}

//*************************************************************************

void Pop( long int * M, int size )
{
    MinHeapify( M, size / 2 );
    int temp = M[1];
    for ( int i = 1; i < size; ++i )
    {
        M[i] = M[i + 1];
    }
    M[size] = temp;
    size --;
    MinHeapify( M, size / 2 );
}

//********************************************************************************

void HeapSort( long int * M, int size )
{
    while( size != 1 )
    {
        Pop( M, size );
        size --;
    }
}
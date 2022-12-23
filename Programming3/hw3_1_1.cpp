#include<iostream>

using namespace std;

void MaxHeap( long int * comsumption, int index );

int main(void)
{
    long int N, Memo, c;
    cin >> N;
    long int M[N + 1], C[N + 1], comsumption[N + 1], heap[N + 1];

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
//----------------------------------------------------------
    for ( int i = 1; i <= N; ++i )
    {
        for ( int j = 1; j <= i ; ++j )
        {   
            for ( int k = 1; k <= j; ++k )
            {
                heap[k] = M[k];
            }
            MaxHeap( heap, j / 2 );
            if ( heap[j] != 0 )
            {
                if ( heap[j] - C[i] >= 0 )
                {
                    comsumption[i] += C[i];
                    heap[j] -= C[i];
                }
                else
                {
                    comsumption[i] += heap[j];
                    heap[j] = 0;
                }
            }
            else
                break;
        }
    }

    for ( int i = 1; i <= N; ++i )
    {
        cout << comsumption[i] << " ";
    }

    return 0;

}

void MaxHeap( long int * comsumption, int index )
{
    while( index != 0 )
    {
	    int x = comsumption[index];
        int y = comsumption[2 * index];
        int z = comsumption[2 * index + 1];
        int first, second, third;
        if ( x >= y )
        {
            if ( y >= z )
            {
                first = x;
                second = y;
                third = z;
            }
            else
            {
                if ( x < z )
                {
                    first = z;
                    second = x;
                    third = y;
                }
                else
                {
                    first = x;
                    second = z;
                    third = y;
                }
            }
        }
        else
        {
            if ( y <= z )
            {
                first = z;
                second = y;
                third = x;
            }
            else
            {
                if ( z <= x )
                {
                    first = y;
                    second = x;
                    third = z;
                }
                else
                {
                    first = y;
                    second = z;
                    third = x;
                }
            }
        }

        comsumption[index] = first;
        comsumption[2 * index] = second;
        comsumption[2 * index + 1] = third;
        index --;
        MaxHeap( comsumption, index );
    }
}
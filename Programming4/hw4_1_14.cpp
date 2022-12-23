#include <iostream>       ////  2019.12.22

using namespace std;

int gcd( int x, int y );
int LBS( int *array, int a, int b, int target );
int HBS( int *array, int a, int b, int target );
int IOI( int *Sequence, int l, int r, int x, int n, int *copy );

int main(void)
{
    int n, s, num_x, x;

    // Address the sequence
    cin >> n;
    int *Sequence = new int[n];
    int *copy = new int[n];
    for ( int i = 0; i < n; ++i )
    {
        cin >> s;
        Sequence[i] = s;
    }

    // Address x
    cin >> num_x;
    int *array = new int[num_x];
    for ( int i = 0; i < num_x; ++i )
    {
        cin >> x;
        array[i] = x;
    }

    // Use an array to store the answer
    int *Ans = new int[num_x];

    for ( int i = 0; i < num_x; ++i )
        Ans[i] = IOI( Sequence, 0, n, array[i], n, copy );

    // Output the answer
    for ( int i = 0; i < num_x; ++i )
        cout << Ans[i] << " ";

    return 0;
}

//-------------------------------------------
int IOI( int *Sequence, int l, int r, int x, int n, int *copy )
{
    int num = 0;
    int left, right;
    int mid = ( l + r ) / 2;

    if ( ( r - l ) == 1)
    {
        if ( Sequence[l] == x )
        {
            left = 1;
            right = 0;
        }
        else
        {
            left = 0;
            right = 0;
        }
    }
    else
    {   
        left = IOI( Sequence, l, mid, x, n, copy );
        right = IOI( Sequence, mid, r, x, n, copy );
    }
//
    if ( ( r - l ) != 1 )
    {
        for ( int i = l; i < r; ++i )
            copy[i] = Sequence[i];

        //int array1[100], array2[100];
        for ( int i = mid - 2; i >= l; --i )
            copy[i] = gcd( copy[i+1], copy[i] );
        for ( int i = mid + 1; i < r; ++i )
            copy[i] = gcd( copy[i-1], copy[i] );

        /////////////////////////////////////////////

        int j = mid;
        int low, high; 
        for ( int i = mid - 1; i >= l; --i )
        { 
            while ( j < r )
            {   
                if( gcd( copy[i], copy[j] ) == x )
                {
                    low = LBS(copy, mid, r, x);
                    high = HBS(copy, mid, r, x);
                    num += ( high - low );
                }
                j += ( high - low );
            }
        }
        ///////////////////////////////////////////////
    }
//
    return num + left + right;
}

//---------------------------------------
int gcd( int x, int y )
{
    if ( y == 0 )
        return x;
    else
        return gcd( y, x % y );
}

//-----------------------------------------
int LBS( int *array, int a, int b, int target )  // return the first position the target occurs
{
    if( a > b || array == NULL)
        return 0;

    int temp = 0;
    int left = a;
    int right = b;
    while( left < right )
    {
        temp = ( left + right ) >> 1;
        if( array[temp] < target )
            left = temp + 1;
        else
            right = temp;
    }

    return left;
}

int HBS( int *array, int a, int b, int target )  // return the last position the target occurs
{
    if( a > b || array == NULL)
        return 0;

    int temp = 0;
    int left = a;
    int right = b;
    while( left < right )
    {
        temp = ( left + right + 1 ) >> 1;
        if( array[temp] > target )
            right = temp - 1;
        else
            left = temp;
    }
    return right;
}

/*
12
2 4 5 2 18 3 9 10 66 24 24 18
2
1 3

51 4 
*/
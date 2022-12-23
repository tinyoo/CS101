#include <iostream>       ////  2019.12.22

using namespace std;

int gcd( int x, int y );
int Count(int x, int *copy, int a, int b);
int IOI( int *Sequence, int l, int r, int x, int n );

int main(void)
{
    int n, s, num_x, x;

    // Address the sequence
    cin >> n;
    int *Sequence = new int[n];
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
        Ans[i] = 0;

    for ( int i = 0; i < num_x; ++i )
    {
        Ans[i] = IOI( Sequence, 0, n, array[i], n );
    }

    // Output the answer
    for ( int i = 0; i < num_x; ++i )
        cout << Ans[i] << " ";

    return 0;
}

//-------------------------------------------
int IOI( int *Sequence, int l, int r, int x, int n )
{
    int num = 0;
    int left, right;
    int mid = ( l + r ) / 2;
    //cout << mid << endl;

    if ( r - l == 1)
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
        left = IOI( Sequence, l, mid, x, n );
        right = IOI( Sequence, mid, r, x, n );
    }
//
    int *copy = new int[n];     // Construct another array used to address the Sequence
    //cout << "start" << endl;  //  
    for ( int i = l; i < r; ++i )
    {
        copy[i] = Sequence[i];
        //cout << copy[i] << " ";
    }
    //cout << "end" << endl;
    // Address copy 
    for ( int i = mid - 2; i >= l; --i )
        copy[i] = gcd( copy[i+1], copy[i] );
    for ( int i = mid + 1; i < r; ++i )
        copy[i] = gcd( copy[i-1], copy[i] );
    
    //cout << "start" << endl;  //  
    //for ( int i = l; i < r; ++i )
    //    cout << copy[i] << " ";  
    //cout << "end" << endl;

    /////////////////////////////////////////////
    int i = mid - 1;
    while ( i >= l )
    {
        int j = mid;
        while ( j < r )
        {
            if( gcd( copy[i], copy[j] ) == x )
            {
                num += 1;//( Count( copy[i], copy, mid - 1, l ) * Count( copy[j], copy, mid, r ) );
                //cout << Count( copy[i], copy, mid - 1, l ) << endl;
            }
            j += 1;//( Count( copy[j], copy, mid, r ) );
        }
        i -= 1;//( Count( copy[i], copy, mid, l ) );
    }
    ///////////////////////////////////////////////
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

//------------------------------------------------
int Count(int x, int *copy, int a, int b)
{
    int num = 0;
    if ( a <= b )
    {
        for( int i = a; i < b; ++i )
        {
            if( copy[i] == x )
                num += 1;
            else
                break;
        }
    }
    else
    {
        for( int i = b; i >= a; --i )
        {
            if( copy[i] == x )
                num += 1;
            else
                break;
        } 
    }

    return num;
}
//---------------------------------------------------

/*
12
2 4 5 2 18 3 9 10 66 24 24 18
2
1 3

51 4 
*/
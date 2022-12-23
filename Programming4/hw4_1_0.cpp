#include <iostream>

using namespace std;

int gcd( int x, int y );

int main(void)
{
    int n, s, num_x, x;

    cin >> n;
    int *Sequence = new int[n];
    for ( int i = 0; i < n; ++i )
    {
        cin >> s;
        Sequence[i] = s;
    }

    cin >> num_x;
    int *Xs = new int[num_x];
    for ( int i = 0; i < num_x; ++i )
    {
        cin >> x;
        Xs[i] = x;
    }

    int *Ans = new int[num_x];
    for ( int i = 0; i < num_x; ++i )
        Ans[i] = 0;

    for ( int i = 0; i < n; ++i )
    {
        for ( int j = i; j < n; ++j )
        {
            for ( int k = 0; k < num_x; ++k )
            {
                if( gcd( Sequence[i], Sequence[j] ) == Xs[k] )
                    Ans[k] += 1;
                else
                    Sequence[i] = gcd( Sequence[i], Sequence[j] );
            }
        }
    }

    for ( int i = 0; i < num_x; ++i )
        cout << Ans[i] << " ";

    return 0;
}

int gcd( int x, int y )
{
    if ( y == 0 )
        return x;
    else
        return gcd( y, x % y );
}


/*
12
2 4 5 2 18 3 9 10 66 24 24 8
2
1 3

51 4 
*/
#include <iostream>
#include <string>

using namespace std;

int gene[5][5] = {
{ 5,-1,-2,-1,-3},
{-1, 5,-3,-2,-4},
{-2,-3, 5,-2,-2},
{-1,-2,-2, 5,-1},
{-3,-4,-2,-1, 0} };

int main(void)
{
    int length1, length2;
    string string1, string2;

    cin >> length1 >> string1;
    cin >> length2 >> string2;

    int num1[300], num2[300];

    int G[300][300];
    for ( int i = 1; i <= length1; ++i )
    {
        for ( int j = 1; j <= length2; ++j )
            G[i][j] = -100000000;
    }

    for ( int i = 1; i <= length1; ++i )
    {
        if ( string1[i-1] == 'A' )
            num1[i] = 0;
        if ( string1[i-1] == 'C' )
            num1[i] = 1;
        if ( string1[i-1] == 'G' )
            num1[i] = 2;
        if ( string1[i-1] == 'T' )
            num1[i] = 3;
    }

    for ( int i = 1; i <= length2; ++i )
    {
        if ( string2[i-1] == 'A' )
            num2[i] = 0;
        if ( string2[i-1] == 'C' )
            num2[i] = 1;
        if ( string2[i-1] == 'G' )
            num2[i] = 2;
        if ( string2[i-1] == 'T' )
            num2[i] = 3;
    }

    for ( int i = 1; i <= length1; ++i )
        G[i][0] = G[i-1][0] + gene[num1[i]][4];
    for ( int i = 1; i <= length2; ++i )
        G[0][i] = G[0][i-1] + gene[num2[i]][4]; 

    for ( int i = 1; i <= length1; ++i )
    {
        for ( int j = 1; j <= length2; ++j )
        {
            G[i][j] = max( G[i][j], G[i][j-1] + gene[num2[j]][4] );
            G[i][j] = max( G[i][j], G[i-1][j] + gene[num1[i]][4] );
            G[i][j] = max( G[i][j], G[i-1][j-1] + gene[num1[i]][num2[j]] );
        }
    }

    cout << G[length1][length2];

    return 0;

}
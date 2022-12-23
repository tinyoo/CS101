#include <cstdio>

void Pairs( int, int[] );

int main(void)
{
    int Number_student, Height_student;
    scanf( "%d", &Number_student );
    int H[Number_student];
    for ( int i = 0; i < Number_student; ++i )
    {
        scanf( "%d", &Height_student );
        H[i] = Height_student;
    }
    Pairs( Number_student, H );
    return 0;
}

void Pairs( int N, int height[] )
{
    int pairs = N - 1;
    for ( int i = 0; i < N - 2; ++i )
    {
        int j;
        for ( j = i + 2; j < N; ++j )
        {
            int k = i + 1;
            while ( k < j )
            {
                if ( ( height[k] <= height[i] ) && ( height[k] <= height[j] ) )
                    k += 1;
                else
                    break;
            }
            if ( k == j )
                pairs += 1;
            else if ( ( k != j ) && ( height[k + 1] > height[i] ) )
                break;
        }
    }
    printf( "%d", pairs );
}
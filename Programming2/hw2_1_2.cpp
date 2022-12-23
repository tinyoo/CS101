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
    int pairs = 0;
    int max;
    for ( int i = 0; i < N - 1; ++i )
    {
        max = 0;
        for ( int j = i + 1; j < N; ++j )
        {
            if ( height[j] > height[i] )
            {
                pairs += 1;
                break;
            }
            else if ( ( height[j] <= height [i] ) &&  ( height[j] >= max ) )
            {
                max = height[j];
                pairs += 1;   
            }   
        }
    }
    printf( "%d", pairs );
}
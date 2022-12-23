#include <iostream>

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
      cin >> length1;
      char string1[length1];
      cin >> string1;
      cin >> length2;
      char string2[length2];
      cin >> string2;
      
      for( int i = 1; i <= length1; ++i )
      {
            if( string1[i-1] == 'A' )
                  string1[i] = 0;
            if( string1[i-1] == 'C' )
                  string1[i] = 1;
            if( string1[i-1] == 'G' ) 
                  string1[i] = 2;
            if( string1[i-1] == 'T' )
                  string1[i] = 3;
      }
    
      for( int i = 1; i <= length2; ++i )
      {
            if( string2[i-1] == 'A' )
                  string2[i] = 0;
            if( string2[i-1] == 'C' )
                  string2[i] = 1;
            if( string2[i-1] == 'G' )
                  string2[i] = 2;
            if( string2[i-1] == 'T' ) 
                  string2[i] = 3;
            }

      int table[length1 + length2][length1 + length2];
      
      for( int i = 1; i <= length1; ++i )
      {
            for( int j = 1; j <= length2; ++j ) 
                  table[i][j] = -1000000000;
      }
	
      for( int i = 1;i <= length1; ++i ) 
            table[i][0] = table[i - 1][0] + gene[string1[i]][4]; 
      for( int j = 1; j <= length2; ++j )
            table[0][j]=table[0][j - 1] + gene[string2[j]][4];
	
      for( int i=1; i <= length1; ++i )
      {
            for( int j = 1;j <= length2; ++j )
            {
	            table[i][j] = max( table[i][j], table[i-1][j-1] + gene[string1[i]][string2[j]] );  
	            table[i][j] = max( table[i][j], table[i-1][j] + gene[string1[i]][4] ); 
	            table[i][j] = max( table[i][j], table[i][j-1] + gene[string2[j]][4] ); 
            }
      }

	cout << table[length1][length2];

      return 0;
}
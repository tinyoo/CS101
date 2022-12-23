#include <cstdlib>
#include <cstdio>
#include <iostream>

typedef int ElementType;
typedef struct Node *List;
struct Node {
    ElementType Data;
    List Next;
};

List Initialize( int n )
{
    List head = (List)malloc( sizeof( struct Node ) );
    head -> Data = 1;
    head -> Next = NULL;
    List PtrL = head;
    for ( int i = 2; i <= n; ++i )
    {
        List node = (List)malloc( sizeof( struct Node ) );
        node -> Data = i;
        node -> Next = NULL;
        PtrL -> Next = node;
        PtrL = PtrL -> Next;
    }
    PtrL -> Next = head;
    return head;
}

void Game( int n, int m, List PtrL )
{
    List p = PtrL;
    while ( p -> Next != PtrL )
        p = p -> Next;
    List temp = PtrL;
    while ( temp -> Data != 1 )
    {
        p = temp;
        temp = temp -> Next;
    }
    for ( int i = 1; i < m; ++i )
    {    
        if ( temp -> Next != temp )
        {
            for ( int j = 1; j < n - i + 1; ++j )
            {
                p = temp;
                temp = temp -> Next;
            }
            p -> Next = temp -> Next;
            free(temp);
            temp = p -> Next;
        }    
    }
    printf( "%d", (temp -> Data) );
    free(temp);
}

int main(void)
{
    int m, n;
    List PtrL;
    if ( m >= 1 && m <= n )
        printf( " Invalid Input! The relation should be: 1 <= m <= n ." );
    else
        scanf( "%d %d", &m, &n );
    PtrL = Initialize(m);
    Game( n, m, PtrL );
    return 0;
}
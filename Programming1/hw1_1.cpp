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

List FindX( ElementType X, List PtrL )
{
    List p = PtrL;
    while ( p -> Data != X )
        p = p -> Next;
    return p;
}

List DeleteX( ElementType X, List PtrL )
{
    List p = FindX( X, PtrL );
    free( p );
    return PtrL;
}

int main(void)
{
    int m, n, i;
    struct Node L;
    List PtrL, p;
    if ( m >= 1 && m <= n )
        printf( " Invalid Input! The relation should be: 1 <= m <= n ." );
    else
        scanf( "%d %d", &m, &n );
    PtrL = Initialize(m);
    for ( i = 1; i <= m - 1; ++ i )
    {   
        DeleteX( ( ( i - 1 ) * (n % m) + (n - i + 1) % ( m - i + 1 ) ) % m, PtrL ); 
    }
    printf( "%d", PtrL -> Data );
    return 0;
}
#include <cstdio>

class underflow {

};

class Node {
    private:
        int element;
        Node *Next;
    public:
        Node( int e, Node *n ) : element(e), Next(n) { };

        int retrieve() const { return element; };
        Node *next() const { return Next; };
};

class List {
    private:
        Node *list_head;

    public:
        List() : list_head( nullptr ) 
        { 

        };

        ~List();

        bool empty() const 
        { 
            return list_head == nullptr; 
        };

        Node *head() const { 
            return list_head; 
        };

        int front() const { 
            if ( empty() )
                throw underflow();
            return head() -> retrieve(); 
        };

        void push_front( int n )
        {
            if ( empty() )
                list_head = new Node( n, nullptr );
            else
                list_head = new Node( n, head() );
        };

        Node FindKth( int K, Node *PtrL)
        {
            Node p = PtrL;
            int i = 1;
            while ( p != NULL && i < K )
            {
                p = p -> Next;
                i++;
         }
            if ( i == K )
                return p;
            else
             return NULL;
        };

        Node Delete( int i, Node *PtrL )
        {
            List p, s;
            if ( i == 1 )
            {
                s = PtrL;
                if ( PtrL != NULL )
                PtrL = PtrL -> Next;
            else
                return NULL;
            free( s );
                return PtrL;
            }
            p = FindKth( i - 1, *PtrL );
            if ( p == NULL )
            {
                printf("The %dth node does not exist.", i - 1);
                return NULL;
            }
            else if ( p -> Next == NULL )
            {
                printf("The %dth node does not exist.", i);
                return NULL;
            }
            else
            {
                s = p -> Next;
                p -> Next = s -> Next;
                free( s );
                return PtrL;
            }
        };
        Node Find( int X, Node *PtrL )
        {
            Node p = *PtrL;
            while ( p != NULL && p -> element != X )
                p = p -> Next;
            return p;
        };
};

int main()
{
    int m, n, i, *temp, *temp2;
    List list;
    if ( m >= 1 && m <= n )
        printf( " Invalid Input! The relation should be: 1 <= m <= n ." );
    else
        scanf( "%d %d", &m, &n );
    for ( i = 1; i <= m; ++i )
        list.push_front(i);
    temp = list.list_head;
    for ( i = 1; i <= m -1 ; ++i )
        list.Delete( list.Find( n - i + 1, temp ) , temp2);
    printf( "%d", list );
    return 0;
}
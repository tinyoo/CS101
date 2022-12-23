#include <iostream>

using namespace std;

//****************************************************************
class Node {
    public:
        int data;      // the substance
        int number;    // # of substance
        Node * prev_node;
        Node * next_node;

        Node() { };
        Node( int d, int n, Node * prev, Node * next ) : data(d), number(n), prev_node(prev), next_node(next) { };
        ~Node() { };
};

//******************************************************************
class  DList {
    public:
        int count;
        Node *list_head;
        Node *list_tail;

        DList() : count(0), list_head(nullptr), list_tail(nullptr) { };
        ~DList() { };
        void PushBack( int x, int n );
        void DeleteFront( int n );
};

//----------------------------------------
void DList :: PushBack( int x, int n )
{
    if( list_head == nullptr )
    {
        list_head = new Node();
        list_head -> data = x;
        list_head -> number = n;
        list_tail = list_head;
    }
    else
    {
        list_tail -> next_node = new Node();
        list_tail -> next_node -> data = x;
        list_tail -> next_node -> number = n;
        list_tail -> next_node -> prev_node = list_tail;
        list_tail = list_tail -> next_node;
    }
    count += n;
}

//---------------------------------------------
void DList :: DeleteFront( int n )
{   
    count -= n;
    while ( n >= list_head -> number )
    {
        int temp = list_head -> number;
        Node *ptr = list_head;
        list_head = list_head -> next_node;
        delete ptr;
        n -= temp;
    }
    if ( n < list_head -> number )
        ( list_head -> number ) -= n;
}

//**************************************************************************
void Furnace( Node * node, DList list, int **oper, int n_substances );

int main(void)
{
    int n_substances, n_rules, n_operations;
    int x, y, z;
    int s, q;
    
    DList list;
    Node * node = list.list_head;

    cin >> n_substances >> n_rules >> n_operations;
    int oper[n_substances][n_substances];
    // Initialize the array with -2.
    for ( int i = 0; i < n_substances; ++i )
    {
        for ( int j = 0; j < n_substances; ++j )
            oper[i][j] = -2;
    }
    
    // x + y -> z
    for ( int i = 0; i < n_rules; ++i )
    {
        cin >> x >> y >> z;
        oper[x][y] = z;
        oper[y][x] = z; 
    }

    for ( int i = 0; i < n_operations; ++i )
    {
        cin >> s >> q;

        if ( s != -1 )
            list.PushBack( s, q );

        else if ( s == -1 )
        {
            Furnace( node, list, (int**)oper, n_substances );
            node = list.list_tail;
            list.DeleteFront( q );
        }
    } 

    cout << list.count; 
    return 0;
}

void Furnace( Node * node, DList list, int **oper, int n_substances )
{ 
    if ( ( node -> next_node != NULL ) && ( *( (int*)oper + n_substances * ( node -> number ) + ( node -> next_node -> number ) ) == -2 ) ) // They cannot act.
    {
        node = node -> next_node;
        Furnace( node, list, oper, n_substances );
    }

    if ( ( node -> next_node != NULL ) && ( *( (int*)oper + n_substances * ( node -> number ) + ( node -> next_node -> number ) ) != -2 ) ) // They can act.
    {
        
        //***** The current node is totally transformed into z, the next node leaves next_node.number - node.number elements.
        if ( ( node -> number ) < ( node -> next_node -> number ) )
        {
            node -> data = *( (int*)oper + n_substances * ( node -> number ) + ( node -> next_node -> number ) );
            node -> next_node -> number -= node -> number;
            list.count -= ( node -> number );
            // If the newly formed substance can act with the previous one
            while ( ( node != NULL ) && ( *( (int*)oper + n_substances * ( node -> number ) + ( node -> prev_node -> number ) ) != -2 ) )
            {
                node = node -> prev_node;
                Furnace( node, list, oper, n_substances );
            }
            // If the newly formed substance cannot act with the previous one
            if ( *( (int*)oper + n_substances * ( node -> number ) + ( node -> prev_node -> number ) ) == -2 )
            {
                node = node -> next_node;
                Furnace( node, list, oper, n_substances );
            }
        }
        //***** The current node is totally transformed into z, the next node is deleted.
        else if ( ( node -> number ) == ( node -> next_node -> number ) )
        {
            node -> data = *( (int*)oper + n_substances * ( node -> number ) + ( node -> next_node -> number ) );
            list.count -= node -> number;
            Node *ptr = node -> next_node;
            node -> next_node = node -> next_node -> next_node;
            delete ptr;
            // If the newly formed substance can act with the previous one
            while ( ( node != NULL ) && ( *( (int*)oper + n_substances * ( node -> number ) + ( node -> prev_node -> number ) ) != -2 ) )
            {
                node = node -> prev_node;
                Furnace( node, list, oper, n_substances );
            }
            // If the newly formed substance cannot act with the previous one
            if ( *( (int*)oper + n_substances * ( node -> number ) + ( node -> prev_node -> number ) ) == -2 )
            {
                node = node -> next_node;
                Furnace( node, list, oper, n_substances );
            }
        }
        //***** The next node is totally transformed into z, the current node leaves node.number - next_node.number elements.
        else if ( ( node -> number ) > ( node -> next_node -> number ) )
        {
            node -> number -= node -> next_node -> number;
            list.count -= node -> next_node -> number;
            node -> next_node -> data = *( (int*)oper + n_substances * ( node -> number ) + ( node -> next_node -> number ) );
            node = node -> next_node;
            Furnace( node, list, oper, n_substances );
        }
    }
}
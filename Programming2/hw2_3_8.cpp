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
        list_tail->next_node = NULL;
        list_head->prev_node = NULL;
    }
    else
    {
        if (x != list_tail->data)
        {
            list_tail -> next_node = new Node();
            list_tail -> next_node -> data = x;
            list_tail -> next_node -> number = n;
            list_tail -> next_node -> prev_node = list_tail;
            list_tail = list_tail -> next_node;
            list_tail->next_node = NULL;            
        }
        else 
        {
            list_tail->number += n;
        }

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
    // if ( n < list_head -> number )
    ( list_head -> number ) -= n;
}

//**************************************************************************
void Furnace( Node * node, DList* list, int **oper, int n_substances );

int main(void)
{
    int n_substances, n_rules, n_operations;
    int x, y, z;
    int s, q;
    
    DList list;
    Node * node = list.list_head;

    cin >> n_substances >> n_rules >> n_operations;
    int** oper = new int*[n_substances];
    for (int i = 0; i < n_substances; i++)
        oper[i] = new int[n_substances];
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
        {
            list.PushBack( s, q );
            node = list.list_head;
            Furnace( node, &list, (int**)oper, n_substances );
        }
        else if ( s == -1 )
        {           
            list.DeleteFront( q );
        }
    } 
    node = list.list_head;
    Furnace( node, &list, (int**)oper, n_substances );

    cout << list.count; 
    return 0;
}


void Furnace( Node * node, DList* list, int **oper, int n_substances )
{ 
    
    Node* tmp;
    if (node == NULL)
    {
        return;
    }
    if ( ( node -> next_node != NULL ) 
      && ( oper[node -> data][node -> next_node -> data] ) == -2 )  // They cannot act.
    {
        node = node -> next_node;
        Furnace( node, list, oper, n_substances );
    }

    else if ( ( node -> next_node != NULL ) 
           && ( oper[node -> data][node -> next_node -> data] != -2 ) ) // They can act.
    {    
        //***** The current node is totally transformed into z, the next node leaves next_node.number - node.number elements. *****//
        if ( ( node -> number ) < ( node -> next_node -> number ) )
        {
            node -> data = ( oper[node -> data][node -> next_node -> data] );
            node -> next_node -> number -= node -> number;
            list->count -= ( node -> number );
            // If the newly formed substance can act with the previous one
            if ( node->prev_node != NULL && ( oper[node -> data][node -> prev_node -> data] != -2 ) )
            {
                node = node -> prev_node;
                Furnace( node, list, oper, n_substances );
            }
            // If the newly formed substance cannot act with the previous one
            else
            {
                node = node -> next_node;
                Furnace( node, list, oper, n_substances );
            }
        }
        //***** The current node is totally transformed into z, the next node is deleted. *****//
        else if ( ( node -> number ) == ( node -> next_node -> number ) )
        {
            node -> data = *( (int*)oper + n_substances * ( node -> number ) + ( node -> next_node -> number ) );
            list->count -= node -> number;
            Node *ptr = node -> next_node;
            node -> next_node = node -> next_node -> next_node;
            delete ptr;
            // If the newly formed substance can act with the previous one
            if ( (node->prev_node != NULL) && ( oper[node -> data][node -> prev_node -> data] != -2 ) )
            {
                node = node -> prev_node;
                Furnace( node, list, oper, n_substances );
            }
            // If the newly formed substance cannot act with the previous one
            else
                Furnace( node, list, oper, n_substances );
        }
        //***** The next node is totally transformed into z, the current node leaves node.number - next_node.number elements. *****//
        else if ( ( node -> number ) > ( node -> next_node -> number ) )
        {
            node -> number -= node -> next_node -> number;
            list->count -= node -> next_node -> number;
            node -> next_node -> data = ( oper[node -> data][node -> next_node -> data] );
            node = node -> next_node;
            Furnace( node, list, oper, n_substances );
        }
    }
    else
        return;
}
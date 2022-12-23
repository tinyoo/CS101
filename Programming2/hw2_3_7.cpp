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
        //int count;
        Node *list_head;
        Node *list_tail;

        DList() : list_head(nullptr), list_tail(nullptr) { };
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
    //count += n;
}

//---------------------------------------------
void DList :: DeleteFront( int n )
{   
    //count -= n;
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
void Furnace( Node * node, int *count, int **oper, int n_substances );

int main(void)
{
    int n_substances, n_rules, n_operations;
    int x, y, z;
    int s, q;
    int * count = 0;
    
    DList list;
    Node * node = list.list_tail;

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

        // When list is empty, just push the node.
        if ( ( s != -1 ) && ( node == NULL ) )
            list.PushBack( s, q );

        // When we are pushing the node: s != -1:    
        // When the list is not empty, we need to determine whether push or pop.
        else if ( ( s != -1 ) && ( node != NULL ) )
        {
            // When the pushing substance is the same with the top, we can just add the number of the top substance.
            if ( node -> data == s )
            {
                node -> number += q;
                count += q;
            }
            // If it is a different kind, we need to determine whether the pushed substance can act with the existing top substances.
            else  // node -> data != s
            {
                //* The pushed substance can act with the top.
                if ( oper[node -> data][s] != -2 )   //act
                {
                    if ( ( node -> number ) < q )
                    {
                        node -> data = oper[node -> data][s];
                        list.PushBack( s, q - ( node -> number ) );
                        list.list_tail = node -> next_node;
                        node = node -> prev_node;
                        Furnace( node, count, (int**)oper, n_substances );
                    }

                    else if ( ( node -> number ) == q )
                    {
                        node -> data = oper[node -> data][s];
                        node = node -> prev_node;
                        Furnace( node, count, (int**)oper, n_substances );
                    }

                    else  //( node -> number ) > q
                    {
                        node -> number -= q;
                        count -= q;
                        list.PushBack( oper[node -> data][s], q );
                    }
                }

                // The pushed substance cannot act with the top.
                else
                {
                    list.PushBack( s, q );
                    node = node -> next_node;
                    list.list_tail = node;
                }
            }
        }
        
        // pop: s == -1
        else if ( ( s == -1 ) && ( node != NULL ) )
        {
            list.DeleteFront(q);
        }

        node = list.list_tail;
    } 

    cout << (*count); 
    return 0;
}

void Furnace( Node * node, int * count, int **oper, int n_substances )
{ 
    if ( ( node -> next_node != NULL ) && ( *( (int*)oper + n_substances * ( node -> number ) + ( node -> next_node -> number ) ) == -2 ) ) // They cannot act.
    {
        node = node -> next_node;
        Furnace( node, count, oper, n_substances );
    }

    else if ( ( node -> next_node != NULL ) && ( *( (int*)oper + n_substances * ( node -> number ) + ( node -> next_node -> number ) ) != -2 ) ) // They can act.
    {
        
        //***** The current node is totally transformed into z, the next node leaves next_node.number - node.number elements.
        if ( ( node -> number ) < ( node -> next_node -> number ) )
        {
            node -> data = *( (int*)oper + n_substances * ( node -> number ) + ( node -> next_node -> number ) );
            node -> next_node -> number -= node -> number;
            count -= ( node -> number );
            // If the newly formed substance can act with the previous one
            while ( ( node != NULL ) && ( *( (int*)oper + n_substances * ( node -> number ) + ( node -> prev_node -> number ) ) != -2 ) )
            {
                node = node -> prev_node;
                Furnace( node, count, oper, n_substances );
            }
            // If the newly formed substance cannot act with the previous one
            if ( *( (int*)oper + n_substances * ( node -> number ) + ( node -> prev_node -> number ) ) == -2 )
            {
                node = node -> next_node;
                Furnace( node, count, oper, n_substances );
            }
        }
        //***** The current node is totally transformed into z, the next node is deleted.
        else if ( ( node -> number ) == ( node -> next_node -> number ) )
        {
            node -> data = *( (int*)oper + n_substances * ( node -> number ) + ( node -> next_node -> number ) );
            count -= node -> number;
            Node *ptr = node -> next_node;
            node -> next_node = node -> next_node -> next_node;
            delete ptr;
            // If the newly formed substance can act with the previous one
            while ( ( node != NULL ) && ( *( (int*)oper + n_substances * ( node -> number ) + ( node -> prev_node -> number ) ) != -2 ) )
            {
                node = node -> prev_node;
                Furnace( node, count, oper, n_substances );
            }
            // If the newly formed substance cannot act with the previous one
            if ( *( (int*)oper + n_substances * ( node -> number ) + ( node -> prev_node -> number ) ) == -2 )
            {
                node = node -> next_node;
                Furnace( node, count, oper, n_substances );
            }
        }
        //***** The next node is totally transformed into z, the current node leaves node.number - next_node.number elements.
        else if ( ( node -> number ) > ( node -> next_node -> number ) )
        {
            node -> number -= node -> next_node -> number;
            count -= node -> next_node -> number;
            node -> next_node -> data = *( (int*)oper + n_substances * ( node -> number ) + ( node -> next_node -> number ) );
        }
    }
}
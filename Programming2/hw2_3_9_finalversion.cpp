#include <iostream>

using namespace std;

//****************************************************************
class Node {           // Node: data -> the kind of substance; number -> the number of this substance
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
        list_tail -> next_node = NULL;
        list_head -> prev_node = NULL;
    }
    else
    {
        if ( x != list_tail -> data )
        {
            list_tail -> next_node = new Node();
            list_tail -> next_node -> data = x;
            list_tail -> next_node -> number = n;
            list_tail -> next_node -> prev_node = list_tail;
            list_tail = list_tail -> next_node;
            list_tail -> next_node = NULL;            
        }
        else 
        {
            list_tail -> number += n;
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
void Furnace( Node * node, DList* list, int **oper );

int main(void)
{
    int n_substances, n_rules, n_operations;
    int x, y, z;
    int s, q;
    
    DList list;
    Node * node = list.list_head;

    cin >> n_substances >> n_rules >> n_operations;
    int** oper = new int*[n_substances];
    for ( int i = 0; i < n_substances; ++i )
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

        // When list is empty, just push the node.
        if ( ( s != -1 ) && ( node == NULL ) )
            list.PushBack( s, q );

        // push: s != -1:    
        // When the list is not empty, we need to determine whether push or pop.
        else if ( ( s != -1 ) && ( node != NULL ) )
        {
            // When the pushing substance is the same with the top, we can just add the number of the top substance.
            if ( node -> data == s )
            {
                node -> number += q;
                list.count += q;
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
                        ////////////
                        Furnace( node, &list, oper );
                        //////////////
                    }

                    else if ( ( node -> number ) == q )
                    {
                        node -> data = oper[node -> data][s];
                        node = node -> prev_node;
                        ////////////
                        Furnace( node, &list, oper );
                        //////////////
                    }

                    else  //( node -> number ) > q
                    {
                        node -> number -= q;
                        list.count -= q;
                        list.PushBack( oper[node -> data][s], q );
                        //node = node -> prev_node;
                        Furnace( node, &list, oper );
                    }
                }

                // The pushed substance cannot act with the top.
                else
                {
                    list.PushBack( s, q );
                    node = node -> next_node;
                    //list.list_tail = node;
                }
            }
        }
        // pop: s == -1
        else if ( ( s == -1 ) && ( node != NULL ) )
            list.DeleteFront(q);

        node = list.list_tail;
    }
    
    node = list.list_head;
    Furnace( node, &list, oper );
    
    cout << list.count; 
    return 0;
}


void Furnace( Node * node, DList* list, int **oper )
{
    //Node* tmp;
    if ( node == NULL )
    {
        //node = node -> prev_node;
        return;
    }
    else if ( ( node -> next_node != NULL ) 
      && ( oper[node -> data][node -> next_node -> data] ) == -2 )  // They cannot act.
    {
        node = node -> next_node;
        Furnace( node, list, oper );
    }

    else if ( ( node -> next_node != NULL ) 
           && ( oper[node -> data][node -> next_node -> data] != -2 ) ) // They can act.
    {    
        //***** The current node is totally transformed into z, the next node leaves next_node.number - node.number elements. *****//
        if ( ( node -> number ) < ( node -> next_node -> number ) )
        {
            node -> data = ( oper[node -> data][node -> next_node -> data] );
            node -> next_node -> number -= node -> number;
            list -> count -= ( node -> number );
            //node = node -> next_node; //*
            // If the newly formed substance can act with the previous one
            if ( ( node -> prev_node != NULL ) && ( oper[node -> data][node -> prev_node -> data] != -2 ) )
            {
                node = node -> prev_node;
                Furnace( node, list, oper );
            }
            // If the newly formed substance cannot act with the previous one
            else
                Furnace( node, list, oper );
        }
        //***** The current node is totally transformed into z, the next node is deleted. *****//
        else if ( ( node -> number ) == ( node -> next_node -> number ) )
        {
            node -> data = oper[node -> data][node -> next_node -> data];
            list -> count -= node -> number;
            Node *ptr = node -> next_node;
            node -> next_node = node -> next_node -> next_node;
            delete ptr;
            // If the newly formed substance can act with the previous one
            if ( (node -> prev_node != NULL) && ( oper[node -> data][node -> prev_node -> data] != -2 ) )
            {
                node = node -> prev_node;
                Furnace( node, list, oper );
            }
            // If the newly formed substance cannot act with the previous one
            else
            {
                //node = node -> next_node;
                Furnace( node, list, oper );
            }
        }
        //***** The next node is totally transformed into z, the current node leaves node.number - next_node.number elements. *****//
        else if ( ( node -> number ) > ( node -> next_node -> number ) )
        {
            node -> number -= node -> next_node -> number;
            list -> count -= node -> next_node -> number;
            node -> next_node -> data = ( oper[node -> data][node -> next_node -> data] );
            //*node = node -> next_node;
            Furnace( node, list, oper );
        }
    }
}

//**************************Tinyoo's idea***********************************//
// push the first node into the empty list;
// if the next substance is the same with the previous one, just add the number of the previous node.
// if the next substance is different from the previous one
//      if next substance cannot act with the current substance: push it into the list
//      if next substance can act with the current substance
//              if number of the current is fewer than the number of the next( A + B -> C ): A -> C, push (# of B - # of A) B
//                      determine whether C can act with the previous one (recursive)
//              if number of the current equals the number of the next( A + B -> C ): A -> C
//                      determine whether C can act with the previous one (recursive)
//              if number of the current is more than the number of the next( A + B -> C ): B -> C, # of A - # of B
//******* Notice: A + B -> C, A + C -> D exist!
// copyright by Tinyoo
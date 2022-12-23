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
int main(void)
{
    int n_substances, n_rules, n_operations;
    int x, y, z;
    int s, q;
    
    DList list;
    Node *node = list.list_tail;

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
                        while ( ( node != nullptr ) && ( oper[node -> data][node -> next_node -> data] != -2 ) )
                        {
                            if ( ( node -> number ) < ( node -> next_node -> number ) )
                            {
                                node -> data = oper[node -> data][node -> next_node -> data];
                                node -> next_node -> number -= node -> number;
                                list.count -= ( node -> number );
                                node = node -> prev_node;
                            }

                            else if ( ( node -> number ) == ( node -> next_node -> number ) )
                            {
                                node -> data = oper[node -> data][node -> next_node -> data];
                                list.count -= node -> number;
                                Node *ptr = node -> next_node;
                                node -> next_node = node -> next_node -> next_node;
                                delete ptr;
                                node = node -> prev_node;
                            }

                            else
                            {
                                node -> number -= node -> next_node -> number;
                                list.count -= node -> next_node -> number;
                                node -> next_node -> data = oper[node -> data][node -> next_node -> data];//
                                //break;
                            }
                        }
                        //////////////
                    }

                    else if ( ( node -> number ) == q )
                    {
                        node -> data = oper[node -> data][s];
                        node = node -> prev_node;
                        ////////////
                        while ( ( node != nullptr ) && ( oper[node -> data][node -> next_node -> data] != -2 ) )
                        {
                            if ( ( node -> number ) < ( node -> next_node -> number ) )
                            {
                                node -> data = oper[node -> data][node -> next_node -> data];
                                list.count -= node -> number;
                                node -> next_node -> number -= node -> number;
                                node = node -> prev_node;
                            }

                            else if ( ( node -> number ) == ( node -> next_node -> number ) )
                            {
                                node -> data = oper[node -> data][node -> next_node -> data];
                                list.count -= node -> number;
                                Node *ptr = node -> next_node;
                                node -> next_node = node -> next_node -> next_node;
                                delete ptr;
                                node = node -> prev_node;
                            }

                            else
                            {
                                node -> number -= node -> next_node -> number;
                                list.count -= node -> next_node -> number;
                                node -> next_node -> data = oper[node -> data][node -> next_node -> data];//
                                //break;
                            }
                        }
                        //////////////
                    }

                    else  //( node -> number ) > q
                    {
                        node -> number -= q;
                        list.count -= q;
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

    cout << list.count; 
    return 0;
}
#include <iostream>

using namespace std;

//****************************************************************
class Node {
    public:
        int data;
        int number;
        Node * prev_node;
        Node * next_node;

        Node() { };
        Node( int d, int n, Node * prev, Node * next ) : data(d), number(n), prev_node(prev), next_node(next) { };
        ~Node(){ };
};

//******************************************************************
class  DList {
    public:
        int count;
        Node *list_head;
        Node *list_tail;

        DList() : count(0), list_head(nullptr), list_tail(nullptr) { };
        ~DList() { };

        bool empty();
        void PushBack( int x, int n );
        void DeleteFront( int n );
};

//----------------------------------------
bool DList :: empty()
{
    return( list_head == nullptr );
}

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
    Node *ptr = list_head;
    if ( n < list_head -> number )
        ( list_head -> number ) -= n;
    else if ( n = list_head -> number )
    {
        list_head = list_head -> next_node;
        delete ptr;
    }
    else
    {
        while ( n > list_head -> number )
        {
            int temp = list_head -> number;
            list_head = list_head -> next_node;
            delete ptr;
            n -= temp;
        }
        if ( n < list_head -> number )
            ( list_head -> number ) -= n;
        else if ( n = list_head -> number )
        {
            list_head = list_head -> next_node;
            delete ptr;
        }
    }
    count -= n;
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
    for ( int i = 0; i < n_substances; ++i )
    {
        for ( int j = 0; j < n_substances; ++j )
            oper[i][j] = -2;
    }
    
    for ( int i = 0; i < n_rules; ++i )
    {
        cin >> x >> y >> z;
        oper[x][y] = z;
        oper[y][x] = z;
    }

    for ( int i = 0; i < n_operations; ++i )
    {
        cin >> s >> q;

        if ( ( s != -1 ) && ( node == NULL ) )
        {
            list.PushBack( s, q );
        }

        else if ( ( s != -1 ) && ( node != NULL ) )
        {
            if ( node -> data == s )
            {
                node -> number += q;
                list.count += q;
            }
            else  // node -> data != s
            {
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
                                list.count -= (ptr -> number); //
                                delete ptr;
                                node = node -> prev_node;
                            }

                            else
                            {
                                node -> number -= node -> next_node -> number;
                                list.count -= node -> next_node -> number;
                                node -> data = oper[node -> data][node -> next_node -> data];
                                Node *ptr = node -> next_node;
                                node -> next_node = node -> next_node -> next_node;
                                list.count -= ptr -> number; //
                                delete ptr;
                                break;
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
                                list.count -= ptr -> number; //
                                delete ptr;
                                node = node -> prev_node;
                            }

                            else
                            {
                                node -> number -= node -> next_node -> number;
                                list.count -= node -> next_node -> number;
                                node -> data = oper[node -> data][node -> next_node -> data];
                                Node *ptr = node -> next_node;
                                node -> next_node = node -> next_node -> next_node;
                                list.count -= ptr -> number; //
                                delete ptr;
                                break;
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

                else  //cannot act
                {
                    list.PushBack( s, q );
                    node = node -> next_node;
                    list.list_tail = node;
                }
            }
            
        }

        else if ( ( s == -1 ) && ( node != NULL ) )
        {
            list.DeleteFront(q);
        }

        node = list.list_tail;
    } 

    cout << list.count; 
    return 0;
}
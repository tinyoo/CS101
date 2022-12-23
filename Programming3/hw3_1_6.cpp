#include<iostream>

using namespace std;

//****************************************************************
class Node {
    public:
        int memo;      // the substance
        Node * next_node;

        Node() { };
        Node( int m, Node * next ) : memo(m), next_node(next) { };
        ~Node() { };
};

//******************************************************************
class List {
    public:
        int size;
        Node *list_head;
        Node *list_tail;

        List() : size(0), list_head(nullptr), list_tail(nullptr) { };
        ~List() { };
        void PushBack( int x );
};

//----------------------------------------
void List :: PushBack( int x )
{
    if( list_head == nullptr )
    {
        list_head = new Node();
        list_head -> memo = x;
        list_tail = list_head;
        list_tail -> next_node = NULL;
    }
    else
    {
        list_tail -> next_node = new Node();
        list_tail -> next_node -> memo = x;
        list_tail = list_tail -> next_node;
        list_tail -> next_node = NULL;            
    }
    size++;
}

//**************************************************************************

int main(void)
{
    long int N, Memo, c;
    cin >> N;
    List M;
    int *C = new int[1];
    long int *comsumption = new long int[1];
    int *Mem = new int[10001];

    for ( int i = 1; i <= N; ++i )
    {
        cin >> Memo;
        Mem[i] = Memo;
    }

    for ( int i = 1; i <= N; ++i )
    {
        C = new int[1];
    }

    for ( int i = 1; i <= N; ++i )
    {
        cin >> c;
        C[i] = c;
    }

    for ( int i = 1; i <= N; ++i )
    {
        comsumption = new long int[1];
    }

    for ( int i = 1; i <= N; ++i )
    {
        comsumption[i] = 0;
    }

//--------------------------------------------

    for ( int x = 1; x <= N; ++x )
    {
        M.PushBack( Mem[x] );
        cout << M.list_tail -> memo;
        for ( int i = 1; i <= M.size; ++i )
        {
            int j = 1;
            Node *ptr = M.list_head;
            while ( j <= i )
            {
                if ( ( ptr -> memo ) - C[i] >= 0 )
                {
                    comsumption[i] += C[i];
                    ptr -> memo -= C[i];
                    ptr = ptr -> next_node;
                    ++j;
                }
                else
                {
                    comsumption[i] += ( ptr -> memo );
                    //---------------
                    if ( ptr -> next_node != nullptr )
                    {
                        ptr -> memo = ptr -> next_node -> memo;
                        Node *temp = ptr -> next_node;
                        ptr -> next_node = ptr -> next_node -> next_node;
                        delete temp;
                        M.size--; 
                    }
                    //----------------
                }
            }
        }
    }


    for ( int i = 1; i <= N; ++i )
    {
        cout << comsumption[i] << " ";
    }

    return 0;

}
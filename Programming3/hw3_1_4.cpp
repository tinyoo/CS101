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
        void Delete( int i );
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
    ++size;
}

//---------------------------------------------
void List :: Delete( int i )
{   
    --size;
    Node *ptr = list_head;
    int j = 1;
    while ( ( ptr != nullptr ) && ( j < i ) )
    {
        ptr = ptr -> next_node;
        ++j;
    }
    if ( j = i )
    {
        ptr -> memo = ptr -> next_node -> memo;
        Node *temp = ptr -> next_node;
        ptr -> next_node = ptr -> next_node -> next_node;
        delete temp;
    }
}

//**************************************************************************

int main(void)
{
    long int N, Memo, c;
    cin >> N;
    List M;
    long int C[N + 1], 
             comsumption[N + 1];

    for ( int i = 1; i <= N; ++i )
    {
        cin >> Memo;
        M.PushBack( Memo );
    }
    for ( int i = 1; i <= N; ++i )
    {
        cin >> c;
        C[i] = c;
    }

    for ( int i = 1; i <= N; ++i )
    {
        comsumption[i] = 0;
    }

//--------------------------------------------

    int k = 1;
    int i = 1;
    while ( i <= N )
    {
        int j = 1;
        Node *ptr = M.list_head;
        while ( j <= k )
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
                ptr = ptr -> next_node;
                M.Delete(j);
                --k;
            }
        }
        ++k;
        ++i;
    }

    for ( int i = 1; i <= N - 1; ++i )
    {
        cout << comsumption[i] << " ";
    }
    cout << comsumption[N];

    return 0;

}
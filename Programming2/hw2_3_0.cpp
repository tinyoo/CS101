#include <iostream>

using namespace std;

class Node { 
    int data;
    Node *Next;
    Node *Prev;

    Node( ) { };
    ~Node( ) { };
};

class DoubleList {
    public:
        Node *head;
        Node *tail;
        int len;

        DoubleList( ) { };
        ~DoubleList( ) { };

        void PushBack( int e );
        void DeleteNode( int n );

};

DoubleList :: DoubleList()
{
    head = NULL;
    tail = NULL;
    len = 0;
}

Doublelist :: DoubleList(int t, Node *Next, Node *Prev) {
		this -> data = t;
		this -> Prev  = Prev;
		this -> Next  = Next;
}

void DoubleList :: PushBack( int e )
{
    if ( head == NULL )
    {
        head = new Node();
        head -> data = data;
        ++ len;
        tail = head;
    }
    else
    {
        tail -> Next = new Node();
        tail -> Next -> data = data;
        ++ len;
        tail -> Next -> Prev = tail;
        tail = tail -> next;
    }
}

void DoubleList :: DeleteNode( int n )
{
    Node *p, *q;
    p = head;
    q = head -> next;
    if( n > len )
        return;
    else
    {
        for( int i = 2; i < n; ++i )
        {
            p = p -> next;
            q = q -> next;
        }
        p -> next = q -> next;
        q -> next -> prev = p;
        delete q;
    }
}




int main(void)
{
    int n_substances, n_rules, n_operations;
    int x, y, z;
    int s, q;
    DoubleList list;
    cin >> n_substances >> n_rules >> n_operations;
    for ( int i = 0; i < n_rules; ++i )
    {
        cin >> x >> y >> z;
    }
    for ( int i = 0; i < n_operations; ++i )
    {
        cin >> s >> q;
        if ( s != -1 )
        {
            for ( int i = 0; i < q; ++i )
                list.PushBack(s);
        }
        else
            DeleteNode(0);
    }
}
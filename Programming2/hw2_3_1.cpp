#include <cstdlib>
#include <cstdio>

//***************************************************************************
class Node {
    public:
        int element;
        Node *next_node;
    
    public:
        Node( int = 0, Node * = nullptr );

        int retrieve() const;
        Node * next() const;
};

//****************************************************************************

Node :: Node ( int e, Node * n ) : element(e), next_node(n) { }

//------------------------------------------
int Node :: retrieve() const
{
    return element;
}

//-------------------------------------------
Node * Node :: next() const
{
    return next_node;
}

//***********************************************************************

class List {
    public:
        Node *list_head;

        List( ) : list_head( nullptr ) { };
        ~List( ) { };

    public:
        int len;
        // Accessors 
        bool empty(); 
        int size(); 
        int front(); 
        Node *head(); 
        int count( int );

        // Mutators 
        void push_front( int ); 
        int pop_front(); 
        void Insert( List* list, int n, void *data);
        void Delete( List* list, int n );
        void PushBack( int x );

};

//**************************************************************************

bool List :: empty() 
{ 
    return ( list_head == nullptr ); 
}

//----------------------------------------------------
Node *List :: head()
{ 
    return list_head; 
}

//-----------------------------------------------------
class underflow 
{ 
    // emtpy 
};

int List :: front() 
{ 
    if ( empty() )  
        throw underflow(); 
    return head() -> retrieve();
}

//------------------------------------------------------
void List :: push_front( int n ) 
{ 
    list_head = new Node( n, list_head ); 
}

//--------------------------------------------------------
int List :: pop_front() 
{ 
    if ( empty() ) 
        throw underflow(); 
    int e = front(); 
    Node *ptr = list_head; 
    list_head = list_head -> next(); 
    delete ptr; 
    return e;
}

//------------------------------------------------------------
int List :: count( int n ) 
{ 
    int node_count = 0;
    //for ( Node *ptr = list(); ptr != nullptr; ptr = ptr -> next() ) 
    { 
        if ( ptr->retrieve() == n ) 
            ++node_count; 
    }
    return node_count;
}

//Insert nth-------------------------------------------------------------
/*void List :: Insert( List* list, int n, void *data)
{
    if ( list == NULL || data == NULL )
    {
        return;
    }
    if ( n < 0 || n > list -> len )
    {
        n = list -> len;
    }

    // create new node
    Node* NewNode = (Node*)malloc( sizeof( Node ) );
    NewNode -> element = element;
    NewNode -> next() = NULL;

    // find the node
    Node* p = list -> head();
    for (int i = 0; i < n; i++)
    {
        p = p -> next();
    }
    // insert
    NewNode -> next() = p -> next();
    p -> next = NewNode;

    // len + 1
    list -> len++;
}
*/
//-----------------------------------------------------------------
void PushBack( int x )  
{  
    if ( head() == NULL )  
    {  
        head() = new Node(x);  
        head() -> next() = NULL;  
    }  
    else  
    {  
        Node *cur = head();  
        while ( cur -> next() != NULL )  
        {  
            cur = cur -> next();  
        }  
        cur -> next() = new Node(x);  
    }    
}  

//********************************************************************************

int main(void)
{
    int n_substances, n_rules, n_operations;
    int x, y, z;
    int s, q;
    List list;
    cin >> n_substances >> n_rules >> n_operations;
    int oper[2 * n_rules][3];
    for ( int i = 0; i < n_rules; ++i )
    {
        cin >> x >> y >> z;
        oper[i][0] = x;
        oper[i][1] = y;
        oper[i][2] = z;
        oper[i + n_rules][0] = y;
        oper[i + n_rules][1] = x;
        oper[i + n_rules][2] = z;
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
            //list.Delete( 0 );
    }
}
#include <iostream>

using namespace std;

//****************************************************************
class Node {
    public:
        int data;
        Node * next_node;
        Node * prev_node;

        Node() { };
        Node( int d, Node * pre_node, Node * next_node )
        {
            this -> data = d;
            this -> prev_node = prev_node;
            this -> next_node = next_node;
        }
        ~Node(){ };
};

//******************************************************************
class  DList {
    public:
        Node *list_head;
        int count;

        DList();
        ~DList();

        Node* GetNode( int n );
        void Push( int n, int x );
        void PushFront( int x ); 
        void PushBack( int x );
        void Delete( int n );
        void DeleteFront();
        void DeleteBack();
};

//----------------------------------------
DList :: DList() : count(0)
{
    list_head = new Node();
	list_head -> prev_node = list_head -> next_node = list_head;
}

//----------------------------------------
DList :: ~DList() 
{
	Node * temp_node;
	Node * node = list_head -> next_node;
	while ( node != list_head )
	{
		temp_node = node;
		node = node -> next_node;
		delete temp_node;
	}
 
	delete list_head;
	list_head = NULL;
}

//-------------------------------------
Node* DList :: GetNode( int n ) 
{
	if ( n < 0 || n >= count)
	{
		return NULL;
	}
 
	if ( n <= count / 2 )
	{
		int i=0;
		Node * node = list_head -> next_node;
		while ( i++ < n ) 
			node = node -> next_node;
		return node;
    }

	int j = 0;
	int rindex = count - n -1;
	Node* r_node = list_head -> prev_node;
	while ( j++ < rindex ) 
		r_node = r_node -> prev_node;
 
	return r_node;
}

//-----------------------------------------
void DList :: Push( int n, int x ) 
{
	if ( n == 0 )
		return PushFront(x);
 
	Node* node1 = GetNode(n);
	Node* node2  = new Node( x, node1 -> prev_node, node1 );
	node1 -> prev_node -> next_node = node2;
	node1 -> prev_node = node2;
	count++;
}

//-------------------------------------------
void DList :: PushFront( int x )
{
	Node* node  = new Node( x, list_head, list_head -> next_node );
	list_head -> next_node -> prev_node = node;
	list_head -> next_node = node;
	count++;
}

//-----------------------------------------
void DList :: PushBack( int x )
{
    Node * new_node = new Node( x, list_head -> prev_node, list_head );
    list_head -> prev_node -> next_node = new_node;
    list_head -> prev_node = new_node;
    count++;
}

//-------------------------------------------
void DList:: Delete( int n )
{
    Node * node = GetNode(n);
	node -> next_node -> prev_node = node -> prev_node;
	node -> prev_node -> next_node = node -> next_node;
	delete node;
	count--;
}

//---------------------------------------------
void DList :: DeleteFront()
{
    return Delete(0);
}

//----------------------------------------------
void DList :: DeleteBack()
{
    return Delete( count - 1 );
}

//**************************************************************************
int main(void)
{
    int n_substances, n_rules, n_operations;
    int x, y, z;
    int s, q;
    
    DList list;
    Node *node = list.list_head;

    cin >> n_substances >> n_rules >> n_operations;
    int oper[n_substances][n_substances];
    for ( int i = 0; i < n_substances; ++i )
    {
        for ( int j = 0; j < n_substances; ++j )
            oper[i][j] = 0;
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
        for ( int j = 0; j < q; ++j )
        {
            if ( s != -1 )
                list.PushBack(s);  
            else
            {
                while ( node != nullptr )
                {




                    if ( node -> data != node -> next_node -> data )
                    {
                        if ( oper[node -> data][node -> next_node -> data] != 0 )
                        {
                            Node * tnode1 = node;
                            Node * tnode2 = node -> next_node;
                            Node * pnode = new Node(oper[node -> data][node -> next_node -> data], node -> prev_node, node -> next_node -> next_node);
                            delete tnode1;
                            delete tnode2;
                        }
                        





                    }






                    node = node -> next_node;
                }
                list.DeleteFront();
            }
        }
    }   
    cout << list.count; 
    return 0;
}
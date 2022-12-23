#include <iostream>

using namespace std;

//****************************************************************
class Node {
    public:
        int data;
        Node * prev_node;
        Node * next_node;

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
	if ( n <0 || n >= count)
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

    cin >> n_substances >> n_rules >> n_operations;
    int oper[n_substances][n_substances];
    for ( int i = 0; i < n_substances; ++i )
    {
        for ( int j = 0; j < n_substances; ++j )
            oper[i][j] = 0;
    }
    int Q[n_operations] = {0};
    int Data[n_operations] = {0};
    for ( int i = 0; i < n_rules; ++i )
    {
        cin >> x >> y >> z;
        oper[x][y] = z;
        oper[y][x] = z;
    }
    cin >> s >> q;
    Q[0] = q;
    Data[0] = s;
    //-------
    for ( int i = 0; i < q; ++i )
        list.PushBack(s);
    for ( int i = 1; i < n_operations; ++i )
    {
        cin >> s >> q;
        Q[i] = q;
        Data[i] = s;
        //Push
        if ( s != -1 )
        {
            for ( int k = i - 1; k >= 0; --k )
            {
                if ( Q[k] != 0 )
                {
                    //If x + y -> z
                    if ( oper[Data[k]][s] != 0 )
                    {
                        if ( Q[k] < q )
                        {
                            for ( int j = 0; j < Q[k]; ++j  ) 
                                list.Delete(-1);
                            for ( int j = 0; j < Q[k]; ++j  ) 
                                list.PushBack(oper[Data[k]][s]);
                            for ( int j = 0; j < q - Q[k]; ++j )
                                list.PushBack(s);
                            Data[k] = oper[Data[k]][s];
                            Q[i] = q - Q[k];
                        }
                        else if ( Q[k] < q )
                        {
                            for ( int j = 0; j < Q[k]; ++j  ) 
                                list.Delete(-1);
                            for ( int j = 0; j < Q[k]; ++j  ) 
                                list.PushBack(oper[Data[k]][s]);
                            Q[k] = 0;
                            Q[i] = q;
                            Data[k] = 0;
                            Data[i] = oper[Data[k]][s];
                        }
                        else
                        {
                            for ( int j = 0; j < Q[k] - q; ++j  ) 
                                list.Delete(-1);
                            for ( int j = 0; j < q; ++j  ) 
                                list.PushBack(oper[Data[k]][s]);
                            Q[k] = Q[k] - q;
                            Data[i] = oper[Data[k]][s];
                            Q[i] = q;
                        }
                    }
                    //if x + y != z
                    else
                    {
                        for ( int j = 0; j < q; ++j )
                        {
                            list.PushBack(s);
                            Q[i] = q;
                            Data[i] = s;
                        }
                    }
                    break;
                }
                else
                    continue;
            }
        }
        //Pop
        else
        {
            for ( int i = 0; i < q; ++i )
                list.Delete(0);
            int total = 0;
            for ( int m = 0; m < i; ++m )
            {
                total += Q[m];
                if ( total > q )
                {
                    for ( int i = 0; i < m; ++i )
                    {
                        Q[i] = 0;
                        Data[i] = 0;
                        Q[m] = total - q;
                    }
                    break;
                }
            }
        }
    }
    return 0;
}
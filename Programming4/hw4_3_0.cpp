#include <iostream>

using namespace std;

//**************************************************************************
class Node         // an edge with vertex X, vertex Y, and weight weight
{
    public:
        int value;

        Node() { };
        Node( int v ) : value(v) { };
        ~Node() { };
};

//******************************************************************************
class MinHeap
{
    public:
        Node *min_heap;
        int size;       // The heap starts from 1.

    public:
        MinHeap() { };
        ~MinHeap() { };

        bool isEmpty();     // Judge whether it is empty

        Node GetTop();
        Node GetBack();
        
        void PercolateDown( int id );
        void PercolateUp( int id );
        void createMinHeap();
        void Pop();

};

//------------------------------

bool MinHeap :: isEmpty()
{
    return size == 1;
}

//--------------------------------

Node MinHeap :: GetTop()
{
    return min_heap[1];
}

//-----------------------------------

Node MinHeap :: GetBack()
{
    return min_heap[size - 1];
}

//---------------------------------

void MinHeap :: PercolateDown( int id ) 
{
    if ( isEmpty() ) 
    {
        return;
    }

    if ( ( 2 * id + 1 ) < size )
    {   
        Node Temp = min_heap[id];
        int temp = Temp.value;   
        int left  = 2 * id;        
        int right = 2 * id + 1;  
        
        if ( min_heap[left].value <= min_heap[right].value )   // Left child is smaller.
        {
            if ( temp > min_heap[left].value )                  // The current node is larger than its left child.
            {
                min_heap[id] = min_heap[left];                   // exchange the current node and its left child
                min_heap[left] = Temp;
                PercolateDown( 2 * id );
            }
        }

        else                                                    // right child is smaller
        {
            if ( temp > min_heap[right].value)                 // The current node is larger than its right child.
            {
                min_heap[id] = min_heap[right];
                min_heap[right] = Temp;
                PercolateDown( 2 * id + 1 );
            }
        }
    }

    if ( ( 2 * id + 1 >= size ) && ( 2 * id < size ) )        // The current node has only left child.
    {
        if ( min_heap[id].value > min_heap[id * 2].value )  // The current node is larger than its left child.
        {
            Node Temp = min_heap[id];
            min_heap[id] = min_heap[id * 2];
            min_heap[id * 2] = Temp;
        }
    }
}

//------------------------------------------------------

void MinHeap :: PercolateUp( int id )
{
    if ( id > 0 )
    {
        int temp = min_heap[id].value;
        Node Temp = min_heap[id];
        int father = id / 2;
        if ( father >= 0 ) 
        {
            if ( temp < min_heap[father].value ) 
            {
                min_heap[id] = min_heap[father];
                min_heap[father] = Temp;
                PercolateUp( id / 2 );
            }
        }
    }
}

//-------------------------------------------------------

void MinHeap :: createMinHeap()     // Floyd
{
    if ( isEmpty() ) 
    {
        return;
    }
    for ( int i = ( size - 1 ) / 2; i > 0; --i ) 
    {
        PercolateDown(i);
    }
}

//-----------------------------------------------------------

void MinHeap :: Pop()
{
    int temp = min_heap[1].value;
    min_heap[1] = min_heap[size - 1];
    size--;
    PercolateDown(1);
}

//**************************************************************************************

int main(void)
{
    int n_dragon, m_knight, hp, cost;
    int total_cost = 0;
    cin >> n_dragon >> m_knight;
    
    MinHeap array_dragon;
    MinHeap array_knight;
    array_dragon.min_heap = new Node[n_dragon + 1];
    array_dragon.size = n_dragon + 1;
    array_knight.min_heap = new Node[m_knight + 1];
    array_knight.size = m_knight + 1;

    for ( int i = 1; i <= n_dragon; ++i )
    {
        cin >> hp;
        array_dragon.min_heap[i].value = hp;
    }
    array_dragon.createMinHeap();

    int dragon[n_dragon];
    int knight[m_knight];

    for ( int i = 0; i < n_dragon; ++i )    //Heapsort
    {
        dragon[i] = array_dragon.min_heap[1].value;
        array_dragon.Pop();
    }


    /*//test1
    cout << endl;
    cout << "test1" << endl;
    for ( int i = 0; i < n_dragon; ++i )
        cout << dragon[i] << endl;
    cout << endl;
    //test1 end*/

    for ( int i = 1; i <= m_knight; ++i )
    {
        cin >> cost;
        array_knight.min_heap[i].value = cost;
    }
    array_knight.createMinHeap();

    for ( int i = 0; i < m_knight; ++i )    //Heapsort
    {
        knight[i] = array_knight.min_heap[1].value;
        array_knight.Pop();
    }

    /*//test2
    cout << endl;
    cout << "test2" << endl;
    for ( int i = 0; i < m_knight; ++i )
        cout << knight[i] << endl;
    cout << endl;
    //test2 end*/

    int *ptr_d = &dragon[0], *ptr_k = &knight[0];
    int tag1 = 0, tag2 = 0;
    while ( ( tag1 <= n_dragon - 1 ) && ( tag2 <= m_knight - 1 ) )
    {
        if ( (*ptr_k) >= (*ptr_d) )
        {
            total_cost += (*ptr_k);
            ptr_k ++;
            tag1 ++;
            ptr_d ++;
            tag2 ++;
        }
        else
        {
            ptr_k ++;
            tag2 ++;
        }
    }

    if ( ( ( tag1 != n_dragon ) && ( tag2 == m_knight ) ) || ( ( ( tag1 == n_dragon ) && ( tag2 == m_knight ) ) && ( knight[tag2 - 1] < dragon[tag1 - 1]) ) )
        cout << "you died!";
    else
        cout << total_cost;

    return 0;
}
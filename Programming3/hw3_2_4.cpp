#include <iostream>

using namespace std;

//**************************************************************************
class Node 
{
    public:
        int vertexX;
        int vertexY;
        int weight;

        Node() : vertexX(0), vertexY(0), weight(0) { };
        Node( int x, int y, int w ) : vertexX(x), vertexY(y), weight(w) { };
        ~Node() { };
};

//******************************************************************************
class MinHeap
{
    public:
        Node *min_heap = new Node[1];
        int index;
        int size;

    public:
        MinHeap() : index(0), size(1) { };
        ~MinHeap() { };

        bool isEmpty();     // Judge whether it is empty
        bool isFull();      // Judge whether it is full
        Node GetTop();
        Node GetBack();
        
        void PercolateDown( int id );
        void PercolateUp(int id);
        void createMinHeap();
        int Pop();
        void Push( int x, int y, int w);

};

//------------------------------

bool MinHeap :: isEmpty()
{
    return index == 0;
}

//-------------------------------

bool MinHeap :: isFull() 
{
    return index == size - 1;
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

    while ( id < index )
    {
        Node Temp = min_heap[id];
        int temp = Temp.weight;
        int left  = 2 * id;
        int right = 2 * id + 1;
        if ( left == index ) 
        {
            min_heap[id] = min_heap[left];
            min_heap[left] = Temp;
        }
        if ( min_heap[left].weight <= min_heap[right].weight ) 
        {
            if ( temp > min_heap[left].weight ) 
            {
                min_heap[id] = min_heap[left];
                min_heap[id] = Temp;
                id = left;
            }
            else 
                id = index;
        }
        else 
        {
            if ( temp > min_heap[right].weight) 
            {
                min_heap[id] = min_heap[right];
                min_heap[right] = Temp;
                id = right;
            }
            else 
                id = index;
        }
    }
}

//------------------------------------------------------

void MinHeap :: PercolateUp( int id )
{
    if ( id > index) 
    {
        return;
    }
    while ( id > 0 )
    {
        int temp = min_heap[id].weight;
        Node Temp = min_heap[id];
        int father = id / 2;
        if ( father >= 0 ) 
        {
            if ( temp < min_heap[father].weight ) 
            {
                min_heap[id] = min_heap[father];
                min_heap[father] = Temp;
                id = father;
            }
            else
                id = 0;
        }
        else
            index = 0;
    }
}

//-------------------------------------------------------

void MinHeap :: createMinHeap() 
{
    if ( isEmpty() ) 
    {
        return;
    }
    for ( int i = ( index ) / 2; i > 0; --i ) 
    {
        PercolateDown(i);
    }
}

//-----------------------------------------------------------

int MinHeap :: Pop()
{
    int temp = min_heap[1].weight;
    min_heap[1] = GetBack();
    size--;
    PercolateDown(1);
    return temp;
}

//-----------------------------------------------------------

void MinHeap :: Push( int x, int y, int w )
{
    min_heap = new Node(x, y, w);
    size++;
	PercolateUp( size - 1 );
}

//**************************************************************************************

int main(void)
{
    int n_vertices, m_edges, k_shortest;
    int vertex_x, vertex_y, weight_w;
    int shortest = 0;

    cin >> n_vertices >> m_edges >> k_shortest;

    Node *array;
    int *array_v;
    int matrix_w[2 * k_shortest][2 * k_shortest];
    for ( int i = 0; i < k_shortest; ++i )
    {
        for ( int j = 0; j < k_shortest; ++j )
        {
            matrix_w[i][j] = 1000000000;
        }
    }
    
    MinHeap heap;
    heap.min_heap = new Node[m_edges];
    for ( int i = 1;i <= m_edges; ++i )
    {
        cin >> vertex_x >> vertex_y >> weight_w;
        heap.min_heap[i].vertexX = vertex_x;
        heap.min_heap[i].vertexY = vertex_y;
        heap.min_heap[i].weight = weight_w;
    }
    heap.createMinHeap();
    
    for ( int i = 0; i < k_shortest; ++i )
    {
        array = new Node( heap.GetTop() );
        array_v = new int( heap.GetTop().vertexX );
        array_v = new int( heap.GetTop().vertexY );
        matrix_w[2 * i][2 * i + 1] = heap.GetTop().weight;
        matrix_w[2 * i + 1][2 * i] = heap.GetTop().weight;
        heap.Pop();
    }

    for( int k = 0; k < 2 * k_shortest; ++k )
    {
        for( int i = 0; i < 2 * k_shortest; ++i )
        {
            for( int j = 0; j < 2 * k_shortest; ++j)
            {
                if( matrix_w[i][j] > matrix_w[i][k] + matrix_w[k][j])
                {
                    matrix_w[i][j] = matrix_w[i][k] + matrix_w[k][j];
                }
            }
        }
    }

    cout << matrix_w[3][4];
    
    return 0;
}
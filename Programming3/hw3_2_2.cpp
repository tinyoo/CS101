#include <iostream>

using namespace std;

//**************************************************************************
class Node 
{
    public:
        int vertexX;
        int vertexY;
        int weight;
};

//******************************************************************************
class MinHeap
{
    public:
        Node *min_heap = new Node;
        int index;
        int size;

    public:
        MinHeap() : min_heap( NULL ), index(0), size(1) { };
        ~MinHeap() { };

        bool isEmpty();     // Judge whether it is empty
        bool isFull();      // Judge whether it is full
        Node GetTop();
        Node GetBack();
        
        void PercolateDown( int id );
        void createMinHeap();
        int Pop();

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
    int temp = min_heap[1];
    min_heap[1] = GetBack();
    size--;
    PercolateDown(1);
    return temp;
}

//**************************************************************************************

int main(void)
{
    int n_vertices, m_edges, k_shortest;
    int vertex_x, vertex_y, weight_w;
    int shortest = 0;
    
    MinHeap heap;
    cin >> n_vertices >> m_edges >> k_shortest;
    heap.min_heap = new Node[m_edges];
    for ( int i = 0; i <= m_edges; ++i )
    {
        cin >> vertex_x >> vertex_y >> weight_w;
        heap.min_heap[i].vertexX = vertex_x;
        heap.min_heap[i].vertexY = vertex_y;
        heap.min_heap[i].weight = weight_w;
    }
    heap.createMinHeap();

    int *array_w = new int[k_shortest];
    int** matrix = new int*[2 * k_shortest];
    for ( int i = 0; i < 2 * k_shortest; ++i )
        matrix[i] = new int[2 * k_shortest];

    for ( int i = 0; i < k_shortest; ++i )
    {
        array_w[i] = heap.Pop();
    }

    while( ( k != 0 ) && ( !heap.isEmpty() ) )
    {
        Node current = heap.GetTop();
        heap.Pop();
        int u = current.vertexX;
        int v = current.vertexY;
        for( int i = 0; i <= u; ++i )
        {
            heap[heap.size] = new Node( v, heap[i].vertexX, heap[i].vertexY + current.vertexX );
            heap.createMinHeap();
        }
        for( int i = 0; i <= v; ++i )
        {
            heap[heap.size] = new Node( u, heap[i].vertexX, heap[i].vertexY + current.vertexX );
            heap.createMinHeap();
        }
        array[v][u] = array[u][v] = current.vertexX;
        shortest = current.vertexX;
        k_shortest;
    }

    return 0;
}
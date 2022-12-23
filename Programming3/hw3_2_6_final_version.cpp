#include <iostream>

using namespace std;

//**************************************************************************
class Node         // an edge with vertex X, vertex Y, and weight weight
{
    public:
        int vertexX;
        int vertexY;
        int weight;

        Node() { };
        Node( int x, int y, int w ) : vertexX(x), vertexY(y), weight(w) { };
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

    if ( ( 2 * id + 1 ) < size )  // The node has two children.
    {
        Node Temp = min_heap[id];  // Temp stores the current node.
        int temp = Temp.weight;    // temp stores the current node's weight.
        int left  = 2 * id;        // left child's index
        int right = 2 * id + 1;    // right child's index
        
        if ( min_heap[left].weight <= min_heap[right].weight )   // Left child is smaller.
        {
            if ( temp > min_heap[left].weight )                  // The current node is larger than its left child.
            {
                min_heap[id] = min_heap[left];                   // exchange the current node and its left child
                min_heap[left] = Temp;
                PercolateDown( 2 * id );
            }
        }

        else                                                    // right child is smaller
        {
            if ( temp > min_heap[right].weight)                 // The current node is larger than its right child.
            {
                min_heap[id] = min_heap[right];
                min_heap[right] = Temp;
                PercolateDown( 2 * id + 1 );
            }
        }
    }

    if ( ( 2 * id + 1 >= size ) && ( 2 * id < size ) )        // The current node has only left child.
    {
        if ( min_heap[id].weight > min_heap[id * 2].weight )  // The current node is larger than its left child.
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
        int temp = min_heap[id].weight;
        Node Temp = min_heap[id];
        int father = id / 2;
        if ( father >= 0 ) 
        {
            if ( temp < min_heap[father].weight ) 
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
    int temp = min_heap[1].weight;
    min_heap[1] = min_heap[size - 1];
    size--;
    PercolateDown(1);
}

//**************************************************************************************

int main(void)
{
    int n_vertices, m_edges, k_shortest;
    int vertex_x, vertex_y, weight_w;
    int shortest = 0;

    cin >> n_vertices >> m_edges >> k_shortest;

    Node array[k_shortest];    // To store the shortest k edges
    
    MinHeap heap;              // Heapsort the k shortest edges
    heap.min_heap = new Node[m_edges + 1];
    heap.size = m_edges + 1;
    for ( int i = 1; i <= m_edges; ++i )
    {
        cin >> vertex_x >> vertex_y >> weight_w;
        heap.min_heap[i].vertexX = vertex_x;
        heap.min_heap[i].vertexY = vertex_y;
        heap.min_heap[i].weight = weight_w;
    }
    heap.createMinHeap();

    /*//test1
    cout << endl;
    cout << "test1" << endl;
    for ( int i = 1; i < heap.size; ++i )
        cout << heap.min_heap[i].vertexX << " " << heap.min_heap[i].vertexY << " " << heap.min_heap[i].weight << endl;
    cout << endl;
    //test1 end*/

    for ( int i = 0; i < k_shortest; ++i )    //Heapsort
    {
        array[i] = heap.min_heap[1];
        heap.Pop();
    }

    /*//test2
    cout << "test2" << endl;
    for ( int i = 0; i < k_shortest; ++i )
        cout << array[i].vertexX << " " << array[i].vertexY << " " << array[i].weight << endl;
    cout << endl;
    //test2 end*/

    int *array_v; 
    array_v = new int[2 * k_shortest];      // To store the vertices of the k shortest edges

    int size_of_array_v = 0;
    for ( int i = 0; i < k_shortest; ++i )
    {
        int t1 = 0, t2 = 0;
        for ( int j = 0; j < size_of_array_v; ++j )
        {
            if ( array_v[j] == array[i].vertexX )
                t1 ++;
        }

        if ( t1 == 0 )
        {
            size_of_array_v ++;
            array_v[size_of_array_v - 1] = array[i].vertexX;
        } 
        
        for ( int j = 0; j < size_of_array_v; ++j )
        {
            if ( array_v[j] == array[i].vertexY )
                t2 ++;
        }

        if ( t2 == 0 )
        {
            size_of_array_v ++;
            array_v[size_of_array_v - 1] = array[i].vertexY;
        }
    }

    /*//test3
    cout << "test3" << endl;
    for ( int i = 0; i < size_of_array_v; ++i )
    {
        cout << array_v[i] << " ";
    }
    cout << endl;*/

    //---------------------------------------------------
    int matrix_w[size_of_array_v][size_of_array_v];
    for ( int i = 0; i < size_of_array_v; ++i )
    {
        for ( int j = 0; j < size_of_array_v; ++j )
        {
            matrix_w[i][j] = 1000000000;
        }
    }

    for ( int i = 0; i < k_shortest; ++i )
    {
        int index1 = -1, index2 = -1;
        for ( int j = 0; j < size_of_array_v; ++j )
        {
            if ( array_v[j] == array[i].vertexX )
                index1 = j;
            if ( array_v[j] == array[i].vertexY )
                index2 = j;
            if ( ( index1 != -1 && ( index2 != -1 ) ) )
                break;
        } 
        matrix_w[index1][index2] = array[i].weight;
        matrix_w[index2][index1] = array[i].weight; 
    }

    /*//test4
    cout << endl;
    cout << "test4" << endl;
    for ( int i = 0; i < size_of_array_v; ++i )
    {
        for ( int j = 0; j < size_of_array_v; ++j )
            cout << matrix_w[i][j] << " ";
        cout << endl;
    }
    cout << endl;
    //test4 end*/

    for( int k = 0; k < size_of_array_v; ++k )
    {
        for( int i = 0; i < size_of_array_v; ++i )
        {
            for( int j = 0; j < size_of_array_v; ++j)
            {
                if( matrix_w[i][j] > matrix_w[i][k] + matrix_w[k][j])
                {
                    matrix_w[i][j] = matrix_w[i][k] + matrix_w[k][j];
                }
            }
        }
    }

    /*//test5
    cout << endl;
    cout << "test5" << endl;
    for ( int i = 0; i < size_of_array_v; ++i )
    {
        for ( int j = 0; j < size_of_array_v; ++j )
            cout << matrix_w[i][j] << " ";
        cout << endl;
    }
    cout << endl;
    //test5 end*/

    MinHeap heap2;       // Heapsort the shortest paths
    
    int number = size_of_array_v * ( size_of_array_v - 1 ) / 2;

    int array3[number];   // To store the shortest paths
    int array3_size = 0;
    for ( int i = 0; i < size_of_array_v - 1; ++i )
    {
        for ( int j = i + 1; j < size_of_array_v; ++j )
        {
            int t = 0;
            for ( int k = 0; k < array3_size; ++k )
            {
                if ( matrix_w[i][j] == array3[k] )
                    t++;
            }
            if ( t == 0 )
            {
                array3[array3_size] = matrix_w[i][j];
                array3_size ++;
            }
        }
    }

    /*//test6
    cout << endl;
    cout << "test6" << endl;
    for ( int i = 0; i < array3_size; ++i )
        cout << array3[i] << " ";
    cout << endl;
    //test6 end*/

    heap2.min_heap = new Node[array3_size + 1];   /////wrong
    heap2.size = array3_size + 1;

    for ( int k = 1; k < array3_size; ++k )
    {
        heap2.min_heap[k].weight = array3[k];
    }
    heap2.createMinHeap();

    /*//test 7
    cout << endl;
    cout << "test7" << endl;
    for ( int i = 1; i <= number; ++i )
    {
        cout << heap2.min_heap[i].weight << " ";
    }
    cout << endl;
    //test7 end*/

    int array2[number];
    for ( int i = 0; i < array3_size; ++i )
    {
        array2[i] = heap2.min_heap[1].weight;
        heap2.Pop();
    }
    
    /*for ( int i = 0; i < number; ++i )
    {
        cout << array2[i] << " ";
    }*/
    
    cout << array2[k_shortest - 1];
    
    return 0;
}
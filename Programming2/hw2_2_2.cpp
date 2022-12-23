#include <cstdio>

void MQSA( int number_nodes, int array[], int degrees[], int decay[] );

int main(void)
{
    int number_nodes, degree_node, index_node, decay_value, initial_strength;
    scanf( "%d", &number_nodes );
    int array[number_nodes + 1], degrees[number_nodes], decay[number_nodes - 1];
    for ( int i = 1; i <= number_nodes; ++i )
    {
        scanf( "%d", &degree_node );
        degrees[i - 1] = degree_node;
        if ( degree_node > 0 )
        {
            for ( int k = 1; k <= degree_node; ++k )
            {
                scanf( "%d %d", &index_node, &decay_value );
                array[index_node] = decay_value; 
                decay[index_node - 2] = decay_value;
            }
        }
    }
    scanf( "%d", &initial_strength );
    array[1] = initial_strength;
    int p = 0;
    for ( int i = 0; i < number_nodes; ++i )
    {
        if ( degrees[i] > 0 )
        {
            for ( int j = 1; j <= degrees[i]; ++j )
            {
                array[p + j + 1] = array[i + 1] - array[p + j + 1];
            }
        }
        p = degrees[i];
    }
    MQSA(number_nodes, array, degrees, decay );
    return 0;
}

void MQSA( int number_nodes, int array[], int degrees[], int decay[] )
{
    for ( int m = 0; m <= number_nodes - 2; ++m )
    {
        if ( decay[m] > array[1] )
            printf("No solution.");
    }
}
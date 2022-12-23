#include <cstdio>

class Tree
{
    public:
        int index;
        int value;
        int number_nodes;
        int decay_value;
        int index_parent;
        int index_child[20000];

        Tree() { };
        ~Tree(){ };
};

void MQSA( Tree tree[], int number_nodes, int number_child[] );

int main(void)
{
    int number_nodes, degree_node, index_node, decay, initial_strength, max_decay = 0;
    scanf( "%d", &number_nodes );
    Tree tree[number_nodes + 1];
    int number_children[number_nodes + 1];
    for ( int j = 1; j <= number_nodes; ++j )
        tree[j].index = j;
    for ( int i = 1; i <= number_nodes; ++i )
    {
        scanf( "%d", &degree_node );
        number_children[i] = degree_node;
        if ( degree_node > 0 )
        {
            for ( int k = 0; k < degree_node; ++k )
            {
                scanf( "%d %d", &index_node, &decay );
                tree[i].index_child[k] = index_node;
                tree[index_node].decay_value = decay;
                tree[index_node].index_parent = i;
                if ( decay > max_decay )
                    max_decay = decay;
            }
        }
    }
    scanf( "%d", &initial_strength );
    tree[1].value = initial_strength;
    for ( int i = 1; i <= number_nodes; ++i )
    {
        for ( int k = 0; k < number_children[i]; ++k )
            tree[tree[i].index_child[k]].value = tree[i].value - tree[tree[i].index_child[k]].decay_value;
    }
    if ( max_decay > initial_strength )
        printf("No solution.");
    else
        MQSA( tree, number_nodes, number_children );
    return 0;
}

void MQSA( Tree tree[], int number_nodes, int number_children[] )
{
    Tree *ptr;
    int total_decay = 0, MinAmp = 0;
    int m_node = 1, n_node;
    for ( int i = 1; i <= number_nodes; ++i )
    {
        if ( number_children[i] == 0 )
        {
            if ( tree[i].value < 0 )
            {
                ptr = &tree[i];
                while ( ptr -> value < 0 )
                {
                    total_decay += ptr -> decay_value;
                    ptr = &tree[ptr -> index_parent];
                }
                n_node = ptr -> index;
                if ( n_node != m_node )
                    MinAmp = MinAmp + ( total_decay - 1 ) / tree[1].value + 1;
                else
                    MinAmp = MinAmp + ( total_decay - 1 ) / tree[1].value;
                n_node = m_node;
            }
        }
    }
    printf( "%d", MinAmp );
}
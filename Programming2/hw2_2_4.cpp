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

void MQSA( Tree tree[], int number_nodes );

int main(void)
{
    int number_nodes, degree_node, index_node, decay, initial_strength, max_decay = 0;
    scanf( "%d", &number_nodes );
    Tree tree[number_nodes + 1];
    tree[1].decay_value = 0;
    int number_children[number_nodes + 1];
    for ( int j = 1; j <= number_nodes; ++j )
        tree[j].index = j;
    for ( int i = 1; i <= number_nodes; ++i )
    {
        scanf( "%d", &degree_node );
        tree[i].number_nodes = degree_node;
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
    for ( int i = 1; i < number_nodes; ++i )
    {
        for ( int k = 0; k < number_children[i]; ++k )
            tree[tree[i].index_child[k]].value = tree[i].value - tree[tree[i].index_child[k]].decay_value;
    }
    if ( max_decay > initial_strength )
        printf("No solution.");
    else
        MQSA( tree, number_nodes );
    return 0;
}

void MQSA( Tree tree[], int number_nodes )
{
    Tree *ptr;
    int MinAmp = 0;
    int max = 0;
    for ( int i = number_nodes; i > 1; --i )
    //for ( int i = number_nodes; i > 1 + tree[1].number_nodes; --i )
    {
        ptr = &tree[i];
        int temp;
        int x = tree[ptr -> index_parent].decay_value;
        if ( ptr -> decay_value <= tree[1].value )
        {
            temp = ptr -> decay_value;
            if ( ( ( i != number_nodes ) && ( ( ptr -> index_parent ) != ( tree[i + 1].index_parent ) ) ) || ( i == number_nodes ) )
            {
                //x = tree[ptr -> index_parent].decay_value;
                ptr = &tree[ptr -> index_parent];
                ptr -> decay_value += temp;
            }
            else if ( ( ptr -> index_parent ) == ( tree[i + 1].index_parent ) )
            {
                //max = tree[i + 1].decay_value;
                if ( ptr -> decay_value >= max )
                {
                    int submax = max;
                    max = ptr -> decay_value;
                    ptr = &tree[ptr -> index_parent];
                    ptr -> decay_value = x + max;
                    if ( ( submax + x > tree[1].value ) && ( tree[i].decay_value + x > tree[1].value ) )
                        MinAmp -= 1;
                }
                
            } 
            if ( ptr -> decay_value > tree[1].value )
            {
                ptr -> decay_value = x;
                MinAmp += 1;
            }
        }
    }
    printf( "%d", MinAmp );
}
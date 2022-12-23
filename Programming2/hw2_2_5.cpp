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

void MQSA( Tree tree[], int number_nodes, int number_children[] );

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
        MQSA( tree, number_nodes, number_children );
    return 0;
}

void MQSA( Tree tree[], int number_nodes, int number_children[] )
{
    Tree *ptr;
    int MinAmp = 0;
    int i = number_nodes;
    while (  i > 1 + number_children[1] )
    {
        ptr = &tree[i];
        int x = tree[ptr -> index_parent].decay_value;
        
        int max = ptr -> decay_value;
        if ( tree[ptr -> index_parent].number_nodes > 1 )
        {
            for ( int i = 0; i < number_children[ptr -> index_parent] - 1; ++i )
            {
                if ( tree[tree[ptr -> index_parent].index_child[i]].decay_value > max )
                    max = tree[tree[ptr -> index_parent].index_child[i]].decay_value;
            }
        }
        ptr = &tree[ptr -> index_parent];
        ptr -> decay_value += max;
        if ( ptr -> decay_value > tree[1].value )
        {
            ptr -> decay_value = x;
            MinAmp += 1;
        }
        
        i = i - number_children[ptr -> index];
    }
    printf( "%d", MinAmp );
}
#include <cstdio>
#include <iostream>

using namespace std;

class Tree
{
    public:
        int value;
        int decay;
        int index_parent;
        int number_children;
        int *index_children = new int[0];

        Tree(){};
        ~Tree(){};
};

void MQSA( Tree tree[], int index, int * );

int main(void)
{
    int number_nodes, degree_node, index_node, decay, initial_strength, max_decay = 0;
    int MinAmp = 0;
    scanf( "%d", &number_nodes );
    Tree tree[number_nodes + 1];
    
    for ( int i = 1; i <= number_nodes; ++i )
    {
        scanf( "%d", &degree_node );
        tree[i].number_children = degree_node;
        if ( degree_node > 0 )
        {
            tree[i].index_children = new int[degree_node];
            for ( int k = 0; k < degree_node; ++k )
            {
                scanf( "%d %d", &index_node, &decay );
                tree[i].index_children[k] = index_node;
                tree[index_node].decay = decay;
                tree[k].index_parent = i;
                if ( decay > max_decay )
                    max_decay = decay;
            }
        }
    }
    scanf( "%d", &initial_strength );
    tree[1].value = initial_strength;
    tree[1].decay = 0;
    if ( max_decay > initial_strength )
        printf("No solution.");
    else
    {
        MQSA( tree, 1, &MinAmp );
        printf( "%d", MinAmp );
    }
    return 0;
}


void MQSA( Tree tree[], int index, int *MinAmp )
{
    int number_children = tree[index].number_children;
    for ( int i = 0; i < number_children; ++i )
    {
        MQSA( tree, tree[index].index_children[i], MinAmp );
    }
    int max = 0;
    if ( tree[index].number_children == 0 )
        tree[index].decay += 0;
    else
    {
        for ( int j = 0; j < tree[index].number_children; ++j )
        {
            if ( tree[tree[index].index_children[j]].decay > max )
                max = tree[tree[index].index_children[j]].decay;
        }
    }
    int initial = tree[index].decay;
    tree[index].decay += max;
    if ( (tree[index].decay > tree[1].value) )
    {
        tree[index].decay = initial;
        *MinAmp += 1;
    }
}
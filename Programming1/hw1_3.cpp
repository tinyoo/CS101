#include <iostream>
#include <cstdlib>

class Node {
    private:
        int element;
        Node *next_node;
    
    public:
        Node( int = 0, Node * = nullptr );

        //Accessors
        int retrieve() const;
        Node * next() const;
};

Node :: Node ( int e, Node * n ) : element(e), next_node(n)
{
    
}

int Node :: retrieve() const
{
    return element;
}

Node * Node :: next() const
{
    return next_node;
}
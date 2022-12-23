#include <iostream>
#include <cstdio>

class underflow { };

class Node {
    private:
        int index_data[2];
        Node *next_node;
    public:
        Node( int index, int data, Node *n ) : index_data[0](index), index_data[1](data), next_node(n) { };

        int retrieve() const { return index_data[1]; };
        Node *next() const { return next_node; }; 
};

class List {
    private:
        Node *list_head;

    public:
        List() : list_head( nullptr ) { };
        ~List() { };

        bool empty() const { return list_head == nullptr; };
        Node *head() const { return list_head };
        int size() const { 
            int number;
            for ( Node *ptr = head(); ptr != nullptr; ptr = ptr -> next() )
            {
                number += 1;
            }
            return number;
        };
        int front() const { 
            if ( empty() )
                throw underflow();
            return head() -> retrieve(); 
        };
        void push_front( int n )
        {
            if ( empty() )
                list_head = new Node( n, nullptr );
            else
                list_head = new Node( n, head() );
        };
};

class Tree {
    private:
        int node[2];
        Tree *parent_node;
        List<Tree *> children;

    public:
        Tree( int &index, int &data, Tree *p ) : node[0]( index ), node[1](data), parent_node( p ) {};

        int retrieve() const { return node -> index_data[1]; };
        Tree *parent() const { return parent_node; };
        int degree() const { return children.size(); };
        bool is_root() const { return parent() == nullptr };
        bool is_leaf() const { return degree() == 0; };
        Tree *child( int n ) const;
};

Tree *Tree :: child( int n ) const
{
    if ( n < 0 || n >= degree() )
    {
        return nullptr;
    }
    Node *ptr = children.head();
    for ( int i = 0; i < n; ++i )
        ptr = ptr -> next();
    return ptr -> retrieve();
}

int main(void)
{
    int number_nodes, degree_node, index_node, decay_value, initial_strength;
    Tree tree;
    scanf( "%d", &number_nodes );
    for ( int i = 1; i <= number_nodes; ++i )
    {
        scanf( "%d", &degree_node );
        for ( int k = 1; k <= degree_node; ++k )
        {
            scanf( "%d %d", &index_node, &decay_value );
        }
    }
    scanf( "%d", &initial_strength );
    
    return 0;
}
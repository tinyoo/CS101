#include <iostream>
#include <cstdio>

class underflow { };

class Node {
    private:
        int element;
        Node *Next;
    public:
        Node( int e, Node *n ) : element(e), Next(n) { };

        int retrieve() const { return element; };
        Node *next() const { return Next; };
};

class List {
    private:
        Node *list_head;

    public:
        List() : list_head( nullptr ) { };
        ~List();

        bool empty() const { return list_head == nullptr; };
        Node *head() const { return list_head; };
        int front() const { 
            if ( empty() )
                throw underflow();
            return head() -> retrieve(); 
        };
};

class Tree {
    private:
        int element;
        Tree *parent_node;
        List<Tree *> children;

    public:
        Tree( int const &obj, Tree *p ) : element( obj ), parent_node( p ) {};

        int retrieve() const { return element; };
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
    scanf( "%d", &number_nodes );
    for ( int i = 1; i <= number_nodes; ++i )
    {
        scanf( "%d", &degree_node );
        for ( int k = 1; k <= degree_node * degree_node; ++k )
        {
            scanf( "%d %d", &index_node, &decay_value );
        }
    }
    scanf( "%d", &initial_strength );
    
    return 0;
}
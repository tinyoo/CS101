#include <iostream>

using namespace std;

//****************************************************************
class Node {           // Node: data -> the kind of substance; number -> the number of this substance
    public:
        int data;      // the substance
        int number;    // # of substance
        Node * prev_node;
        Node * next_node;

        Node() { };
        Node( int d, int n, Node * prev, Node * next ) : data(d), number(n), prev_node(prev), next_node(next) { };
        ~Node() { };
};

//******************************************************************
class  DList {
    public:
        int count;
        Node *list_head;
        Node *list_tail;

        DList() : count(0), list_head(nullptr), list_tail(nullptr) { };
        ~DList() { };
        void PushBack( int x, int n );
        void DeleteFront( int n );
};

//----------------------------------------
void DList :: PushBack( int x, int n )
{
    if( list_head == nullptr )
    {
        list_head = new Node();
        list_head -> data = x;
        list_head -> number = n;
        list_tail = list_head;
        list_tail -> next_node = NULL;
        list_head -> prev_node = NULL;
    }
    else
    {
        if ( x != list_tail -> data )
        {
            list_tail -> next_node = new Node();
            list_tail -> next_node -> data = x;
            list_tail -> next_node -> number = n;
            list_tail -> next_node -> prev_node = list_tail;
            list_tail = list_tail -> next_node;
            list_tail -> next_node = NULL;            
        }
        else 
        {
            list_tail -> number += n;
        }

    }
    count += n;
}

//---------------------------------------------
void DList :: DeleteFront( int n )
{   
    count -= n;
    while ( n >= list_head -> number )
    {
        int temp = list_head -> number;
        Node *ptr = list_head;
        list_head = list_head -> next_node;
        delete ptr;
        n -= temp;
    }
    // if ( n < list_head -> number )
    ( list_head -> number ) -= n;
}

//**************************************************************************
void Furnace( Node * node, DList* list, int **oper );

void Furnace(Node * node, DList* list, int **oper)
{
    if(node == NULL) return;
    if(node -> next_node == NULL) return;
    if(oper[node -> data][node -> next_node -> data] == -2) return;
    if(node -> number > node -> next_node -> number) {
        node -> number -= node -> next_node -> number;
        list -> count -= node -> next_node -> number;
        node -> next_node -> data = oper[node -> data][node -> next_node -> data];
    }
    else if (node -> number == node -> next_node -> number)
    {
        node -> data = oper[node -> data][node -> next_node -> data];
        list -> count -= node -> number;
        Node *ptr = node -> next_node;
        node -> next_node = node -> next_node -> next_node;
        delete ptr;
    }
    else// (node -> number < node -> next_node -> number)
    {
        list -> count -= node -> number;
        node -> next_node -> number -= node -> number;
        node -> data = oper[node -> data][node -> next_node -> data];
    }
    Furnace(node->prev_node,list,oper);
    Furnace(node,list,oper);
}

int main(void)
{
    /*SOME CODE*/
    for (int i = 0; i < n_operations; ++i)
    {
        cin >> s >> q;
        if(s!=-1)
        {        
            list.PushBack(s,q);
            if(list.list_tail!=NULL)
                Furnace(node->prev_node,&list,oper);
        }
        else if ( ( s == -1 ) && ( node != NULL ) )
            list.DeleteFront(q);
    }
    /*SOME CODE*/
}

//**************************Tinyoo's idea***********************************//
// push the first node into the empty list;
// if the next substance is the same with the previous one, just add the number of the previous node.
// if the next substance is different from the previous one
//      if next substance cannot act with the current substance: push it into the list
//      if next substance can act with the current substance
//              if number of the current is fewer than the number of the next( A + B -> C ): A -> C, push (# of B - # of A) B
//                      determine whether C can act with the previous one (recursive)
//              if number of the current equals the number of the next( A + B -> C ): A -> C
//                      determine whether C can act with the previous one (recursive)
//              if number of the current is more than the number of the next( A + B -> C ): B -> C, # of A - # of B
//******* Notice: A + B -> C, A + C -> D exist!
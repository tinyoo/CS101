#include <iostream>
#include <iomanip>

using namespace std;

int gcd( int x, int y );

//*************************************************************************
class AVLNode {
    public:
        int value;         // the value of x
        int index;         // to record the x's position, for we need to print the number in sequence
        int height;
        AVLNode *left;
        AVLNode *right;

        AVLNode() { };
        AVLNode(int v, int i, AVLNode *l, AVLNode *r) : value(v), index(i), height(0), left(l), right(r) { };
        ~AVLNode() { };
};

//***************************************************************************
class AVLTree {
    public:
        AVLNode *root;
    
    public:
        AVLTree() : root(NULL) { };
        ~AVLTree() { };

        int GetHeight(AVLNode *tree);
        int max(int a, int b);

        AVLNode* LLRotation(AVLNode *node);
        AVLNode* RRRotation(AVLNode *node);
        AVLNode* LRRotation(AVLNode *node);
        AVLNode* RLRotation(AVLNode *node);

        AVLNode* Insert(AVLNode *tree, int v, int i);
        void Insert(int v, int i);

        AVLNode* search(AVLNode *node, int v);
        AVLNode* search(int v);

        void PrintAVL(AVLNode* tree, int value, int direction);
        void PrintAVL();
};

//-----------------------------------------------
int AVLTree :: GetHeight(AVLNode *tree)
{
    if ( tree != NULL )
        return tree -> height;
    else
        return 0;
}

//-----------------------------------------------
int AVLTree :: max(int x, int y)
{
    return ( x > y ) ? x : y;
}

//-----------------------------------------------
AVLNode* AVLTree :: LLRotation(AVLNode *node)
{
    AVLNode *node2 = node -> left;
    node -> left = node2 -> right;
    node2 -> right = node;

    node -> height = max( GetHeight( node -> left ), GetHeight( node -> right ) ) + 1;
    node2 -> height = max( GetHeight( node2 -> left ), GetHeight( node2 -> right ) ) + 1;

    return node2;
}

//-----------------------------------------------
AVLNode* AVLTree :: RRRotation(AVLNode *node)
{
    AVLNode *node2 = node -> right;
    node -> right = node2 -> left;
    node2 -> left = node;

    node -> height = max( GetHeight( node -> left ), GetHeight( node -> right ) ) + 1;
    node2 -> height = max( GetHeight( node2 -> left ), GetHeight( node2 -> right ) ) + 1;

    return node2;
}

//-----------------------------------------------
AVLNode* AVLTree :: LRRotation(AVLNode *node)
{
    node -> left = RRRotation( node -> left );
    return LLRotation(node);
}

//-----------------------------------------------
AVLNode* AVLTree :: RLRotation(AVLNode *node)
{
    node -> right = LLRotation( node -> right );
    return RRRotation(node);
}

//-----------------------------------------------
AVLNode* AVLTree :: Insert(AVLNode *tree, int v, int i)
{
    if( tree == NULL )
        tree = new AVLNode(v, i, NULL, NULL);
    else if( v < ( tree -> value ) )
    {
        tree -> left = Insert(tree -> left, v, i);
        if( GetHeight(tree -> left) - GetHeight(tree -> right) == 2 )
        {
            if( v < ( tree -> left -> value ) )
                tree = LLRotation(tree);
            else
                tree = LRRotation(tree);
        }
    }
    else if( v > ( tree -> value ) )
    {
        tree -> right = Insert(tree -> right, v, i);
        if( GetHeight(tree -> right) - GetHeight(tree -> left) == 2 )
        {
            if( v > tree -> right -> value )
                tree = RRRotation(tree);
            else
                tree = RLRotation(tree);
        }
    }

    tree -> height = max( GetHeight(tree -> left), GetHeight(tree -> right) ) + 1;

    return tree;
}

//---------------------------------------------------
void AVLTree :: Insert(int v, int i)
{
    root = Insert(root, v, i);
}

//-----------------------------------------------------
AVLNode* AVLTree :: search(AVLNode *node, int v)
{
    if( node == NULL )
        return NULL;
    if( node -> value == v )
        return node;
    if( v < node -> value )
        return search(node -> left, v);
    else
        return search(node -> right, v);
}

//-------------------------------------------------------
AVLNode* AVLTree :: search(int v)
{
    return search(root, v);
}

//--------------------------------------------------------
void AVLTree :: PrintAVL(AVLNode *tree, int value, int direction)
{
    if( tree != NULL )
    {
        if( direction == 0 )
            cout << setw(2) << tree -> value << " is root" << endl;
        else
            cout << setw(2) << tree -> value << " is " << setw(2) << value << "'s " << setw(12) << ( direction == 1 ? "right child" : "left child" ) << endl;
        
        PrintAVL( tree -> left, tree -> value, -1 );
        PrintAVL( tree -> right, tree -> value, 1 );
    }
}

//-----------------------------------------------------------
void AVLTree :: PrintAVL()
{
    if( root != NULL )
    {
        cout << "not empty" << endl;
        PrintAVL( root, root -> value, 0 );
    }
    else if ( root == NULL )
        cout << "ERROR" << endl;  ////
}

//**********************************************************************************

int main(void)
{
    int n, s, num_x, x;

    cin >> n;
    int *Sequence = new int[n];
    for ( int i = 0; i < n; ++i )
    {
        cin >> s;
        Sequence[i] = s;
    }

    //test1
    /*cout << endl;
    for ( int i = 0; i < n; ++i )
        cout << Sequence[i] << " ";
    */

    cin >> num_x;
    AVLTree Xs;
    for ( int i = 0; i < num_x; ++i )
    {
        cin >> x;
        Xs.Insert(x, i);
    }

    //test2
    //if ( Xs.root == NULL )
    //    cout << "NULL" << endl;   ////

    Xs.PrintAVL();

/*
    int *Ans = new int[num_x];
    for ( int i = 0; i < num_x; ++i )
        Ans[i] = 0;

    for ( int i = 0; i < n; ++i )
    {
        for ( int j = i; j < n; ++j )
        {
            if( Xs.search( gcd( Sequence[i], Sequence[j] ) ) != nullptr )
            {
                int k = ( Xs.search( gcd( Sequence[i], Sequence[j] ) ) ) -> index;
                Ans[k] += 1;
                Sequence[i] = gcd( Sequence[i], Sequence[j] );
            }
            else
                Sequence[i] = gcd( Sequence[i], Sequence[j] );
        }
    }

    for ( int i = 0; i < num_x; ++i )
        cout << Ans[i] << " ";
*/
    return 0;
}

int gcd( int x, int y )
{
    if ( y == 0 )
        return x;
    else
        return gcd( y, x % y );
}
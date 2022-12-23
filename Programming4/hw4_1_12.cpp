#include <iostream>       ////  2019.12.22

using namespace std;

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
        AVLTree() : root(nullptr) { };
        ~AVLTree() { };

        int GetHeight(AVLNode *node);
        AVLNode* LLRotation(AVLNode *node);
        AVLNode* RRRotation(AVLNode *node);
        AVLNode* LRRotation(AVLNode *node);
        AVLNode* RLRotation(AVLNode *node);

        AVLNode* Insert(AVLNode *tree, int v, int i);
        void Insert(int v, int i);

        AVLNode* search(AVLNode *node, int v);
        AVLNode* search(int v);

};

//-----------------------------------------------
int AVLTree :: GetHeight(AVLNode *node)
{
    if ( node != nullptr )
        return node -> height;
    else
        return 0;
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
    if( tree == nullptr )
    {
        tree = new AVLNode(v, i, nullptr, nullptr);
    }
    else if( ( tree != nullptr ) & ( v < ( tree -> value ) ) )
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

//**********************************************************************************

int gcd( int x, int y );
int Count(int x, int *copy, int a, int b);
void IOI( int *Sequence, int l, int r, int x, int *number, int n );

int main(void)
{
    int n, s, num_x, x;

    // Address the sequence
    cin >> n;
    int *Sequence = new int[n];
    for ( int i = 0; i < n; ++i )
    {
        cin >> s;
        Sequence[i] = s;
    }

    // Address x
    cin >> num_x;
    AVLTree Xs;
    int *array = new int[num_x];
    for ( int i = 0; i < num_x; ++i )
    {
        cin >> x;
        Xs.Insert(x, i);
        array[i] = x;
    }

    int b = 0;
    // Use an array to store the answer
    int **Ans = new int*[num_x];
    for ( int i = 0; i < num_x; ++i )
        Ans[i] = &b;

    //for ( int i = 0; i < num_x; ++i )
    //    cout << Ans[i] << " ";

    for ( int i = 0; i < num_x; ++i )
    {
        IOI( Sequence, 0, n, array[i], Ans[i], n );
    }

    // Output the answer
    for ( int i = 0; i < num_x; ++i )
        cout << Ans[i] << " ";

    return 0;
}

//-------------------------------------------
void IOI( int *Sequence, int l, int r, int x, int *number, int n )
{
    int mid = ( l + r ) / 2;

    if ( r - l == 1)
    {
        if ( Sequence[l] == x )
            number += 1;
    }
    else
    {
        IOI( Sequence, l, mid, x, number, n );
        IOI( Sequence, mid, r, x, number, n );
    }

    int copy[n];    // Construct another array used to address the Sequence
    for ( int i = l; i < r; ++i )
        copy[i] = Sequence[i];
    // Address copy 
    for ( int i = mid - 2; i >= l; --i )
        copy[i] = gcd( copy[i+1], copy[i] );
    for ( int i = mid + 1; i < r; ++i )
        copy[i] = gcd( copy[i-1], copy[i] );

    /////////////////////////////////////////////
    int i = mid - 1;
    while ( i >= l )
    {
        int j = mid;
        while ( j < r )
        {
            if( gcd( copy[i], copy[j] ) == x )
            {
                number += ( Count( copy[i], copy, mid - 1, l ) * Count( copy[j], copy, mid, r ) );
            }
            j += ( Count( copy[j], copy, mid, r ) );
        }
        i -= ( Count( copy[i], copy, mid, l ) );
    }
    ///////////////////////////////////////////////
}

//---------------------------------------
int gcd( int x, int y )
{
    if ( y == 0 )
        return x;
    else
        return gcd( y, x % y );
}

//------------------------------------------------
int Count(int x, int *copy, int a, int b)
{
    int num = 0;
    if ( a <= b )
    {
        for( int i = a; i < b; ++i )
        {
            if( copy[i] == x )
                num += 1;
            else
                break;
        }
    }
    else
    {
        for( int i = b; i >= a; --i )
        {
            if( copy[i] == x )
                num += 1;
            else
                break;
        } 
    }

    return num;
}
//---------------------------------------------------

/*
12
2 4 5 2 18 3 9 10 66 24 24 18
2
1 3

51 4 
*/
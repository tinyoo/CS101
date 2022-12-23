#include <iostream>

using namespace std;

int gcd( int x, int y );

//*************************************************************************
class AVLNode {
    public:
        int value;
        int index;
        int height;
        AVLNode *left;
        AVLNode *right;

        AVLNode() { };
        AVLNode(int v, int i) : value(v), index(i), height(1), left(nullptr), right(nullptr) { };
        ~AVLNode() { };
};

//***************************************************************************
class AVLTree {
    private:
        AVLNode *root;
    
    public:
        AVLTree() { };
        ~AVLTree() { };

        int GetHeight(AVLNode *tree);
        AVLNode* LLRotation(AVLNode *node);
        AVLNode* RRRotation(AVLNode *node);
        AVLNode* LRRotation(AVLNode *node);
        AVLNode* RLRotation(AVLNode *node);

        AVLNode* insert(AVLNode *tree, int v, int i);
        AVLNode* insert(int v, int i);

        AVLNode* search(AVLNode *node, int v);
        AVLNode* search(int v);
};

//-----------------------------------------------
int AVLTree :: GetHeight(AVLNode *tree)
{
    if ( tree != nullptr  )
        return tree -> height;
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
    node2 -> height = max( GetHeight( node2 -> left ), node -> height ) + 1;

    return node2;
}

//-----------------------------------------------
AVLNode* AVLTree :: RRRotation(AVLNode *node)
{
    AVLNode *node2 = node -> right;
    node -> right = node2 -> left;
    node2 -> left = node;

    node -> height = max( GetHeight( node -> left ), GetHeight( node -> right ) ) + 1;
    node2 -> height = max( GetHeight( node2 -> right ), node -> height ) + 1;

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
AVLNode* AVLTree :: insert(AVLNode *tree, int v, int i)
{
    if( tree == nullptr )
        tree = new AVLNode(v, i);
    else if( v < tree -> value )
    {
        tree -> left = insert(tree -> left, v, i);
        if( GetHeight(tree -> left) - GetHeight(tree -> right) == 2 )
        {
            if( v < tree -> left -> value )
                tree = LLRotation(tree);
            else
                tree = LRRotation(tree);
        }
    }
    else if( v > tree -> value )
    {
        tree -> right = insert(tree -> right, v, i);
        if( GetHeight(tree -> right) - GetHeight(tree -> left) == 2 )
        {
            if( v < tree -> right -> value )
                tree = RRRotation(tree);
            else
                tree = RLRotation(tree);
        }
    }

    tree -> height = max( GetHeight(tree->left), GetHeight(tree->right) ) + 1;

    return tree;
}

//---------------------------------------------------
AVLNode* AVLTree :: insert(int v, int i)
{
    insert(root, v, i);
}

//-----------------------------------------------------
AVLNode* AVLTree :: search(AVLNode *node, int v)
{
    if( node == nullptr )
        return nullptr;
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

    cin >> num_x;
    AVLTree Xs;
    for ( int i = 0; i < num_x; ++i )
    {
        cin >> x;
        Xs.insert(x, i);
    }

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
            }
            else
                Sequence[i] = gcd( Sequence[i], Sequence[j] );
        }
    }

    for ( int i = 0; i < num_x; ++i )
        cout << Ans[i] << " ";

    return 0;
}

int gcd( int x, int y )
{
    if ( y == 0 )
        return x;
    else
        return gcd( y, x % y );
}
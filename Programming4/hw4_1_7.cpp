#include <iostream>

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
void IOI( int a, int b, AVLTree Xs, int *Sequence, int num_x, int *Ans, int *leftnum, int *rightnum );

int main(void)
{
    int n, s, num_x, x;

    cin >> n;
    int *Sequence = new int[n];
    int *Sequence2 = new int[n];
    for ( int i = 0; i < n; ++i )
    {
        cin >> s;
        Sequence[i] = s;
        Sequence2[i] = s;
    }

    cin >> num_x;
    AVLTree Xs;
    for ( int i = 0; i < num_x; ++i )
    {
        cin >> x;
        Xs.Insert(x, i);
    }

    int *Ans = new int[num_x];
    for ( int i = 0; i < num_x; ++i )
        Ans[i] = 0;

    int *leftnum = new int[num_x];
    for ( int i = 0; i < num_x; ++i )
        leftnum[i] = 0;

    int *rightnum = new int[num_x];
    for ( int i = 0; i < num_x; ++i )
        rightnum[i] = 0;

    IOI( 0, n / 2, Xs, Sequence2, num_x, Ans, leftnum, rightnum );
    IOI( n / 2, n, Xs, Sequence2, num_x, Ans, leftnum, rightnum );

    int temp = Sequence[n / 2 - 1];
    for ( int j = n / 2; j < n; ++j )
    {
        if( Xs.search( gcd( Sequence[n / 2 - 1], Sequence[j] ) ) != nullptr )
        {
            int k = ( Xs.search( gcd( Sequence[n / 2 - 1], Sequence[j] ) ) ) -> index;
            rightnum[k] += 1;
            //cout << k << " " << rightnum[k] << endl;
        }
        Sequence[n / 2 - 1] = gcd( Sequence[n / 2 - 1], Sequence[j] );
    }

    Sequence[n / 2] = Sequence[n / 2 - 1];
    Sequence[n / 2 - 1] = temp;
    for ( int j = n / 2 - 2; j >= 0; --j )
    {
        if( Xs.search( gcd( Sequence[n / 2], Sequence[j] ) ) != nullptr )
        {
            int k = ( Xs.search( gcd( Sequence[n / 2], Sequence[j] ) ) ) -> index;
            leftnum[k] += 1;
            //cout << k << " " << leftnum[k] << endl;
        }
        Sequence[n / 2] = gcd( Sequence[n / 2], Sequence[j] );
    }
    
    for ( int k = 0; k < num_x; ++k )
    {
        if ( ( leftnum[k] == 0 ) && ( rightnum[k] != 0 ) )
            Ans[k] += rightnum[k];
        else if ( ( rightnum[k] == 0 ) && ( leftnum[k] != 0 ) )
            Ans[k] += leftnum[k];
        else
            Ans[k] += ( leftnum[k] * rightnum[k] );
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

void IOI( int a, int b, AVLTree Xs, int *Sequence, int num_x, int *Ans, int *leftnum, int *rightnum )
{
    for ( int i = a; i < b; ++i )
    {
        for ( int j = i; j < b; ++j )
        {
            if( Xs.search( gcd( Sequence[i], Sequence[j] ) ) != nullptr )
            {
                int k = ( Xs.search( gcd( Sequence[i], Sequence[j] ) ) ) -> index;
                Ans[k] += 1;
            }
            Sequence[i] = gcd( Sequence[i], Sequence[j] );
        }
    }
}
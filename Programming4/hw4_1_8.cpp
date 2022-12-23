#include <iostream>       ////  2019.12.20

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
int gcd2( int a, int b, int n, int *temp );
int Count(int x, int *Sequence, int a, int b);
void IOI1( int a, int b, AVLTree Xs, int *Sequence, int num_x, int *Ans );
void Change( int a, int b, AVLTree Xs, int *Sequence, int *temp2, int num_x, int n, int *Ans );
void IOI( int a, int b, AVLTree Xs, int *Sequence, int num_x, int n, int *Ans );

int main(void)
{
    int n, s, num_x, x;

    cin >> n;
    int *Sequence = new int[n];
    int *temp = new int[n];
    for ( int i = 0; i < n; ++i )
    {
        cin >> s;
        Sequence[i] = s;
        temp[i] = s;
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

    IOI( 0, n, Xs, Sequence, num_x, n, Ans );

    for ( int i = 0; i < num_x; ++i )
        cout << Ans[i] << " ";

    return 0;
}

//---------------------------------------
int gcd( int x, int y )
{
    if ( y == 0 )
        return x;
    else
        return gcd( y, x % y );
}

//----------------------------------------
int gcd2( int a, int b, int n, int *temp )
{
    int *T = new int[n];
    for ( int i = 0; i < n; ++i )
        T[i] = temp[i];
    for ( int i = a; i <= b; ++i )
    {
        T[a] = gcd( T[a], T[i] );
    }
    return T[a];
}

//------------------------------------------------
void IOI1( int a, int b, AVLTree Xs, int *Sequence, int num_x, int *Ans )
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
    /*for ( int i = a; i < b; ++i )
        cout << Sequence[i] << endl;
    cout << endl;*/
}

//-------------------------------------------------
void Change( int a, int b, AVLTree Xs, int *Sequence, int *temp2, int num_x, int n, int *Ans )
{
    for ( int i = a; i < b; ++i )
    {
        Sequence[i] = gcd2(a, i, n, temp2);
        //cout << Sequence[i] << endl;
    }
    /*cout << endl;
    for ( int i = a; i < b; ++i )
        cout << Sequence[i] << endl;
    cout << endl;*/
}

//---------------------------------------------------
void IOI( int a, int b, AVLTree Xs, int *Sequence, int num_x,  int n, int *Ans )
{
    int mid = ( a + b ) / 2;
    if ( mid - a <= 2 )
    {
        //
        int *temp1 = new int[n];
        for ( int i = 0; i < n; ++i )
        {
            temp1[i] = Sequence[i];
        }
        //
        //
        int *temp2 = new int[n];
        for ( int i = 0; i < n; ++i )
        {
            temp2[i] = Sequence[i];
        }
        //
        IOI1(a, mid, Xs, Sequence, num_x, Ans);
        IOI1(mid, b, Xs, temp1, num_x, Ans);
        Change(mid, b, Xs, Sequence, temp2, num_x, n, Ans);
        //////////////////////////////////////////////
        int i = mid - 1;
        while ( i >= a )
        {
            int j = mid;
            while ( j < b )
            {
                if( Xs.search( gcd( Sequence[i], Sequence[j] ) ) != nullptr )
                {
                    int k = ( Xs.search( gcd( Sequence[i], Sequence[j] ) ) ) -> index;
                    Ans[k] += ( Count( Sequence[i], Sequence, a, mid ) * Count( Sequence[j], Sequence, mid, b ) );
                }
                j += ( Count( Sequence[j], Sequence, mid, b ) );
            }
            i -= ( Count( Sequence[i], Sequence, a, mid ) );
        }
        ///////////////////////////////////////////////
    }
    else
    {
        IOI(a, mid, Xs, Sequence, num_x, n, Ans);
        IOI(mid, b, Xs, Sequence, num_x, n, Ans);
    }
}

//------------------------------------------------
int Count(int x, int *Sequence, int a, int b)
{
    int num = 0;
    for( int i = a; i < b; ++i )
    {
        if( Sequence[i] == x )
            num += 1;
    }
    return num;
}
//---------------------------------------------------
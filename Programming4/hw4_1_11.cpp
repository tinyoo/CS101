#include <iostream>       ////  2019.12.21

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
int gcd2( int a, int b, int n, int *copy );
int Count(int x, int *Sequence, int a, int b);
void Change1( int a, int b, AVLTree Xs, int n, int *Ans, int *temp, int *copy );
void Change2( int a, int b, AVLTree Xs, int n, int *Ans, int *temp, int *copy );
int IOI( int a, int b, AVLTree Xs, int *Sequence, int n, int *Ans, int k, int *temp );
int Jump( int a, int b, AVLTree Xs, int *copy, int n, int *Ans, int k, int *temp );

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

    for ( int k = 0; k < num_x; ++k )
        Ans[k] = IOI( 0, n, Xs, Sequence, n, Ans, k, temp );
    
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

//---------------------------------------------------
int IOI( int a, int b, AVLTree Xs, int *Sequence, int n, int *Ans, int k, int *temp )
{
    int answer = 0;
    int left, right, jump;
    int *copy = new int[n];
    for ( int i = 0; i < n; ++i )
        copy[i] = Sequence[i];
    if ( b - a == 1 )
    {
        if ( ( Xs.search( copy[a] ) != nullptr ) && ( Xs.search( copy[a] ) -> index == k ) )
            answer += 1;
        //cout << "H" << Ans[k] << endl;  
    }
    else
    {
        left = IOI( a, (a + b) / 2, Xs, copy, n / 2, Ans, k, temp );
        right = IOI( (a + b) / 2, b, Xs, copy, n - n / 2, Ans, k, temp ); 
        jump = Jump( a, b, Xs, copy, n, Ans, k, temp );
        answer = answer + left + right + jump;
    }
    return answer;
}

//---------------------------------------------------
int Jump( int a, int b, AVLTree Xs, int *copy, int n, int *Ans, int k, int *temp )
{
    int number = 0;
    int mid = ( a + b ) / 2;
    Change1(a, mid, Xs, n, Ans, temp, copy);
    Change2(mid, b, Xs, n, Ans, temp, copy);
    //cout << temp[0] << " " << temp[1] << endl;
    int i = mid - 1;
    int numl = 0, numr = 0;
    while ( i >= a )
    {
        int j = mid;
        while ( j < b )
        {
            if( ( Xs.search( gcd( temp[i], temp[j] ) ) != nullptr ) && ( ( ( Xs.search( gcd( temp[i], temp[j] ) ) ) -> index ) ) == k )
            {
                numl = Count( temp[i], temp, a, mid );
                numr = Count( temp[j], temp, mid, b );
                number += (numl * numr);
                //cout << numl << " " << numr << endl;
            }
            j += numr;
            //cout << "J" << j << endl;
        }
        i -= numl;
    }
    //cout << "A" << Ans[k] << endl;
    return number;
}

//-------------------------------------------------
void Change1( int a, int b, AVLTree Xs, int n, int *Ans, int *temp, int *copy )
{
    for ( int i = b - 1; i >= a; --i )
        temp[i] = gcd2(i, b, n, copy);
}

//-------------------------------------------------
void Change2( int a, int b, AVLTree Xs, int n, int *Ans, int *temp, int *copy )
{
    for ( int i = a; i < b; ++i )  
        temp[i] = gcd2(a, i, n, copy);
}

//----------------------------------------
int gcd2( int a, int b, int n, int *copy )
{
    for ( int i = a; i < b; ++i )
    {
        copy[a] = gcd( copy[a], copy[i] );
    }
    return copy[a];
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
    //cout << "N" << num << endl;
    return num;
}


/*
12
2 4 5 2 18 3 9 10 66 24 24 8
2
1 3

51 4 
*/
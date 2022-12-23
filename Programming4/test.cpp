#ifndef _AVL_TREE_HPP_
#define _AVL_TREE_HPP_

#include <iomanip>
#include <iostream>
using namespace std;

int gcd( int x, int y );

class AVLTreeNode{
    public:
        int key;                // 关键字(键值)
        int index;
        int height;         // 高度
        AVLTreeNode *left;    // 左孩子
        AVLTreeNode *right;    // 右孩子

        AVLTreeNode(int value, int i, AVLTreeNode *l, AVLTreeNode *r):
            key(value), index(i), height(0),left(l),right(r) {}
};

class AVLTree {
    private:
        AVLTreeNode *mRoot;    // 根结点

    public:
        AVLTree();
        ~AVLTree() {};

        // 获取树的高度
        int height();
        
        // (递归实现)查找"AVL树"中键值为key的节点
        AVLTreeNode* search(int key);

        AVLTreeNode* insert(AVLTreeNode* tree, int key, int i);
        // 将结点(key为节点键值)插入到AVL树中
        void insert(int key, int i);

    public:
        // 获取树的高度
        int height(AVLTreeNode* tree) ;


        // (递归实现)查找"AVL树x"中键值为key的节点
        AVLTreeNode* search(AVLTreeNode* x, int key) const;

        // LL：左左对应的情况(左单旋转)。
        AVLTreeNode* leftLeftRotation(AVLTreeNode* k2);

        // RR：右右对应的情况(右单旋转)。
        AVLTreeNode* rightRightRotation(AVLTreeNode* k1);

        // LR：左右对应的情况(左双旋转)。
        AVLTreeNode* leftRightRotation(AVLTreeNode* k3);

        // RL：右左对应的情况(右双旋转)。
        AVLTreeNode* rightLeftRotation(AVLTreeNode* k1);

};

/* 
 * 构造函数
 */
AVLTree::AVLTree():mRoot(NULL)
{
}

/*
 * 获取树的高度
 */
int AVLTree::height(AVLTreeNode* tree) 
{
    if (tree != NULL)
        return tree->height;

    return 0;
}

int AVLTree::height() 
{
    return height(mRoot);
}

/*
 * (递归实现)查找"AVL树x"中键值为key的节点
 */
AVLTreeNode* AVLTree::search(AVLTreeNode* x, int key) const
{
    if (x==NULL || x->key==key)
        return x;

    if (key < x->key)
        return search(x->left, key);
    else
        return search(x->right, key);
}

AVLTreeNode* AVLTree::search(int key) 
{
    return search(mRoot, key);
}

/*
 * LL：左左对应的情况(左单旋转)。
 *
 * 返回值：旋转后的根节点
 */
AVLTreeNode* AVLTree::leftLeftRotation(AVLTreeNode* k2)
{
    AVLTreeNode* k1;

    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = max( height(k2->left), height(k2->right)) + 1;
    k1->height = max( height(k1->left), k2->height) + 1;

    return k1;
}

/*
 * RR：右右对应的情况(右单旋转)。
 *
 * 返回值：旋转后的根节点
 */
AVLTreeNode* AVLTree::rightRightRotation(AVLTreeNode* k1)
{
    AVLTreeNode* k2;

    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;

    k1->height = max( height(k1->left), height(k1->right)) + 1;
    k2->height = max( height(k2->right), k1->height) + 1;

    return k2;
}

/*
 * LR：左右对应的情况(左双旋转)。
 *
 * 返回值：旋转后的根节点
 */
AVLTreeNode* AVLTree::leftRightRotation(AVLTreeNode* k3)
{
    k3->left = rightRightRotation(k3->left);

    return leftLeftRotation(k3);
}

/*
 * RL：右左对应的情况(右双旋转)。
 *
 * 返回值：旋转后的根节点
 */
AVLTreeNode* AVLTree::rightLeftRotation(AVLTreeNode* k1)
{
    k1->right = leftLeftRotation(k1->right);

    return rightRightRotation(k1);
}

/* 
 * 将结点插入到AVL树中，并返回根节点
 *
 * 参数说明：
 *     tree AVL树的根结点
 *     key 插入的结点的键值
 * 返回值：
 *     根节点
 */
AVLTreeNode* AVLTree::insert(AVLTreeNode* tree, int key, int i)
{
    if (tree == NULL) 
    {
        // 新建节点
        tree = new AVLTreeNode(key, i, NULL, NULL);
        if (tree==NULL)
        {
            cout << "ERROR: create avltree node failed!" << endl;
            return NULL;
        }
    }
    else if (key < tree->key) // 应该将key插入到"tree的左子树"的情况
    {
        tree->left = insert(tree->left, key, i);
        // 插入节点后，若AVL树失去平衡，则进行相应的调节。
        if (height(tree->left) - height(tree->right) == 2)
        {
            if (key < tree->left->key)
                tree = leftLeftRotation(tree);
            else
                tree = leftRightRotation(tree);
        }
    }
    else if (key > tree->key) // 应该将key插入到"tree的右子树"的情况
    {
        tree->right = insert(tree->right, key, i);
        // 插入节点后，若AVL树失去平衡，则进行相应的调节。
        if (height(tree->right) - height(tree->left) == 2)
        {
            if (key > tree->right->key)
                tree = rightRightRotation(tree);
            else
                tree = rightLeftRotation(tree);
        }
    }
    else //key == tree->key)
    {
        cout << "添加失败：不允许添加相同的节点！" << endl;
    }

    tree->height = max( height(tree->left), height(tree->right)) + 1;

    return tree;
}

void AVLTree::insert(int key, int i)
{
    insert(mRoot, key, i);
}

#endif

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
                Sequence[i] = gcd( Sequence[i], Sequence[j] );
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
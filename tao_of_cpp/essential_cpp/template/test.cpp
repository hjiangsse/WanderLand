#include <iostream>

using namespace std;

template <typename T>
class BinaryTree;

template <typename T>
class BTnode {
public:
    friend class BinaryTree<T>;
    BTnode(const T &val);
private:
    T _val;
    int _cnt;
    BTnode *_lchild;
    BTnode *_rchild;
};

template <typename T>
inline BTnode<T>::
BTnode(const T &val)
    :_val(val)
{
    _cnt = 1;
    _lchild = _rchild = 0;
}

template <typename T>
class BinaryTree {
public:
    BinaryTree();
    BinaryTree(const BinaryTree& );
    ~BinaryTree();
    BinaryTree& operator=(const BinaryTree& );

    bool is_empty() { return root == NULL; }
    void clear();
private:
    BTnode<T> *root;
    void copy(BTnode<T> *tar, BTnode<T> *src);
};

template <typename T>
inline BinaryTree<T>::
BinaryTree():
    root(NULL)
{
}

template <typename T>
inline BinaryTree<T>::
BinaryTree(const BinaryTree &rhs)
{
    copy(root, rhs.root);
}

template <typename T>
inline BinaryTree<T>::
~BinaryTree()
{
    clear();
}

template <typename T>
inline BinaryTree<T>&
BinaryTree<T>::
operator=(const BinaryTree &rhs)
{
    if( this != &rhs )
    {
	clear();
	copy(root, rhs.root);
    }
    return *this;
}





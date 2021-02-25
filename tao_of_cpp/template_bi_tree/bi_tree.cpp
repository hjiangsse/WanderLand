#include <iostream>

using namespace std;

template <typename valType>
class BTnode;

template <typename Type>
class BinaryTree;

//--------------definition of class BinaryTree------------------
template <typename elemType>
class BinaryTree {
public:
    BinaryTree();
    BinaryTree(const BinaryTree& );
    ~BinaryTree();
    BinaryTree& operator=( const BinaryTree& );

    bool empty() { return root == 0; }
    void clear();

    remove(elemType &elem);
private:
    BTnode<elemType> *root;

    //copy subtree pointed by src to tar
    void copy(BTnode<elemType> *tar, BTnode<elemType> *src);
};

template <typename elemType>
inline BinaryTree<elemType>::
BinaryTree()
    :root(0)
{}

template <typename elemType>
inline BinaryTree<elemType>::
BinaryTree(const BinaryTree &rhs)
{
    copy(root, rhs.root);
}

template <typename elemType>
inline BinaryTree<elemType>::
~BinaryTree()
{
    clear();
}

template <typename elemType>
inline BinaryTree<elemType>&
BinaryTree<elemType>::
operator=(const BinaryTree &rhs)
{
    if(this != &rhs) {
	clear();
	copy(root, rhs.root);
    }
    return *this;
}

template <typename elemType>
inline void BinaryTree<elemType>::
insert(const elemType &elem) {
    if(!root)
	root = new BTnode<elemType>(elem);
    else
	root->insert_value(elem);
}

template <typename valType>
inline void BinaryTree<elemType>::
remove(const elemType &elem)
{
    if(root->val == elem)
	remove_root();
    else
	root->remove_value(elem, _root);
}
//--------------definition of class BinaryTree------------------

//--------------definition of class BTnode----------------------
template <typename valType>
class BTnode {
public:
    friend class BinaryTree<valType>;
    void insert_value(const valType &);
private:
    valType _val;
    int _cnt;
    BTnode *_lchild;
    BTnode *_rchild;
};

template <typename valType>
inline BTnode<valType>::
BTnode(const valType& val)
    :_val(val)
{
    _cnt = 1;
    _lchild = _rchild = 0;
}

template <typename valType>
void BTnode<valType>::
insert_value(const valType &val)
{
    if(val == _val) {
	_cnt++;
	return;
    }

    if(val < _val)
    {
	if(!_lchild)
	    _lchild = new BTnode(val);
	else
	    _lchild->insert_value(val);
    }
    else
    {
	if(!_rchild)
	    _rchild = new BTnode(val);
	else
	    _rchild->insert_value(val);
    }
}
//--------------definition of class BTnode----------------------

int main(int argc, char **argv) {
    return 0;
}

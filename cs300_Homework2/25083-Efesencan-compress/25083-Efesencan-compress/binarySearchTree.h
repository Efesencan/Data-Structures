#ifndef _BINARYSEARCHTREE_H
#define _BINARYSEARCHTREE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

template <class T1, class T2>

struct treeNode
{
	T1 name;
	T2 code;
	treeNode<T1,T2> * right;
	treeNode<T1,T2> * left;

	treeNode<T1,T2>(T1 st,T2 cd,treeNode<T1,T2> * rt,treeNode<T1,T2> * lf)
		: name(st), code(cd), right(rt), left(lf)
	{}
};

template <class T1, class T2>

class binarySearchTree
{
public:
	binarySearchTree();
	~binarySearchTree();
	void printTree();
	void insert(T1 & str_val, T2 & code_num);
	bool isInTree(T1 & str_val);
	void deleteRecursively(treeNode<T1,T2> * & r);
	T2 findCodeValue(T1 & string_value);

private:
	treeNode<T1,T2> * root;
	bool isInTree(treeNode<T1,T2> *  r,T1 & str_val);
	treeNode<T1,T2> * findCodeValue(treeNode<T1,T2> * r,T1 & string_value);
	void insert(treeNode<T1,T2> * & r,T1 & str_val, T2 & code_num);
	void printTree(treeNode<T1,T2> * & r);
};



template <class T1, class T2>
binarySearchTree<T1,T2>::binarySearchTree()
{
	root = NULL;
}

template <class T1, class T2>
void binarySearchTree<T1,T2>::deleteRecursively(treeNode<T1,T2> *& r)
{
	if(r)
	{
		deleteRecursively(r->left);
		deleteRecursively(r->left);
		delete r;
	}
	r = NULL;
}

template <class T1, class T2>
binarySearchTree<T1,T2>::~binarySearchTree()
{
	deleteRecursively(root);
}

template <class T1, class T2>
void binarySearchTree<T1,T2>::insert(T1 & str_val, T2 & code_num)
{
	insert(root,str_val,code_num);
}

template <class T1, class T2>
void binarySearchTree<T1,T2>::insert(treeNode<T1,T2> * & r,T1 & str_val, T2 & code_num)
{
	if(r == NULL)
	{
		r = new treeNode<T1,T2>(str_val,code_num,NULL,NULL);
	}
	else
	{
		if(str_val > r->name)
		{
			insert(r->right,str_val,code_num);
		}
		else if(str_val < r->name)
		{
			insert(r->left,str_val,code_num);
		}
		else;
	}
}

template <class T1, class T2>
treeNode<T1,T2> * binarySearchTree<T1,T2>::findCodeValue(treeNode<T1,T2> * r,T1 & string_value)
{
	if(!r)
		return NULL;
	if(string_value > r->name)
	{
		return findCodeValue(r->right,string_value);
	}
	else if(string_value < r->name)
	{
		return findCodeValue(r->left,string_value);
	}
	else
	{
		return r;
	}
}

template <class T1, class T2>
T2 binarySearchTree<T1,T2>::findCodeValue(T1 & string_value)
{
	if(findCodeValue(root,string_value))
		return findCodeValue(root,string_value)->code;
	return NULL;
	
}

template <class T1, class T2>
bool binarySearchTree<T1,T2>::isInTree(treeNode<T1,T2> * r,T1 & str_value)
{
	while(r)
	{
		if(r->name > str_value)
		{
			r = r->left;
		}
		else if(r->name < str_value)
		{
			r = r->right;
		}
		else
		{
			return true;
		}
	}
	return false;
}

template <class T1, class T2>
bool binarySearchTree<T1,T2>::isInTree(T1 & str_value)
{
	return isInTree(root,str_value);
}

template <class T1, class T2>
void binarySearchTree<T1,T2>::printTree()
{
	printTree(root);
}

template <class T1, class T2>
void binarySearchTree<T1,T2>::printTree(treeNode<T1,T2> * & r)
{
	if(r)
	{
		printTree(r->left);
		if(r->code == 256)
			cout<<"string name:"<<r->name<<" "<<r->name.length()<<"code: "<<r->code<<"-----------------------"<<endl;
		cout<<"string name:"<<r->name<<" "<<r->name.length()<<"code: "<<r->code<<endl;
		printTree(r->right);
	}
}

#endif
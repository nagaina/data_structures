#ifndef _TREE_HPP_
#define _TREE_HPP_

#include "node.hpp"
#include <iostream>
#include <queue>
#include <stack>

template <typename T>
class RBtree
{
public:
	RBtree(Node<T>* r = 0):root(r) {}
	void insert(const T&);
	void delete_node(const T&);
	void levelorder();
	void inorder();
	void clear();
	~RBtree();
private:
	void clear(Node<T>* );
	void left_rotate(Node<T>*);
	void right_rotate(Node<T>*);
	void _insert(Node<T>*);
	void insert_fix(Node<T>*);
	Node<T>* predesser(Node<T>*);
	void delete_fix(Node<T>*);

	Node<T>* root;
};

template <typename T>
void RBtree<T>::left_rotate(Node<T>* x)
{
	Node<T>* y = x -> right;
	x -> right = y -> left;
	if (x -> right != 0)
		x -> right -> parent = x;
	y -> parent = x -> parent;
	if (x -> parent == 0)
		root =y;
	else if (x == x -> parent -> left)
		x -> parent -> left = y;
	else
		x -> parent -> right = y;
	y -> left = x;
	x -> parent = y;
}

template <typename T>
void RBtree<T>::right_rotate(Node<T>* x)
{	
	Node<T>* y = x -> left;
	x -> left = y -> right;
	if (x -> left != 0)
		x -> left -> parent = x;
	y -> parent = x -> parent;
	if (x -> parent == 0)
		root =y;
	else if (x == x -> parent -> left)
		x -> parent -> left = y;
	else
		x -> parent -> right = y;
	y -> right = x;
	x -> parent = y;
}

template <typename T>
void RBtree<T>::_insert(Node<T>* x)
{
	if (root == 0)
	{
		root = x;
		return;
	}
	Node<T>* temp = root;
	while (temp)
	{
		if (temp -> data > x -> data)
			if ( temp -> left)		
				temp = temp -> left;
			else break;		
		else
			if (temp -> right)
				temp = temp -> right;
			else break;
	}
	
	if (temp -> data > x -> data)
		temp -> left = x;
	else
		temp -> right =x;
	x -> parent = temp;

}

template <typename T>
void RBtree<T>::insert_fix(Node<T>* x)
{

	Node<T>* parent = 0;
	Node<T>* g_parent = 0;
	while ((x != root) && (x -> color != 'b') && (x -> parent -> color == 'r'))
	{
		parent = x -> parent;
		g_parent = x -> parent -> parent;
		if (parent == g_parent -> left) //left case
		{
			if ((g_parent -> right != 0) && (g_parent -> right -> color == 'r'))
			{
				parent -> color = 'b';
				g_parent -> right -> color = 'b';
				g_parent -> color = 'r';
				x = g_parent;
			}
			else if ((parent -> left != 0) && (parent -> left == x))
				{
					right_rotate(g_parent);
					parent -> color = 'b';
					g_parent -> color = 'r';
					x = parent;
				}
			else
			{
				left_rotate(parent);
				right_rotate(g_parent);
				g_parent -> color = 'r';
				x -> color = 'b';
			}
		}
		else // right case
		{
			if ((g_parent -> left != 0) && (g_parent -> left -> color == 'r'))
			{	
				parent -> color = 'b';
				g_parent -> left -> color = 'b';
				g_parent -> color = 'r';
				x = g_parent;
			}
			else  if ((parent -> left != 0) && (parent -> left == x))
				{
					left_rotate(g_parent);
					parent -> color = 'b';
					g_parent -> color = 'r';
					x = parent;
				}
			else
			{
				right_rotate(parent);
				left_rotate(g_parent);
				g_parent -> color = 'r';
				x -> color = 'b';
			}
		}
	} // end while
	root -> color = 'b';	
}

template <typename T>
void RBtree<T>::insert(const T& data)
{
	Node<T>* new_node = new Node<T>(data);
	_insert(new_node);
	insert_fix(new_node);

}

template <typename T>
void RBtree<T>::levelorder()
{
	if (root == 0)
		return;
	std::queue<Node<T>*> q;
	q.push(root);
	
	while (!q.empty())
	{
		Node<T>* temp = q.front();
		q.pop();
		std::cout << temp -> data <<std::endl;
		if (temp -> left != 0)
			q.push(temp -> left);
		if (temp -> right != 0)
			q.push(temp -> right);
	
	}
}

template <typename T>
void RBtree<T>::inorder()
{
	if (root == 0)
		return;

	std::stack<Node<T>* > stack;
	
	Node<T>* curr = root;
	
	while (curr != 0)
	{
		stack.push(curr);
		curr = curr -> left;
	}
	while (!stack.empty())
	{
		Node<T>* temp = stack.top();
		stack.pop();
		std::cout << temp -> data <<std::endl;
		curr = temp -> right;
		
		while (curr != 0)
		{
			stack.push(curr);
			curr = curr -> left;
		}
	} 
}

template <typename T>
void RBtree<T>::clear()
{
	clear(root);
	root = 0;
}

template <typename T>
void RBtree<T>::clear(Node<T>* t)
{
	if (t == 0)
		return;
	clear(t -> left);
	clear(t -> right);
	delete t;
}

template <typename T>
RBtree<T>::~RBtree()
{
	clear();
	delete root;
}

template <typename T>
Node<T>* RBtree<T>::predesser(Node<T>* p)
{
	if (p -> left != 0)
		p = p -> left;
	while (p -> right != 0)
	{
		p = p -> right;
	}
	return p;
}

template <typename T>
void RBtree<T>::delete_fix(Node<T>* v)
{
	Node<T>* parent = 0;
	Node<T>* s = 0;
	while (v != root && v -> color == 'b')
	{
		parent = v -> parent;
		if (parent -> left == v) //left case
		{
			s = parent -> right;
			if (s -> color == 'r')
			{
				left_rotate(parent);
				parent -> color = 'r';
				s -> color = 'b';
				s = v -> parent -> right;
			}
			if (s -> right == 0 && s -> left == 0)
			{
				s -> color = 'r';
				v = v -> parent;
			}
			else if (s -> right == 0)
			{		
				if (s -> left -> color == 'r')
				{
					s -> left ->  color = 'b';
					right_rotate(s);
					s -> color = 'r';
					s = parent -> right;					
				}
				else 
				{
					s -> color = 'r';
					v = v -> parent;
				}
			} 
			else if ( s -> left == 0)
			{
				if ( s -> right -> color == 'r')
				{				
					s -> color = parent -> color;
					parent -> color = 'b';
					s -> right -> color = 'b';
					left_rotate(parent);	
					v = root;
				}
				else {
					s -> color = 'r';
					v = v -> parent;
				}
			}
			else
			if (s -> right -> color == 'b' && s -> left -> color == 'b')
			{
				s -> color = 'r';
				v = v -> parent;
			}
			else
			{
				if (s -> right -> color == 'b')
				{
					s -> left ->  color = 'b';
					right_rotate(s);
					s -> color = 'r';
					s = parent -> right;
				}
					s -> color = parent -> color;
					parent -> color = 'b';
					s -> right -> color = 'b';
					left_rotate(parent);	
					v = root;
			}
		}
		else //right case
		{
			s = parent -> left;
			if (s -> color == 'r')
			{
				right_rotate(parent);
				parent -> color = 'r';
				s -> color = 'b';
				s = v -> parent -> left;
			}
			if (s -> right == 0 && s -> left == 0)
			{
				s -> color = 'r';
				v = v -> parent;
			}
			else if (s -> right == 0)
			{		
				if (s -> left -> color == 'r')
				{
					right_rotate(parent);	
					s -> color = parent -> color;
					parent -> color = 'b';
					s -> left -> color = 'b';
					v = root;				
				}
				else 
				{
					s -> color = 'r';
					v = v -> parent;
				}
			} 
			else if ( s -> left == 0)
			{
				if ( s -> right -> color == 'r')
				{				
					s -> right ->  color = 'b';
					left_rotate(s);
					s -> color = 'r';	
				}
				else {
					s -> color = 'r';
					v = v -> parent;
				}
			}
			else 
			if (s -> right -> color == 'b' && s -> left -> color == 'b')
			{
				s -> color = 'r';
				v = v -> parent;
			}
			else
			{
				if (s -> left -> color == 'b')
				{
					s -> right ->  color = 'b';
					left_rotate(s);
					s -> color = 'r';	
				}
				right_rotate(parent);	
				s -> color = parent -> color;
				parent -> color = 'b';
				s -> left -> color = 'b';
				v = root;
			}	
		}
	
	}
	root -> color = 'b';
	v -> color = 'b';
}

template <typename T>
void RBtree<T>::delete_node(const T& data)
{
	if (root == 0)
		return;
	Node<T>* u = root;
	while (u != 0 && u -> data != data)
	{
		if (u -> data > data)
			u = u -> left;		
		else
			u = u -> right;
	}
	
	if (u -> data != data)
		return;
	
	Node<T>* v = 0;
	Node<T>* l = 0;
	bool flag = 1;
	if (u -> left == 0 || u -> right == 0)
		v = u;
	else
		v = predesser(u);
	if (v -> left != 0)
		v = v -> left;
	else if ( v -> right != 0)		
		v = v -> right;
	if (v == v -> parent -> left )
		flag = 1;
	else  flag = 0;
	if (v != u)
	{
		u -> data = v -> data;
	}
	if (v -> color == 'b')
	{ 
		delete_fix(v);
	}
	if (flag)
		v -> parent -> left = 0;
	else v -> parent -> right = 0;
	//delete v;
	
}


#endif

#ifndef _NODE_HPP_
#define _NODE_HPP_

template <typename T>
struct Node
{
	Node(T d = 0, Node<T>* p = 0, Node<T>* l = 0, Node<T>* r = 0, char c = 'r'):data(d), parent(p), left(l), right(r), color(c) {}
	T data;
	Node<T>* parent;
	Node<T>* left;
	Node<T>* right;
	char color;
};
#endif

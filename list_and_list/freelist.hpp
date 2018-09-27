#ifndef _freelist_hpp
#define _freelist_hpp
//
// single linked freelist
//
#include "list.hpp"
#include <iostream>

//
// struct Node
//
template <typename T>
struct Node{
	void* operator new(size_t);
	void operator delete(void*);
	
	Node(T = 0, Node<T>* = 0);
	
	T _value;
	Node<T>* _next;
	
	static Node<T>* stack;
};

template <typename T>
Node<T>* Node<T>::stack = 0;

template <typename T>
Node<T>::Node(T val, Node<T>* p):_value(val), _next(p) {}

template <typename T>
void* Node<T>::operator new(size_t n)
{
	if(stack == 0) return ::new Node;
	Node<T>* temp = stack;
	stack = stack -> _next;
	return temp;
}

template <typename T>
void Node<T>::operator delete(void* ptr)
{
	Node<T>* p = static_cast<Node<T>*>(ptr);
	p -> _next = stack;
	stack = p;
}


//
//class Slist
//
template <typename T>
class Slist: public list<T>{
public:
	Slist();
	virtual	~Slist();

	int size() const;
	int curr_pos() const;
	T value() const;
	
	bool insert(const T& );
	bool append(const T& );
	
	bool empty() const;
	bool erase(const T& );
	bool erase_curr();
	void clear();
	
	void next();
	void move_to_start();
	void move_to(int);
protected:
	void remove_all();	
	
	int _size;
	Node<T>* head; // first input is head
	Node<T>* tail;  // secound input is tail
	Node<T>* curr;
};


template <typename T>
Slist<T>::Slist():_size(0)
{
        tail = curr = head = new Node<T>();
}

template <typename T>
Slist<T>::~Slist()
{
	remove_all();	
}

template <typename T>
void Slist<T>::remove_all()
{
	while(head != 0){
		curr = head;
		--_size;
		head = head -> _next;
		delete curr;
	}
}

template <typename T>
int Slist<T>::size() const
{
	return _size;
}

template <typename T>
int Slist<T>::curr_pos() const
{	
	int count = 0 ;
	Node<T>* temp = head;	
	for(temp; temp != curr ; ++count)
		temp = temp -> _next; 	
	return count;
}

template <typename T>
T Slist<T>::value() const 
{
	return curr -> _value;
}

template <typename T>
bool Slist<T>::insert(const T& val) 
{
	if(_size == 0){
		head -> _value = val;
		curr -> _next = new Node<T>();
		tail = curr -> _next;
	}
	else if(_size == 1) 
		tail -> _value = val;

	else if(curr_pos() == _size){
		append(val);
		return true;
	}
	else{
		Node<T>* new_node = new Node<T>(val, curr -> _next);
		curr -> _next = new_node;
		
	}
	++_size;
	return true;
}

template <typename T>
bool Slist<T>::append(const T& val)
{
	if(_size == 0){
		head -> _value = val;
		curr -> _next = new Node<T>();
		tail = curr -> _next;
	}
	else if(_size == 1)
		tail -> _value = val;
	else {
		Node<T>* new_node = new Node<T>(val);
		tail -> _next = new_node;
		tail = new_node;
	}
	++_size;
	return true;
}

template <typename T>
bool Slist<T>::empty() const
{
	return _size !=0 ? false : true;
}

template <typename T>
void Slist<T>::next()
{
	if(curr_pos() < _size)//(curr != tail)
		curr = curr -> _next;  
	else 
		std::cout<<"curr is tail"<<std::endl;
	
}

template <typename T>
void Slist<T>::move_to_start()
{
	curr = head;
}

template <typename T>
void Slist<T>::move_to(int m)
{
	int count = 0 ;
	if(m> _size){
		std::cout<<"wrong index"<<std::endl;
		return;
	}
	curr = head;
	while(count < m){
		curr = curr -> _next;
		++count;
	}
}

template <typename T>
bool Slist<T>::erase(const T& val)
{
	int pos = 0;
	curr = head;
	while( curr -> _next != 0){
		if( curr -> _value == val)
			break;
		++pos;
		curr = curr -> _next;
	}
	if( pos >= _size ){
		std::cout<<"wrong value for erase"<<std::endl;
		return false;
	}
	Node<T>* temp;
	if( pos == 0){
		temp = head;
		head = head -> _next;
	}
	else {
		move_to(pos);
		temp = curr;
		move_to(pos-1);
	 	curr -> _next = temp -> _next;
	}
	temp -> _next = Node<T> :: stack;
	Node<T> :: stack = temp;
	--_size;	
	return true;
}

template <typename T>
bool Slist<T>::erase_curr()
{
	Node<T>* temp = 0;
	int pos = curr_pos();
	if(pos >= _size){
		std::cout<<" wrong pos"<<std::endl;
		return false;	
	}
	if (pos == 0){
		temp = head;
		head = head -> _next;
	}
	else {
		move_to(pos);
		temp = curr;
		move_to(pos-1);
		curr -> _next = temp -> _next;
	}
	--_size;
	
	temp -> _next = Node<T> :: stack;
	Node<T> :: stack = temp;
	return true;
}

template <typename T>
void Slist<T>::clear()
{
	if( _size == 0)
		return;
	for( curr = head; curr -> _next == 0 ; curr = curr -> _next){
		
		curr -> _next = Node<T> :: stack;
		Node<T> :: stack = curr;
	}
	delete head;
	delete curr;
	delete tail;
	head = curr = tail = new Node<T>();
	_size = 0;
}

 
	
#endif

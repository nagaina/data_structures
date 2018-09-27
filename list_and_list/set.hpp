#ifndef _set_hpp_
#define _set_hpp_

#include "freelist.hpp"

//
// sorted list 
//

template <typename T >
class Set: public Slist<T>{
public:
	Set();
	virtual ~Set();
	bool insert(const T&);
	bool append(const T&); //can't insert at the end
	
	bool erase(const T&);	
	
	//int size() const;		
private:
	int _find_pos(const T& , int , int); 
//	typedef  Slist<T>::_size _size;
//	typedef  Slist<T>::head head;
//	typedef  Slist<T>::tail tail;
//	typedef  Slist<T>::curr curr;
	
};

template <typename T>
Set<T>::Set()
{
}

template <typename T>
Set<T>::~Set()
{
	Slist<T>::remove_all();	
}

template <typename T >
bool Set<T>::insert(const T& val)
{
	if(Slist<T>::_size == 0){
		Slist<T>::head ->_value = val;
		Slist<T>::head -> _next = new Node<T>();
		Slist<T>::tail = Slist<T>::head -> _next;	
	}
	else if(Slist<T>::_size == 1){
		if(val < Slist<T>::head -> _value){
			Slist<T>::tail -> _value = Slist<T>::head -> _value;
			Slist<T>::head -> _value = val;
		}
		else {
			Slist<T>::tail -> _value = val;
		}
	}
	else {
		int pos = _find_pos(val,0 ,Slist<T>::_size-1);
		if(pos == 0) {
			Node<T>* new_node = new Node<T>(val, Slist<T>::head);
			Slist<T>::head = new_node;
		}
	
		else if(pos < Slist<T>::_size){
			Slist<T>::move_to(pos);
			if(Slist<T>::curr -> _value > val)
				Slist<T>::move_to(pos-1);
			Node<T>* new_node = new Node<T>(val, Slist<T>::curr-> _next);
			Slist<T>::curr -> _next = new_node;
		}	
		else{ 
		 	if(Slist<T>::tail -> _value < val){
				Node<T>* new_node = new Node<T>(val, 0);
				Slist<T>::tail -> _next = new_node;
				Slist<T>::tail = new_node;
			}
			else{
				Slist<T>::move_to(pos-1);
				Node<T>* new_node = new Node<T>(val,Slist<T>::curr -> _next);
				Slist<T>::curr -> _next = new_node;
			}
		}
	}			
	
	++Slist<T>::_size;
	return true;
		
}

template <typename T >
bool Set<T>::append(const T& val)
{
	std::cout<<"can't use append "<<std::endl;
	return true;
}

template <typename T >
bool Set<T>::erase(const T& val)
{
	int first = 0, last = Slist<T>::_size -1;
	int pos = ( first + last) /2;
	while( first <= last){
		Slist<T>::move_to(pos);
		if(Slist<T>::curr -> _value < val)
			first = pos +1;
		else if(Slist<T>::curr -> _value == val){
			std::cout<<"find and removed"<<std::endl;
			Slist<T>::erase_curr();
			//--Slist<T>::_size;
			break;
		}
		else
			last = pos -1;
		pos = (first + last) / 2;
	}
	if(first > last)
		std::cout<<"incorect value"<<std::endl;
	return true;
}

template <typename T>
int Set<T>::_find_pos(const T& val , int first, int last)
{
	
	if(first >= last){
		Slist<T>::move_to(first);
		return val < Slist<T>::curr -> _value ? first : first +1;
	}
	int pos = (first + last) / 2;
	Slist<T>::move_to(pos);
	if(val == Slist<T>::curr -> _value)
		return pos+1;
	if(val< Slist<T>::curr -> _value)
		return _find_pos(val, first, pos-1) ;
	 return _find_pos(val, pos+1 , last);

}

#endif

#include <iostream>
#include "set.hpp"

template <typename T>
void _union(Slist<T>* a ,Slist<T>* b, Slist<T>* c)
{
	c -> clear();
	a -> move_to_start();
	while ( a -> curr_pos() != a -> size()){
		c -> insert(a -> value());
		a -> next();
	}

	int first = 0 , last = c -> size()-1;
	int pos = (first + last) /2;
	b-> move_to_start();
	while( b -> curr_pos() != b -> size()){
		first = 0 , last = c -> size()-1;
		pos = (first + last) /2;

		while(first <= last){
			c -> move_to(pos);
			if(c -> value() < b -> value())
				first = pos +1;
			else if(c -> value() == b -> value())
				break;
			else 
				last = pos -1;
			pos = (first + last) /2;
			}
		if(first > last) 
			c -> insert( b -> value());
		b -> next();
	}
		
	
}

template <typename T>
void intersection(Slist<T>* a, Slist<T>* b, Slist<T>* c)
{
	int first = 0, last = b ->size() - 1;
	int pos = (first + last) /2;
	a -> move_to_start();
	b -> move_to_start();
	c -> clear();
	while( a -> curr_pos() != a -> size()){
		first = 0, last = b ->size() - 1;
	 	pos = (first + last) /2;
		while( first <= last){
			b -> move_to(pos);
			if(b -> value() < a-> value())
				first = pos + 1;
			else if( b -> value() == a -> value()){
					c -> insert( b -> value());
					break;
			}
			else
				last = pos -1;
			pos = ( first + last)/2;
		}
		a -> next();
	}
	if( c -> size() == 0)
		std::cout<<"there is no intersection"<<std::endl;
}

int main()
{
	std::cout<<"enter size of A ->"<<std::endl;
	int n = 0;
	std::cin>>n;
	std::cout<<"enter values ->"<<std::endl;
	Slist<int>* set_a = new Set<int>();
	int x = 0;
	while( n!= 0){
		std::cin>>x;
		set_a -> insert(x);
		--n;
	} 
	std::cout<<"set A created"<<std::endl;
	std::cout<<"enter size of B ->"<<std::endl;
	std::cin>>n;
	std::cout<<"enter values - >"<<std::endl;
	Slist<int>* set_b = new Set<int>();
	while( n!=0){
		std::cin>>x;
		set_b -> insert(x);
		--n;
	}
	std::cout<<"set B created "<<std::endl;
	set_a -> move_to_start();
	while( set_a -> curr_pos() != set_a -> size()){
		std::cout<<"member in set A::"<<" "<<set_a -> value()<<std::endl;
		set_a -> next();
	}
	std::cout<<std::endl;
	set_b -> move_to_start();
	while( set_b -> curr_pos() != set_b -> size()){
		std::cout<<"member in set B::"<<" "<<set_b -> value()<<std::endl;
		set_b -> next();
	}

	Slist<int>* set_c = new Set<int>();
	_union(set_a , set_b , set_c );
	std::cout<<"Union is ->"<<std::endl;
	set_c -> move_to_start();
	while( set_c -> curr_pos() != set_c -> size()){
		std::cout<<"member in set C::"<<" "<<set_c -> value()<<std::endl;
		set_c -> next();
	}
	std::cout<<std::endl;
	intersection(set_a, set_b, set_c);
	std::cout<<"Intersection is ->"<<std::endl;
	set_c -> move_to_start();
	while( set_c -> curr_pos() != set_c -> size()){
		std::cout<<"member in set C::"<<" "<<set_c -> value()<<std::endl;
		set_c -> next();
	}

}


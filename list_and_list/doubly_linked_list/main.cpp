#include <iostream>
#include <conio.h>
#include "list.hpp"
int main()
{
	node Node1, Node2 , Node3 , Node4;
	std::cout<<"enter 4 integers"<<std::endl;
	std::cin>>Node1.number>>Node2.number>>Node3.number>>Node4.number;
    list ob;
	ob.push_back(Node1);
	ob.insert(Node2);
	ob.push_front(Node3);
	ob.push_back(Node4);
	std::cout<<"the first is  "<<ob.front()<<std::endl;
	std::cout<<"the last is  "<<ob.back()<<std::endl;
	std::cout<<"size is  "<<ob.getsize()<<std::endl;
	std::cout<<"erase function  "<<ob.erase(Node2)<<std::endl;
    getch();
	return 0;
}
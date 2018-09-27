#include "tree.hpp"
#include <fstream>

int main()
{
	RBtree<int> tree;
	
	int data = 0;
	std::fstream file("data.txt");
	if (file.is_open())
	{
		while (file >> data)
		{
			tree.insert(data);
			file.get();	
		}
		file.close();
	}
	tree.delete_node(7);
	tree.levelorder();

}

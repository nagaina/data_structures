#ifndef LIST_HPP
#define LIST_HPP
	struct node{
	node* Lptr;// left pointer
	node* Rptr; //right poiner
	int number; 
};
class list{
public:

	list(); 
	int getsize() const;
	void push_back(node& );//put behind
	void push_front(node&); //put in front
	int back() const; //return last elemenat of class->last node
    int front() const; //return first node
	void insert(node& );
    int erase(node& ); //for delete
private:
	void initial(node& ); //function for initiation if there is no element
	node* firstptr; //pointer to first node
	node* lastptr; //pointer to last node
	int size;
};
#endif

#include "list.hpp"

list::list()
{
	firstptr=0;
	size=0;
	lastptr=0;

}


void list::initial(node &ptr) //private function , it calls only when first and last pointers are 0
{
	node* new_ptr= new node();
	node* current_ptr=&ptr;
	//new_ptr->Rptr=current_ptr;
	new_ptr->Lptr=0;
	new_ptr->number=current_ptr->number;
	current_ptr=new_ptr;
	size++;
	firstptr=new_ptr;
	lastptr=new_ptr;

}

void list::insert(node &ptr )
{
	if(firstptr==0 && lastptr==0) 
		initial(ptr);
	if(firstptr=lastptr)
		push_back(ptr);
	else {
		node* new_ptr= new node();
		node* temp_ptr=&ptr;
	    node* current_ptr=temp_ptr->Rptr;
	    temp_ptr->Rptr=new_ptr;
		new_ptr->number=temp_ptr->number;
	    current_ptr->Lptr=new_ptr;
	    new_ptr->Lptr=temp_ptr;
	    new_ptr->Rptr=current_ptr;
		size++;
	}
}
void list::push_front(node &ptr)
{
	if(firstptr==0 && lastptr==0) 
		initial(ptr);
	else 
	{
		node* new_ptr=new node();
		node* temp_ptr=&ptr;
		firstptr->Lptr=new_ptr;
		new_ptr->Rptr=firstptr;
		new_ptr->number=temp_ptr->number;
		new_ptr->Lptr=0;
		firstptr=new_ptr;
		size++;
	}
}
void list::push_back(node &ptr)
{
	if(firstptr==0 && lastptr==0) 
		initial(ptr);
	else 
	{
		node* new_ptr=new node();
		node* temp_ptr=&ptr;
		lastptr->Rptr=new_ptr;
		new_ptr->Lptr=lastptr;
		new_ptr->number=temp_ptr->number;
		new_ptr->Rptr=0;
		lastptr=new_ptr;
		size++;
	}
}
int list::back() const
{
	return lastptr->number;
}
int list::front() const
{
	return firstptr->number;
}
int list::erase(node &ptr)
{
	if(firstptr==0 && lastptr==0)
		return 0; // there is no node for erase
  node* temp_ptr=&ptr;
  node* hold=firstptr;
  while(hold->Rptr!=0 )
  {
	  if(hold=temp_ptr)
	  {
		node*  prev_ptr=hold->Lptr;
		node* curr_ptr=hold->Rptr;
		prev_ptr->Rptr=curr_ptr;
		curr_ptr->Lptr=prev_ptr;
		delete  temp_ptr;
		size--;
      }
	  hold=hold->Rptr;
  } //while end
  if(hold->Rptr==0 && hold->number!=temp_ptr->number)
	  return size;
  else if(hold->Rptr==0 && hold->number==temp_ptr->number)
  { firstptr=0;
    lastptr=0;
	size=0;
	delete temp_ptr;
	
  }
  return size;
}
	
int list::getsize() const
{
	return size;
}




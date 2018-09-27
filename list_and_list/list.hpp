#ifndef _list_hpp_
#define _list_hpp_

//
// abstract list
//

template <typename T>
class list{
public:
	list( ) {}
	virtual ~list() {}
	
	virtual int size() const = 0;
	virtual int curr_pos() const = 0;
	virtual T value() const = 0;
	
	virtual bool insert(const T& ) = 0;
	virtual bool append(const T& ) = 0;
	
	virtual bool empty() const = 0;
	virtual bool erase(const T& ) = 0;
	virtual bool erase_curr() = 0;
	virtual void clear() = 0;
	
	virtual void next() = 0;
	virtual void move_to_start() = 0;
	virtual void move_to(int) = 0;
}; //end class list

#endif

//Vaughn Poulo
//CS202
//May 8, 2022
//Program 2

#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;


/////////////////////////////////////////
////////////////////////////////////////
//////////IMPLEMENT NODE CLASS 
////////////////////////////////////////
///////////////////////////////////////


//Constructor
template <typename TYPE>
node<TYPE>::node(const TYPE & newReservation)
{
	next = nullptr;
	previous = nullptr;
	data = newReservation;
}



//Returns next pointer.
template <typename TYPE>
node<TYPE> *  node<TYPE>::get_next()
{
	return next;
}



//Returns previous pointer.
template <typename TYPE>
node<TYPE> * node<TYPE>::get_previous()
{
	return previous;
}



//Returns if next pointer is not null.
template <typename TYPE>
bool node<TYPE>::has_next()
{
	if(next)
		return true;
	else
		return false;
}



//Returns if previous pointer is not null.
template <typename TYPE>
bool node<TYPE>::has_previous()
{
	if(previous)
		return true;
	else 
		return false;
}



//Sets the next pointer.
template <typename TYPE>
void node<TYPE>::set_next(node_ptr_dt next_ptr)
{
	next = next_ptr;
}



//Sets the previous pointer.
template <typename TYPE>
void node<TYPE>::set_previous(node_ptr_dt previous_ptr)
{
	previous = previous_ptr;
}




/////////////////////////////////////////
////////////////////////////////////////
//////////IMPLEMENT DLL CLASS 
////////////////////////////////////////
///////////////////////////////////////



//Constructor
template <typename TYPE>
DLL<TYPE>::DLL()
{
	head = nullptr;
	tail = nullptr;
}



//Destructor
template<typename TYPE>
DLL<TYPE>::~DLL()
{
	remove_all();
}



//Insert new node at beginning of list.
template <typename TYPE>
bool DLL<TYPE>::insert(const TYPE & toAdd)
{
	//Create new node.
	node<TYPE> * temp = new node<TYPE>(toAdd);

	//If list is empty, insert first node.
	if(!head)
	{
		head = temp;
		tail = temp;
		return true;
	}

	//If list is not empty, insert new node at beginning of list.
	temp->set_next(head);
	head->set_previous(temp);
	head = temp;

	return true;	
}



//Wrapper Function: remove matching node.
template <typename TYPE>
bool DLL<TYPE>::remove(char * guest_name)
{
	//If list is empty, return
	if(!head)
		return false;

	//If node to remove is first node
	if(head->data.reservation::operator==(guest_name))
	{
		head = head->get_next();
		delete head->get_previous();
		head->set_previous(nullptr);	
		return true;
	}	

	//If tail node is the one to remove.
	if(tail->data.reservation::operator==(guest_name))
	{
		tail = tail->get_previous();
		delete tail->get_next();
		tail->set_next(nullptr);
		return true;
	}

	//Recursive function
	return remove(head, guest_name);
}



//Recursive function: remove matching node
template <typename TYPE>
bool DLL<TYPE>::remove(node<TYPE> * & current, char * guest_name)
{
	bool is_deleted {false};

	//Base case: if end of list, return
	if(!current)
		return is_deleted;

	//If match found, delete.
	if(current->data.reservation::operator==(guest_name))
	{
		node<TYPE> * prev = current->get_previous();
		node<TYPE> * next = current->get_next();
		prev->set_next(next);
		next->set_previous(prev);
		delete current;
		current = prev;
		is_deleted = true;
		return is_deleted;
	}

	//Update pointer to next node
	current = current->get_next();

	//Recursive call
	is_deleted = remove(current, guest_name);

	return is_deleted;
}



//Wrapper function: remove all nodes
template <typename TYPE>
void DLL<TYPE>::remove_all()
{
	//If list is empty, return
	if(!head)
		return;

	//Recursive function call
	remove_all(head);

	return;
}



//Recursive function: remove all nodes.
template <typename TYPE>
void DLL<TYPE>::remove_all(node<TYPE> * & current)
{
	//Base Case: if list is empty, return
	if(!current)
		return;

	//Recursive call until at end of list
	current = current->get_next();
	remove_all(current);

	//Delete nodes on the way back.
	delete current;
	current = nullptr;

	return;
}



//Wrapper function: display matching node.
template <typename TYPE>
bool DLL<TYPE>::display(char * guest_name)
{
	//If list is empty, return
	if(!head)
		return false;

	//If node to display is first node
	if(head->data.reservation::operator==(guest_name))
	{
		cout << head->data;
		return true;
	}	

	//If tail node is the one to remove.
	if(tail->data.reservation::operator==(guest_name))
	{
		cout << tail->data;
		return true;
	}

	//Recursive function
	return remove(head, guest_name);
}



//Recursive function: display matching node.
template <typename TYPE>
bool display(node<TYPE> * current, char * guest_name)
{
	bool is_found {false};

	//Base case: if end of list, return
	if(!current)
		return is_found;

	//If match found, delete.
	if(current->data.reservation::operator==(guest_name))
	{
		cout << current->data;
		is_found = true;
		return is_found;
	}

	//Update pointer to next node
	current = current->get_next();

	//Recursive call
	is_found =  remove(current, guest_name);

	return is_found;
}



//Wrapper function: display all nodes.
template <typename TYPE>
void DLL<TYPE>::display_all()
{
	//If list is empty, return
	if(!head)
		return;

	//Recursive call
	display_all(head);

	return;
}



//Recursive function: display all nodes.
template <typename TYPE>
void DLL<TYPE>::display_all(node<TYPE> * current)
{
	//If at end of list, return.
	if(!current)
		return;

	//Display each node
	cout << current->data;

	//Recursice call
	display_all(current->get_next());

	return;
}


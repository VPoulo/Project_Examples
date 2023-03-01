//Vaughn Poulo
//CS202
//Program 1
//April 22, 2022
//These node functions are used by outside classes and 
//allow the manipulation of an animal instance. There are 
//three different nodes, 1 for each derived animal. Each node
//is dervived from a specific animal.

#include "node.h"


//Node for Penguin
//Constructor.
penguin_node::penguin_node(char name[]): penguin(name)
{
	//Set next pointer to null.
	next = nullptr;
}



//Destructor.
penguin_node::~penguin_node()
{
}



//Returns next pointer.
penguin_node * penguin_node::get_next()
{
	return next;
}



//Returns true if node has a non-null next pointer.
bool penguin_node::has_next()
{
	if(next != nullptr)
		return true;
	else
		return false;
}



//Sets the next pointer to animal passes in.
int penguin_node::set_next(penguin_node * nextNode)
{
	next = nextNode;

	return 1;
}



//Functions for kangaroo node.
//Constructor.
k_node::k_node(char name[]): kangaroo(name)
{
	//Set next pointer to null.
	next = nullptr;
}



//Destructor.
k_node::~k_node()
{
}



//Returns next pointer.
k_node * k_node::get_next()
{
	return next;
}



//Returns true if node has a non-null next pointer.
bool k_node::has_next()
{
	if(next != nullptr)
		return true;
	else
		return false;
}



//Sets the next pointer to animal passes in.
int k_node::set_next(k_node * nextNode)
{
	next = nextNode;

	return 1;
}



//Functions for horse node.
//Constructor.
h_node::h_node(char name[]): horse(name)
{
	//Set next pointer to null.
	next = nullptr;
}



//Destructor.
h_node::~h_node()
{
}



//Returns next pointer.
h_node * h_node::get_next()
{
	return next;
}



//Returns true if node has a non-null next pointer.
bool h_node::has_next()
{
	if(next != nullptr)
		return true;
	else
		return false;
}



//Sets the next pointer to animal passes in.
int h_node::set_next(h_node * nextNode)
{
	next = nextNode;

	return 1;
}





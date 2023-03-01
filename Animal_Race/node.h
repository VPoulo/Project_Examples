//Vaughn Poulo
//CS202
//Program 1
//April 22, 2022
//Each node is derived from a specific animal. The node
//points to another instance of the same type of animal, 
//allowing several data structures to be used. 

#pragma once 
#include "animal.h"


//Node derived from penguin.
class penguin_node: public penguin {
	public:
		penguin_node(char []);
		~penguin_node();
		penguin_node * get_next();
		bool has_next();
		int set_next(penguin_node *);
	
	private:
		penguin_node * next;
};



//Node derived from kangaroo.
class k_node: public kangaroo {
	public:
		k_node(char []);
		~k_node();
		k_node * get_next();
		bool has_next();
		int set_next(k_node *);
	
	private:
		k_node * next;
};


//Node derived from horse.
class h_node: public horse {
	public:
		h_node(char []);
		~h_node();
		h_node * get_next();
		bool has_next();
		int set_next(h_node *);
	
	private:
		h_node * next;
};

//Vaughn Poulo
//CS202
//Program 3
//May 23, 2022
//This class should be used when needing to store
//different concepts and the derviced classes. The
//tree class is a balanced 2-3 tree that supports
//insertion, removal, display, and other functions
//of the derived classes from the concept class.
//The 2-3 tree consists of nodes, which point
//to the abstract base class, concept, in concept.h.


#include "concept.h"
#include <string>

//Node for a balanced 2-3 tree.
class node23 
{
	public:
		friend class tree;
		node23();
		~node23();

	private:
		concept * leftData;
		concept * middleData;
		concept * rightData;
		node23 * child1;
		node23 * child2;
		node23 * child3;
		node23 * child4;
}; 


		
//This is a balanced 2-3 tree.
class tree
{
	public:
		tree();															//Constructor.
		~tree();														//Destructor.
		int insert(char);												//Wrapper function to add concept.
		void displayAll();												//Wrapper function to display all concepts.
		void removeAll();												//Wrapper to delete all nodes in tree.
		void changeRating(string);										//Wrapper to change the description of a concept.
		void addMethod(string);											//Wrapper to add method to STL Syntax or Python Library. -- RTTI used.
		void selectConcept(string);										//Wrapper to display URL of conceot.

	private:
		int insert(node23 *, node23 *, concept *);						//Recursive function to add concept.
		void displayAll(node23 *);										//Recursive function to display all concepts.
		void removeAll(node23 *);										//Removes all nodes recursively.
		int changeRating(node23 *, string);								//Recursice function to change description.
		int addMethod(node23 *, string, bool &);						//Adds a method to concept vector.  --RTTI used.
		void createConcept(char, concept * &);							//Creates instance of concept class.
		int addDataToNode(node23 *, concept *);							//Add data to correct node.
		void sortNodes(node23 *);										//Sorts children nodes.
		void rearrangeChildren(node23 *, node23 *, int);				//Arranges children of 2-3 tree after split.
		void addNodeToRoot(node23 *, node23 *);							//Adds node to the top of tree when needed. 
		int selectConcept(node23 *, string);							//Recursicve function to display URL of concept.
		int downcastConcept(concept *);								//Attemps to downcast pointer and add method to concept.  --RTTI used.
		node23 * root;													//Pointer to root node.
};


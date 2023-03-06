//Vaughn Poulo
//CS202
//Program 3
//May 23, 2022
//The tree class had a balanced 2-3 tree data structure. The structure
//contains nodes, which point to the concept base class. The tree class
//supports the removal, addition, display of instances of the concept class
//and its derived classes. Dynamic binding is used to call functions in the
//derived classes. The add method function is only applicable to two of the
//three derived classes. Therefore, RTTI is used to determine if downcasting
//is possible.

#include "tree.h"


//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//NODE CLASS
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

//Constructor.
node23::node23()
{
	leftData = nullptr;
	middleData = nullptr;
	rightData = nullptr;
	child1 = nullptr;
	child2 = nullptr;
	child3 = nullptr;
	child4 = nullptr;
}



//Destructor.
node23::~node23()
{
}



//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//TREE CLASS
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////


//Constructor.		
tree::tree()
{
	root = nullptr;
}



//Destructor.
tree::~tree()
{
	removeAll(root);
}



//Creates instance of class chosen by user and returns
//pointer to that class.
void tree::createConcept(char conceptChoice, concept * & temp)
{
	//Create instance of class chosen by user.
	switch(conceptChoice)
	{
		case 'A':
			temp = new stl_syntax;
			break;
		case 'B':
			temp = new modern_concept;
			break;
		case 'C':
			temp = new python_library;
			break;
	}

	temp->getInformation();

	return;
}



//Wrapper function to add concept.
int tree::insert(char conceptChoice)
{
	//Create new instance of class.
	concept * newData = nullptr;
	createConcept(conceptChoice, newData);

	//Create helper pointers. 
	concept * temp = nullptr;
	node23 * parent = nullptr;
	
	//If no nodes exist, create one and add data;
	if(!root)
	{
		root = new node23;
		root->leftData = newData;
		return 1;
	}
	
	//Call recursive function.
	int retval = insert(root, parent, newData);
	return retval;
}



//Recursive function to add concept.
int tree::insert(node23 * current, node23 * parent, concept * toAdd)
{
	//Base Case #1: past leaf node and pointer is null (nothing to do).
	if(!current)
		return 0;

	//Base Case #2: If at leaf node, insert new data directly.	
	if(!current->child1 && !current->child2 && !current->child3)
		addDataToNode(current, toAdd);
	
	//Traverse
	else
	{
		//Check if node has two data values
		if (current->leftData && current->rightData)
		{
			//If less than leftData
			if (*toAdd < *(current->leftData))
				insert(current->child1, current, toAdd);

			//If greater than leftData and less than rightData
			else if (*toAdd > *(current->leftData) && *toAdd < *(current->rightData))
				insert(current->child2, current, toAdd);

			//If greater than rightData
			else if (*toAdd > *(current->rightData))
				insert(current->child3, current, toAdd);
		}

		//If node only has left data value.
		else if (current->leftData && !current->rightData)
		{
			if (*toAdd < *(current->leftData))
				insert(current->child1, current, toAdd);

			else if (*toAdd > *(current->leftData))
				insert(current->child3, current, toAdd);
		}
	}

	//Post Recussion.
	//If middle data item exists, we need to split the node and push the middle data to the parent.
	if(current->middleData)
	{
		//Check for already being at the top of the tree.
		if (!parent)
			parent = root = new node23;
	
        //Add the middle data to the parent and track where in the parent the data was added.
		int location = addDataToNode(parent, current->middleData);
		current->middleData = nullptr;

        //A generic child pointer to point to child node where we took middle data from.
        node23 * childPtr = nullptr;
        
        //Arrange tree depnding on which child node needs to be split.
        if(location == 0) //Add new node to root.
            addNodeToRoot(parent, current);
        
        //Arrange children.
        if(location > 0)
            rearrangeChildren(parent, current, location);
        
		return 1;
	}
		
	return 0;
}


//Adds node to top of tree when needed.
void tree::addNodeToRoot(node23 * parent, node23 * current)
{
	parent->child1 = current;   //Attach parent to tree.
	parent->child3 = new node23;	//Make a new node to split current node.
	parent->child3->leftData = current->rightData;	//Take greater data and add to parent child 3, splitting the node.
	current->rightData = nullptr; 	//Delete data as it was split and moved into another node.

	//Rearrange Children of current node.
	parent->child3->child1 = current->child3;
	current->child3 = nullptr;
	parent->child3->child3 = current->child4;
	current->child4 = nullptr;
	current->child3 = current->child2;
	current->child2 = nullptr;
    return;
}



//Arranges children of node that is being split.
void tree::rearrangeChildren(node23 * parent, node23 * current, int location)
{
	//Create a new node in order to split full node.
    node23 * childPtr = nullptr;
    node23 * newnode = new node23;

	newnode->leftData = current->rightData;	//Fill new node.
	current->rightData = nullptr;	//Remove data from old node.
	parent->child4 = newnode;	//Attach new node in temporary 4th child spot.
	sortNodes(parent);		//Sort the 4th node in correct alphabetical order.

    if (location == 1) //Rearrange smallest child.
        childPtr = parent->child2;
    else if(location == 2) //Rearrange middle child.
        childPtr = parent->child3;
    else if(location == 3) //Rearrange largest child.
    {
        if(!parent->child4)      
            childPtr = parent->child3;
        else 
            childPtr = parent->child4;
    }

	//Arrange the children of split node correctly.
	childPtr->child1 = current->child3;
	current->child3 = nullptr;
	childPtr->child3 = current->child4;
	current->child4 = nullptr;
	current->child3 = current->child2;
	current->child2 = nullptr;

    return;
}



//Sorts children nodes of parent, when a node splits.
void tree::sortNodes(node23 * parent)
{
	//Holds onto nodes for rearranging pointers.
	node23 * nodeHolder = nullptr;

	//If child2 is null, then we only have 3 children nodes.
	if(!parent->child2)
	{
		//Should child 4 be child 2.
		if(*(parent->child4->leftData) < *(parent->child3->leftData))
		{
			parent->child2 = parent->child4;
			parent->child4 = nullptr;
			return;
		}

		//Child 4 should be child 3.
		parent->child2 = parent->child3;
		parent->child3 = parent->child4;
		parent->child4 = nullptr;
		return;
	}

	//If child4 should be child2
	if(*(parent->child4->leftData) < *(parent->child2->leftData))
	{
		nodeHolder = parent->child2;
		parent->child2 = parent->child4;
		parent->child4 = parent->child3;
		parent->child3 = nodeHolder;
		return;
	}

	//If child4 should be child3
	if(*(parent->child4->leftData) < *(parent->child3->leftData))
	{
		nodeHolder = parent->child3;
		parent->child3 = parent->child4;
		parent->child4 = nodeHolder;
		return;
	}
	
	return;
} 



//Return value is 1,2,3 for putting data in left,middle,right.
//0 means putting data in an empty node.
int tree::addDataToNode(node23 * current, concept * toAdd)
{
	//Check if node is empty.
	if (!current->leftData)
	{
		current->leftData = toAdd;
		return 0;
	}

	//Check if node contains one value.
	if(!current->rightData)
	{
		//New Data is smaller.
		if(*toAdd < *(current->leftData))
		{
			current->rightData = current->leftData;
			current->leftData = toAdd;
			return 1;
		}

		//New Data is bigger than or equal to.
		if(*toAdd >= *(current->leftData))
		{
			current->rightData = toAdd;
			return 3;
		}
	}

	//Node contains two values.
	//Smaller
	if(*toAdd < *(current->leftData))
	{
		current->middleData = current->leftData;
		current->leftData = toAdd;
		return 1;
	}

	//Inbetween
	if(*toAdd > *(current->leftData) && *toAdd < *(current->rightData))
	{
		current->middleData = toAdd;
		return 2;
	}

	//Greater
	if(*toAdd > *(current->rightData))
	{
		current->middleData = current->rightData;
		current->rightData = toAdd;
		return 3;
	}
	
	return -1;
}



//Wrapper function to display all concepts.
void tree::displayAll()
{	
	try
	{
		if(!root)
			throw "Root Null";
	}
	catch(char const *)
	{
		cout << endl << "Nothing to display." << endl;
	}

	displayAll(root);

	return;
}



//Recursive function to display all concepts.
void tree::displayAll(node23 * current)
{
	//If past leaf, return;
	if(!current)
		return;

	//Traverse to child 1.
	displayAll(current->child1);

	//Display left data, if exists..
	if(current->leftData)
		current->leftData->display();

	//Traverse to child 2
	displayAll(current->child2);

	//Display right node, if exists.
	if(current->rightData)
		current->rightData->display();

	//Traverse to child 3
	displayAll(current->child3);

	return;
}



//Wrapper function to delete all nodes.
void tree::removeAll()
{
	//If root is null, output that tree is emtpy.
	try
	{
		if(!root)
			throw "Tree Empty";
	}
	catch(char const *)
	{
		cout << endl << "No concepts to remove." << endl;
		return;
	}
	
	//Recursive call
	removeAll(root);	

	root = nullptr;

	return;
}



//Recursive function to delete all nodes.
void tree::removeAll(node23 * current)
{
	//Base case, if current is null, return;
	if(!current)
		return;

	//Traverse
	removeAll(current->child1);
	removeAll(current->child2);
	removeAll(current->child3);

	//Remove node
	delete current;	

	return;
}



//Wrapper function to change the rating of a concept.
void tree::changeRating(string keyword)
{
	int retVal;

	//If root is null, throw an error.
	try
	{
		if(!root)	
			throw "Empty Tree";
	}
	catch (char const *)
	{
		cout << endl << "No concepts exist yet." << endl;
	}

	//Call recursive function. If no match found, throw error.
	try
	{
		retVal = changeRating(root, keyword);

		if(retVal == 0)
			throw "No Match Found";
		else
			throw "Success";
	}
	catch(char const * msg)
	{
		if(msg == "No Match Found")
			cout << endl << "No match was found.";
		else
			cout << endl << "Success.";
	}
	
	return;
}



//Recursive function to change rating of a concept.
int tree::changeRating(node23 * current, string keyword)
{
	int count = 0;

	//Base case: if current is null, return.
	if(!current)
		return 0;

	//Traverse
	count += changeRating(current->child1, keyword);
	count += changeRating(current->child2, keyword);
	count += changeRating(current->child3, keyword);

	//Check if node is a match
	if(*(current->leftData) == keyword)
	{
		current->leftData->changeRating();
		current->leftData->display();
		++count;
	}	

	//Check right data if exists
	if(current->rightData)
	{
		//Compare right data for match,
		if(*(current->rightData) == keyword)
		{
			current->rightData->changeRating();
			current->rightData->display();
			++count;
		}
	}

	return count;
}



//Wrapper function to add method to STL Syntax Concept or Python Library Concept.
void tree::addMethod(string keyword)
{
	int retVal = 0;
	bool matchFound = false;

	//If root is null, throw an error.
	try
	{
		if(!root)	
			throw "Empty Tree";
	}
	catch (char const *)
	{
		cout << endl << "No concepts exist yet." << endl;
	}

	//Call recursive function. If no match found, throw error.
	try
	{
		retVal = addMethod(root, keyword, matchFound);

		if(retVal >= 1)
			throw "Success";
		if(matchFound == false)
			throw "No Match";
	}
	catch(char const * msg)
	{
		if(msg == "Success")
			cout << endl << "Success." << endl;
		else
			cout << endl << "No match found" << endl;
	}

	return;
}



//Recursive function to add method to STL Syntac Concept or Python Library Concept.
int tree::addMethod(node23 * current, string keyword, bool & matchFound)
{
	int count = 0;
	bool success = false;

	//Base case: if current is null, return.
	if(!current)
		return 0;

	//Traverse
	count += addMethod(current->child1, keyword, matchFound);
	count += addMethod(current->child2, keyword, matchFound);
	count += addMethod(current->child3, keyword, matchFound);

	//Check if node is a match
	if(*(current->leftData) == keyword)
	{
		count = downcastConcept(current->leftData);
		matchFound = true;
	}

	//Check right data if exists
	if(current->rightData)
	{
		if(*(current->rightData) == keyword)
		{
			count = downcastConcept(current->rightData);
			matchFound = true;
		}
	}

	return count;
}

int tree::downcastConcept(concept * ptr)
{
	int count = 0;

	try
	{
		//RTTI - determine if downcast to STL Syntax is possible..	
		stl_syntax * stl_ptr = dynamic_cast<stl_syntax *>(ptr);	//Try downcasting.

		if(stl_ptr)	//Check if downcasting was successful
		{
			stl_ptr->addMethod(); //Add method to concept.
			stl_ptr->display();
			++count;
		}

		//RTTI - determine if downcast to Python Library is possible.
		python_library * py_ptr = dynamic_cast<python_library *>(ptr);	//Try downcasting.

		if(py_ptr)
		{
			py_ptr->addMethod();	//Add method to concept.
			py_ptr->display();
			++count;
		}

		//Throw error if downcasting not possible.
		if(!stl_ptr && !py_ptr)
			throw "downcasting unsuccessful";
	}
	catch(char const *)
	{
		cout << endl << "Unable to add method to that type of concept." << endl; 						
	}
	
	return count;
}



//Returns URL of concept selected.
void tree::selectConcept(string keyword)
{
	int retVal = 0;

	//If root is null, throw an error.
	try
	{
		if(!root)	
			throw "Empty Tree";
	}
	catch (char const *)
	{
		cout << endl << "No concepts exist yet." << endl;
	}

	//Call recursive function. If no match found, throw error.
	try
	{
		retVal = selectConcept(root, keyword);

		if(retVal == 0)
			throw "No Match Found";
		else
			throw "Success";
	}
	catch(char const * msg)
	{
		if(msg == "No Match Found")
			cout << endl << "No match was found.";
		else
			cout << endl << "Success.";
	}
	
	return;
}


int tree::selectConcept(node23 * current, string keyword)
{
	int count = 0;

	//Base case: if current is null, return.
	if(!current)
		return 0;

	//Traverse
	count += changeRating(current->child1, keyword);
	count += changeRating(current->child2, keyword);
	count += changeRating(current->child3, keyword);

	//Check if node is a match
	if(*(current->leftData) == keyword)
	{
		current->leftData->select();
		++count;
	}	

	//Check right data if exists
	if(current->rightData)
	{
		//Compare right data for match,
		if(*(current->rightData) == keyword)
		{
			current->rightData->select();
			++count;
		}
	}

	return count;
}


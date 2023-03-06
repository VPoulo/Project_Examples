//Vaughn Poulo
//March 1, 2022
//Program 4
//CS163
//Each recursive functions has a wrapper function that calls it. This is to
//make sure the client application does not see or have access to the data structure.
//The wrapper functions will take either a itemNode struct or a character array as
//an arugment. The itemNode is a client node that contains all the information
//regarding the item, but has no pointers. The class node, call bstNode, has pointers.
//Each BST node has a right and left pointer. The return number of the function indicates
//the success or failure of the function. This allows the client application to display
//an appropraite message to the user.


#include "bst.h"
using namespace std;

//Constructor
bstClass::bstClass()
{
	root = nullptr;
}



//Destructor.
bstClass::~bstClass()
{
	//Recursive function to delete BST.
	deleteBST(root);
}



//Wrapper function to add vertex to BST.
int bstClass::insertItem(itemNode & toAdd)
{
	int isSuccess {0}; //Tracks success of recursive function.

	//Make new bstNode to be added.
	bstNode * temp = new bstNode;

	//copy itemNode into a bstNode
	copyToBSTNode(toAdd, temp); 

	//Call recursive function
	isSuccess = insertItem(root, temp);

	//Set temp pointer to null.
	temp = nullptr;

	return isSuccess;
}



//recursive function to add vertex to BST.
int bstClass::insertItem(bstNode * & root, bstNode * toAdd)
{
	//Base Case: If root is null, or at bottom of BST.
	if(!root)
	{
		root = toAdd;
		return 1;
	}

	//Test if data is less than or greater than root data.
	//If less than, traverse to the left.
	if(strcmp(toAdd->keyword, root->keyword) < 0)
		insertItem(root->left, toAdd);

	//if greater than or equal to, traverse to the right.
	else if(strcmp(toAdd->keyword, root->keyword) >= 0)
		insertItem(root->right, toAdd);

	return 1;
}



//This function displays one bstNode
void bstClass::displayOne(bstNode * node)
{
	cout << endl;
	cout << "Name: " << node->keyword << endl;
	cout << "Description: " << node->desc << endl;
	cout << "Type of Game: " << node->gameType << endl;
	cout << "Platform: " << node->platform << endl;
	cout << "Rating: " << node->rating << endl;
}



//Wrapper function that calls recursive function to display all nodes in BST.
int bstClass::displayAll()
{
	int countPrinted {0}; 	//Catches number of nodes printed for return value.

	//If BST is empty, return.
	if(!root)
		return 5;

	countPrinted =  displayAll(root);

	if(countPrinted > 0)
		return 1;
	else
		return 0;
}



//Recursively prints BST in order and returns count of nodes printed.
int bstClass::displayAll(bstNode * & root)
{
	int counter {0}; 	//Tracks the number of nodes printed

	//Base Case: If root is null, then we are at a leaf and should return.
	if(!root)
		return 0;

	//Traverse left.
	counter +=	displayAll(root->left);
	++counter;

	//Print node
	displayOne(root);

	//Traverse right
	counter += displayAll(root->right);
	
	return counter;
}



//Wrapper function to display matching node in BST.
int bstClass::displayMatch(char toFind[])
{
	int count {0};		//Catched count returned from recursive function.

	//Check if root is null.
	if(!root)
		return 5;

	//Call recursive function.
	count = displayMatch(root, toFind);

	if(count > 0)
		return 1;
	else
		return 4;

}



//Recursive function to display matching node in BST.
int bstClass::displayMatch(bstNode * & root, char toFind[])
{
	int valueCompare {0};	//Variable to hold comparison of toFind and root value.
	int count{0};			//Counts matches found.

	//Base Case: If root is null, or at leaf, return.
	if(!root)
		return 0;

	//Compare root value with toFind value.
	valueCompare = strcmp(toFind, root->keyword);

	//Base Case:  Root matches value toFind.
	if(valueCompare == 0)
	{
		displayOne(root);
		++count; 
		return 1;
	}

	//Case: toFind value is less than root.
	if(valueCompare < 0)
	{
		count += displayMatch(root->left, toFind);
	}
	//Case: toFind value is greater than root.
	else if(valueCompare > 0)
	{
		count += displayMatch(root->right, toFind);
	}

	return count;
}



//Wrapper function that retrieves matching info based on Name
//and stores the data in a struct for the client application.
int bstClass::retrieve(char toFind[], itemNode & clientNode)
{
	int count {0};	//Holds count returned by recursive function.

	//If BST is empty, return.
	if(!root)
		return 5;

	//Call recursive function
	count = retrieve(root, toFind, clientNode);

	if(count > 0)
		return 1;
	else
		return 4;

}



//Recursive function that finds the correct node and stores info in struct for client.
int bstClass::retrieve(bstNode * & root, char toFind[], itemNode & clientNode)
{
	int valueCompare {0};	//Holds the value of the toFind and root keyword comparison.
	int count {0};			//Tracks if match is found.

	//Base Case: if root is null
	if(!root)
		return 0;

	//Compare root value with toFind value.
	valueCompare = strcmp(toFind, root->keyword);

	//Base Case:  Root matches value toFind.
	if(valueCompare == 0)
	{
		copyToItemNode(clientNode, root);
		++count;
		return 1;
	}

	//Case: toFind value is less than root.
	if(valueCompare < 0)
	{
		count += retrieve(root->left, toFind, clientNode);
	}
	//Case: toFind value is greater than root.
	else if(valueCompare > 0)
	{
		count += retrieve(root->right, toFind, clientNode);
	}
	
	return count;
}



//Deletes dynamic memory of one node.
int bstClass::deleteDynamicMemory(bstNode * node)
{
	delete [] node->keyword;
	delete [] node->desc;
	delete [] node->gameType;
	delete [] node->platform;
	node->left = nullptr;
	node->right = nullptr;
	
	return 1;
}



//Recursive function to delete all nodes in BST. Used in destructor. (postorder traversal).
int bstClass::deleteBST(bstNode * & root)
{
	int count {0};	//Variable to count number of nodes deleted.

	//Base Case: root is null
	if(!root)
		return 5;

	//Traverse left
	count += deleteBST(root->left);
	
	//Traverse right
	count += deleteBST(root->right);

	//Increase count
	++count;

	//Delete node contents and then node itself.
	deleteDynamicMemory(root);
	delete root;
	root = nullptr;

	//If nodes deleted, return success.
	if(count > 0)
		return 1;
	else
		return 0;
}



//Wrapper function that displays all equitment matched by type.
int bstClass::displayType(char toFind[])
{
	int count {0}; 	//Catches return value.

	//If BST is empty, return.
	if(!root)
		return 5;

	//Call recursive function.
	count = displayType(root, toFind);

	if(count > 0)
		return 1;
	else
		return 4;

}



//Recursive function that displays all nodes matching type of game. (Preorder Traversal).
int bstClass::displayType(bstNode * & root, char toFind[])
{
	int count {0};				//Trakcs number of matches found.
	int valueCompare {0};		//Stores output of strcmp.
	
	//Base Case: If root is null, return.
	if(!root)
		return 0;

	//Compare root type and toFind value.
	valueCompare = strcmp(toFind, root->gameType);
	
	//Check root
	if(valueCompare == 0)
	{
		displayOne(root);
		++count;
	}

	//Traverse Left
	count += displayType(root->left, toFind);

	//Traverse Right
	count += displayType(root->right, toFind);
	
	return count;
}



//Deletes node when the node is a leaf.
int bstClass::deleteLeaf(bstNode * & root)
{
	//Delete dynamic memory.
	deleteDynamicMemory(root);

	//Delete leaf.
	delete root;
	
	//Set pointer to null.
	root = nullptr;

	return 1;
}



//Deletes internal node when it has a left leaf only.
int bstClass::deleteInternalNodeLeftLeaf(bstNode * & root)
{
	//Temporary pointer to hold onto node.
	bstNode * hold = nullptr;

	//Hold onto child node.
	hold = root->left;	
	
	//Delete dynamic memory, delete node, and rearrange node pointers.
	deleteDynamicMemory(root);
	delete root;
	root = hold;
	hold = nullptr;

	return 1;
}



//Deletes an internal node when it has a right leaf only.
int bstClass::deleteInternalNodeRightLeaf(bstNode * & root)
{
	//Temporary pointer to hold onto node.
	bstNode * hold = nullptr;

	//Hold onto child node.
	hold = root->right;
	
	//Delete dynamic memory, delete node and rearrange pointers.
	deleteDynamicMemory(root);
	delete root;
	root = hold;
	hold = nullptr;

	return 1;
}



//Deletes internal node when it has two children nodes and
//right node has a left child.
int bstClass::deleteInternalNodeIOS(bstNode * & root)
{
	bstNode * hold = nullptr;		//Holds onto IOS.
	bstNode * parent = nullptr;		//Holds onto parent of IOS.

	//Set pointer to right child of node to be deleted.
	hold = root->right;

	//Case: right child doesn't have a left node. IOS is right child.
	if(hold->left == nullptr)
	{
		//Copy IOS into root.
		copyBSTNode(hold, root);
	
		//Connect root around IOS.
		root->right = hold->right;		

		//Delete IOS.
		deleteDynamicMemory(hold);
		delete hold;

		//Set pointer to null
		hold = nullptr;

		return 1;
	}

		
	//Case: right child has a left node.
	//Traverse to left most child to find IOS.
	while(hold->left)
	{
		parent = hold;
		hold = hold->left;
	}

	
	//Copy IOS node into node to be deleted.
	//This replaces node with IOS.
	copyBSTNode(hold, root);

	//Hold onto child of IOS.
	hold = hold->right;
	parent->left = hold;

	//Delete IOS from original spot
	deleteDynamicMemory(hold);
	delete hold;

	//Set pointers to null
	hold = nullptr;
	parent = nullptr;

	return 1;
}



//Wrapper function to remove a node based on matching name.
int bstClass::deleteMatchingNode(char toFind[])
{
	//If BST is null, return.
	if(!root)
		return 5;

	//Call recursive function.
	return deleteMatchingNode(root, toFind);
}



//Recursive function that deletes BST node matching value passed in.
int bstClass::deleteMatchingNode(bstNode * & root, char toFind[])
{
	int count {0}; 				//Counts number of nodes deleted.
	int valueCompare {0};		//Stores value of strcmp.
	
	//Base Case: Root is null
	if(!root)
		return 0;

	//Compare root keyword and toFind value
	valueCompare = strcmp(toFind, root->keyword);

	//If match is found, remove node.
	if(valueCompare == 0)
	{

		//If match found at leaf.
		if(root->right == nullptr && root->left == nullptr)
			deleteLeaf(root);

		//Internal node with 1 left node, no right node.
		else if(root->right == nullptr && root->left != nullptr)
			deleteInternalNodeLeftLeaf(root);

		//Internalnode with 1 right node, no left node.
		else if(root->right != nullptr && root->left == nullptr)
			deleteInternalNodeRightLeaf(root);

		//Internal node with 2 children.
		else if(root->right != nullptr && root->left != nullptr)
			deleteInternalNodeIOS(root);

		//Increase count
		++count;		
	}

	//If value is less than, traverse left.
	if(valueCompare < 0)
		count += deleteMatchingNode(root->left, toFind);

	//If value is greater than, traverse right.
	if(valueCompare > 0)
		count += deleteMatchingNode(root->right, toFind);

	//If at least one node deleted, return success.
	if(count > 0)
		return 1;
	else
		return 4;
}



//Copies info from one BST node to another.
void bstClass::copyBSTNode(bstNode * copyFrom, bstNode * & copyTo)   // FIX THIS TO REALLOCATE DYNAMIC MEMORY TO CORRECT SIZE.
{
	//Delete dynamic memory in destination struct.
	delete [] copyTo->keyword;
	delete [] copyTo->desc;
	delete [] copyTo->gameType;
	delete [] copyTo->platform;

	//Allocate dynamic memory.
	copyTo->keyword = new char[strlen(copyFrom->keyword) + 1];
	copyTo->desc = new char[strlen(copyFrom->desc) + 1];
	copyTo->gameType = new char[strlen(copyFrom->gameType) + 1];
	copyTo->platform = new char[strlen(copyFrom->platform) + 1];

	//Copy over data.
	strcpy(copyTo->keyword, copyFrom->keyword);
	strcpy(copyTo->desc, copyFrom->desc);
	strcpy(copyTo->gameType, copyFrom->gameType);
	strcpy(copyTo->platform, copyFrom->platform);
	copyTo->rating = copyFrom->rating;
}



//Copies itemNode Struct info into bstNode struct.
void bstClass::copyToBSTNode(itemNode & copyFrom, bstNode * copyTo)
{
	//Initialize dynamic memory in class node.
	copyTo->keyword = new char[strlen(copyFrom.keyword) + 1];
	copyTo->desc = new char[strlen(copyFrom.desc) + 1];
	copyTo->gameType = new char[strlen(copyFrom.gameType) + 1];
	copyTo->platform = new char[strlen(copyFrom.platform) + 1];

	//Copy over information from client node to class node.
	strcpy(copyTo->keyword, copyFrom.keyword);  
	strcpy(copyTo->desc, copyFrom.desc);
	strcpy(copyTo->gameType, copyFrom.gameType);
	strcpy(copyTo->platform, copyFrom.platform);
	copyTo->rating = copyFrom.rating;

	//Set pointer to null
	copyTo->right = nullptr;
	copyTo->left = nullptr;
}



//Copies bstNode struct info into itemNode struct.
void bstClass::copyToItemNode(itemNode & copyTo, bstNode * copyFrom)
{
	//Copy info from hashNode to itemNode.
	strcpy(copyTo.keyword, copyFrom->keyword);
	strcpy(copyTo.desc, copyFrom->desc);
	strcpy(copyTo.gameType, copyFrom->gameType);
	strcpy(copyTo.platform, copyFrom->platform);
	copyTo.rating = copyFrom->rating;
}


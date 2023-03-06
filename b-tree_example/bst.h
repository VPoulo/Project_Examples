//Vaughn Poulo
//March 1, 2022
//Program 4
//CS163
//This class allows the client application to add, display, retrieve,
//and delete items from the has table. The public functions take character
//arrays to search for that value, or an itemNode which has no pointer. Each
//of the public functions returns an integer value which can be mapped to
//a successful or unsuccessful executution of the function. 1 always means
//the functionw as successful. This class should be used when the application
//should store data based on a keyword value. The data is not sorted.

//Preprocessor Directives
#include <cctype>
#include <cstring>
#include <iostream>

//Struct definition
//This struct is the same as in the client application but with
//left and right pointers so can be a BST.
struct bstNode {
	char * keyword;
	char * desc;
	char * gameType;
	char * platform;
	int rating;
	bstNode * left;
	bstNode * right;
};

//Struct definition for client application to use.
struct itemNode {
	char keyword[100];
	char desc[200];
	char gameType[100];
	char platform[100];
	int rating;
};

class bstClass
{
	public:
		bstClass();											//Constructor to initialize all variables.
		~bstClass();										//Destructor to delete all dynamic memory.
		int insertItem(itemNode &);							//Wrapper function to add  electronics item to BST.
		int displayAll();									//Wrapper function to display BST in sorted order. 
		int displayMatch(char []);							//Wrapper function to display matching node in BST.
		int retrieve(char [], itemNode &);					//Wrapper function to retrieve matching info based one name.
		int deleteMatchingNode(char []);					//Wrapper function to delete node matching name passed in.
		int displayType(char []);							//Wrapper function that displays all nodes matching type of game.

	private:
		int insertItem(bstNode * &, bstNode *);				//Recursive function to add data to bst.
		int displayAll(bstNode * &);						//Recursive function to display all nodes in sorted order (inorder traversal).
		int displayMatch(bstNode * &, char []);				//Recursive function to display matching node.
		int retrieve(bstNode * &, char [], itemNode &);		//Recursive function to retrieve and store matching data in node for client.
		int deleteMatchingNode(bstNode * &, char []);		//Recursive function that finds and deletes node matching name passed in.
		int displayType(bstNode * &, char []);				//Recursive function that displays all nodes matching type of game.
		int deleteBST(bstNode * &);							//Recursive function to delete all nodes in BST. Used in destructor.
		int deleteDynamicMemory(bstNode *);					//Deletes one node.
		void displayOne(bstNode *);							//Displays one node.
		void copyToBSTNode(itemNode &, bstNode *);			//Copies itemNode struct information into bstNode struct.
		void copyToItemNode(itemNode &, bstNode *);			//Copies bstNode struct information into itemNode struct.
		void copyBSTNode(bstNode *, bstNode * &);			//Copies one bstNode to another bstNode.
		int deleteLeaf(bstNode * &);						//Deletes node that is a leaf.
		int deleteInternalNodeLeftLeaf(bstNode * &);		//Deletes internal node that has only a left child.
		int deleteInternalNodeRightLeaf(bstNode * &);		//Deletes internal node that has only a right child.
		int deleteInternalNodeIOS(bstNode * &);				//Deletes internal node with two children.
		bstNode * root;										//Pointer to bst root node.
};


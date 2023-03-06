//Vaughn Poulo
//March 1, 2022
//Program 4
//CS163
//The client application fully meets the test plan because it allows the user
//to add an item to the external file, load the external file into the hash table,
//search, display, and delete items based on the keyword. In addition, the user 
//can search by the type of game.  This allows the client application developer
//to test the functionality of the program without knowing how the backend of
//the program works.

//Preprocessor Directives
#include "bst.h"
#include <fstream> //for writing and reading from external data file.
using namespace std;

//Prototypes
void welcomeMessage();
char userMenu();
int writeFile();
int readFile(itemNode [], int &);
void messageOutput(int);
void makeUpper(itemNode &);
void getElectronicsData(itemNode &);
void displayItem(itemNode &);
int addToBST(itemNode [], bstClass &, int);
void getName(char []);
void getTypeName(char []);

int main()
{
	//For file read and write.
	ifstream file_in;
	ofstream file_out;

	int messageIndicator {0};		//This tracks the success or failure of each function. 
	int userSelection {'X'};		//Stores the user desired action for the switch statement.
	itemNode itemArray[50];			//Array of structs to store items from external file.
	int count {0};					//Tracks how many electronic items have been read in from file.
	char name[100];					//Name for the user to search for an item.
	char typeName[100];				//Name for the user to search by type of game.
	itemNode retrieveNode;			//Struct to store found items in hash table.

	//Create instance of class.
	bstClass myBST;

	//Display welcome message to user.
	welcomeMessage();

	do
	{
		//Prompt user with text based menu.
		userSelection = userMenu();	

		switch(userSelection)
		{
			case 'A':
				//Add an electronics item to file
				writeFile();
				break;
			case 'B': 
				//Load electronics item from file & display it
				readFile(itemArray, count);
				messageIndicator = addToBST(itemArray, myBST, count);
				messageOutput(messageIndicator);
				break;
			case 'C':
				//Display all in sorted order.
				messageIndicator = myBST.displayAll();
				messageOutput(messageIndicator);
				break;
			case 'D':
				//Display information for a match by Name
				getName(name);
				messageIndicator = myBST.displayMatch(name);
				messageOutput(messageIndicator);
				break;
			case 'E':
				//Retieve information for a match by Name
				getName(name);
				messageIndicator = myBST.retrieve(name, retrieveNode);
				messageOutput(messageIndicator);
				break;
			case 'F':
				//Delete information by name.
				getName(name);
				messageIndicator = myBST.deleteMatchingNode(name);
				messageOutput(messageIndicator);
				break;
			case 'G':
				//Display all ites of a certain type (search through entire hash table)
				getTypeName(typeName);
				messageIndicator = myBST.displayType(typeName);
				messageOutput(messageIndicator);
				break;
			case 'X':
				break;
		}
	} while(userSelection != 'X');

	return 0;
}



//This function welcomes the user and explains the program.
void welcomeMessage()
{
	cout << endl;
	cout << "Welcome to this super awesome information storing program! This program \n";
	cout << "allows you to save game information (name, description, \n";
	cout << "type of game, platform, and rating) to an external data file. You can load \n";
	cout << "the electronics data and then search for products based on the name of the \n";
	cout << "product. You can also display all products of a certain type. Cool, right?";
	cout << endl;
}



//This function is a text based menu for the user to select an action.
char userMenu()
{
	char userSelection {'X'};

	cout << endl;
	cout << "Please select an action from the menu below:" << endl;
	cout << "\t A - Add an item to external file." << endl;
	cout << "\t B - Load all items from external file into BST and display." << endl;
	cout << "\t C - Display all in sorted order." << endl;
	cout << "\t D - Display item for a match by Name." << endl;
	cout << "\t E - Retrieve item for a match by Name." << endl;
	cout << "\t F - Delete item by Name." << endl;
	cout << "\t G - Display all items of a certain type (ie. Audio)." << endl;
	cout << "\t X - Exit program." << endl;
	cout << "Desired Action: ";
	cin >> userSelection;
	cin.ignore(200, '\n');
	userSelection = toupper(userSelection);

	return userSelection;

}



//This function writes to an external data file.
int writeFile()
{
	ifstream file_in;
	ofstream file_out;

	itemNode node;	//Initialize node to store electronics data.

	//open the file
	file_out.open("electronics_items.txt", ios::app);

	//check if the file opened successfully.
	if(!file_out)
		return 2;

	//Prompt user to fill node with data.
	getElectronicsData(node);

	//Write to external file. Deliminate node members with | and each node with new line.
	file_out << node.keyword << '|';
	file_out << node.desc << '|';
	file_out << node.gameType << '|';
	file_out << node.platform << '|';
	file_out << node.rating << '\n';

	//Close the file.
	file_out.close();
	
	//Return success.
	return 1;
}



//This function reads from an external data file and stores 
//data in a itemNode struct.
int readFile(itemNode myArray[], int & count)
{
	ifstream file_in;
	ofstream file_out;

	int i {0};			//Variable to loop through array.
	
	//Open file.
	file_in.open("electronics_items.txt");
	
	//Check if file could open.
	if(!file_in)
		return 2;

	//try reading from file
	file_in.get(myArray[0].keyword, 100, '|');
	file_in.ignore(100, '|');

	//if file is empty, return.
	if(file_in.eof())
		return 3;

	//While we are not at the end of the file and array is not full.
	while(!file_in.eof() && i < 50)
	{
		file_in.get(myArray[i].desc, 200, '|');
		file_in.ignore(100, '|');
		file_in.get(myArray[i].gameType, 100, '|');
		file_in.ignore(100, '|');
		file_in.get(myArray[i].platform, 100, '|');
		file_in.ignore(100, '|');
		file_in >> myArray[i].rating;
		file_in.ignore(100, '\n');
		++i;
		
		//Try reading next line to test if its empty.
		file_in.get(myArray[i].keyword, 100, '|');
		file_in.ignore(100, '|');		
	}
	
	//Close file after reading in all data.
	file_in.close();

	//update count of items.
	count = i;
	
	//Display all items to user & add to hash table.
	for(int i = 0; i < count; ++i)
	{
		displayItem(myArray[i]);
	}

		return 1;
}



//This function outputs messages of success or failure to the user.
void messageOutput(int messageIndicator)
{
	switch(messageIndicator)
	{
		case 0: 
			cout << endl << "Error: action failed." << endl;
			break;
		case 1:
			cout << endl << "Action Successful." << endl;
			break;
		case 2:
			cout << endl << "Error: could not open file." << endl;
			break;
		case 3:
			cout << endl << "Error: external file is empty." << endl;
			break;
		case 4:
			cout << endl << "Error: no matches found." << endl;
			break;
		case 5:
			cout << endl << "Error: No data loaded." << endl;
			break;
	}
}



//This function makes all characters in character arrays uppercase.
void makeUpper(char array[])
{
	int len {0};

	//Get the length of the array.
	len = strlen(array);

	//Loop through and make each character uppercase.
	for(int i = 0; i < len; ++i)
		array[i] = toupper(array[i]);
}



//This function prompts the user to store eletronic data details in a struct
void getElectronicsData(itemNode & node)
{
	//Promt the user to enter each piece of information and save it in the struct.
	cout << endl;
	cout << "Enter the name (ex. Zelda): ";
	cin.get(node.keyword, 100, '\n');
	cin.ignore(200, '\n');
	cout << "Enter the description for this item: ";
	cin.get(node.desc, 200, '\n');
	cin.ignore(200, '\n');
	cout << "Enter the type of game (ex. computer): ";
	cin.get(node.gameType, 100, '\n');
	cin.ignore(200, '\n');
	cout << "Enter the platform (ex. Mac, Windows): ";
	cin.get(node.platform, 100, '\n');
	cin.ignore(200, '\n');
	cout << "Enter the rating (ex. 5): ";
	cin >> node.rating;
	cin.ignore(200, '\n');
	cout << endl;

	//Make all character arrays uppercase.
	makeUpper(node.keyword);
	makeUpper(node.desc);
	makeUpper(node.gameType);
	makeUpper(node.platform);
}



//This function displays a struct to the user.
void displayItem(itemNode & item)
{
	cout << endl;
	cout << "Name: " << item.keyword << endl;
	cout << "Description: " << item.desc << endl;
	cout << "Type of Game: " << item.gameType << endl;
	cout << "Platform: " << item.platform << endl;
	cout << "Rating: " << item.rating << endl; 
}



//Adds items from external file to BST.
int addToBST(itemNode myArray[], bstClass & myBST, int count)
{
	int successCount {0};	//Tracks the number of items successfully added to BST.

	//Loop through index and add each node in index to BST.
	for(int i = 0; i < count; ++i)
	{
		successCount += myBST.insertItem(myArray[i]);
	}

	if(successCount = count)
		return 1;
	else
		return 0;
}



//Promots the user to enter a name to search by.
void getName(char name[])
{
	//Prompt the user to enter a name to search by.
	cout << "Enter the keyword (Name) you would like to search by: ";
	cin.get(name, 100, '\n');
	cin.ignore(200, '\n');
	
	//make the name uppercase.
	makeUpper(name);
	
	return;
}



//Prompts the user to enter a type of game they want to search for.
void getTypeName(char typeName[])
{
	//Prompt the user to enter the type of game name.
	cout << "Enter the type of game you would like to search by: ";
	cin.get(typeName, 100, '\n');
	cin.ignore(200, '\n');

	//Make it uppercase
	makeUpper(typeName);

	return;
}


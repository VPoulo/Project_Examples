//Vaughn Poulo
//CS202
//Program 3
//May 23, 2022
//This client application fully tests the test plan because all functionality
//of the program can be tested, regardless of the data structure behind the
//program. The client application allows for the addition, removal, display,
//and adjustment of the concept topics. If the data structure behind the program
//were to change, the client application would not be aware, and the functinoality
//of the new structure could be fully tested/


//Proprocessor Directives
#include "tree.h"

//Prototypes
void welcomeMessage();
char textMenu();
char userClassSelection();
int insert();
void getKeyword(string &);

int main()
{

	//Create instance of class.
	tree myConcepts;

	//Variable to hold user selection.
	char userSelection;
	char classSelection;
	string keyword;

	//Welcome user and explain program.
	welcomeMessage();

	//Keep prompting user and performing actions until user quits.
	do 
	{
		//Prompt user for desired action.
		userSelection = textMenu();

		//Perform desired action.
		switch(userSelection)
		{	
			case 'A':
				//Add new concept.
				classSelection = userClassSelection();
				myConcepts.insert(classSelection);
				break;
			case 'B':
				//Display all concepts.
				myConcepts.displayAll();
				break;
			case 'C':
				//Add method to concept.
				getKeyword(keyword);
				myConcepts.addMethod(keyword);
				break;
			case 'D':
				//Select a concept.
				getKeyword(keyword);
				myConcepts.selectConcept(keyword);
				break;
			case 'E':
				//Change rating.
				getKeyword(keyword);
				myConcepts.changeRating(keyword);
				break;
			case 'F':
				//Remove all.
				myConcepts.removeAll();
				cout << endl << "Success." << endl;
				break;
			case 'X':
				//Exit;
				break;
		}
	} while(userSelection != 'X');

	return 0;
}




//Explains program to the user.
void welcomeMessage()
{
	cout << endl;
	cout << "Welcome to Concept Tracker 5000! This handy little program helps \n";
	cout << "you keep track of new concepts related to the STL, Modern C++, and \n";
	cout << "the Python Library. How useful! This programs allows you to add \n";
	cout << "new concepts, display all concepts, remove all concepts, and add \n";
	cout << "information to an existing concept. You can also select the URL of \n";
	cout << "a concept, which will display the URL so you can copy and paste it into\n";
	cout << "your browser.  Have fun studying and may the odds be ever in your favor." << endl;
	cout << endl;
}



//Text based menu for user to select desired action.
char textMenu()
{
	char userSelection;

	do
	{
		try
		{
			//Display menu.
			cout << endl;
			cout << "Select an action from the menu:" << endl;
			cout << "\t A - Add a new concept." << endl;
			cout << "\t B - Display all concepts." << endl;
			cout << "\t C - Add a method." << endl;
			cout << "\t D - Select concept (display URL)." << endl;
			cout << "\t E - Change rating." << endl;
			cout << "\t F - Remove all concepts." << endl;
			cout << "\t X - Exit." << endl;
			cout << "Enter selection: ";
			cin >> userSelection;
			cin.ignore(200, '\n');
	
			//Make selection uppercase.
			userSelection = toupper(userSelection);
		
			//Check for invalid selection.
			if(userSelection < 'A' || userSelection > 'F' && userSelection != 'X')
				throw userSelection;
		}
		catch(char userSelection)
		{
			cout << endl << userSelection << " is not a valid selection" << endl;
		}
	} while(userSelection < 'A' || userSelection > 'F' && userSelection != 'X');

	//Return user selection.
	return userSelection;
}



//Prmopts user to select type of concept desired.
char userClassSelection()
{
	char userSelection {'X'};
	
	do {
		try
		{
			//Prompt user for selection.
			cout << endl;
			cout << "Select the type of concept you wish to create: " << endl;
			cout << "\t A - STL Syntax." << endl;
			cout << "\t B - Modern C++ Concept." << endl;
			cout << "\t C - Python Library." << endl;
			cout << "Enter selection: ";
			cin >> userSelection;
			cin.ignore(200, '\n');
			userSelection = toupper(userSelection);

			//Test user input for validity.
			if(userSelection != 'A' && userSelection != 'B' &&  userSelection != 'C')
				throw userSelection;
		}
		catch(char userSelection)
		{
			cout << endl << userSelection << " is not a valid selection." << endl;
		}
	} while(userSelection != 'A' && userSelection != 'B' && userSelection != 'C');

	return userSelection;
}



//Prompts user to enter keyword search term.
void getKeyword(string & keyword)
{
	//Prompt user.
	cout << endl << "Please enter concept keyword to search for: ";
	getline(cin, keyword, '\n');
	
	//Make keyword uppercase.
	for(string::iterator i = keyword.begin(); i != keyword.end(); ++i)
		*i = toupper(*i);

	return;
}





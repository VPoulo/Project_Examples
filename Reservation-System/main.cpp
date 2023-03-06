//Vaughn Poulo
//CS202
//May 8, 2022
//Program 2
//This program fully meets the test plan because it test all functionality
//required of it. The client can add, remove and display reservations. In the 
//background, operator overloading is being used without the user knowing. 
//If the data structure or overloading were to be changed, the client wouldn't 
//know but the application could still test the functionality required of the program.


//FOR GRADER:
//Exception Handling used in main.cpp Line 120 & Line 180.
//Exception Handling also used in reservation.cpp Line 74.
//String and Character Arrays used in reservation.h.
//Vector and Forward List used in reservation_list.h.
//DLL template implemented in DLL.tpp.
//Full compliment of operator overloading used in reservation.h.



//Preprocessor Directives
#include "reservation_list.h"

//Prototypes
void welcomeMessage();
char userMenu();
char getReservationType();
void messageOutput(int);
int getName(char []);
void makeUpper(char []);
int makeReservation(char, museum &, ski_lodge &, restaurant &);
int displayReservation(char, museum &, ski_lodge &, restaurant &);
int displayAllReservations(char, museum &, ski_lodge &, restaurant &);
int removeReservation(char, museum &, ski_lodge &, restaurant &);
int removeAllReservations(char, museum &, ski_lodge &, restaurant &);
void getSkiInfo(char * &, int &, int &, string &);
void getRestaurantInfo(char * &, int &, bool &, int &);
void getMuseumInfo(char * &, int &, bool &, string &);
void addStarterReservations(museum &, ski_lodge &, restaurant &);

int main()
{
	char userSelection {'X'};		//Variable to track user selection.
	char reservationType {'X'};		//Variable to hold the type of reservation being worked with.
	int messageIndicator {0};		//Tracks if function was successful.
	museum museum_list;				//Instance of Museum Reservation list.
	ski_lodge ski_list;				//Instance of Ski Lodge Reservation list.
	restaurant restaurant_list;		//Instance of Restaurant Reservation list.
	

	//Display welcome messaage.
	welcomeMessage();

	//Add some reservations to start.
	addStarterReservations(museum_list, ski_list, restaurant_list);

	do{
		//Display text based menu to get user desired action.
		userSelection = userMenu();

		switch(userSelection)
		{
			case 'A':
				//Make a reservation.	
				reservationType = getReservationType();
				messageIndicator = makeReservation(reservationType, museum_list, ski_list, restaurant_list);
				messageOutput(messageIndicator);
				break;
			case 'B': 
				//Display a reservation.
				reservationType = getReservationType();
				messageIndicator = displayReservation(reservationType, museum_list, ski_list, restaurant_list);
				messageOutput(messageIndicator);
				break;
			case 'C':
				//Display all reservastions.
				reservationType = getReservationType();
				messageIndicator = displayAllReservations(reservationType, museum_list, ski_list, restaurant_list);
				messageOutput(messageIndicator);
				break;
			case 'D':
				//Delete a reservation.
				reservationType = getReservationType();
				messageIndicator = removeReservation(reservationType, museum_list, ski_list, restaurant_list);
				messageOutput(messageIndicator);
				break;
			case 'E':
				//Delete all reservations.
				reservationType = getReservationType();
				messageIndicator = removeAllReservations(reservationType, museum_list, ski_list, restaurant_list);
				messageOutput(messageIndicator);
				break;
			case 'X':
				//Exit
				break;
		} 
	} while(userSelection != 'X');

	return 0;
}


	
//Explains the program to the user.
void welcomeMessage()
{
	cout << endl;
	cout << "Welcome to the Automated Reservaton System. You can make a \n";
	cout << "reservation to go Skiing, eat at a Restaurant, or visit a \n";
	cout << "museum! Reservations are valid for anytime on anyday. \n";
	cout << "You can display or delete a specific reservation or \n";
	cout << "display / delete all reservations." << endl;
	cout << endl;
}



//Lists options for the user.
char userMenu()
{
	try
	{
		char userSelection {'X'};	//Holds user selection.

		//Output text based menu.
		cout << endl;
		cout << "Please select an action below: " << endl;
		cout << "\t A - Make a reservation" << endl;
		cout << "\t B - Display a matching reservation" << endl;
		cout << "\t C - Display all reservations" << endl;
		cout << "\t D - Delete a matching reservation" << endl;
		cout << "\t E - Delete all reservations" << endl;
		cout << "\t X - Exit" << endl;
		cout << endl;
		cout << "Enter Action: ";
		cin >> userSelection;
		cin.ignore(200, '\n');
	
		//Make uppercase.
		userSelection = toupper(userSelection);
		
		if(userSelection != 'X' && (userSelection < 'A' ||  userSelection >  'E'))
			throw userSelection;

		//Return user preference.
		return userSelection;
	}
	catch(char c)
	{
		cout << endl << c << " is not a valid selection" << endl;
		return c;
	}
}



//Make an array uppercase
void makeUpper(char name[])
{
	int length {0};		//Variable to hold length of array

	//Find length of array.
	length = strlen(name);

	//Loop through array elements and make uppercase
	for(int i = 0; i < length; ++i)
		name[i] = toupper(name[i]);

	return;
}



//Prompts the user to specifiy the type of reservation they want to work with.
char getReservationType()
{
	char reservationType {'X'};

	do
	{
		try
		{
			//Prompt user.
			cout << endl << "What type of reservation would you like to work with?" << endl;
			cout << "\t S - Ski Reservation" << endl;
			cout << "\t D - Dinner Reservation" << endl;
			cout << "\t M - Museum Reservation" << endl;
			cout << endl;
			cout << "Enter reservation selection: ";
			cin >> reservationType;
			cin.ignore(200, '\n');

			//Make selection uppercase
			reservationType = toupper(reservationType);

			if(reservationType != 'S' && reservationType != 'D' && reservationType != 'M')
				throw reservationType;
		}
		catch(char c)
		{
			cout << endl << c << " is not a valid selection." << endl;
		}

	} while(reservationType != 'S' && reservationType != 'D' && reservationType != 'M');

	return reservationType;
}



//Prompts the user to enter a name.
int getName(char aName[])
{
	//Prompt user for name.
	cout << endl;
	cout << "Please enter reservation name: ";
	cin.get(aName, 50, '\n');
	cin.ignore(200, '\n');

	//Make name uppercase.
	makeUpper(aName);

	return 1;
}



//Adds a reservation to user selected reservation type.
int makeReservation(char reservationType, museum & museum_list, ski_lodge & ski_list, restaurant & restaurant_list)
{
	int successTracker {0};
	char * name;
	int num_guests {0};

	//Continue with making reservation.
	switch(reservationType)
	{
		case 'S': 	//Ski Reservation
			{
				int num_rentals {0};
				string lodge_name;
				getSkiInfo(name, num_guests, num_rentals, lodge_name);
				successTracker = ski_list.insert(name, num_guests, num_rentals, lodge_name);	
				break;
			}
		case 'D': 	//Dinner Reservation
			{	
				bool is_veg {false};
				int num_children {0};
				getRestaurantInfo(name, num_guests, is_veg, num_children);
				successTracker = restaurant_list.insert(name, num_guests, is_veg, num_children);
				break;
			}
		case 'M':	//Museum Reservation
			{
				bool is_tour {false};
				string exhibit;
				getMuseumInfo(name, num_guests, is_tour, exhibit);
				successTracker = museum_list.insert(name, num_guests, is_tour, exhibit);
				break;
			}
	}

	delete [] name;

	return successTracker;	
}



//Gets all information needed for ski reservation.
void getSkiInfo(char * & name, int & guests, int & rentals, string & lodge)
{
	char aName[100];
	
	//Get basic reservation info from user.
	cout << endl << "Reservation Name: ";
	cin.get(aName, 100);
	cin.ignore(200, '\n');
	cout << "Number of Guests: ";
	cin >> guests;
	cin.ignore(200, '\n');
	cout << "Number of ski rentals needed: ";
	cin >> rentals;
	cin.ignore(200, '\n');
	cout << "Name of lodge: ";
	getline(cin, lodge, '\n');

	//Allocate dynamic memory for name.
	name = new char[strlen(aName) + 1];
	strcpy(name, aName);
	
	//Make name uppercase
	makeUpper(name);

	return;
}



//Gets all information needed for restaurant reservation.
void getRestaurantInfo(char * & name, int & guests, bool & is_veg, int & num_children)
{
	char aName[100];
	char vegetarian;

	//Get basic reservation info from user.
	cout << endl << "Reservation Name: ";
	cin.get(aName, 100);
	cin.ignore(200, '\n');
	cout << "Number of Guests: ";
	cin >> guests;
	cin.ignore(200, '\n');
	cout << "Is anyone in the party vegetarian? (Y / N): ";
	cin >> vegetarian;
	cin.ignore(200, '\n');
	cout << "Number of children in the party: ";
	cin >> num_children;
	cin.ignore(200, '\n');

	//Allocate dynamic memory for name.
	name = new char[strlen(aName) + 1];
	strcpy(name, aName);
	
	//Make name uppercase
	makeUpper(name);

	//Assign vegetarian status
	if(toupper(vegetarian) == 'Y')
		is_veg = true;
	else
		is_veg = false; 

	return;
}



//Gets all informaiton needed for museum reservation.
void getMuseumInfo(char * & name, int & guests, bool & is_tour, string & exhibit)
{
	char aName[100];
	char tour;
		
	//Get basic reservation info from user.
	cout << endl << "Reservation Name: ";
	cin.get(aName, 100);
	cin.ignore(200, '\n');
	cout << "Number of Guests: ";
	cin >> guests;
	cin.ignore(200, '\n');
	cout << "Would you like a guided tour? (Y / N): ";
	cin >> tour;
	cin.ignore(200, '\n');
	cout << "What exhibit are you most interested in? (ex. Van Gogh): ";
	getline(cin, exhibit, '\n');

	//Allocate dynamic memory for name.
	name = new char[strlen(aName) + 1];
	strcpy(name, aName);
	
	//Make name uppercase
	makeUpper(name);

	//Assign tour status
	if(toupper(tour) == 'Y')
		is_tour = true;
	else
		is_tour = false;

	return;
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
			cout << endl << "Error: no reservation under that name was found." << endl;
			break;
		case 3:
			cout << endl << "Error: no reservations have been made." << endl;
			break;
	}
}



//Displays a reservating matching a reservation name input from user.
int displayReservation(char reservationType, museum & museum_list, ski_lodge & ski_list, restaurant & restaurant_list)
{
	int successTracker {0};

	//Prompt user for name to match.
	char aName[100];
	getName(aName);

	//Allocate dynamic memory for name.
	char * name;
	name = new char[strlen(aName) + 1];
	strcpy(name, aName);
	
	switch(reservationType)
	{
		case 'S': 	//Ski Reservation
			{
				successTracker = ski_list.display(name);
				break;
			}
		case 'D': 	//Dinner Reservation
			{	
				successTracker = restaurant_list.display(name);
				break;
			}
		case 'M':	//Museum Reservation
			{
				successTracker = museum_list.display(name);
				break;
			}
	}

	delete [] name;

	return successTracker;
}



//Displays all reservations.
int displayAllReservations(char reservationType, museum & museum_list, ski_lodge & ski_list, restaurant & restaurant_list)
{
	int successTracker {0};

	switch(reservationType)
	{
		case 'S': 	//Ski Reservation
			{
				successTracker = ski_list.display_all(); 
				break;
			}
		case 'D': 	//Dinner Reservation
			{	
				successTracker = restaurant_list.display_all();
				break;
			}
		case 'M':	//Museum Reservation
			{
				successTracker = museum_list.display_all();
				break;
			}
	}

	return successTracker;
}



//Removes a reservation matching a reservation name input from user.
int removeReservation(char reservationType, museum & museum_list, ski_lodge & ski_list, restaurant & restaurant_list)
{
	int successTracker {0};
	
	//Prompt user for name to match.
	char aName[100];
	getName(aName);

	//Allocate dynamic memory for name.
	char * name;
	name = new char[strlen(aName) + 1];
	strcpy(name, aName);
	
	switch(reservationType)
	{
		case 'S': 	//Ski Reservation
			{
				successTracker = ski_list.delete_reservation(name);
				break;
			}
		case 'D': 	//Dinner Reservation
			{	
				successTracker = restaurant_list.delete_reservation(name);
				break;
			}
		case 'M':	//Museum Reservation
			{
				successTracker = museum_list.delete_reservation(name);
				break;
			}
	}

	delete [] name;

	return successTracker;
}



//Removes all reservations.
int removeAllReservations(char reservationType, museum & museum_list, ski_lodge & ski_list, restaurant & restaurant_list)
{
	int successTracker {0};
	
	switch(reservationType)
	{
		case 'S': 	//Ski Reservation
			{
				successTracker = ski_list.delete_all();
				break;
			}
		case 'D': 	//Dinner Reservation
			{	
				successTracker = restaurant_list.delete_all();
				break;
			}
		case 'M':	//Museum Reservation
			{
				successTracker = museum_list.delete_all();
				break;
			}
	}

	return successTracker;
}



//Adds reservations to start the program off with
void addStarterReservations(museum & museum_list, ski_lodge & ski_list, restaurant & restaurant_list)
{

	//Add Poulo
	char * name = new char[strlen("Poulo") + 1];
	strcpy(name, "POULO");
	ski_list.insert(name, 5, 2, "Timberline");

	//Add Valusek
	delete [] name;
	name = new char[strlen("Valusek") + 1];
	strcpy(name, "VALUSEK");
	ski_list.insert(name, 3, 3, "Ski Bowl");
	
	//Add Johnson
	delete [] name;
	name = new char[strlen("Johnson") + 1];
	strcpy(name, "JOHNSON");
	ski_list.insert(name, 9, 2, "Meadows");

	//Add Smith
	delete [] name;
	name = new char[strlen("Smith") + 1];
	strcpy(name, "SMITH");
	restaurant_list.insert(name, 5, true, 3);

	//Add Warren	
	delete [] name;
	name = new char[strlen("Warren") + 1];
	strcpy(name, "WARREN");
	restaurant_list.insert(name, 7, false, 2);
	
	//Add Sanders
	delete [] name;
	name = new char[strlen("Sanders") + 1];
	strcpy(name, "SANDERS");
	restaurant_list.insert(name, 2, false, 0);
	
	//Add Tate
	delete [] name;
	name = new char[strlen("Tate") + 1];
	strcpy(name, "TATE");
	museum_list.insert(name, 4, true, "Van Gogh");	

	//Add Filippov
	delete [] name;
	name = new char[strlen("Filippov") + 1];
	strcpy(name, "FILIPPOV");
	museum_list.insert(name, 12, false, "Banksy");	

	//Add Charlton
	delete [] name;
	name = new char[strlen("Charlton") + 1];
	strcpy(name, "CHARLTON");
	museum_list.insert(name, 2, true, "Monet");	

	delete [] name;

}


//Vaughn Poulo
//CS202
//Program 1
//April 22, 2022
//This client application fully meets the test plan because all 
//aspects of the program and data structures can be tested. Adding 
//a contestant adds nodes to the data structure, removing all contestants
//deletes nodes from the strucute, and displaying the nodes happens
//when starting the race. If the data structures changed behind the scenes,
//this client applicaiton wouldn't know it, and it would still be able to test
//the functionality required.


//Preprocessor Directives
#include <string>
#include "animal.h"
#include "race.h"
#include "node.h"
#include <cctype>
#include <cstring>
#include <iostream>
using namespace std;

//Prototypes
void welcomeMessage();
char userMenu();
void announce_race(char &, char [], int &, swimRace &, hurtleRace &, sprintRace &);
char announcement_menu();
int announce_swim_race(swimRace &, char []);
int announce_hurtle_race(hurtleRace &, char []);
int announce_sprint_race(sprintRace &, char []);
int start_race(char, int, bool &, swimRace &, hurtleRace &, sprintRace &);
int stop_race(char &, int &, bool &, swimRace &, hurtleRace &, sprintRace &);
int add_contestant_to_race(char, char [], bool, int &, swimRace &, hurtleRace &, sprintRace &);
int remove_all_contestants(char &, int &, bool &, swimRace &, hurtleRace &, sprintRace &);
int get_name(char []);
void toUpper(char []);

int main()
{
	int size = 3;					//Size of array of LLL.
	int count_contestants {0};		//Tracks number of contestants in race.
	char userSelection {'X'};		//Variable to track user selection.
	char ongoingRace {'N'};			//Tracks which race user has selected, if any.
	char name[50];					//Hold the name input by the user.
	bool raceStarted {false};		//Tracks if the race has already been started.
	swimRace aSwim;					//Instance of swim race.
	hurtleRace aHurtle(size);		//Instance of hurtle race.
	sprintRace aSprint;				//Instance of sprint race.

	//Display welcome messaage.
	welcomeMessage();

	do{
		//Display text based menu
		userSelection = userMenu();

		switch(userSelection)
		{
			case 'A':
				//Announce a race.
				announce_race(ongoingRace, name, count_contestants, aSwim, aHurtle, aSprint);
				break;
			case 'B': 
				//Add a contestant.
				add_contestant_to_race(ongoingRace, name, raceStarted, count_contestants,  aSwim, aHurtle, aSprint);
				break;
			case 'C':
				//Start race.
				start_race(ongoingRace, count_contestants, raceStarted, aSwim, aHurtle, aSprint);
				break;
			case 'D':
				//Stop race.
				stop_race(ongoingRace, count_contestants, raceStarted, aSwim, aHurtle, aSprint);
				break;
			case 'E':
				//Remove all contestants.
				remove_all_contestants(ongoingRace, count_contestants, raceStarted,  aSwim, aHurtle, aSprint);
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
	cout << "Welcome to the International Animal Race Competition 2022! \n";
	cout << "As the head of the games, you can decide what race to announce \n";
	cout << "and decide how many contestants should be in each race. There \n";
	cout << "are three different races: \n";
	cout << "\t 1) 1-mile Penguin swimming race. \n";
	cout << "\t 2) 1-mile Kangaroo Hurdle race. \n";
	cout << "\t 3) 1-mile Horse sprint race \n";
	cout << "Each race only accepts contestants that are of the specified animal. \n";
	cout << endl;
	cout << "Starting the race will display all the contestant as well as kick off the race!" << endl;
	cout << "Stopping the race will display the winners as well as remove all contestants \n";
	cout << "from the race." << endl;
	cout << "Good Luck!" << endl;
	cout << endl;
}



//Lists options for the user.
char userMenu()
{
	char userSelection {'X'};	//Holds user selection.

	//Output text based menu.
	cout << endl;
	cout << "Please select an action below: " << endl;
	cout << "\t A - Announce a race" << endl;
	cout << "\t B - Add a contestant" << endl;
	cout << "\t C - Start race" << endl;
	cout << "\t D - Stop race" << endl;
	cout << "\t E - Remove all contestants" << endl;
	cout << "\t X - Exit" << endl;
	cout << endl;
	cout << "Enter Action: ";
	cin >> userSelection;
	cin.ignore(200, '\n');
	
	//Make uppercase.
	userSelection = toupper(userSelection);
	
	//Return user preference.
	return userSelection;
}



//Make an array uppercase
void toUpper(char anArray[])
{
	int arrayLen {0};	//Variable to hold length of array

	//Find length of array.
	arrayLen = strlen(anArray);

	//Loop through array elements and make uppercase
	for(int i = 0; i < arrayLen; ++i)
		anArray[i] = toupper(anArray[i]);
}



//Prompts user to select what kind of race to announce, and then calls correct function to announce that race.
void announce_race(char & ongoingRace, char name[], int & count, swimRace & aSwim, hurtleRace & aHurtle, sprintRace & aSprint)
{
	//Check if user already announced a race.
	if(ongoingRace != 'N')
	{
		cout << endl << "Oops! Looks like you already announced a race." << endl;
		cout << "You must stop the first race before announcing another." << endl << endl;
		return;
	}
	
	//Ask user for race preference.
	do
	{	
		ongoingRace = announcement_menu();
		++count;

		//Announce race user has selected.
		switch(ongoingRace)
		{
			case 'S':	//Swim Race
				announce_swim_race(aSwim, name);
				break;
			case 'H':	//Hurtle Race
				announce_hurtle_race(aHurtle, name);
				break;
			case 'T':	//Srint Race
				announce_sprint_race(aSprint, name);
				break;
		}

	} while (ongoingRace != 'S' &&  ongoingRace != 'H' && ongoingRace != 'T');
	
	return;
}



//Text based menu to select type of race.
char announcement_menu()
{
	char raceChoice {'X'};	//Holds user selection.

	//Output race menu.
	cout << endl;
	cout << "Select the race you would like to announce: \n";
	cout << "\t S: 1-mile Penguin Swim Race." << endl;
	cout << "\t H: 1-mile Kangaroo Hurtle Race." << endl;
	cout << "\t T: 1-mile Horse Sprint Race." << endl;
	cout << endl;
	cout << "Race Selection: ";
	cin >> raceChoice;
	cin.ignore(200, '\n');

	//Make selection uppercase
	raceChoice = toupper(raceChoice);

	return raceChoice;
}



//Announces a swim race and adds one contestant.
int announce_swim_race(swimRace & aSwim, char name[])
{
	//Add an animal to race for user.
	strcpy(name, "FLOPSY");
	aSwim.add_contestant(name);
	
	//Inform user of competition.
	cout << endl;
	cout << "A SWIMMING COMPETITION HAS BEEN ANNOUNCED!" << endl;
	cout << "A contestant has already entered the competition." << endl;
	cout << "Enter a few more penguins into the competition \n";
	cout << "to make the competition exciting." << endl;
	cout << endl; 
	cout << "The current contestants are: " << endl;

	//Display current contestants.
	aSwim.display_all();

	return 1;
}



//Announces a hurtle race and adds one contestant.
int announce_hurtle_race(hurtleRace & aHurtle, char name[])
{
	//Add an animal to race for user.
	strcpy(name, "TIGGER");
	aHurtle.add_contestant(name);
	
	//Inform user of competition.
	cout << endl;
	cout << "A HURTLE COMPETITION HAS BEEN ANNOUNCED!" << endl;
	cout << "A contestant has already entered the competition." << endl;
	cout << "Enter a few more kangaroos into the competition \n";
	cout << "to make the competition exciting." << endl;
	cout << endl; 
	cout << "The current contestants are: " << endl;

	//Display current contestants.
	aHurtle.display_all();

	return 1;
}



//Announces a sprint race and adds one contestant.
int announce_sprint_race(sprintRace & aSprint, char name[])
{
	//Add an animal to race for user.
	strcpy(name, "BUTTERCUP");
	aSprint.add_contestant(name);
	
	//Inform user of competition.
	cout << endl;
	cout << "A SPRINT COMPETITION HAS BEEN ANNOUNCED!" << endl;
	cout << "A contestant has already entered the competition." << endl;
	cout << "Enter a few more horses into the competition \n";
	cout << "to make the competition exciting." << endl;
	cout << endl; 
	cout << "The current contestants are: " << endl;

	//Display current contestants.
	aSprint.display_all();

	return 1;
}



//Adds the correct contestant depending on the race current taking place.
int add_contestant_to_race(char ongoingRace, char name[], bool raceStarted, int & count, swimRace & aSwim, hurtleRace & aHurtle, sprintRace & aSprint)
{
	//If race has already started, then output error as its too late to add a contestant.
	if(raceStarted == true)
	{
		cout << endl << "Race has already started! It's too late to add a contestant now." << endl;
		return 1;
	}

	//Add contestant to correct race that user has announced.
	switch(ongoingRace)
	{
		case 'S': 	//Swim race
			get_name(name);	//Get name for contestant.
			aSwim.add_contestant(name);	//Add contestant.
			cout << endl << "Penguin " << name << " added to the race!" << endl << endl;;	//Inform user contestant has been added.
			++count;	//Increase contestant count
			break;
		case 'H':	//Hurtle Race
			get_name(name);	//Get name for contestant.
			aHurtle.add_contestant(name);	//Add contestant.
			cout << endl << "Kangaroo " << name << " added to the race!" << endl << endl;  //Inform user contestant has been added.
			++count;	//Increase contestant count.
			break;
		case 'T':	//Sprint Race
			get_name(name);	//Get name for contestant.
			aSprint.add_contestant(name);	//Add contestant.
			cout << endl << "Horse " << name << " added to the race!" << endl << endl;	//Inform user contestant has been added.
			++count;	//Increase contestant count.
			break;
		case 'N':	//No Race has been announced.
			cout << endl << "Oops, looks like no race has been announced!" << endl;
			break;
	}
	
	return 1;
}



//Starts the race that has been announced.
int start_race(char ongoingRace, int count, bool & raceStarted,  swimRace & aSwim, hurtleRace & aHurtle, sprintRace & aSprint)
{
	//If no contestants have been added to race, ouput error to user.
	if(count == 0)
	{
		cout << endl << "Looks like all there are no contestants in the race." << endl;
		cout << "The race cannot begin without at least 1 contestant." << endl;
		return 1;		
	}

	//If the race has already been started, output error to user.
	if(raceStarted == true)
	{
		cout << endl << "Looks like the race has already started. Stop the race to see the results!" << endl;
		return 1;
	}

	//Start the race for the correct race.
	switch(ongoingRace)
	{
		case 'S':	//Swim Race
			cout << endl << "THE RACE HAS BEGUN!" << endl;
			cout << "The contestants are: " << endl;
			aSwim.display_all();	//Display all contestants
			aSwim.start_race();		//Start the race
			raceStarted = true;		//Set race variable
			break;
		case 'H':	//Hurtle Race
			cout << endl << "THE RACE HAS BEGUN!" << endl;
			cout << "The contestants are: " << endl;
			aHurtle.display_all();	//Display all contestants
			aHurtle.start_race();	//Start the race
			raceStarted = true;		//Set race variable
			break;
		case 'T':	//Sprint Race
			cout << endl << "THE RACE HAS BEGUN!" << endl;
			cout << "The contestants are: " << endl;
			aSprint.display_all();	//Display all contestants
			aSprint.start_race();	//Start the race	
			raceStarted = true;		//Set race variable
			break;
		case 'N':	//No race has been announced, output error.
			cout << endl << "Oops! Looks like a race hasn't been announced yet!." << endl;
			break;
	}
	
	return 1;
}



//Stops the race and displays contestants.
int stop_race(char & ongoingRace, int & count, bool & raceStarted, swimRace & aSwim, hurtleRace & aHurtle, sprintRace & aSprint)
{
	//If race hasn't started yet, it cannot be ended. Output error message to user.
	if(raceStarted == false)
	{
		cout << endl << "The race hasn't started yet! You must first start the race before stopping it!" << endl;
		return 1;
	}

	//Stop corresponding race.
	switch(ongoingRace)
	{
		case 'S':	//Swim Race
			cout << endl << "THE RACE HAS STOPPED!" << endl;
			aSwim.stop_race();	//Stop the race and output winners
			cout << endl << "All contestants have left the race." << endl;
			aSwim.remove_all();	//Remove all contestants.
			count = 0;		//Change count of contestants.
			ongoingRace = 'N';	//Change race variables to be accurate.
			raceStarted = false;
			break;
		case 'H':	//Hurtle Race
			cout << endl << "THE RACE HAS STOPPED!" << endl;
			aHurtle.stop_race(); //Stop the race and output winners.
			cout << endl << "All contestants have left the race." << endl;
			aHurtle.remove_all(); //Remove all contestants.
			count = 0;	//Update race variables.
			ongoingRace = 'N';
			raceStarted = false;
			break;
		case 'T':	//Sprint Race
			cout << endl << "THE RACE HAS STOPPED!" << endl;
			aSprint.stop_race();	//Stop race and output winners.
			cout << endl << "All contestants have left the race." << endl;
			aSprint.remove_all();	//Remove all contestants.
			count = 0;		//Update race variables.
			ongoingRace = 'N';
			raceStarted = false;
			break;
	}
	
	return 1;
}



//Removes all contestants from a race.
int remove_all_contestants(char & ongoingRace, int & count, bool & raceStarted, swimRace & aSwim, hurtleRace & aHurtle, sprintRace & aSprint)
{
	//If there are no contestants to remove, display error.
	if(count == 0)
	{
		cout << endl << "There are no contestants to remove." << endl;
		return 1;
	}

	//If race has already stared, cancel race and output error.
	if(raceStarted == true)
	{
		cout << endl << "RACE CANCELLED" << endl;
		cout << "All contestants have been removed from the race and \n";
		cout << "the race has been cancelled." << endl;

		count = 0;	//Update race variables to match cancelled status.
		ongoingRace = 'N';
		raceStarted = false;
		
		return 1;
	}

	//Remove contestants from corresponding race.
	switch(ongoingRace)
	{
		case 'S':	//Swim Race
			cout << endl << "All contestants have left the race." << endl;
			aSwim.remove_all();
			count = 0;
			break;
		case 'H':	//Hurtle Race
			cout << endl << "All contestants have left the race." << endl;
			aHurtle.remove_all();
			count = 0;
			break;
		case 'T':	//Sprint Race
			cout << endl << "All contestants have left the race." << endl;
			aSprint.remove_all();
			count = 0;
			break;
		case 'N':	//No race has been announced.
			cout << endl << "Oops! Looks like no race has been announced. Therefore, \n" << endl;
			cout << "no there are no contestants to remove." << endl;
			break;
	}
	
	return 1;
}



//Prompts the user to enter a name.
int get_name(char name[])
{
	//Prompt user for name.
	cout << endl;
	cout << "Please enter the animal name: ";
	cin.get(name, 50, '\n');
	cin.ignore(200, '\n');

	//Make name uppercase.
	toUpper(name);

	return 1;
}


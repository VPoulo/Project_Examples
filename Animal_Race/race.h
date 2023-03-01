//Vaughn Poulo
//CS202
//Program 1
//April 22, 2022
//This data type has a race base class and three different
//races dervied from the race class. Each race has a different
//data structure. The Swim Race utilises a Circular Linked List.
//the Hurtle Race uses an Array of Linear Linked Lists, and the 
//Sprint Race uses a Linear Linked List. Each derived class points
//a specific type of node found in animals.h. This class should be used
//when wanting to store these animals and race them. This class adds, 
//removes and displays all nodes in its data structure.

#include <vector>
#include <string>
#include "node.h"
using namespace std;

class race
{
	public:
		race();																		//Constructor.
		~race();																	//Destructor.
		void display();																//Displays race information.

	protected:
		string race_name;															//Race name (swim, hurtle, sprint). --STRING USED HERE
};


	
class swimRace: public race
{
	public:
		swimRace();																	//Constructor.
		swimRace(const swimRace &);													//Copy Constructor.
		~swimRace();																//Destructor.
		int start_race();															//Tells each animal to calculate the time taken to complete race. --WRAPPER
		int add_contestant(char []);												//Wrapper function for adding penguin contestant to race.	--WRAPPER
		int remove_all();															//Removes all 	--WRAPPER
		int display_all();															//Displays all contestants.	--WRAPPER
		int stop_race();															//Displays winner and runner up. --WRAPPER --VECTOR USED HERE.
		swimRace & operator= (const swimRace &);									//Assignment operator overload.
	
	private:
		penguin_node * rear;														//CIRCULAR LINKED LIST.
		int add_contestant(penguin_node *, penguin_node *, penguin_node *);			//Recursively inserts a new node (contestant). --RECURSIVE
		int display_all(penguin_node *);											//Recursive function to display entire CLL. --RECURSIVE
		int remove_all(penguin_node *);												//Recursive function to remove all nodes in CLL. --RECURSIVE
		int start_race(penguin_node *);												//Recursive function to start race for all contestants. --RECURSIVE
		int stop_race(penguin_node *, float &, float &, vector<penguin_node *> &);	//Recursive function to stop the race and display winners. --RECURSIVE
		int copy_cll();																//Wrapper function for private function to copy all CLL nodes. --WRAPPER	
		int copy_cll(penguin_node *, penguin_node *, penguin_node *);				//Recursive function to copy all CLL nodes.
};



class hurtleRace: public race
{
	public:
		hurtleRace(int);															//Constructor.
		~hurtleRace();																//Destructor.
		int add_contestant(char []);												//Adds kangaroo contestant to race. --WRAPPER
		int remove_all();															//Removes all contestants. --WRAPPER
		int display_all();															//Displays all contestants.  --WRAPPER
		int start_race();															//Starts race for all contestants. --WRAPPER
		int stop_race();															//Displays winners of race. --WRAPPER
		int display_winners(float);													//Displays winners matching time passed in. --WRAPPER

	private:
		k_node ** array_head;														//ARRAY OF LINEAR LINKED LISTS.
		int size;																	//Size of array.
		bool add_contestant(k_node *, k_node *);									//Recursively adds new contestant. --RECURSIVE
		int display_all(k_node *);													//Recursively displays all nodes. --RECURSIVE
		int start_race(k_node *);													//Recursively starts race for all contestants. --RECURSIVE
		int remove_all(k_node * &);													//Recursively delete all nodes.	--RECURSIVE
		int stop_race(k_node *, vector<float> &);									//Recursively finds fastest and seconds fastest race time. --RECURIVE --VECTOR USED HERE.
		int display_winners(k_node *, float);										//Recursive function to print winenrs.	--RECURSIVE
};



class sprintRace: public race
{
	public:
		sprintRace();																//Constructor.
		~sprintRace();																//Destructor.
		int add_contestant(char []);												//Adds horse contestant to race.  --WRAPPER
		int remove_all();															//Removes all contestants.	--WRAPPER
		int display_all();															//Displays all contestants. 	--WRAPPER		
		int start_race();															//Tells contestants to calculate race time. --WRAPPER
		int stop_race();															//Displays winners of race.		--WRAPPER

	private:
		h_node * head;																//LINEAR LINKED LIST.
		int add_contestant(h_node *, h_node *);										//Recursive function that adds new contestant. --RECURSIVE
		int remove_all(h_node * &);													//Removes all contestants from race.		--RECURSIVE
		int display_all(h_node *);													//Recursively displays all contestants.			--RECURSIVE
		int start_race(h_node *);													//Tells each contstant to calculate race time. 		--RECURSIVE
		int stop_race(h_node *, vector<float> &);									//Stop the race and display winners. 			--RECURSIVE
		int display_winners(h_node *, float);										//Recurively display any contestant with float matching race time.	--RECURSIVE
};



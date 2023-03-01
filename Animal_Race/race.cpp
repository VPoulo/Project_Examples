//Vaughn Poulo
//CS202
//Program 1
//April 22, 2022
//The functions for these classes all relate to managing the data structures.
//There are three data structures contained in this file, CLL, ARR, and LLL.
//The member funtions for each derived class can add a node
//to their data structure, remove all nodes, display a node,
//display all nodes, find the node that contains the fastest time,
//find the node with the second fastest time, prompt each node to 
//calculate its race time and also stop the race and display the results.

#include "race.h"
#include <cctype>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;


//Constructor.
race::race()
{
}



//Destructor.
race::~race()
{
}



//Displays all race related information.
void race::display()
{
	cout << endl;
	cout << "Race: " << race_name << endl;
	cout << endl;	
}



//Swim Class	
//Constructor.
swimRace::swimRace()
{	
	//Initialize race name to appropriate race.
	race_name = "Swim Race";
	
	//Initialize rear pointer to nullptr.
	rear = nullptr;
}



//Copy Constructor.
swimRace::swimRace(const swimRace & copyFrom)
{
	//Create a new swimRace class instance
	swimRace * temp = new swimRace;

	//Copy info into new swimRace
	*temp = copyFrom;
}



//Destructor.
swimRace::~swimRace()
{
	remove_all();
}



//Wrapper function to add a penguin conestant to race.
int swimRace::add_contestant(char name[])
{
	//Create a new instance of penguin class with name argument provided.
	penguin_node * temp  = new penguin_node(name);

	//Case #1: CLL is empty, insert node.
	if(!rear)
	{
		rear = temp;
		temp->set_next(rear);
		return 1;
	}

	//Case #2: CLL has only one node
	if(rear->get_next() == rear)
	{
		//rear points to new node.
		rear->set_next(temp);

		//Temp node should point to rear.
		temp->set_next(rear);

		return 1;
	}

	//Set a temporary pointer to node after rear.
	penguin_node * current = rear->get_next();
	
	//Call recursive insert.
	return add_contestant(rear, current, temp);
}



//Recursively insert node.
int swimRace::add_contestant(penguin_node * rear, penguin_node * current, penguin_node * temp)
{
	int count {0};	//Tracks number of nodes inserted.

	//Base Case: Current equals Rear
	if(rear == current)
		return 0;

	//Base Case: next node is rear, time to insert.
	if(current->get_next() == rear)
	{
		//Temp points to rear.
		temp->set_next(rear);

		//Current points to temp.
		current->set_next(temp);

		//Set current pointer after node just inserted.
		current = rear;
		
		return 1;
	}

	//Next smaller case.
	count += add_contestant(rear, current->get_next(), temp);

	return count;
}



//Wrapper function to remove all contestants from the race.
int swimRace::remove_all()
{
	int count {0};	//Catch number of nodes deleted.

	//If CLL is emtpy, return.
	if(!rear)
		return 3;

	//Set temp pointer to node after rear.
	penguin_node * temp = rear->get_next();

	//Recursive function call
	count = remove_all(temp);

	if(count > 0)
		return 1;
	else
		return 0;
}



//Recursive function to delete all nodes in CLL
int swimRace::remove_all(penguin_node * temp)
{
	int count {0};	//Tracks number of nodes deleted.

	//Base Case: If pointer is null, return;
	if(!temp)
		return 0;

	//Base Case: if temp pointer equals rear, delete last node.
	if(temp == rear)
	{
		delete rear;
		rear = nullptr;
		temp = nullptr;
		return 1;
	}
	
	//Set rear next value to node after temp, thus removing temp from CLL.
	rear->set_next(temp->get_next());	

	//delete temp	
	delete temp;
	
	//increase count.
	++count;

	//Recurse to next smaller instance.
	count +=remove_all(temp = rear->get_next());

	return count;
}



//Displays all contestants.
int swimRace::display_all()
{
	int count {0};	//Catch number of nodes output by recursive call.

	//If CLL is empty, return.
	if(!rear)
		return 0;

	//If CLL has only one node, display it
	if(rear->get_next() == rear)
	{
		rear->display();
		return 1;
	}

	//Set temp pointer to node after rear.
	penguin_node * temp = rear->get_next();

	//Display head, and then recursive function call.
	rear->display();
	count = display_all(temp);

	if(count > 0)
		return 1;
	else
		return 0;
}



//Recursive function to display every node in CLL
int swimRace::display_all(penguin_node * temp)
{
	int count {0};		//Tracks number of nodes displayed.

	//Base Case: If temp back to rear, return;
	if(temp == rear)
		return 0;
	
	//Display node.
	temp->display();

	//Add to count.;
	++count;

	//Next smaller recursive case.
	count += display_all(temp->get_next());

	return count;
}




//Wrapper function. Displays the winner and runner up.
int swimRace::stop_race()
{
	int count {0};			//Catches count from recursive function.
	float first {10000.0};	//Fastest time
	float second {10000.0};	//Second fastest time
	vector<penguin_node *>  winnerVector(2);	//Vector to hold winners.

	//If rear is null, return.
	if(!rear)
		return 3;

	//Check if only one contestant exists.
	if(rear->get_next() == rear)
	{
		cout << "FIRST PLACE: " << endl;
		rear->display();
		return 1;
	}

	//Set fastest past to rear as starting value.
	first = rear->race_time;
	
	//Recursive function call
	count = stop_race(rear->get_next(), first, second, winnerVector);

	//Display first place winner
	cout << endl << "FIRST PLACE: " << endl;
	winnerVector[0]->display();

	cout << endl << "RUNNER UP: " << endl;
	winnerVector[1]->display();
	
	if(count > 0)
		return 1;
	else
		return 0;
}



//Recursive function that displays the winner and the runner up.
int swimRace::stop_race(penguin_node * temp, float & fastest_time, float & second_fastest, vector<penguin_node *> & winnerVector)
{
	int count {0};	//Variable holds number of winners output
	
	//Base Case: If back at rear, check if rear matches criteria and return.
	if(temp == rear)
	{
		if(temp->race_time == fastest_time)
		{
			winnerVector[0] = temp;
			++count;
		}

		//Add second place winner to vector.
		if(temp->race_time == second_fastest)
		{
			winnerVector[1] = temp;
			++count;
		}
		return count;
	}

	//Compare current contestant with fast time.
	//If greater, update fastest time.
	if(temp->race_time < fastest_time)
	{
		//Check if old fastest value should be second fastest.
		if(fastest_time < second_fastest)
			second_fastest = fastest_time;
		fastest_time = temp->race_time;
	}

	//If current value is less than fastest but greater than second_fastest, update.
	if(temp->race_time < second_fastest && temp->race_time > fastest_time)
		second_fastest = temp->race_time;

	//Next smaller recursive instance.
	count += stop_race(temp->get_next(), fastest_time, second_fastest, winnerVector);

	//Add first place winner to vector.
	if(temp->race_time == fastest_time)
	{
		winnerVector[0] = temp;
		++count;
	}

	//Add second place winner to vector.
	if(temp->race_time == second_fastest)
	{
		winnerVector[1] = temp;
		++count;
	}
		
	return count;
}



//Wrapper. Starts the race. Loops through CLL and calls function for penguin to calculate its race time.
int swimRace::start_race()
{
	//Catch return count from recursive function.
	int count {0};
	
	//If CLL is emtpy, return.
	if(!rear)
		return 3;

	//Set temp pointer to node after rear.
//	penguin_node * temp = rear->get_next();

	//Recursive function
	count = start_race(rear->get_next());

	if(count > 0)
		return 1;
	else
		return 0;
}



//Recursive funtion to start race.
int swimRace::start_race(penguin_node * temp)
{
	int count {0};	//Tracks number of contestants for which race is stated.

	//Base Case: if temp equals rear
	if(temp == rear)
	{
		temp->race_time = temp->calc_time();
		return 1;
	}

	//Tell penguin instance to calculate race time.
	temp->race_time = temp->calc_time();

	//Next smaller recursive call.
	count += start_race(temp->get_next()) + 1;

	return count;
}



//Assignment Operator Overload.
swimRace & swimRace::operator= (const swimRace & copyFrom)
{
	//Check for self-assignment
	if(this == &copyFrom)
		return *this;

	//Copy race name.
	race_name = copyFrom.race_name;

	//Call function that copies CLL nodes.	
	copy_cll();

	return * this;
}


int swimRace::copy_cll()
{
	//If CLL is empty, return
	if(!rear)
		return 0;

	//Create new rear pointer
	penguin_node * new_rear = new penguin_node(rear->name);

	//Copy first rear node before recursive function.
	*new_rear = *rear;

	//Check if original CLL has more than 1 node;
	if(rear->get_next() == rear)
	{
		new_rear->set_next(new_rear);
		return 1;
	}

	//Pointer to traverse new CLL.
	penguin_node * new_current = new_rear;

	//Recursive call
	copy_cll(rear->get_next(), new_current, new_rear);	
	
	return 1;

}



//Copy nodes in CLL
int swimRace::copy_cll(penguin_node * current, penguin_node * new_current, penguin_node * new_rear)
{
	if(current == rear)
	{
		//Finish loop in new CLL
		new_current->set_next(new_rear);	
		return 0;
	}

	//Create new node
	penguin_node * temp = new penguin_node(current->name);
	
	//Copy info into new node
	*temp = *current;
	
	//Link new node to new rear CLL
	new_current->set_next(temp);

	copy_cll(current->get_next(), new_current->get_next(), new_rear);

	return 1;
}



//Hurtle Class
//Constructor.
hurtleRace::hurtleRace(int array_size)
{
	size = array_size;

	//Set race name.
	race_name = "Hurtle Race";
	
	//Initialize to point to array of pointers
	array_head = new k_node * [size];

	//Initialize every pointer in array.
	for(int i = 0; i < size; ++i)
		array_head[i] = nullptr;
}



//Destructor.
hurtleRace::~hurtleRace()
{
	for(int i = 0; i < size; ++i)
		delete array_head[i];

	delete [] array_head;

	array_head = nullptr;
}



//Wrapper. Adds a kangaroo contestant to race.
int hurtleRace::add_contestant(char name[])
{
	bool is_added {false};	//Catch whether node was added from recursive function.

	//Create new kangaroo node
	k_node * temp = new k_node(name);


	//Check if head is null, if so, insert first node.
	if(!array_head[0])
	{
		array_head[0] = temp;
		return 1;
	}

	//Call recursive function.
	is_added = add_contestant(array_head[0], temp);

	if(is_added == true)
		return 1;
	else
		return 0;
}



//Recursive function adds node to list.
bool hurtleRace::add_contestant(k_node * current, k_node * temp)
{
	//Base Case: If at last node in list, insert node.
	if(!current->get_next())
	{
		current->set_next(temp);
		temp = nullptr;
		return true;
	}

	//Recursive function call
	return add_contestant(current->get_next(), temp);
}



//Wrapper. Removes all contestants
int hurtleRace::remove_all()
{
	int count {0}; //Track count of nodes deleted.

	for(int i = 0; i < size; ++i)
	{
		//Call recursive function to print LLL
		count += remove_all(array_head[i]);
	}

	if(count > 0)
		return 1;
	else
		return 0;
}



//Recursively removed all functions.
int hurtleRace::remove_all(k_node * & head)
{
	int count {0};		//Track number of nodes deleted.

	//Base Case: If at end of list, return
	if(!head)
		return 0;

	//Recurse to end of list
	k_node * temp_next = head->get_next();
	count += remove_all(temp_next);
	
	//Delete node
	delete head;
	
	//Set node ptr to null
	head = nullptr;

	//Increase count	
	++count;

	return count;
}



//Wrapper. Displays all contestants.
int hurtleRace::display_all()
{
	int count {0}; //Track count of nodes displayed.

	for(int i = 0; i < size; ++i)
	{
		//Call recursive function to print LLL
		count += display_all(array_head[i]);
	}

	if(count > 0)
		return 1;
	else
		return 0;
}



//Recursive function to display all nodes
int hurtleRace::display_all(k_node * current)
{
	int count {0}; 	//Track nodes output

	//Base case: if null, return
	if(!current)
		return 0;

	current->display();
	++count;

	count += display_all(current->get_next());
	
	return count;
}



//Wrapper. Loops through ARR and tells each kangaroo to calculate race time.
int hurtleRace::start_race()
{
	int count {0}; //Track count of nodes started.

	for(int i = 0; i < size; ++i)
	{
		//Call recursive function to print LLL
		count += start_race(array_head[i]);
	}

	if(count > 0)
		return 1;
	else
		return 0;
}



//Recursive function.
int hurtleRace::start_race(k_node * current)
{
	int count {0};	//Track nodes started.

	//Base Case: if null, return;
	if(!current)
		return 0;

	//Tell kangaroo instance to calculate race time and save it.
	current->race_time = current->calc_time();

	//Add to count
	++count;

	//Recursive function call
	
	count += start_race(current->get_next());

	return count;
}



//Wrapper. Displays the first place and second place winners.
int hurtleRace::stop_race()
{
	vector<float> winning_times(2);		//Initialize a vector to hold fastest and second fastest race time.
	winning_times[0] = 10000.0;			//Fastest race time set to impossibly high number to start.
	winning_times[1] = 10000.0;			//Second fastest race time.
	
	//Loop through each element in array
	for(int i = 0; i < size; ++i)
	{
		//recursive function call
		stop_race(array_head[i], winning_times);
	}

	//Display winner
	cout << endl << "FIRST PLACE: " << endl;
	display_winners(winning_times[0]);

	//Check if seconds place winner exists, if so, display
	if(winning_times[1] != 10000.0)
	{
		cout << endl << "RUNNER UP: " << endl;
		display_winners(winning_times[1]);
	}

	return 1;
}



//Recursive function to find fasest and second fastest race times.
int hurtleRace::stop_race(k_node * head, vector<float> & winning_times)
{
	//Base case: if head is null, return
	if(!head)
		return 0;

	//If contestant is faster than current fastest time, change fastest time
	if(head->race_time < winning_times[0])
	{
		//Check if winning time should shift to second fastest time.
		if(winning_times[0] < winning_times[1])	
			winning_times[1] = winning_times[0];

		winning_times[0] = head->race_time;
	}

	//If contestants is slower than fastest but faster than second fastest, change seconds fastest.
	if(head->race_time > winning_times[0] && head->race_time < winning_times[1])
		winning_times[1] = head->race_time;

	//Recursive call
	stop_race(head->get_next(), winning_times);

	return 1;
}



//Wrapper to display winners based on time match
int hurtleRace::display_winners(float timeMatch)
{
	int count {0};	//Track number of winners displayed

	//Loop through each element in array
	for(int i = 0; i < size; ++i)
	{
		//recursive function call
		count += display_winners(array_head[i], timeMatch);
	}

	if(count > 0)
		return 1;
	else
		return 0;
}



//Displays contestants that match time passed in as argument.
int hurtleRace::display_winners(k_node * head, float timeMatch)
{
	int count{0};	//Count number of contestants displayed

	//Base Case: if head is null, return;
	if(!head)
		return 0;

	//Check if contestant matches time.
	if(head->race_time == timeMatch)
	{
		head->display();
		++count;
	}

	//Recursive call
	count += display_winners(head->get_next(), timeMatch);

	return count;
}



//Sprint Class
//Constructor.
sprintRace::sprintRace()
{
	race_name = "Sprint Race";
	head = nullptr;;
}



//Destructor.
sprintRace::~sprintRace()
{
}



//Wrapper. Adds horse contestant to race.
int sprintRace::add_contestant(char name[])
{
	//Create new contestant node
	h_node * temp = new h_node(name);

	//If list is empty, add first node
	if(!head)
	{
		head = temp;
		return 1;
	}
	
	//Call recursive fuction.
	return add_contestant(head, temp);
}



//Recursice function to add new contestant.
int sprintRace::add_contestant(h_node * head, h_node * temp)
{
	//Base case: If at last node, add node
	if(!head->get_next())
	{
		head->set_next(temp);
		return 1;
	}

	//Recursive function call
	return add_contestant(head->get_next(), temp);	
}



//Wrapper. Removes all contestants.
int sprintRace::remove_all()
{
	int count {0};	//Track number of nodes deleted.

	//If list is empty, return
	if(!head)
		return 0;

	//Recursive function call
	count = remove_all(head);

	if(count > 0)
		return 1;
	else
		return 0;
}



//Recursive function to remove all nodes.
int sprintRace::remove_all(h_node * & head)
{
	int count {0};	//Track deletions

	//Base case: if head is null return.
	if(!head)
		return 0;

	//Traverse to end of LLLa
	h_node * temp_next = head->get_next();
	count = remove_all(temp_next) + 1;

	//Delete nodes on way back
	delete head;
	head = nullptr;

	return count;
}


//Wrapper. Displays all contestants.
int sprintRace::display_all()
{
	int count {0};	//Tracks number of nodes displayed.

	//If list is empty, return 
	if(!head)
		return 0;

	//Recursive function call
	count =  display_all(head);

	if(count > 0)
		return 1;
	else
		return 0;
}



//Recursive function to display all contestants.
int sprintRace::display_all(h_node * head)
{
	//Base Case: if head is null return.
	if(!head)
		return 0;

	//Display contestant
	head->display();

	//Recursive functio call
	return display_all(head->get_next()) + 1;
}



//Wrapper function. Tells each contestant in race to calculate its race time.
int sprintRace::start_race()
{
	int count{0};		//Track number of contestants started.

	//If list is empty, return.
	if(!head)
		return 0;


	//Recursive function call
	count = start_race(head);
	
	if(count > 0)
		return 1;
	else
		return 0;
}



//Recursive function for start race.
int sprintRace::start_race(h_node * head)
{
	//Base Case: if head is null, return.
	if(!head)
		return 0;

	//Tell each contestant to calculate race time and store it
	head->race_time = head->calc_time();

	//Recursive function call
	return start_race(head->get_next()) + 1;
}



//Finds winning times and displays winners.
int sprintRace::stop_race()
{
	vector<float> winning_times(2); 	//Holds fastest and second fastest time
	winning_times[0] = 10000.0;			//Fastest Time. Set default time.
	winning_times[1] = 10000.0;			//Second Fastest Time. Set default time.

	//If list is empty, return.
	if(!head)
		return 0;

	//Recursive function call
	stop_race(head, winning_times);

	//Display Winner
	cout << endl << "FIRST PLACE: " << endl;
	display_winners(head, winning_times[0]);
	
	//If runner up exists, display it
	if(winning_times[1] != 10000.0)
	{
		cout << endl << "RUNNER UP: " << endl;
		display_winners(head, winning_times[1]);
	}

	return 1;
}



//Recursive function. Finds fastest and second fastest times.
int sprintRace::stop_race(h_node * head, vector<float> & winning_times)
{
	//Base Case: If head is null, return
	if(!head)
		return 0;

	//if current contestant is fastest so far, save time.
	if(head->race_time < winning_times[0])
	{
		//check if former fastest time should be made second fastest
		if(winning_times[0] < winning_times[1])
			winning_times[1] = winning_times[0];

		winning_times[0] = head->race_time;
	}

	//If time is slower than fastest but faster than second fastest
	if(head->race_time > winning_times[0] && head->race_time < winning_times[1])
		winning_times[1] = head->race_time;

	//Traverse to next node.
	return stop_race(head->get_next(), winning_times) + 1;
}



//Displays contestants that match time passed in as argument
int sprintRace::display_winners(h_node * head, float timeMatch)
{
	//Base Case: if list is empty, return
	if(!head)
		return 0;

	//If contestant matches time, display
	if(head->race_time == timeMatch)
		head->display();
	
	//Traverse LLL
	display_winners(head->get_next(), timeMatch);

	return 1;
}


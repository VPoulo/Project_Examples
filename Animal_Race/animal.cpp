//Vaughn Poulo
//CS202
//Program 1
//April 22, 2022
//Animal is the base class. This provides common characteristics and functions
//such as the animal name and type (because each animal has a type). The derived
//classes, penguin, kangaroo, and horse all have specific information stored in their
//own classes. Each derived class generates random numbers for its specific animal. 
//Each specific animal is the parent to a node class which allows it to point to the next
//instance of that specific animal. 

//Preprocessor Directives.
#include "animal.h"
#include <cctype>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

bool animal::seeded = false;	//Tracks if random number generator has already been seeded.



//Animal Base Class
//Constructor.
animal::animal()
{
	name = nullptr;			//Pointer to array of chars for name.
	type = nullptr;			//Pointer to array of chars for type.
	height = 0;
	age = 0;
	race_time = 0.0;		//Time taken to complete race.
	speed = 0;				//Speed of animal.
	speed_factor = 0.0;		//Speed factor which is applied to animal speed. Depending on animal attributes.
}



//Copy Constructor to copy instance of animal class.
animal::animal(animal & obj)
{
	//Create a new instance of animal class.
	animal * temp = new animal;

	//Use assignment operator to copy object.
	*temp = obj;
}



//Destructor.
animal::~animal()
{
	//Only need to delete dynamic memory in this instance.
	delete [] name;
	delete [] type;		
}



//Assignment Operator Overloading for deep copy.
animal & animal::operator = (const animal & copyFrom)
{	
	int name_len {0};
	int type_len {0};

	//Check for self-assignment
	if(this == &copyFrom)
		return *this;

	//Check if the current dynamic memory objects have values
	if(name)
	{
		delete [] name;
		name = nullptr;
	}

	if(type)
	{
		delete [] type;
		type = nullptr;
	}

	//Get length of new dynamically allocated char arrays
	name_len = strlen(copyFrom.name);
	type_len = strlen(copyFrom.type);

	//Allocated dynamic memory
	name = new char[name_len + 1];
	type = new char[type_len +1];		

	//Copy object 
	strcpy(name, copyFrom.name);
	strcpy(type, copyFrom.type);
	height = copyFrom.height;
	age = copyFrom.age;
	race_time = copyFrom.race_time;
	speed = copyFrom.speed;
	speed_factor = copyFrom.speed_factor;

	return *this;
}



//Displays animal data (name, height, age).
int animal::display()
{
	cout << endl;
	cout << "Name: " << name << endl;
	cout << "\t Animal Type: " << type << endl;
	cout << "\t Height (inches): " << height << endl;
	cout << "\t Age: " << age << endl;
	cout << "\t Speed (mph): " << speed << endl;

	return 1;
}



//Generates a random number between a min and max provided as arguments.
int animal::generate_random_number(int min, int max)
{
	int rand_num {0};

	if(!seeded)
	{
		//Seed the random generator.
		srand(1);
		seeded = true;
	}

	//Generate a random number between min and max.
	rand_num = min + rand() % ((max - min) + 1);

	return rand_num;
}



//Calculates the seconds taken to travel a distance provided (in miles) as an argument.
float animal::calc_time()
{
	float seconds_time {0.0};
	float hours_time {0.0};

	//Divide distance by speed to get the time
	hours_time = 1.0 / speed;

	//Convert hours to seconds
	seconds_time = hours_time * 60 * 60; 

	return seconds_time;
}



//Penguin Class
//Constructor.
penguin::penguin(char myName[])
{
	//Allocate dynamic memory and copy name.
	name = new char[strlen(myName) + 1];
	strcpy(name, myName);

	//Allocate dynamic memory and copy type.
	type = new char[strlen("penguin") + 1];
	strcpy(type, "penguin");

	//Assign all other attributes.
	assign_stats();
	speed_factor = assign_speed_factor();

	//Adjust animal speed based on their strength and size.
	speed = speed * speed_factor;
}



//Destructor.
//Penguin class has no dynamic memory, but this will call the animal base class destructor.
penguin::~penguin()
{
}



//Copy constructor because animal base class has dynamic memory.
penguin::penguin(const penguin & copyFrom)
{
	//Create new penguin class instance.
	penguin * temp = new penguin(copyFrom.name);

	//Copy over penguin data using assignment operator.
	*temp = copyFrom;
}



//Assignment operator overload,, since base class has dynamic memory
penguin & penguin::operator= (const penguin & copyFrom)
{
	//Call animal base class copy constructor to copy dynamic memory.
	animal::operator=(copyFrom);

	//Copy penguin specific data members.
	flipper_strength = copyFrom.flipper_strength;
	flipper_size = copyFrom.flipper_size;

	return *this;
}



//Display penguin attributes.
int penguin::display()
{
	//Call animal class display first.
	animal::display();

	//Display penguin class specific information.
	cout << "\t Flipper Size (inches): " << flipper_size << endl;
	cout << "\t Flipper Strength (1-10): " << flipper_strength << endl;
	cout << endl;

	return 1;
}



//Randomly generates penguin speed between a pre-defined range.
int penguin::assign_stats()
{	
	//Assign animal attributes randomly
	speed = generate_random_number(10, 25);
	height = generate_random_number(20, 40);
	age = generate_random_number(1, 41);
	flipper_size = generate_random_number(10, 16);
	flipper_strength = generate_random_number(0, 10);	 

	return 1;
}



//Assigns a factor to be applied to a speed based on flipper size and strength. 
float penguin::assign_speed_factor()
{
	float size_boost {0.5};
	float strength_boost {0.5};

	//If fipper strength is above average, give 10% boost.
	if(flipper_strength > 5)
		strength_boost = 0.6;

	//If flipper size is above average, give 10% boost.
	if(flipper_size > 13)
		size_boost = 0.6;

	return (size_boost + strength_boost);
}



//Kangaroo Class
//Constructor 
kangaroo::kangaroo(char myName[])
{
	//Assign dynamic memory and copy name.
	name = new char[strlen(myName) + 1];
	strcpy(name, myName);

	//Assign dynamic memory and copy type.
	type = new char[strlen("kangaroo") + 1];
	strcpy(type, "kangaroo");

	//Assign all other attributes.
	assign_stats();
	speed_factor = assign_speed_factor();

	//Adjust speed by speed_factor to account for animal size and strength.
	speed = speed * speed_factor;
}



//Destructor.
kangaroo::~kangaroo()
{
}



//Displays kangaroo specific attributes.
int kangaroo::display()
{
	animal::display();

	cout << "\t Jumping Height (inches): " << jumping_height << endl;
	cout << "\t Leg Strength (0 -10): " << leg_strength << endl;
	cout << "\t Foot Size (inches): " << foot_size << endl;
	cout << endl;
	
	return 1;
}



//
kangaroo::kangaroo(const kangaroo & copyFrom)
{
	//Create a new instance of kangaroo class
	kangaroo * temp = new kangaroo(copyFrom.name);

	//Copy info to new class instance
	*temp = copyFrom;
}



//Assignment operator overload for kangaroo, since base class has dynamic memory
kangaroo & kangaroo::operator= (const kangaroo & copyFrom)
{
	//copy base class data
	animal::operator=(copyFrom);

	//Copy over kangaroo specific data.
	leg_strength = copyFrom.leg_strength;
	jumping_height = copyFrom.jumping_height;
	foot_size = copyFrom.foot_size;
	
	return *this;
}



//Assigns characteristics of a kangroo randomly, but between pre-defines ranges.
int kangaroo::assign_stats()
{
	height = generate_random_number(48, 84);
	age = generate_random_number(3, 20);
	speed = generate_random_number(20, 45);
	jumping_height = generate_random_number(24, 84);
	leg_strength = generate_random_number(0, 10);
	foot_size = generate_random_number(8, 16);

	return 1;
}



//Assigns a factor which will be applied to the kangaroo's speed. Based on strength and size.
float kangaroo::assign_speed_factor()
{
	float size_boost {0.5};
	float strength_boost {0.5};

	//If leg strength is above average, give 10% boost.
	if(leg_strength > 5)
		strength_boost = 0.6;

	//If foot size is above average, give 10% boost.
	if(foot_size > 8)
		size_boost = 0.6;

	return (size_boost + strength_boost);
}
	


//Horse Class
//Consttructor.
horse::horse(char myName[])
{
	//Assign dynamic memory and copy name.
	name = new char[strlen(myName) + 1];
	strcpy(name, myName);

	//Assign dynamic memory and copy type.
	type = new char[strlen("horse") + 1];
	strcpy(type, "horse");

	//Assign all other attributes.
	assign_stats();
	speed_factor = assign_speed_factor();

	//Adjust animal speed by speed_factor to account for animal strength and size
	speed = speed * speed_factor;
}



//Destructor.
horse::~horse()
{
}



//Copy Constructor because base class has dynamic memory
horse::horse(const horse & copyFrom)
{
	//Create new instance of horse class
	horse * temp = new horse(copyFrom.name);

	//Copy horse information to new instance.
	*temp = copyFrom;
}



//Assignment operator overload since base class has dynamic memory
horse & horse::operator= (const horse & copyFrom)
{
	//Copy over base class data
	animal::operator=(copyFrom);

	//Copy over horse specific data
	agility = copyFrom.agility;
	leg_strength = copyFrom.leg_strength;

	return *this;
}



//Displays horse related attributes.
int horse::display()
{
	animal::display();

	cout << "\t Leg Strength: " << leg_strength << endl;
	cout << "\t Agility: " << agility << endl;
	cout << endl;

	return 1;
}



//Randomly assigns horse attributes.
int horse::assign_stats()
{
	height = generate_random_number(36, 72);
	age = generate_random_number(2, 30);
	leg_strength = generate_random_number(0, 10);
	agility = generate_random_number(0, 10);
	speed = generate_random_number(20, 55);

	return 1;
}



//Assigns a speed factor based on horse attributes.
float horse::assign_speed_factor()
{
	float agility_boost {0.5};
	float strength_boost {0.5};

	//If leg strength is above average, give 10% boost.
	if(leg_strength > 6)
		strength_boost = 0.6;

	//If foot size is above average, give 10% boost.
	if(agility > 7)
		agility_boost = 0.6;

	return (agility_boost + strength_boost);
}



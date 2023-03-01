//Vaughn Poulo
//CS202
//Program 1
//April 22, 2022
//This data type is about animals. Three animals are derived from the animal
//base class: penguin, kangaroo, and horse. A node is derived from each one 
//of those specific animals. This allows each specific animal to point to 
//another instance the same specific animal. This class should be used 
//when racing one of the animals listed is desired. Each animal calculates
//how fast it can finish a one mile race. Each animal instance created
//generates random statisitcs about itself, such as speed.


#pragma once

class animal 
{
	public:
		animal();									//Constructor.
		animal(animal &);							//Copy Constructor.
		~animal();									//Destructor.
		animal & operator= (const animal &);		//Assignment Operator.
		int display();								//Displays animal information (name, height, etc).
		int generate_random_number(int, int);		//Generates a random number between a min and max provided.  -- RANDOM NUMBERS USED
		float calc_time();							//Calculates the seconds needed to travel a distance provided.
		float race_time;							//Time, in seconds, taken to complete race.
		char * name;								//Name of the animal. --CHARACTER ARRAY USED.

	protected:
		char * type;								//Type of animal.	--CHARACTER ARRAY USED.
		int height;									//Height of animal.
		int age;									//Age of animal.
		float speed;								//Animal speed in mph.
		float speed_factor;							//Factor applied to speed based on animal attributes.

	private:
		static bool seeded;
};



class penguin:public animal
{
	public:
		penguin(char []);							//Constructor.
		~penguin();									//Destructor.
		penguin(const penguin &);					//Copy Constructor.
		penguin & operator= (const penguin &);		//Assignment operator overload.
		int display();								//Displays penguine attributes.
		int assign_stats();							//Randomly assigns penguin characteristics.
		float assign_speed_factor();				//Assigns a factor to be applied to speed based on flipper size and strength.

	private:
		int flipper_size;							//Penguin attributes.
		int flipper_strength;
};



class kangaroo:public animal
{
	public: 
		kangaroo(char []);							//Constructor.
		~kangaroo();								//Destructor.
		kangaroo(const kangaroo &);					//Copy Constructor.
		kangaroo & operator= (const kangaroo &);	//Assignment operator overload
		int display();								//Displays kangaroo attributes.
		int assign_stats();							//Randomly assigns kangaroo characteristics.
		float assign_speed_factor();				//Assigns a factor to be applied to speed based on strength and size
	
	private:
		int jumping_height;							//Kangaroo attributes.
		int leg_strength;
		int foot_size;
};



class horse:public animal
{
	public:
		horse(char []);								//Constructor.
		~horse();									//Destructor.
		horse(const horse &);						//Copy Constructor.
		horse & operator= (const horse &);			//Assignment oeprator overload.
		int display();								//Displays horse attributes.
		int assign_stats();							//Randomly asigns horse characteristics.
		float assign_speed_factor();				//Assigns a factor to be applied to speed based on agility and strength.

	private:
		int leg_strength;							//Horse Attributes.
		int agility;	
};




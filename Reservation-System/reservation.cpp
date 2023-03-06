//Vaughn Poulo
//CS202
//May 8, 2022
//Program 2
//This file contains the operator overloading required reservations to be easily used
//as a class. Reservation is the base class. From that there are three derived classes.
//There is a ski reservation dervied class, a dinner reservation derived class and a 
//museum reservation derviced class. These classes contain a combination of int,
//bool, char arrays, and strings to store the information needed. These classes
//store information like the reservation name, and other details related to a reservation.
//These classes do not contain data structures as one instnce of the class is one reservation.



#include "reservation.h"


//////////////////////////////////////////
//////////////////////////////////////////
///////////RESERVATIONS
//////////////////////////////////////////
//////////////////////////////////////////



//Constructor
reservation::reservation()
{
	guest_name = nullptr;
	reservation_type = nullptr;
}



//Constructor
reservation::reservation(char * name, int num_guests)
{
	//Allocate dynamic memory for guest name.
	guest_name = new char[strlen(name) + 1];

	//Copy over name.
	strcpy(guest_name, name);

	//Set reservation type to nullptr. Will be initialized by derived class.
	reservation_type = nullptr;

	//Add number of guests passed in. 
	number_guests = num_guests;
}



//Destructor
reservation::~reservation()
{
	//Delete dynamic memory
	delete [] guest_name;
	delete [] reservation_type;
}



//Copy Constructor
reservation::reservation(const reservation & obj)
{
	//Create new dynamic memory for name and copy over
	guest_name  = new char[strlen(obj.guest_name) + 1];
	strcpy(guest_name, obj.guest_name);

	//Create new dynamic memory for type and copy over.
	reservation_type = new char[strlen(obj.reservation_type) + 1];
	strcpy(reservation_type, obj.reservation_type);

	//Copy over number of guests.
	number_guests = obj.number_guests;
}



//Equality comparison operator. Returns true if the guest name and reservation type are the same.
bool reservation::operator== (const reservation & obj2)
{
	try
	{
		int name_compare {1};
		int reservation_compare {1};

		if(strlen(guest_name) == 0)
			throw "Name is NULL";

		//Compare guest names
		name_compare = strcmp(guest_name, obj2.guest_name);
	
		//Compare reservation types
		reservation_compare = strcmp(reservation_type, obj2.reservation_type);
	
		//If both are equal, return true
		if(name_compare == 0 && reservation_compare == 0)
			return true;
		else
			return false;
	}
	catch(char *)
	{
		cout << endl << "Cannot compare empty name.";
		return false;
	}
}



//Returns true if name matches reservation guest name.
bool reservation::operator== (char * name)
{

	//If empty pointer passed in, then do nothing
	if(!name)
		return false;

	//Copy new name into reservation
	if(0 == strcmp(guest_name, name))
		return true;
	else
		return false;
}



//Inequality comparison operator. Returns true if guest name and reservation type are different.
bool reservation::operator!= (const reservation & obj2)
{
	int name_compare {1};
	int reservation_compare {1};

	//Compare guest names
	name_compare = strcmp(guest_name, obj2.guest_name);
	
	//Compare reservation types
	reservation_compare = strcmp(reservation_type, obj2.reservation_type);

	//If both are equal, return true
	if(name_compare != 0 && reservation_compare != 0)
		return true;
	else
		return false;
}



//Assignment Operator. Copies information from one reservation into another.
reservation & reservation::operator= (const reservation & obj2)
{
	//Check for self assignment.
	if(this == &obj2)
		return *this;

	//Check if current object has values already
	if(guest_name)
	{
		delete [] guest_name;
		guest_name = nullptr;
	}

	if(reservation_type)
	{
		delete reservation_type;
		reservation_type = nullptr;
	}

	//Allocate new dynamic memory
	guest_name = new char[strlen(obj2.guest_name) + 1];
	reservation_type = new char[strlen(obj2.reservation_type) + 1];

	//Copy obj2 values into current object.
	strcpy(guest_name, obj2.guest_name);
	strcpy(reservation_type, obj2.reservation_type);
	number_guests = obj2.number_guests;

	return *this;
}

 

//Assignment Operator. Assigns the guest name to the reservation.
reservation & reservation::operator= (const char * name)
{
	//If empty pointer passed in, then do nothing
	if(!name)
		return *this;

	//Check if reservation already has name, if so delete memory.
	if(guest_name)
		delete [] guest_name;

	//Allocate new memory
	guest_name = new char[strlen(name) + 1];

	//Copy new name into reservation
	strcpy(guest_name, name);

	return *this;
}



//Assignment Operator. Updates reserction with number of guests.
reservation & reservation::operator= (int guests)
{
	//Copy number of guests into reservation.
	number_guests = guests;

	return *this;
}



//Returns true if name reservation in left value is later in the alphabet than right value.
bool reservation::operator> (const reservation & obj2)
{
	if(0 > strcmp(guest_name, obj2.guest_name))
		return true;
	else
		return false;
}



//Returns true if name reservation in left value is earlier in the alphabet than right value.
bool reservation::operator< (const reservation & obj2)
{
	if(0 < strcmp(guest_name, obj2.guest_name))
		return true;
	else
		return false;
}



//Returns true if name reservation in left value is later or equal in the alphabet than right value.
bool reservation::operator>= (const reservation & obj2)
{
	if(0 >= strcmp(guest_name, obj2.guest_name))
		return true;
	else
		return false;
}



//Returns true if name reservation in left value is earlier or equal in the alphabet than right value.
bool reservation::operator<= (const reservation & obj2)
{
	if(0 <= strcmp(guest_name, obj2.guest_name))
		return true;
	else
		return false;
}



//Adds guests from one reservation to another.
reservation& reservation::operator+= (const reservation & obj2)
{
	//Add guests to reservation.
	number_guests += obj2.number_guests;

	return *this;
}



//Adds guests to reservation.
reservation& reservation::operator+= (int add_guests)
{
	//Add guests to reservation.
	number_guests += add_guests;

	return *this;
}



//Subtracts guests from a resercation.
reservation& reservation::operator-= (int subtract_guests)
{
	//Subtract guests from reservaiton.
	number_guests -= subtract_guests;

	return *this;
}



//Addition Operator. Adds guests to the reservation.
reservation operator+ (int add_guests, const reservation & aReservation)
{
	//Copy reservation
	reservation copyReservation(aReservation);

	//Add number of guests to the reservation.	
	copyReservation.number_guests += add_guests;

	//Return copy
	return copyReservation;
}



//Addition Operator. Adds guests to the reservation.
reservation operator+ (const reservation & aReservation, int add_guests)
{
	//Copy reservation
	reservation copyReservation(aReservation);

	//Add number of guests to the reservation.	
	copyReservation.number_guests += add_guests;

	//Return copy
	return copyReservation;
}



//Minus Operator.
reservation operator- (const reservation & aReservation, int subtract_guests)
{
	//Copy reservation
	reservation copyReservation(aReservation);

	//Add number of guests to the reservation.	
	copyReservation.number_guests -= subtract_guests;

	//Return copy
	return copyReservation;
}



//Output Operator
ostream & operator<< (ostream & out, const reservation & aReservation)
{
	if(!aReservation.guest_name)
		cout << endl << "NO NAME" << endl;

	out << "Reservation: " << endl;
	out << "\t Name: " << aReservation.guest_name << endl;
	out << "\t Venue: " << aReservation.reservation_type << endl;
	out << "\t Number of Guests: " << aReservation.number_guests << endl;

	return out;
}



//Input Operator. Adds name to reservation.
istream & operator>> (istream & in, reservation & aReservation)
{
	int temp = 50;

	//Temp char array for storage
	char aName[temp];

	//Read in name to temporary storage.
	in >> aName;

	//If already has a value, delete.
	if(aReservation.guest_name)
		delete [] aReservation.guest_name;

	//Allocate new dynamic memory and copy
	aReservation.guest_name = new char[strlen(aName) + 1];
	strcpy(aReservation.guest_name, aName);

	return in;
}




//////////////////////////////////////////
//////////////////////////////////////////
///////////SKI RESERVATIONS
//////////////////////////////////////////
//////////////////////////////////////////



//Constructor.
ski_reservation::ski_reservation(char * name, int num_guests, int rentals, string lodge): reservation(name, num_guests)
{
	//Allocate dynamic memory
	reservation_type = new char[strlen("SKIING") + 1];
	
	//Copy type of reservation 
	strcpy(reservation_type, "SKIING");

	//Assign equiptment rental and lodge name
	number_equiptment_rentals = rentals;
	lodge_name = lodge;
}



//Destructor.
ski_reservation::~ski_reservation()
{
}



//Equality Comparison Operator.
bool ski_reservation::operator== (const ski_reservation & obj2)
{
	bool reservation_equal {false};
	bool equiptment_equal {false};
	bool lodge_equal {false};

	//Check if the base class data is equal
	reservation_equal = this->reservation::operator==(obj2);

	//Check other variables for equality
	equiptment_equal = (number_equiptment_rentals == obj2.number_equiptment_rentals);
	lodge_equal = (lodge_name == obj2.lodge_name);

	//If all data equal, return true
	if(reservation_equal == true && lodge_equal == true && equiptment_equal == true)
		return true;
	else
		return false;
}



//Inequality Comparison Operator.
bool ski_reservation::operator!= (const ski_reservation & obj2)
{
	return !(*this == obj2);
}



//Assignment Operator. 
ski_reservation & ski_reservation::operator= (const ski_reservation & obj2)
{
	if(*this == obj2)
		return *this;

	//Use assignment operator from base class.
	this->reservation::operator=(obj2);

	//Copy information from object
	lodge_name = obj2.lodge_name;
	number_equiptment_rentals = obj2.number_equiptment_rentals;

	return *this;	
}



//Assignment Operator. Assigns Ski Lodge.
ski_reservation & ski_reservation::operator= (const string lodge)
{
	//Assign lodge name to reservation; 
	this->lodge_name = lodge;

	//Return reservation.
	return *this;
}



//Addition Operator. Adds to the equiptment rental.
ski_reservation operator+ (int add_equiptment, const ski_reservation & obj2)
{
	//Copy Ski reservation
	ski_reservation copyReservation(obj2);				//WILL THIS COPY CORRECTLY.

	//Add equiptment to copied ski reservation
	copyReservation.number_equiptment_rentals += add_equiptment;

	//Return copied reservation
	return copyReservation;				
}



//Addition Operator. Adds to the equiptment rental.
ski_reservation operator+ (const ski_reservation & obj2, int add_equiptment)
{
	//Copy ski reservation
	ski_reservation copyReservation(obj2);

	//Add equiptment to the copied ski reservation
	copyReservation.number_equiptment_rentals += add_equiptment;

	//Return copied reservation
	return copyReservation;
}



//Minus Operator. Subtracts from the equiptment rental.
ski_reservation operator- (const ski_reservation & obj2, int subtract_equiptment)
{
	//Make a copy of the reservation
	ski_reservation copyReservation(obj2);

	//Subtract equiptment from reservation
	copyReservation.number_equiptment_rentals -= subtract_equiptment;

	//Return copied reservation
	return copyReservation;	
}



//Output Operator.
ostream & operator<< (ostream & out, const ski_reservation & obj2)
{
	//Output the parent class reservation data.
	out << static_cast<const reservation &>(obj2);

	//Output ski reservation data
	out << "\t Number of Equiptment Rentals: " << obj2.number_equiptment_rentals << endl;
	out << "\t Lodge Name: " << obj2.lodge_name << endl;
	out << endl;

	return out;	
}




//////////////////////////////////////////
//////////////////////////////////////////
///////////DINNER RESERVATIONS
//////////////////////////////////////////
//////////////////////////////////////////



//Constructor.
dinner_reservation::dinner_reservation(char * name, int guest_number, bool is_veg, int children): reservation(name, guest_number)
{
	//Allocate dynamic memory
	reservation_type = new char[strlen("DINNER") + 1];
	
	//Copy type of reservation 
	strcpy(reservation_type, "DINNER");

	//Assign number of children and vegetarian status.
	is_vegetarian = is_veg;
	number_children = children;
}



//Destructor.
dinner_reservation::~dinner_reservation()
{
}



//Equality Assignment Operator. Returns true if all fields match.
bool dinner_reservation::operator== (const dinner_reservation & obj2)
{
	bool reservation_equality {false};

	//Check if parent class reservation data is the same.
	reservation_equality = this->reservation::operator==(obj2);	

	if(reservation_equality == true && obj2.is_vegetarian == is_vegetarian && obj2.number_children == number_children)
		return true;
	else
		return false;
}



//Inequality Assignment Operator. Returns true if reservations don't match.
bool dinner_reservation::operator!= (const dinner_reservation & obj2)
{
	return !(*this == obj2);
}



//Assignment Operator. Makes reservation match assigned one.
dinner_reservation & dinner_reservation::operator= (const dinner_reservation & obj2)
{
	if(*this == obj2)
		return *this;

	//Use base class assignment operator for parent data
	this->reservation::operator=(obj2);

	//Copy over dinner specific reservation members
	is_vegetarian = obj2.is_vegetarian;
	number_children = obj2.number_children;

	//Return copy
	return *this;
}



//Assignment Operator. Updates number of children in reservation.
dinner_reservation & dinner_reservation::operator= (int num_kids)
{
	//Assign new number of children.
	number_children = num_kids;

	//Return updated reservation.
	return *this;
}



//Assignment Operator. Updates vegetarian status.
dinner_reservation & dinner_reservation::operator= (bool is_veg)
{
	//Assign vegetarian status
	is_vegetarian = is_veg;

	//Return updated reservation
	return *this;
}



//Addition Operator.  Adds children to the reservation.
dinner_reservation operator+ (int add_children, const dinner_reservation & obj2)
{
	//Copy reservation
	dinner_reservation copyReservation(obj2);

	//Update resercation 
	copyReservation.number_children += add_children;

	//Return updated copy.
	return copyReservation;
}



//Addition Operator. Adds children to the reservation.
dinner_reservation operator+ (const dinner_reservation & obj2, int add_children)
{
	//Copy reservation
	dinner_reservation copyReservation(obj2);

	//Update resercation 
	copyReservation.number_children += add_children;

	//Return updated copy.
	return copyReservation;
}



//Minus Operator. Subtracts children from the reservation.
dinner_reservation operator- (const dinner_reservation & obj2, int subtract_children)
{
	//Copy reservation
	dinner_reservation copyReservation(obj2);

	//Update resercation 
	copyReservation.number_children -= subtract_children;

	//Return updated copy.
	return copyReservation;
}



//Output Operator.
ostream & operator<< (ostream & out, const dinner_reservation & obj2)
{
	//Output the parent class reservation data.
	out << static_cast<const reservation &>(obj2);

	//Output dinner specific data members
	out << "\t Vegetarian Guests Attending: " << obj2.is_vegetarian << endl;
	out << "\t Number of Children in Party: " << obj2.number_children << endl;
	out << endl;

	return out;
}



//////////////////////////////////////////
//////////////////////////////////////////
///////////MUSEUM RESERVATIONS
//////////////////////////////////////////
//////////////////////////////////////////



//Constuctor.
museum_reservation::museum_reservation()
{
}



//Constructor
museum_reservation::museum_reservation(char * name, int guest_number, bool tour, string exhibit): reservation(name, guest_number)
{
	//Allocate dynamic memory
	reservation_type = new char[strlen("MUSEUM") + 1];
	
	//Copy type of reservation 
	strcpy(reservation_type, "MUSEUM");

	//Initialize other variables.
	guided_tour = tour;
	exhibit_name = exhibit;
}



//Destructor.
museum_reservation::~museum_reservation()
{
}



//Equality Operator. If all reservation details are the same, then return true.
bool museum_reservation::operator== (const museum_reservation & obj2)
{
	bool reservation_equality {false};

	//Check if reservation base class data is the same.
	reservation_equality = reservation::operator==(obj2);

	//Check if other data members match.
	if(reservation_equality == true && guided_tour == obj2.guided_tour && exhibit_name == obj2.exhibit_name)
		return true;
	else
		return false;
}



//Inequality Operator. Returns true if not every field matches.
bool museum_reservation::operator!= (const museum_reservation & obj2)
{
	return !(*this == obj2);
}



//Assignment Operator.	Assigns one reservation to another.
museum_reservation & museum_reservation::operator= (const museum_reservation & obj2)
{
	//Assign base class reservation data over. 
	reservation::operator=(obj2);

	//Assign remaiing information over.
	guided_tour = obj2.guided_tour;
	exhibit_name = obj2.exhibit_name;

	return *this;
}



//Assignment Operator.	Assigns the exhibit name.
museum_reservation & museum_reservation::operator= (const string exhibit)
{
	//Assign exhibit name to reservation
	exhibit_name = exhibit;

	return *this;
}



//Assignment Operator.	Assigns if a tour is part of the reservtion.
museum_reservation & museum_reservation::operator= (bool tour)
{
	//Assign guided tour to reservation
	guided_tour = tour;

	return *this;
}



//Ouptut Operator.
ostream & operator<< (ostream & out, const museum_reservation & obj2)
{
	//Output the parent class reservation data.
	out << static_cast<const reservation &>(obj2);

	//Output Museum specific data members
	out << "\t Exhibit Name: "  << obj2.exhibit_name << endl;
	out << "\t Guided Tour Requested: " <<boolalpha<< obj2.guided_tour << endl; 
	out << noboolalpha;
	out << endl;

	return out;	
}


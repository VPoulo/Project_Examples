//Vaughn Poulo
//CS202
//May 8, 2022
//Program 2
//In this file there are three classes. One class to manage each
//type of reservation. Each class contains a different data structure
//and supports the following functions: add a new reservation,
//display a reservation that matches a name, delete a reserveration
//that matches a name, display all reservations, delete all reservations.
//These classes rely heavily on the operator overloading of the reservation
//classes.


#include "reservation_list.h"


/////////////////////////////////////////////////
/////////////////////////////////////////////////
/////////////SKI RESERVATIONS LIST
/////////////////////////////////////////////////
////////////////////////////////////////////////


//Constructor.
ski_lodge::ski_lodge()
{
}



//Destructor.
ski_lodge::~ski_lodge()
{
}



//Adds a new reservation to the list.
int ski_lodge::insert(char * name, int guests, int rentals, string lodge)
{
	//Create new reservation.
	ski_reservation * temp = new ski_reservation(name, guests, rentals, lodge);

	//Add reservation to the list.
	ski_reservation_list.push_back(*temp);

	delete temp;

	return 1;
}



//Deletes a reservation from the list.
int ski_lodge::delete_reservation(char * name)
{
	int count {0};
	int list_size {0};

	//Get size of vector.
	list_size = ski_reservation_list.size();

	//Loop through vector.
	for(int element = 0; element < list_size; ++element)
	{
		//If name matches, delete.
		if(ski_reservation_list[element].reservation::operator==(name))
		{
			ski_reservation_list.erase(ski_reservation_list.begin() + element);
			++count;
		}
	}

	if(count > 0)
		return 1;
	else
		return 2;
	
}



//Remove all reservations from the list.
int ski_lodge::delete_all()
{
	//Delete all elements in vector.
	ski_reservation_list.clear();

	return 1;
}



//Display a particular reservation
int ski_lodge::display(char * name)
{
	int count {0};
	int list_size {0};

	//Get size of vector.
	list_size = ski_reservation_list.size();

	//Loop through vector.
	for(int element = 0; element < list_size; ++element)
	{
		//If name matches, display.
		if(ski_reservation_list[element].reservation::operator==(name))
		{
			cout << ski_reservation_list[element];
			++count;
		}
	}
	
	if(count > 0)
		return 1;
	else
		return 2;
}



//Display all reservations
int ski_lodge::display_all()
{
	int count {0};
	int list_size {0};

	//Get size of vector.
	list_size = ski_reservation_list.size();

	//Loop through vector
	for(int element = 0; element < list_size; ++element)
	{
		//Display each element.
		cout << ski_reservation_list[element];
		++count;
	}

	if(count > 0)
		return 1;
	else
		return 3;
}




/////////////////////////////////////////////////
/////////////////////////////////////////////////
/////////////DINNER RESERVATIONS LIST
/////////////////////////////////////////////////
////////////////////////////////////////////////



//Constructor.
restaurant::restaurant()
{
}



//Destructor.
restaurant::~restaurant()
{
}



//Add a reservation to the list.
int restaurant::insert(char * name, int number, bool veg, int children)
{
	//Create new dinner reservation.
	dinner_reservation * temp = new dinner_reservation(name, number, veg, children);

	//Add reservation to DLL.
	dinner_reservation_list.push_front(*temp);

	delete temp;

	return 1;	
}



//Delete a matching reservation.
int restaurant::delete_reservation(char * name)
{
	int count {0};

	//Traverse DLL and print each reservation.
	for(dinner_reservation i : dinner_reservation_list)
	{
		//Is the name matches, delete.
		if(i.reservation::operator==(name))
		{
			dinner_reservation_list.remove(i);	
			++count;
		}
	}
	
	//If at least one reservation printed, return success.
	if(count > 0)
		return 1;
	else
		return 0;
}



//Delete all reservations.
int restaurant::delete_all()
{
	//Clear all contents of list.
	dinner_reservation_list.clear();

	return 1;
}



//Display a specific reservation.
int restaurant::display(char * name)
{
	int count {0};

	//Traverse DLL and print each reservation.
	for(dinner_reservation i : dinner_reservation_list)
	{
		//If the name matched, display.
		if(i.reservation::operator==(name))
		{
			cout << i;
			++count;
		}
	}
	
	//If at least one reservation printed, return success.
	if(count > 0)
		return 1;
	else
		return 2;
}



//Display all reservations.
int restaurant::display_all()
{
	int count {0};

	//Traverse DLL and print each reservation.
	for(dinner_reservation i : dinner_reservation_list)
	{
		cout << i;
		++count;
	}
	
	//If at least one reservation printed, return success.
	if(count > 0)
		return 1;
	else
		return 3;
}




/////////////////////////////////////////////////
/////////////////////////////////////////////////
/////////////MUSEUM RESERVATIONS LIST
/////////////////////////////////////////////////
////////////////////////////////////////////////



//Constructor.
museum::museum()
{	
}



//Destructor.
museum::~museum()
{
	museum_reservation_list.remove_all();
}



//Adds new reservation to reservation list.
int museum::insert(char * name, int number, bool tour, string exhibit)
{
	//Make a new museum reservation.
	museum_reservation * temp = new museum_reservation(name, number, tour, exhibit);
	
	//Add new reservation to list.
	museum_reservation_list.insert(*temp);	

	delete temp;

	return 1;
}



//Deletes a specific reservation.
int museum::delete_reservation(char * name)
{
	return museum_reservation_list.remove(name);
}



//Deletes everything in the list.
int museum::delete_all()
{
	museum_reservation_list.remove_all();
	return 1;
}



//Display matching reservation.
int museum::display(char * name)
{
	return museum_reservation_list.display(name);
}



//Display all reservations. 
int museum::display_all()
{
	museum_reservation_list.display_all();
	return 1;
}


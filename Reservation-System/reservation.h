//Vaughn Poulo
//CS202
//May 8, 2022
//Program 2
//This file contains a base reservation class and three derived class.
//The base reservation class contains information that would be neeed
//for any kind of reservation, such as size, and name. The derived classes
//are each for a specific type of reservation. This file contains reservations
//for dinner, skiing, and a museums. The base class has a full compiment of
//operator overloading, which makes it easy to work with. The derived classes
//have all appropriate operator overloading depending on the information that
//class holds.


#pragma once
#include <string>
#include <cctype>
#include <cstring>
#include <iostream>
using namespace std;


class reservation
{
	public:
		reservation();															//Constructor.
		reservation(char * name, int guest_number);								//Constructor.
		~reservation();															//Destructor.
		reservation(const reservation &);										//Copy Constructor.
		bool operator== (const reservation &);									//Compares two reservations.
		bool operator== (char *);												//Compares reservation name to name.
		bool operator!= (const reservation &);									//Compares two reservations.
		reservation& operator= (const reservation &);							//Assigns reservation.
		reservation& operator= (const char *);									//Assigns name of reservation.
		reservation& operator= (int);											//Assigns number of guests.
		bool operator> (const reservation &);									//Compares name of two reservations.
		bool operator< (const reservation &);									//Compares name of two reservations.
		bool operator>= (const reservation &);									//Compares names of two reservations.
		bool operator<= (const reservation &);									//Compares name of two reservations.
		reservation& operator+= (const reservation &);							//Combines reservations.
		reservation& operator+= (int);											//Increases guest count.
		reservation& operator-= (int);											//Descreases guest count.
		friend reservation operator+ (int, const reservation &);				//Adds to guest count.
		friend reservation operator+ (const reservation &, int);				//Combines two reservations.
		friend reservation operator- (const reservation &, int);				//Decreases guest count.
		friend ostream& operator<< (ostream &, const reservation &);			//Displays.
		friend istream& operator>> (istream &, reservation &);					//Reads in name to reservation.

	protected:
		char * guest_name;
		char * reservation_type;
		int number_guests;
};



class ski_reservation: public reservation
{
	public:
		ski_reservation(char *, int, int, string);								//Constructor.
		~ski_reservation();														//Destructor.
		bool operator== (const ski_reservation &);								//Returns true if two reservations are equal.
		bool operator!= (const ski_reservation &);								//Inequality check.
		ski_reservation & operator= (const ski_reservation &);					//Assings one reservation into another.
		ski_reservation & operator= (const string);								//Assigns lodge name.
		friend ski_reservation operator+ (int, const ski_reservation &);		//Add to rental.
		friend ski_reservation operator+ (const ski_reservation &, int);		//Add to rental.
		friend ski_reservation operator- (const ski_reservation &, int);		//Subtract rental.
		friend ostream & operator<< (ostream &, const ski_reservation &);		//Display.

	protected:
		int number_equiptment_rentals;
		string lodge_name;
};



class dinner_reservation: public reservation
{
	public:
		dinner_reservation(char *, int, bool, int);									//Constructor.
		~dinner_reservation();														//Destructor.
		bool operator== (const dinner_reservation &);								//Checks if two reservations are equal.
		bool operator!= (const dinner_reservation &);								//Checks inequality of two reservations.
		dinner_reservation & operator= (const dinner_reservation &);				//Assigns one reservation to another.
		dinner_reservation & operator= (int);										//Assigns number of children.
		dinner_reservation & operator= (bool);										//Assigns vegetarian status.
		friend dinner_reservation operator+ (int, const dinner_reservation &);		//Increase number of children.
		friend dinner_reservation operator+ (const dinner_reservation &, int);		//Increase number of children.
		friend dinner_reservation operator- (const dinner_reservation &, int);		//Decrease number of children.
		friend ostream & operator<< (ostream &, const dinner_reservation &);		//Displays

	protected:
		bool is_vegetarian;
		int number_children;
};



class museum_reservation: public reservation
{
	public:
		museum_reservation();														//Constructor.
		museum_reservation(char *, int, bool, string);								//Constructor.
		~museum_reservation();														//Destructor.
		bool operator== (const museum_reservation &);								//Checks equality of two reservations.
		bool operator!= (const museum_reservation &);								//Checks inequality of two reservations.
		museum_reservation & operator= (const museum_reservation &);				//Assigns one reservation into another.
		museum_reservation & operator= (const string);								//Assigns exhibit name.
		museum_reservation & operator= (bool);										//Assigns guided tour.
		friend ostream & operator<< (ostream &, const museum_reservation &);		//Displays

	protected:
		bool guided_tour;
		string exhibit_name;
};


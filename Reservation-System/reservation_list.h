//Vaughn Poulo
//CS202
//May 8, 2022
//Program 2
//This file contains three classes, one for each type of reservation.
//Each class uses a different data type. The ski_lodge classes uses a
//vector data structure from the STL. The restaurant class uses
//a forward list from the STL. The museum classes uses a DLL template
//which can be found in DLL.h and DLL.tpp.



#pragma once
#include <string>
#include <vector>
#include <forward_list>
#include <cctype>
#include <cstring>
#include <iostream>
#include "reservation.h"
#include "DLL.h"
using namespace std;



class ski_lodge
{
	public:
		ski_lodge();										//Constructor.
		~ski_lodge();										//Destructor.
		int insert(char *, int, int, string);				//Adds new reservation to list.
		int delete_reservation(char *);						//Delete matching reservation.
		int delete_all();									//Delete all reservations.
		int display(char *);								//Display specific reservation.
		int display_all();									//Display all reservations.

	private:
		vector<ski_reservation> ski_reservation_list;
};



class restaurant
{
	public:
		restaurant();										//Constructor.
		~restaurant();										//Destructor.
		int insert(char *, int, bool, int);					//Add new reservation to list.
		int delete_reservation(char *);						//Deletes a specific reservation.
		int delete_all();									//Deletes all reservations.
		int display(char *);								//Display matching reservation.
		int display_all();									//Display all reservations.

	private:
		forward_list<dinner_reservation> dinner_reservation_list;
};



class museum
{
	public:
		museum();											//Constructor.
		~museum();											//Destructor.
		int insert(char *, int, bool, string);				//Add new reservation.
		int delete_reservation(char *);						//Delete a specific reservation.
		int delete_all();									//Delete all reservations.
		int display(char *);								//Display specific reservation.
		int display_all();									//Display all reservations.

	private:
		DLL<museum_reservation> museum_reservation_list;						
};


//Vaughn Poulo
//CS202
//Program 3
//May 23, 2022
//The concept class and its derived classes should be used if storing
//information about programming concepts is desired. The base class holds
//information about the core of a topic. There are three derviced classes,
//which hold specific informtion about STL syntax, Modern C++ topics,
//and the Python Library. The base class is a abstract base class, and 
//has a structure that allows for dynamic binding to be used. Each class
//has a function getInformation that prompts the user to fill in information.


#include "concept.h"


//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//CONCEPT CLASS
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

concept::concept()
{
}


concept::~concept()
{
}


//Compares keyword of concepts for equality.
bool concept::operator==(string matchKeyword)
{
	//Check if string are equal.
	if(keyword == matchKeyword)
		return true;
	else
		return false;
}



//Compares keyword of concept for inequality.
bool concept::operator!=(string matchKeyword)
{
	//Return opposite of equality comparison.
	return !(*this == matchKeyword);
}



//Compares keyword of concepts.
bool concept::operator<=(const concept & aConcept)
{
	//Check if string is less than or equal.
	if(keyword <= aConcept.keyword)
		return true;
	else
		return false;
}



//Compares keyword of concepts.
bool concept::operator<(const concept & aConcept)
{
	//Check if keyword is less than
	if(keyword < aConcept.keyword)
		return true;
	else
		return false;
}



//Compares keyword of concepts.
bool concept::operator>=(const concept & aConcept)
{
	//Check if keyword is greater than or equal to.
	if(keyword >= aConcept.keyword)
		return true;
	else
		return false;
}



//Compares keyword of concepts.
bool concept::operator>(const concept & aConcept)
{
	//Check if keyword is greater than.
	if(keyword > aConcept.keyword)
		return true;
	else
		return false;
}



//Prompt the user for base level information.
void concept::getInformation()
{
	//Continue asking for keyword until satisfactory keyword is given.
	do {
		try	{
			//Prompt user for keyword.
			cout << endl << "Enter a keyword for the concept: ";
			getline(cin, keyword, '\n');
			
			for(string::iterator i = keyword.begin(); i != keyword.end(); ++i)
				*i = toupper(*i);
		
			//If user doesn't enter meaningful data, throw error.
			if(keyword == "" || keyword == " ")
				throw "name required";	
		}
		catch(char const * error)
		{
			cout << endl << "The keyword field is required" << endl;
		}
	} while(keyword == "" || keyword == " ");

	//Continue asking for URL until satisfactory URL is given.
	do {
		try {
			//Prompt user for URL.
			cout << "Enter the URL: ";
			getline(cin, url, '\n');

			//If user doesn't enter meaningful data, throw error.
			if(url == "" || url == " ")
				throw "url required";
		}
		catch(char const * error)
		{
			cout << endl << "The URL field is required" << endl;
		}
	} while(url == "" || url == " ");

	//Continue asking for Rating until number 1-10 is given.
	do	{
		try {
			//Prompt user to enter a rating.
			cout << "Enter a rating for the website (1 - 10): ";
			cin >> rating;
			cin.ignore(200, '\n');

			if(rating < 0.0 || rating > 10.0)
				throw rating;
		}
		catch(float rating)
		{
			cout << endl << rating << " is not a valid rating. You must enter a number between 1 and 10.";
		}
	} while (rating < 0.0 || rating > 10.0);
}


void concept::display()
{
	cout << endl;
	cout << "Concept Keyword: " << keyword << endl;
	cout << "\t Type: " << concept_type << endl;
	cout << "\t URL: " << url << endl;;
	cout << "\t Rating: " << rating << endl;;
}



//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//STL_SYNTAX CLASS
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////



//Constructor.
stl_syntax::stl_syntax()
{
	concept_type = "STL Syntax";	
}



//Destructor.
stl_syntax::~stl_syntax()
{
}



//Displays concept.
void stl_syntax::display()
{
	//Call base class display.
	concept::display();

	//Create an iterator.
	vector<method_container>::iterator element;

	//Loop through vector and print each element.
	for(element = methods.begin(); element != methods.end(); ++element)
	{
		cout << "\t Method: " << element->name << endl;
		cout << "\t Description: " << element->desc << endl;
		cout << endl;
	}
}



//WHAT SHOULD THIS DO
void stl_syntax::select()
{
	cout << endl;
	cout << "Copy & Paste the URL for the STL Syntax Concept into your browser:" << endl;
	cout << url;
	cout << endl;
}



//Prompts the user to privde information.
void stl_syntax::getInformation()
{
	//Call base class method
	concept::getInformation();

	//Create instance of method container class to add to vector.
	method_container new_method;

	//Continue asking for method until satisfactory answer given.
	do {
		try	{
			//Prompt user for keyword.
			cout << "Enter a method related to concept: ";
			getline(cin, new_method.name, '\n');
	
			//If user doesn't enter meaningful data, throw error.
			if(new_method.name == "" || new_method.name == " ")
				throw "method required";	
		}
		catch(char const * error)
		{
			cout << endl << "The method name is required" << endl;
		}
	} while(new_method.name  == "" || new_method.name == " ");

	//Continue asking for method description until one is given.
	do {
		try {
			//Prompt user for URL.
			cout << "Enter method description: ";
			getline(cin, new_method.desc, '\n');

			//If user doesn't enter meaningful data, throw error.
			if(new_method.desc == "" || new_method.desc == " ")
				throw "description required";
		}
		catch(char const * error)
		{
			cout << endl << "The method description is required" << endl;
		}
	} while(new_method.desc == "" || new_method.desc == " ");

	
	//Add new method to vector.
	methods.push_back(new_method);
}



//Changes the rating of the website.
void stl_syntax::changeRating()
{
	//Prompt user for new rating.
	do	{
		try {
			//Prompt user to enter a rating.
			cout << "Enter a new rating for the website (1 - 10): ";
			cin >> rating;
			cin.ignore(200, '\n');

			if(rating < 0 || rating > 10)
				throw rating;
		}
		catch(float rating)
		{
			cout << endl << rating << " is not a valid rating. You must enter a number between 1 and 10." << endl;
		}
	} while (rating < 0 || rating > 10);


	cout << endl << "UPDATED:" << endl;
}



//Adds method to array.
void stl_syntax::addMethod()
{
	//Create instance of method container class to add to vector.
	method_container new_method;

	//Continue asking for method until satisfactory answer given.
	do {
		try	{
			//Prompt user for keyword.
			cout << "Enter a method related to concept: ";
			getline(cin, new_method.name, '\n');
	
			//If user doesn't enter meaningful data, throw error.
			if(new_method.name == "" || new_method.name == " ")
				throw "method required";	
		}
		catch(char const * error)
		{
			cout << endl << "The keyword field is required" << endl;
		}
	} while(new_method.name  == "" || new_method.name == " ");

	//Continue asking for method description until one is given.
	do {
		try {
			//Prompt user for URL.
			cout << "Enter method description: ";
			getline(cin, new_method.desc, '\n');

			//If user doesn't enter meaningful data, throw error.
			if(new_method.desc == "" || new_method.desc == " ")
				throw "description required";
		}
		catch(char const * error)
		{
			cout << endl << "The URL field is required" << endl;
		}
	} while(new_method.desc == "" || new_method.desc == " ");

	//Add new method to vector.
	methods.push_back(new_method);

	cout << endl << "UPDATED:" << endl;
}




//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//MODERN CONCEPT CLASS
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////


//Constructor.
modern_concept::modern_concept()
{
	concept_type = "Modern Concept";
}



//Destructor.
modern_concept::~modern_concept()
{
}



//Displays concept.
void modern_concept::display()
{
	//Display base class information.
	concept::display();

	cout << "\t Description: " << desc << endl;
	cout << "\t Benefit: "	<< benefit << endl;
	cout << "\t Drawback: " << drawback << endl;
	cout << endl;
}



//WHAT SHOULD THIS DO
void modern_concept::select()
{
	cout << endl;
	cout << "Copy & Paste the URL for the Modern C++ Concept into your browser:" << endl;
	cout << url;
	cout << endl;
}



//Prompts user for information.
void modern_concept::getInformation()
{
	//Get base class concept informaiton.
	concept::getInformation();

	//Prompt user for desc. 
	//Continue prompting until field is satisfactory.
	do {
		try {
			cout << "Enter a description of the modern concept: ";
			getline(cin, desc, '\n');
	
			if(desc == "" || desc == " ")
				throw "Desc Required";
		}
		catch(char const * error)
		{
			cout << endl << "A description is required." << endl;
		}
	} while(desc == "" || desc == " ");

	//Prompt user for benefit.
	cout << "Enter a benefit: ";
	getline(cin, benefit, '\n');
	
	//Prompt user for drawback.
	cout << "Enter a drawback: ";
	getline(cin, drawback, '\n');
}



//Changes the rating of the concept.
void modern_concept::changeRating()
{
	//Prompt user for new rating.
	do	{
		try {
			//Prompt user to enter a rating.
			cout << "Enter a new rating for the website (1 - 10): ";
			cin >> rating;
			cin.ignore(200, '\n');

			if(rating < 0 || rating > 10)
				throw rating;
		}
		catch(float rating)
		{
			cout << endl << rating << " is not a valid rating. You must enter a number between 1 and 10." << endl;
		}
	} while (rating < 0 || rating > 10);

	cout << endl << "UPDATED:" << endl;
}



//Adds benefits to the concept.
void modern_concept::addBenefit()
{
	//Loop until non-empty field is given.
	do {
		try {
			cout << endl;
			cout << "Enter a benefit: ";
			getline(cin, benefit, '\n');

			//If nothing entered, throw error
			if(benefit == "" || benefit == " ")
				throw "benefit required";
		}
		catch(char const * error)
		{
			cout << endl << "A benefit field is required and cannot be empty." << endl;
		}
	} while( benefit == "" || benefit == " ");
}



//Adds drawbacks to the concept.
void modern_concept::addDrawback()
{
	//Loop until non-empty field is given.
	do {
		try {
			cout << endl;
			cout << "Enter a drawback: ";
			getline(cin, drawback, '\n');

			//If nothing entered, throw error
			if(drawback == "" || drawback == " ")
				throw "drawback required";
		}
		catch(char const * error)
		{
			cout << endl << "A drawback field is required and cannot be empty." << endl;
		}
	} while(drawback == "" || drawback == " ");
}




//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//PYTHON LIBRARY CLASS
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////



//Constructor.
python_library::python_library()
{
	concept_type = "Python Library";
}



//Destructor.
python_library::~python_library()
{
}



//Displays the concept.
void python_library::display()
{
	//Display concept data.
	concept::display();

	//Display class sepcific data.
	cout << "\t Library Description: " << desc << endl;
	
	//Loop through array and print elements.
	for(int i = 0; i < element; ++i)
	{
		cout << "\t Method: " << methods[i].name << endl;
		cout << "\t Description: " << methods[i].desc << endl;
		cout << endl;
	}
	
	cout << endl;
}



//WHAT SHOULD THIS DO
void python_library::select()
{
	cout << endl;
	cout << "Copy & Paste the URL for the Python Library Concept into your browser:" << endl;
	cout << url;
}



//Prompts user for information.
void python_library::getInformation()
{
	//Call base class method
	concept::getInformation();

	//Prompt user to enter library description.
	//Continue prompting until field is satisfactory.
	do {
		try {
			cout << "Enter a description of the library: ";
			getline(cin, desc, '\n');
	
			if(desc == "" || desc == " ")
				throw "Desc Required";
		}
		catch(char const * error)
		{
			cout << endl << "A description is required." << endl;
		}
	} while(desc == "" || desc == " ");

	//Continue asking for method until satisfactory answer given.
	do {
		try	{
			//Prompt user for keyword.
			cout << "Enter a method related to concept: ";
			getline(cin, methods[element].name, '\n');
	
			//If user doesn't enter meaningful data, throw error.
			if(methods[element].name == "" || methods[element].name == " ")
				throw "method required";	
		}
		catch(char const * error)
		{
			cout << endl << "The keyword field is required" << endl;
		}
	} while(methods[element].name  == "" || methods[element].name == " ");

	//Continue asking for method description until one is given.
	do {
		try {
			//Prompt user for URL.
			cout << "Enter method description: ";
			getline(cin, methods[element].desc, '\n');

			//If user doesn't enter meaningful data, throw error.
			if(methods[element].desc == "" || methods[element].desc == " ")
				throw "description required";
		}
		catch(char const * error)
		{
			cout << endl << "The method description is required" << endl;
		}
	} while(methods[element].desc == "" || methods[element].desc == " ");	

	//Increase the element variable to stay updated.
	++element;
}



//Changes the rating of the website.
void python_library::changeRating()
{
	//Prompt user for new rating.
	do	{
		try {
			//Prompt user to enter a rating.
			cout << "Enter a new rating for the website (1 - 10): ";
			cin >> rating;
			cin.ignore(200, '\n');

			if(rating < 0 || rating > 10)
				throw rating;
		}
		catch(float rating)
		{
			cout << endl << rating << " is not a valid rating. You must enter a number between 1 and 10.";
		}
	} while (rating < 0 || rating > 10);

	cout << endl << "UPDATED:" << endl;
}



//Adds method to array.
void python_library::addMethod()
{
	//Continue asking for method until satisfactory answer given.
	do {
		try	{
			//Prompt user for keyword.
			cout << "Enter a method related to concept: ";
			getline(cin, methods[element].name, '\n');
	
			//If user doesn't enter meaningful data, throw error.
			if(methods[element].name == "" || methods[element].name == " ")
				throw "method required";	
		}
		catch(char const * error)
		{
			cout << endl << "The keyword field is required" << endl;
		}
	} while(methods[element].name  == "" || methods[element].name == " ");

	//Continue asking for method description until one is given.
	do {
		try {
			//Prompt user for URL.
			cout << "Enter method description: ";
			getline(cin, methods[element].desc, '\n');

			//If user doesn't enter meaningful data, throw error.
			if(methods[element].desc == "" || methods[element].desc == " ")
				throw "description required";
		}
		catch(char const * error)
		{
			cout << endl << "The method descrioption is required" << endl;
		}
	} while(methods[element].desc == "" || methods[element].desc == " ");	

	//Increase the element variable to stay updated.
	++element;

	cout << endl << "UPDATED:" << endl;
}



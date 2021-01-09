#include "hospital.cpp"
#include <iostream>
using namespace std;

int main()
{
	hospital<string> PATIENT;   // name of linked list (our system)

	//read data from file and store in linkedlist (our system)
	PATIENT.ReadFrom_file("listOfpatient.txt");

	//Execution all function in the system
	PATIENT.displayIN_main();

	//delete all data from file befor store the new
	remove("listOfpatient.txt");

	//write all date from linkedlist to file
	PATIENT.WriteIn_file("listOfpatient.txt");

	
	return 0;
}
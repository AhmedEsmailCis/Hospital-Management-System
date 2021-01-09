#include "hospital.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
template <class T>
Pdata<T>::Pdata()
{
	Fname = "";
	address = "";
	disease = "";
	sex = "";
	date = "";
	age = 0;
	total_money = 0.0;
	total_deposited = 0.0;
	next = 0;
}
//********************************************************************************************************************
template <class T>
Pdata<T>::Pdata(T n, T a, T d, T s, T Date, int g, int D, double x, double y)
{
	Fname = n;
	address = a;
	disease = d;
	sex = s;
	date = Date;
	age = g;
	department = D;
	total_money = x;
	total_deposited = y;
	next = 0;
}
//********************************************************************************************************************
template <class T>
hospital<T>::hospital(void)
{
	size = 0;
	head = tail = 0;
}
//********************************************************************************************************************
template <class T>
void hospital<T>::ReadFrom_file(T patientFilePath)
{
	char line[1000];
	char* token;
	ifstream read;
	//Open listOfpatient.txt
	read.open(patientFilePath);
	//If file not found, return
	if (!read.is_open())
	{
		cout << "File not found" << endl;
		return;
	}
	//While end of file is not reached
	while (!read.eof())
	{
		Pdata<T> patient;
		//Readline
		read.getline(line, 1000);
		char *ptr;
		token = strtok_s(line, "-", &ptr);
		while (token)
		{
			patient.Fname = token;
			token = strtok_s(NULL, "-", &ptr);
			patient.address = token;
			token = strtok_s(NULL, "-", &ptr);
			patient.disease = token;
			token = strtok_s(NULL, "-", &ptr);
			patient.sex = token;
			token = strtok_s(NULL, "-", &ptr);
			patient.date = token;
			token = strtok_s(NULL, "-", &ptr);
			patient.age = atoi(token);     //convert to int
			token = strtok_s(NULL, "-", &ptr);
			patient.department = atoi(token);      //convert to int
			token = strtok_s(NULL, "-", &ptr);
			patient.total_money = atof(token);    //convert to double
			token = strtok_s(NULL, "-", &ptr);
			patient.total_deposited = atof(token);  //convert to double
			Add_patient(patient.Fname, patient.address, patient.disease, patient.sex, patient.date, patient.age, patient.department, patient.total_money, patient.total_deposited);
			token = strtok_s(NULL, "-", &ptr);
		}
	}
}
//********************************************************************************************************************
template <class T>
void hospital<T>::displayIN_main(void)
{
	cout << "            *************************************************" << endl;
	cout << "            *                                               *" << endl;
	cout << "            *                                               *" << endl;
	cout << "            *     Welcome To Hospital Management System     *" << endl;
	cout << "            *                                               *" << endl;
	cout << "            *                                               *" << endl;
	cout << "            *************************************************" << endl;
	int number;
	do
	{
		//show all option in our system
		cout << "            *************************************************" << endl;
		cout << "            *    1-Add a new patient .                      *" << endl;
		cout << "            *    2-Find (search) patient and modify data .  *" << endl;
		cout << "            *    3-List patients in alphabetical order .    *" << endl;
		cout << "            *    4-List Emergency patients .                *" << endl;
		cout << "            *    5-List O.P.D. patients .                   *" << endl;
		cout << "            *    6-List patients in a particular date .     *" << endl;
		cout << "            *    7-Show the patient financial information . *" << endl;
		cout << "            *    8-Delete patient records .                 *" << endl;
		cout << "            *    9-Exit And Save .                          *" << endl;
		cout << "            *************************************************" << endl;
		cout << "Enter Your Choice : ";
		cin >> number;
		if (number == 1)
		{
			addIN_hosoital();
		}
		else if (number == 2)
		{
			T l;
			cout << "Enter the Patient Name to Search :";
			cin.ignore();
			getline(std::cin, l);
			search(l);
		}
		else if (number == 3)
		{
			listPatientBy_alphabeticalOrder();
		}
		else if (number == 4)
		{
			listPatientIn_Emergency();
		}
		else if (number == 5)
		{

			listPatientIn_OPD();
		}
		else if (number == 6)
		{
			T l;
			cout << "Enter the Date as 00/00/2000:";
			cin.ignore();
			getline(std::cin, l);
			listPatientBy_date(l);
		}
		else if (number == 7)
		{
			T l;
			cout << "Enter the Patient Name  :";
			cin.ignore();
			getline(std::cin, l);
			patientExpenditures(l);
		}
		else if (number == 8)
		{
			T l;
			cout << "Enter the Patient Name to Delete:";
			cin.ignore();
			getline(std::cin, l);
			Delete_patient(l);
		}

	} while (number != 9);
	cout << "            ***{ Thank You For Using Our System }*** " << endl;
}
//********************************************************************************************************************
template <class T>
Pdata<T>* hospital<T>::findPatient(T val)
{
	Pdata<T>* tmp = head;
	while ((tmp != NULL) && (tmp->Fname != val))
		tmp = tmp->next;
	return tmp;
}
//********************************************************************************************************************
template <class T>
bool hospital<T>::contains(T val)
{
	Pdata<T>* tmp = findPatient(val);
	return (tmp != NULL);
}
//********************************************************************************************************************

template <class T>
void hospital<T>::show(T val)
{
	Pdata<T>* tmp = findPatient(val);
	cout << "----------------------------------------------------------------" << endl;
	cout << "the name :" << tmp->Fname << endl;
	if (tmp->department == 0)
		cout << "The Department is : Emergency department" << endl;
	else
		cout << "The Department is : outpatient department (O.P.D)." << endl;
	cout << "the address :" << tmp->address << endl;
	cout << "disease description :" << tmp->disease << endl;
	cout << "the sex :" << tmp->sex << endl;
	cout << "the date :" << tmp->date << endl;
	cout << "the age :" << tmp->age << " years" << endl;
	cout << "the total money :" << tmp->total_money << " EGP." << endl;
	cout << "the total deposited :" << tmp->total_deposited << " EGP." << endl;
	cout << "----------------------------------------------------------------" << endl;
}
//********************************************************************************************************************
template <class T>
void hospital<T>::addIN_hosoital(void)
{
	Pdata<T> patient;
	int x;
	cout << " 1-Emergency department ." << endl;
	cout << " 2-outpatient department (O.P.D) ." << endl;
	cout << "Enter the department 1 OR 2 : ";
	cin >> x;
	if (x == 1)
		patient.department = 0;
	else if (x == 2)
		patient.department = 1;

	getline(std::cin, patient.Fname);
	cout << "Enter the name :";
	getline(std::cin, patient.Fname);
	cout << "Enter the sex :";
	getline(std::cin, patient.sex);
	cout << "Enter the Address :";
	getline(std::cin, patient.address);
	cout << "Enter the Disease Description  :";
	getline(std::cin, patient.disease);
	cout << "Enter the Date :";
	getline(std::cin, patient.date);
	cout << "Enter the Age :";
	cin >> patient.age;
	cout << "Enter the Total money  :";
	cin >> patient.total_money;
	cout << "Enter the Total deposited  :";
	cin >> patient.total_deposited;
	Add_patient(patient.Fname, patient.address, patient.disease, patient.sex, patient.date, patient.age, patient.department, patient.total_money, patient.total_deposited);
}
//********************************************************************************************************************
template <class T>
void hospital<T>::Add_patient(T n, T a, T d, T s, T Date, int g, int D, double x, double y)
{
	Pdata<T>* patient = new Pdata<T>(n, a, d, s, Date, g, D, x, y);
	if (head == 0)
		head = tail = patient;
	else
	{
		tail->next = patient;
		tail = patient;
	}
	size++;
}
//********************************************************************************************************************
template <class T>
void hospital<T>::search(T val)
{
	if (!contains(val))
	{
		cout << "The Patient Not Found" << endl;
		cout << "----------------------------------------------------------------" << endl;
	}
	else
	{
		show(val);
		int x;
		do
		{
			cout << "to Modify data Enter 1 OR to End Enter 0 " << endl;
			cout << "Enter Your choice :";
			cin >> x;
			if (x == 1)
			{
				Pdata<T>* tmp = findPatient(val);
				edit(tmp);
			}
			else if (x == 0)
				return;
			cout << endl;
		} while ((x != 1) && (x != 0));
	}
}
//********************************************************************************************************************
template <class T>
void hospital<T>::edit(Pdata<T>* s)
{
	Pdata<T>* tmp = s;
	int x;
	cout << " 1-Emergency department ." << endl;
	cout << " 2-outpatient department (O.P.D) ." << endl;
	cout << "Enter the department 1 OR 2 : ";
	cin >> x;
	if (x == 1)
		tmp->department = 0;
	else if (x == 2)
		tmp->department = 1;

	getline(std::cin, tmp->Fname);
	cout << "Enter the new name :";
	getline(std::cin, tmp->Fname);
	cout << "Enter the sex :";
	getline(std::cin, tmp->sex);
	cout << "Enter the address :";
	getline(std::cin, tmp->address);
	cout << "Enter the disease description  :";
	getline(std::cin, tmp->disease);
	cout << "Enter the age :";
	cin >> tmp->age;
	cout << "Enter the date :";
	getline(std::cin, tmp->date);
	cout << "Enter the total money  :";
	cin >> tmp->total_money;
	cout << "Enter the total deposited  :";
	cin >> tmp->total_deposited;
	cout << "done" << endl;
	cout << "----------------------------------------------------------------" << endl;
}
//********************************************************************************************************************
template <class T>
void hospital<T>::listPatientBy_alphabeticalOrder(void)
{
	Pdata<T>* tmp = head;
	T *tmpname = new T[size];
	for (int m = 0; m < size; m++)
	{
		tmpname[m] = tmp->Fname;
		tmp = tmp->next;
	}
	for (int i = 0; i<size; i++)
	{
		for (int j = 0; j<size; j++)
		{
			tmpname[j];
			if (tmpname[i]<tmpname[j])
				swap(tmpname[j], tmpname[i]);
		}
	}
	for (int i = 0; i<size; i++)
	{
		cout << tmpname[i] << endl;
	}
	delete [] tmpname;
}
//********************************************************************************************************************
template <class T>
void hospital<T>::listPatientIn_Emergency(void)
{
	Pdata<T>* tmp = head;
	while (tmp != NULL)
	{
		if (tmp->department == 0)
		{
			show(tmp->Fname);
		}
		tmp = tmp->next;
	}
}
//********************************************************************************************************************
template <class T>
void hospital<T>::listPatientIn_OPD(void)
{
	Pdata<T>* tmp = head;
	while (tmp != NULL)
	{
		if (tmp->department == 1)
		{
			show(tmp->Fname);
		}
		tmp = tmp->next;
	}
}
//********************************************************************************************************************
template <class T>
void hospital<T>::listPatientBy_date(T dat)
{
	Pdata<T>* tmp = head;
	while (tmp != NULL)
	{
		if (tmp->date == dat)
		{
			show(tmp->Fname);
		}
		tmp = tmp->next;
	}
}
//********************************************************************************************************************
template <class T>
void hospital<T>::patientExpenditures(T val)
{
	if (!contains(val))
	{
		cout << "The Patient Not Found" << endl;
		cout << "----------------------------------------------------------------" << endl;
	}
	else
	{
		Pdata<T>*tmp = findPatient(val);
		cout << "----------------------------------------------------------------" << endl;
		cout << "the name of patient " << tmp->Fname << endl;
		cout << "the total money :" << tmp->total_money << " EGP." << endl;
		cout << "the total deposited :" << tmp->total_deposited << " EGP." << endl;
		double rest = (tmp->total_money) - (tmp->total_deposited);
		cout << "The rest of the money = " << rest << " EGP." << endl;
		cout << "----------------------------------------------------------------" << endl;
		cout << "to edit Enter 1 and to End Enter 0" << endl;
		int x;
		cin >> x;
		if (x == 1)
		{
			cout << "Enter the total money  :";
			cin >> tmp->total_money;
			cout << "Enter the total deposited  :";
			cin >> tmp->total_deposited;
			cout << "done" << endl;
			cout << "----------------------------------------------------------------" << endl;
		}
		else if (x == 0)
			return;
	}
}
//********************************************************************************************************************
template <class T>
void hospital<T>::Delete_patient(T val)
{
	if (!contains(val))
	{
		cout << "The Patient Not Found" << endl;
		cout << "----------------------------------------------------------------" << endl;
	}
	else
	{
		Pdata<T>* tmp = head;
		int x = 0;
		for (int i = 0; i < size; i++)
		{
			if (tmp->Fname == val)
			{
				DeleteAt(x);
				cout << "           {The patient successfully deleted}" << endl;
				break;
			}
			else
			{
				tmp = tmp->next;
				x += 1;
			}
		}
		cout << "----------------------------------------------------------------" << endl;
	}
}
//********************************************************************************************************************
template <class T>
void hospital<T>::DeleteAt(int pos)
{
	Pdata<T>* tmp = head;
	if (pos == 0)
	{
		head = head->next;
		delete tmp;
	}
	else
	{
		for (int i = 0; i<pos - 1; i++)
			tmp = tmp->next;
		Pdata<T>* del = tmp->next;
		tmp->next = del->next;
		delete del;
		if (pos == size - 1)
			tail = tmp;
	}
	size--;
}
//********************************************************************************************************************
template <class T>
void hospital<T>::WriteIn_file(T file)
{
	ofstream write(file, ios::in | ios::app | ios::binary);
	Pdata<T>* tmp = head;

	while (tmp != NULL)
	{
		write << tmp->Fname << "-" << tmp->address << "-" << tmp->disease << "-" << tmp->sex << "-" << tmp->date << "-" << tmp->age << "-" << tmp->department << "-" << tmp->total_money << "-" << tmp->total_deposited << endl;
		tmp = tmp->next;
	}

}
//********************************************************************************************************************
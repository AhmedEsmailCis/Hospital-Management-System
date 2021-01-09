template <class T>
class Pdata
{
public:
	Pdata<T>* next;
	T Fname;
	T address;
	T disease;
	T sex;   //male or female
	T date;  // EXAMBLE 20/12/2015
	int age; //Number of years
	int department; //(O.P.D): 1 , (Emergency department): 0
	double total_money;
	double total_deposited;
	Pdata();
	Pdata(T n, T a, T d, T s, T Date, int g, int D, double x, double y);
};
template <class T>
class hospital 
{
	int size;
	Pdata<T>* head;
	Pdata<T>* tail;
public:
	hospital();
	void ReadFrom_file(T);
	void displayIN_main(void);
	Pdata<T>* findPatient(T val);
	bool contains(T val);
	void show(T);
	void addIN_hosoital(void);
	void Add_patient(T n, T a, T d, T s, T Date, int g, int D, double x, double y);
	void search(T val);
	void edit(Pdata<T> * s);
	void listPatientBy_alphabeticalOrder(void);
	void listPatientIn_Emergency(void);
	void listPatientIn_OPD(void);
	void listPatientBy_date(T dat);
	void patientExpenditures(T val);
	void Delete_patient(T val);
	void DeleteAt(int pos);
	void WriteIn_file(T file);
};
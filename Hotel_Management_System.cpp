#include <iostream>
#include <cstdlib>
#include <sstream>
#include <ctime>

using namespace std;

static int max_employee = 500;
int counter = 0;

class Employee{
	public:
		string Last_name;
		string First_name;
		string DOB;
		int holday_took;
		int status;
				
	//public:
		Employee():status(0){};
		
		void Create_Emply(){
			cout << "Enter Last Name: ";
			cin >> Last_name;
			cout << "Enter First Name: ";
			cin >> First_name;
			cout << "Enter Date of Birth (dd.mm.yyyy): ";
			cin >> DOB;
			cout << "Number of initial Holidays: ";
			cin >> holday_took;
			status = 1;
			cout << "Employee data created." << endl;
			counter++;
		}
		
		void Delete_Emply(){
			status = 0;
			cout << "Employee data deleted." << endl;
			counter--;
		}
		
		int Search_Emply(string Lname, string Fname){
			if (Lname == Last_name && Fname == First_name){
				return 1;
			}	
			else{
				return 0;
			}
		}
		
		int Took_Holiday(int days, int year){
			stringstream geek(DOB.substr(6,9));
			int x = 0;
			geek >> x;
			int age = (year+1900) - x;
			int hlday_temp = holday_took + days; 
			if (hlday_temp <= 30 && age < 50){
				holday_took = hlday_temp;
				cout << "Holiday granted" << endl;
				return 1;
			}
			else if (hlday_temp <= 32 && age >= 50){
				holday_took = hlday_temp;
				cout << "Holiday granted" << endl;
				return 1;
			}
			else{
				cout << "Sorry! You have exceeded the amount of holidays allowed." << endl;
				return 0;
			}
		}
		
		void Display(int year){
			cout << "Last Name: " << Last_name << endl;
			cout << "First Name: " << First_name << endl;
			cout << "Date of Birth (dd.mm.yyyy): " << DOB << endl;
			stringstream geek(DOB.substr(6,9));
			int x = 0;
			geek >> x;
			int age = (year+1900) - x;
			if (age < 50){
				cout << "Remaining Holidays: " << 30 - holday_took << endl;
			}
			else if (age >= 50){
				cout << "Remaining Holidays: " << 32 - holday_took << endl;
			}
		}
};

int main(){
	int hlday_date;
	int input = 0,curr_year,k=1,det;
	string Lname,Fname;
	Employee employee[max_employee];
	
	time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	curr_year = timePtr->tm_year;
	
	cout << "\t\t\t\t!!HOTEL MANAGEMENT SYSTEM!! \n\n";
	do {
		cout << "\n 1. Create new Employee data \n 2. Delete Employee data \n 3. Holiday for Employee \n 4. Search Employee \n 5. Display all stored data \n 6. Exit \n";
		cin >> input;
		switch(input){
			case 1:
				if (max_employee - counter >= 0){
					for (int i=0;i<max_employee;i++){
						if (employee[i].status == 0){
							employee[i].Create_Emply();
							break;
						}
					}
				}
				else{
					cout << "Maximum number of employees reached." << endl;
				}
				break;
			case 2:
				cout << "Enter Last Name: ";
				cin >> Lname;
				cout << "Enter First Name: ";
				cin >> Fname;
				for (int i=0;i<max_employee;i++){
					det = employee[i].Search_Emply(Lname,Fname);
					if (det){
						employee[i].Delete_Emply();
						break;
					}
				}
				break;
			case 3:
				cout << "Enter Last Name: ";
				cin >> Lname;
				cout << "Enter First Name: ";
				cin >> Fname;
				for (int i=0;i<max_employee;i++){
					det = employee[i].Search_Emply(Lname,Fname);
					if (det){
						do{
						cout << "Enter Number of Holidays: ";
						cin >> hlday_date;
						employee[i].Took_Holiday(hlday_date,curr_year);
						cout << "Press 0 to stop taking more holidays. Press 1 to take more holidays." << endl;
						cin >> k; 
						}while(k != 0);	
						break;
					}
				}
				break;
			case 4:
				cout << "Enter Last Name: ";
				cin >> Lname;
				cout << "Enter First Name: ";
				cin >> Fname;
				for (int i=0;i<max_employee;i++){
					det = employee[i].Search_Emply(Lname,Fname);
					if (det && employee[i].status != 0){
						employee[i].Display(curr_year);
						break;
					}
				}
				if (!det){
					cout << "Data not found" << endl;
				}
				break;
			case 5:
				for (int i=0; i<max_employee; i++){
					if (employee[i].status != 0){
						employee[i].Display(curr_year);
					}
				}
				break;
			default:
				break;			
		}  
	}while(input != 6);
	return 0;
}

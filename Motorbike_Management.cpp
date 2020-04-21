#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

string Bikes[] = {"Suzuki", "Honda", "BMw", "Kawasaki"};
bool bookes[] = {0, 0 ,0, 0};

class Customer{
	private:
		string name;
		string first_name;
		string street;
		int postal_code;
		string city;
		int YOB;
		int tel_numer;
		bool Lice_A;
		int bike_booked;
		Customer *Next;
		Customer *Prev;
		
	public:
		
		Customer():postal_code(0),YOB(0),tel_numer(0),Next(0),Prev(0){}
		
		bool getLicA(){ return Lice_A; }
		int get_bike(){ return bike_booked; }
		string getFirstName(){ return first_name; }
		string getLastName(){ return name; }
		Customer *getPrev(){ return Prev; }

	friend istream& operator>>(istream& is,Customer& info);
	friend ostream& operator<<(ostream& os, const Customer& info);
	friend class Customer_List;
};


class Customer_List{
	public:
		Customer *Beginning;
		Customer *End;
		
		Customer_List():Beginning(0),End(0){}
		~Customer_List(){
			cout << "!!Step back!! The Customer Data destructor is activated." << endl;
		}
		
		void add(Customer *pr){
			
			if (Beginning == 0){
				Beginning = pr;
				
			}
			if (End != 0){
				End->Next = pr;
			}
			pr->Next = 0;
			pr->Prev = End;
			
			End = pr;
		}
		
		void delet(Customer *pr){
			
			if (pr->Next == 0 && pr->Prev == 0){
				Beginning = 0;
				End = 0;
			}
			else if (pr->Next == 0){
				(pr->Prev)->Next = 0;
				End = pr->Prev;
			}
			else if (pr->Prev == 0){
				(pr->Next)->Prev = 0;
				Beginning = pr->Next;
			}
			else{
				(pr->Prev)->Next = (pr->Next);
				(pr->Next)->Prev = (pr->Prev);
			}
		}							
};



istream& operator>>(istream& is,Customer& info){
	cout << "Do you have Bike License-A (1.Yes / 0.No): ";
	is >> info.Lice_A;
	if(info.Lice_A){
		cout << "\n\t\tCustomer Details\n";
		cout << "Enter Last Name: ";
		is >> info.name;
		cout << "Enter First Name: ";
		is >> info.first_name;
		cout << "Enter Street: ";
		is >> info.street;
		cout << "Enter Postal Code: ";
		is >> info.postal_code;
		cout << "Enter City: ";
		is >> info.city;
		cout << "Enter Year of Birth: ";
		is >> info.YOB;
		cout << "Enter Telephone Number: ";
		is >> info.tel_numer;
		cout << "\n\t\tBikes Available\n";
		for (int i=0;i<4;i++){
			if (bookes[i] == 0){
				cout << i+1 << ". " << Bikes[i] << endl; 
			}
		}
		is >> info.bike_booked;
		bookes[info.bike_booked - 1] = 1;
		//info.curr_stat = 1;		
		return is;
	}
	else{
		cout << "First you need License." << endl;
		return is;
	}
}

ostream& operator<<(ostream& os,const Customer& info){
	cout << "\n\t\t Customer Data " << endl;
	cout << "Last Name: " << info.name << endl;
	cout << "First Name: " << info.first_name << endl;
	cout << "Street: " << info.street << endl;
	cout << "Postal Code: " << info.postal_code << endl;
	cout << "City: " << info.city << endl;
	cout << "Year of Birth: " << info.YOB << endl;
	cout << "Telephone Number: " << info.tel_numer << endl;
	cout << "Bike Reserved: " << Bikes[info.bike_booked-1] << endl;
	return os;
}



int main(){
	
	ofstream WriteFile;
	Customer *cr;
	Customer_List cr_lst;
	string ls_nm, fs_nm;
	int stp1;
	int k;
	
	try{
		WriteFile.open("reservations.txt",ios_base::out | ios_base::app);
		if (!WriteFile.good()){
			throw (string)"reservations.txt";
		}
		do{
			cout << "\t\tBike Rental\n";
			cout << " 1. Reservation \n 2. Display Customers \n 3. Hand Over \n 4. Exit \n";
			cin >> stp1;
			switch(stp1){
				case 1:
					cr = new Customer();
					cin >> *cr;
					if (!cr->getLicA()){
						delete cr;
					}
					else{
						cr_lst.add(cr);
						WriteFile << cr->getLastName() << ' ' << cr->getFirstName() << ' ' << Bikes[cr->get_bike()-1] << ' ' << "today" << endl;
					}
					break;
				case 2:
					for (cr = cr_lst.End; cr != 0; cr = cr->getPrev()){
						cout << *cr;
					}
					break;
				case 3:
					cout << "Enter Last Name: ";
					cin >> ls_nm;
					cout << "Enter First Name: ";
					cin >> fs_nm;
					for (cr = cr_lst.End; cr != 0; cr = cr->getPrev()){
						if (cr->getLastName() == ls_nm && cr->getFirstName() == fs_nm){
							bookes[cr->get_bike()-1] = 0;
							WriteFile << cr->getLastName() << ' ' << cr->getFirstName() << ' ' << Bikes[cr->get_bike()-1] << ' ' << "cancelled" << endl;
							cout << Bikes[cr->get_bike()-1] << " is returned. " << endl;
							cr_lst.delet(cr);
						}
					}
					break;
				default:
					break;
			}
		}while(stp1 != 4);
		WriteFile.close();
	}

	catch(string filename){
		cout << "Error in file " << filename << endl;
	}
	
	return 0;
}

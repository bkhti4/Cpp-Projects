#include <iostream>
#include <cstdlib>
#include <string.h>

using namespace std;

string categories[] = {"Fuel","Food","Rent","Books","Clothing","Holiday","Electronics","Other"};
string calendar[] = {"January","Feburary","March","April","May","June","July","August","September","October","November","December"};
float Budget = 500;


class Invoice{
	private:
		int unique_number;
		string month;
		float amount;
		int categ;
		
	friend class InvoiceList;
	
	public:
		// List address
		Invoice *Next;
		Invoice *Prev;
		
		// De/Constructors
		Invoice(){}  //Default Constructor
		~Invoice(){			 //Default Deconstructor
			cout << "Invoice destructor activated" << endl;
		}
		Invoice(int uq_n,string mn,float bill,int cat):unique_number(uq_n),month(mn),amount(bill),categ(cat),Next(0),Prev(0){} //"User Defined"
		
		// Functions
		void Display_Data(){
			cout << "Unique Number: " << unique_number << endl;
			cout << "Month: " << month << endl;
			cout << "Amount: " << amount << endl;
			cout << "Category: " << categories[categ-1] << endl;
		}
		int getInvno(){return unique_number;}
		int get_category(){return categ;}
		string get_month(){return month;}
		float get_amount(){return amount;}
	
};


class InvoiceList{
	public:
		Invoice *Beginning;
		Invoice *End;
		
		InvoiceList():Beginning(0),End(0){}
		~InvoiceList(){
			cout << "!!Step back!! The Invoice List destructor is activated." << endl;
		}
		
		void add(Invoice *pr){
			
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
		
		void delet(Invoice *pr){
			
			if (pr->Next == 0 && pr->Prev == 0){
				Beginning = 0;
				End = 0;
			}
			else if (pr->Next == 0){
				//cout << "chk1";
				(pr->Prev)->Next = 0;
				End = pr->Prev;
			}
			else if (pr->Prev == 0){
				//cout << "chk2";
				(pr->Next)->Prev = 0;
				Beginning = pr->Next;
			}
			else{
				//cout << "chk3";
				(pr->Prev)->Next = (pr->Next);
				(pr->Next)->Prev = (pr->Prev);
			}
		}				
};

int get_indx(string s){
	int k;
	for (int i=0;i<12;i++){
		if (calendar[k] == s){
			k = i;
		} 
	}
	return k;
}

void display_data_sort(float matr[][8]){
	for (int i=0;i<12;i++){
		float Total = 0;
		cout << "-----------------\n\t" << calendar[i] << "\n-----------------\n";
		for (int j=0;j<8;j++){
			Total = Total + matr[i][j];
		}
		if (Total > Budget){
			cout << "Spent more than planned!!!\n---------\n";
		}
		for (int j=0;j<8;j++){
			cout << categories[j] << ": " << matr[i][j] << endl;
		}
		cout << "Total: " << Total << endl;
	}
}

int main(){
	//Initialization of objects and variables
	int user_input;
	Invoice *inv_std;
	InvoiceList inv_list;
	int inv_numer, categy, mn_indx, indx;
	float sum_categ[] = {0,0,0,0,0,0,0,0};
	float sum_categ_sort[12][8];
	float amnt, val;
	string mnth;
	
	// Filling Matrix
	for(int k=0;k<12;k++){
		for(int l=0;l<8;l++){
			sum_categ_sort[k][l] = 0;
		}
	}

	// Menu list and main loop
	do{
		cout << "\t\t Budget Planner \n 1. Enter invoice \n 2. Display Expense \n 3. Total Amount per Category \n 4. Delete Invoice \n 5. Exit \n";
		cin >>  user_input;
		switch(user_input){
			case 1:
				cout << "Enter Invoice Number: ";
				cin >> inv_numer;
				cout << "Enter Month: ";
				cin >> mnth;
				cout << "Enter Amount: ";
				cin >> amnt;
				cout << "Enter Category: ";
				cin >> categy;
				inv_std = new Invoice(inv_numer,mnth,amnt,categy);
				inv_list.add(inv_std);
				break;
			case 2:
				for(inv_std=inv_list.End;inv_std != 0;inv_std = inv_std->Next){
					mnth = inv_std->get_month();
					mn_indx = get_indx(mnth);
					indx = inv_std->get_category();
					val = inv_std->get_amount();
					sum_categ_sort[mn_indx][indx-1] = sum_categ_sort[mn_indx][indx-1] + val;
					display_data_sort(sum_categ_sort);
				}
				break;
			case 3:
				for(inv_std=inv_list.End;inv_std != 0;inv_std = inv_std->Next){
					indx = inv_std->get_category();
					val = inv_std->get_amount();
					sum_categ[indx-1] = sum_categ[indx-1] + val;
				}
				for(int i=0;i<8;i++){
					cout << categories[i] << ": " << sum_categ[i] << " | ";
				}
				cout << endl;
				break;
			case 4:
				for(inv_std=inv_list.End;inv_std != 0;inv_std = inv_std->Prev){
					inv_std->Display_Data();
				}
				cout << "Enter Invoice Number: ";
				cin >> inv_numer;
				//Invoice *tmp;
				//tmp = inv_list.End;
				inv_std = inv_list.End;
				while(inv_std->getInvno() != inv_numer && inv_std != 0){
					inv_std = inv_std->Prev;
				}
				inv_list.delet(inv_std);
				delete inv_std;
				break;
			default:
				break;
		}
		system("pause");
		system("cls");
	}while(user_input != 5);
	return 0;
}

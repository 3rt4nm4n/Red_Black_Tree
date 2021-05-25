#include <iostream>
#include "RedBlackTree.h"
#include <cstddef>
using namespace std;

class Employee{
	public:
	int regNum;
	int depId;
	int phNum;

	Employee(int r, int d, int p):regNum(r),depId(d),phNum(p){	//Employee constructor
		this->regNum=r;
		this->depId=d;
		this->phNum=p;
	}
	
	Employee(){}//Employee default constructor
	
	bool operator > (Employee empl) {//operator > overloading
            if( regNum > empl.regNum)
            return true;
            else
			return false;
	}
	
	bool operator==(Employee empl){//operator == overloading
		if( regNum == empl.regNum)
            return true;
        else
			return false;
	}
	
	void display(){//displays information about the employee in order, when  called
			cout<<"Department id is : "<<depId<<". Internal Phone Number is : "<<phNum<<endl;
		}
};



int main(){
	
	int regNum, depid, phnum;
	int a=5;
	char ch, add;

	RedBlackTree<Employee> tree; //creating tree
	//creating objects
	Employee emp1=Employee(1001,51,6467); 
	
	Employee emp2=Employee(1002,43,2359);
	
	Employee emp3=Employee(1010,34,4342);
	
	Employee emp4=Employee(1008,21,6761);
	
	Employee emp5=Employee(2001,45,2345);
	
	Employee emp6=Employee(2006,23,6862);
	
	//passing objects into the tree
	tree.InsertNode(emp1);
	tree.InsertNode(emp2);
	tree.InsertNode(emp3);
	tree.InsertNode(emp4);
	tree.InsertNode(emp5);
	tree.InsertNode(emp6);
	
	start:
		cout<<"Enter Employee's Registration Number: ";
		cin>>regNum;
		if(tree.AccessNode(Employee(regNum,0,0))!=NULL){//if the registration number is in the tree the program will show Employee's informations
			tree.AccessNode(Employee(regNum,0,0))->GetValue().display();
		}
		else
		{
			cout<<"Employee not found"<<endl;
			cout<<"Do you want to add this employee to the system? (y/n)"<<endl;//if registration number is not found in the tree the program will ask if user would like to add
			cin>>add;
			if(add=='y'){//if yes, the program will ask user to input information of the new Employee
				Employee newEmp = Employee(regNum,NULL,NULL);
				cout<<"What is the Department id and Internal phone number?: ";
				cin>>depid>>phnum;
				newEmp.depId=depid;
				newEmp.phNum=phnum;
				tree.InsertNode(newEmp);//the program will insert new employee to the tree
				cout<<"Added succesfully."<<endl;
			}	
		}
		cout<<"Continue(y/n): ";
		cin>>ch;
		if(ch=='y')
		goto start;//if user wants to continue, the program will go to line 70 (continuing the loop)
		else//if else, the program will stop
		return 0;	
}

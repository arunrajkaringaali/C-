#include "iostream"

using namespace std;

class base{
	public:
		int dm_base;
		virtual void base_func(){
			cout << "base : "<<typeid(*this).name()<<"::"<<__func__ <<endl;
		}
};

class base1: virtual public base{
	public:
		int dm_base1;
};

class base2: virtual public base{
	public:
		int dm_base2;
};

class derived : public base1, public base2 {
	public:
		int dm_derived;
};

int main() {
	
	derived d;
	d.base_func();
	d.dm_base = 40;
	d.dm_base1 = 10;
	d.dm_base2 = 20;
	d.dm_derived = 30;
	
	//======================================//
	cout <<endl << "<=======Entering in to VTABLE=======>"<<endl;
	typedef void (*fp)(derived*);
	
	fp fptr = NULL;

	cout << *((int*)(&d)+ 0) <<endl;
	cout << *((int*)(&d)+ 1) <<endl;
	cout << *((int*)(&d)+ 2) <<endl;
	cout << *((int*)(&d)+ 3) <<endl;
	cout << *((int*)(&d)+ 4) <<endl;
	cout << *((int*)(&d)+ 5) <<endl;
	cout << *((int*)(&d)+ 6) <<endl;
	
	cout <<endl<<"Base1 VTABLE"<<endl;
	cout << *((int*)*((int*)(&d)+ 0) + 0) <<endl;
	cout << *((int*)*((int*)(&d)+ 0) + 1) <<endl;
	cout << *((int*)*((int*)(&d)+ 0) + 2) <<endl;
	cout << *((int*)*((int*)(&d)+ 0) + 3) <<endl;
	cout << *((int*)*((int*)(&d)+ 0) + 4) <<endl;
	cout << *((int*)*((int*)(&d)+ 0) + 5) <<endl;
	cout << *((int*)*((int*)(&d)+ 0) + 6) <<endl;
	
	fptr = (fp)(*((int*)*((int*)(&d)+ 0) + 6));fptr((derived*)&d);
	
	cout <<endl<<"Base2 VTABLE"<<endl;
	cout << *((int*)*((int*)(&d)+ 2) + 0) <<endl;
	cout << *((int*)*((int*)(&d)+ 2) + 1) <<endl;
	cout << *((int*)*((int*)(&d)+ 2) + 2) <<endl;
	cout << *((int*)*((int*)(&d)+ 2) + 3) <<endl;
	cout << *((int*)*((int*)(&d)+ 2) + 4) <<endl;
	cout << *((int*)*((int*)(&d)+ 2) + 5) <<endl;
	cout << *((int*)*((int*)(&d)+ 2) + 6) <<endl;
	
	fptr = (fp)(*((int*)*((int*)(&d)+ 2) + 3));fptr((derived*)&d);
	
	//======================================//
}

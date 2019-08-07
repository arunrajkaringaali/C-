#include "iostream"

using namespace std;

class mostbase {
	public :
		virtual void func() { cout << "mostbase : " << typeid(*this).name()<<"::"<<__func__ <<endl; }
		void tunk() { cout << "mostbase : "<<typeid(*this).name()<<"::"<<__func__ <<endl; }
		virtual void punk() { cout <<"mostbase : "<< typeid(*this).name()<<"::"<<__func__ <<endl; }
};

class base : public mostbase {
	public:
		void func() { cout <<"base : " <<  typeid(*this).name()<<"::"<<__func__ <<endl; }
		virtual void tunk() { cout<<"base : " << typeid(*this).name()<<"::"<<__func__ <<endl; }
		void punk() { cout<<"base : " <<typeid(*this).name()<<"::"<<__func__ <<endl; }
};

class derived : public base {
	public:
		void func() { cout<<"derived : " <<typeid(*this).name()<<"::"<<__func__ <<endl; }
		void tunk() { cout<<"derived : " <<typeid(*this).name()<<"::"<<__func__ <<endl; }
		void punk() { cout<<"derived : " <<typeid(*this).name()<<"::"<<__func__ <<endl; }
};

class mostderived : public derived {
	public:
		void func() { cout<<"mostderived : " <<typeid(*this).name()<<"::"<<__func__ <<endl; }
};



int main(){
	mostderived md;
	cout << sizeof(md) <<endl;
	
	cout <<endl << "<=======Calling mostderived functions using mostbase pointer=======>"<<endl;
	mostbase* mbptr = new mostderived;
	mbptr -> func();
	mbptr -> punk();
	mbptr -> tunk();
	
	//======================================//
	cout <<endl << "<=======Entering in to VTABLE=======>"<<endl;
	typedef void (*fp)(mostderived*);
	
	fp fptr = NULL;
	int *objptr 			= (int*)(mbptr);
	int *vptr 				= (int*)(*objptr);
	int *zeroth_entry		= (int*)(*vptr);
	int *first_entry		= (int*)(*(vptr +1));
	int *second_entry 		= (int*)(*(vptr +2));
	int *third_entry 		= (int*)(*(vptr +3));
	
	fptr = (fp)(zeroth_entry);
	fptr((mostderived*)mbptr);//Calling Zeroth Entry in VTABLE
	
	fptr = (fp)(first_entry);
	fptr((mostderived*)mbptr);//Calling First Entry in VTABLE
	
	fptr = (fp)(second_entry);
	fptr((mostderived*)mbptr);//Calling Second Entry in VTABLE
	
	fptr = (fp)(third_entry);//No third entry available in the VTABLE
							 //So this call results segmentation fault
	fptr((mostderived*)mbptr);
	//======================================//
	

	
}

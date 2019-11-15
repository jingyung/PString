// PString.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//


#include <iostream>
#include"PString.h"
#include"PException.h"
using namespace PLibary;
class MyClass
{
public:
	MyClass();
	~MyClass();

private:
	PString a = { "44" };
};

MyClass::MyClass()
{
	try
	{
		double fff = 123456.354234;
		a += a[3];
		a += "test";
		a = "";	a = "3";
		a += "2 ";
		a += fff;
	}
	catch (PException& exectption)
	{
		std::cout << exectption.GetMessage() << "\n";
	}
	std::cout << a << "\n";
}

MyClass::~MyClass()
{
}



int main()
{
	char		 	_space[1] ;

	
	new (_space) PString();

	(reinterpret_cast<PString*>(_space))->set("test");

	PString  *d = reinterpret_cast<  PString*>(_space) ;
	int f1 = sizeof(PString);
	unsigned int g;
	g = -1;

	int p = sizeof(PString);
	MyClass MyClass;

	PString f = "    test     ";
	f.trimWhitespace();

	std::cout << f << "\n";
	PException eee;
	PException eeea("tsetset");
	eee.SetMessage(f);

	std::cin.get();
}

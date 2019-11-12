// PString.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

 
#include <iostream>
#include"PString.h"
class MyClass
{
public:
	MyClass();
	~MyClass();

private:
	PString a = {"44",4};
};

MyClass::MyClass()
{
	std::cout << a[3] << "\n";
	a += "test";
	a = "";	a = "3";
	a += "2";

	std::cout << a << "\n";
}

MyClass::~MyClass()
{
}



int main()
{
 

	MyClass MyClass;

	PString f = "test";
	f += 123213.12312312;
	std::cout << f  << "\n";
 
 
	std::cin.get();
}
 
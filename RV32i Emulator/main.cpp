#include<iostream>
#include<conio.h>

#include "System.h"

using namespace std;


int main()
{
	System system;
	system.loadProgram("test.bin");
	system.memory.printData(4);

	

	cout << "hello world" << endl;
	char c = _getch();
	return 0;
}
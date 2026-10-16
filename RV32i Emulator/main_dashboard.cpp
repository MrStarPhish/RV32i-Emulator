#include<iostream>
#include<conio.h>


#include "Dashboard.h"
#include "ConsoleBufferEssentials.h"
#include "StateSnapshot.h" // remove later

int main()
{
	// dummy comment

	Dashboard dashboard;
	
	//------------------------------ Dashbaord Initialization 
	do
	{
		std::cout << "Press any key to load dashbaord\n" << std::endl;
		_getch();
		dashboard.loadShm();
	} while (!dashboard.isLoaded);

	dashboard.initialize();

	////----------------  Dashboard loop


	dashboard.run();




	char c = _getch();
	return 0;
}
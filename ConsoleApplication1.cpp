// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <process.h>
#include <windows.h>
#include <cstdio>
#include <cmath>
#include <cstdlib>
using namespace std;

bool enableMutex = false; //Command line parameter
int count = 0; //Actual count after update by threads
unsigned long numberIter = 0; //Command line parameter


int main(int argc, char * argv[])
{
	//Local variables
	//Get the command line parameters
	//If correct, argc should be 4 and argv[1] should be numberOfThreads,
	//argv[2] is number of Iterations, and argv[3] is enableMutex

	//Create a mutex (see text for how to do this)

	//for each thread
	for (i = 0; i < numberOfThreads; i++) {
		//create new thread to execute simulated work
		Sleep(10); //Let the new thread run
	}

	//Loop while threads run to completion
	/*while (any thread is running) {
		sleep(1000);
	}*/

	//output the actual value of count and the theoretical value
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

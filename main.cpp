// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <process.h>
#include <windows.h>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <mutex>
#include <iostream>
#include <string>
#include <vector>

#define MAX_THREADS 100
#define MAX_ITER 100000000
using namespace std;

bool enableMutex = false;			//Command line parameter
long long globalCount = 0;				//Actual count after update by threads
unsigned long numberIter = 0;		//Command line parameter
HANDLE mtx;							//global mutex to lock critical sections

unsigned WINAPI threadWork(LPVOID param) {
	int threadID = GetCurrentThreadId();						//variable to hold thread ID
	cout << "Thread " << threadID << " created\n";				//output thread creation message

	if (numberIter > MAX_ITER) { numberIter = MAX_ITER; }		//make sure number of iterations is not more than the allowable max
	
	for (int i = 0; i < numberIter; i++) {						//loop based on how many iterations were specified in the parameters
		if (enableMutex) {
			DWORD waitSig = WaitForSingleObject(mtx, INFINITE); //use WaitForSingleObject to enforce mutex lock
			if (waitSig == WAIT_OBJECT_0) {						//if waitSig is the accepted value
				globalCount = globalCount + abs((int)threadID); //increment with the thread ID
			}
			else {												//error messageif waitSig is not the accepted value
				cout << "An error has ocurred: " << hex << waitSig << "\n";
				break;
			}
			ReleaseMutex(mtx);									//release the mutex
		}
		else {
			globalCount = globalCount + abs((int)threadID);		//increment if mutex is not enabled
		}
	}
	cout << "Thread " << threadID << " terminated\n";			//print thread termination message

	return TRUE;
}


int main(int argc, char * argv[])
{
	long int numberOfThreads;									//variable to hold number of threads
	long long theoCount = 0;											//variable to hold theoretical count
	mtx = CreateMutex(NULL, FALSE, NULL);						//create the mutex
	
	if (atol(argv[1]) > MAX_THREADS) { numberOfThreads = MAX_THREADS;}
	else { numberOfThreads = atol(argv[1]); }					//set number of threads according to function call parameters
	numberIter = atol(argv[2]);									//set number of iterations according to function call parameters
	if (*argv[3] == '1') {
		enableMutex = true;										//enable/disable mutex according to function call parameters
	}

	HANDLE allThreads[MAX_THREADS] = {};						//array to hold threads

	//for each thread
	for (int i = 0; i < numberOfThreads; i++) {
		//create new thread to execute threadWork function and add it to the array of threads
		allThreads[i]=(HANDLE)_beginthreadex(0, 0, threadWork, NULL, 0, 0);
		//Theoretical count not affected by race events
		theoCount = theoCount + (abs((int)GetThreadId(allThreads[i])) * numberIter);
		cout << "Actual Count: \t\t" << globalCount << "\n";
		cout << "Theoretical Count: \t" << theoCount << "\n";
		//Let the new thread run
		Sleep(10);
	}

	//wait for each thread to complete and the close it out
	for (int j = 0; j < numberOfThreads; j++) {					//loop through array of threads
		DWORD rc = WaitForSingleObject(allThreads[j], INFINITE);//wait for each thread to complete
		if (rc != WAIT_OBJECT_0) {								//output error code in case of error
			cout << "Something has happened: " << rc << "\nError Code: " << hex << GetLastError();
		}
		else {													//if there is no error, CloseHandle to close the thread
			CloseHandle(allThreads[j]);
		}
	}

	//output the actual value of count and the theoretical value
	cout << "Actual Count: \t\t" << globalCount << "\n";
	cout << "Theoretical Count: \t" << theoCount << "\n";
	system("pause");
	return 0;
}


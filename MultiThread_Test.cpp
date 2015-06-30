// MultiThread_Test.cpp : définit le point d'entrée pour l'application console.

#include "stdafx.h"
#include <iostream> 
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <fstream>
#include <string>
#include <thread>

#define NUM_THREADS 5
using namespace std;
HANDLE hMutex;


DWORD WINAPI ThreadWriting(LPVOID pM)  
{   
	
	
	while(1){
		WaitForSingleObject(hMutex,INFINITE);
		ofstream myfile;
		cout<<"Thread " << GetCurrentThreadId() << " is writing..." << endl; 
		myfile.open("mySources.txt",ios::ate);
		if (myfile.is_open())
		{
			myfile << time(0) << endl;
			myfile.close();
		}
		else cout << "Unable to open file"; 
		Sleep(3000);
		ReleaseMutex(hMutex);
	}
	
	return 0;
}  

DWORD WINAPI ThreadReading(void* args)
{
	
	
	
	while(1){
		WaitForSingleObject(hMutex,INFINITE);
		cout<<"Thread " << GetCurrentThreadId() << " is reading..." << endl; 
		ifstream myfile;
		string line;
		myfile.open("mySources.txt");
		if (myfile.is_open())
		{
			while ( getline (myfile,line) )
			{
				cout << "I am in the file" << endl;
				cout << line << '\n';
			}
			myfile.close();
		}
		else cout << "Unable to open file"; 
		Sleep(3000);
		ReleaseMutex(hMutex);
		
	}
	
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{	
	
	std::cout<<("The simplest example of multithread in the hello world: \n");

	hMutex = CreateMutexW(NULL,FALSE,(LPCWSTR)"text");

	HANDLE handleWriting = CreateThread(NULL, 0, ThreadWriting, NULL, 0, NULL); 
    	HANDLE handleReading = CreateThread(NULL, 0, ThreadReading, NULL, 0, NULL);  
	
    	getchar();
	/*
	CloseHandle(handlefun);
	CloseHandle(handlenotfun);
	*/
	return 0;
}


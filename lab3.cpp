#include "lab3.h"
#include <iostream>
#include <windows.h>
#include <map>
#include <string>

using namespace std;

const int num_of_th = 11;
HANDLE th[num_of_th];
HANDLE lock; 
HANDLE sem[num_of_th];
const int SLEEP_TIME = 1;
 unsigned int lab3_task_number()
{
	return 44 % 20; 
}


DWORD WINAPI a(LPVOID tName) 
{
	for (int i = 0; i < 3; i++)
	{
		WaitForSingleObject(lock, INFINITE);
		cout << "a";
		ReleaseMutex(lock);
		sleep_ms(SLEEP_TIME);
	}
	ReleaseSemaphore(sem[0], 1, NULL); 
	return 1;
}

DWORD WINAPI d(LPVOID tName)
{
	for (int i = 0; i < 9; i++)
	{
		WaitForSingleObject(lock, INFINITE);
		cout << "d";
		ReleaseMutex(lock);
		sleep_ms(SLEEP_TIME);
	}
	ReleaseSemaphore(sem[1], 1, NULL);
	return 1;
}

DWORD WINAPI c(LPVOID tName)
{
	for (int i = 0; i < 6; i++)
	{
		WaitForSingleObject(lock, INFINITE);
		cout << "c";
		ReleaseMutex(lock);
		sleep_ms(SLEEP_TIME);
	}
	ReleaseSemaphore(sem[2], 2, NULL);
	return 1;
}

DWORD WINAPI e(LPVOID tName)
{

	for (int i = 0; i < 12; i++)
	{
		WaitForSingleObject(lock, INFINITE);
		cout << "e";
		ReleaseMutex(lock);
		sleep_ms(SLEEP_TIME);
	}
	ReleaseSemaphore(sem[3], 2, NULL);
	return 1;
}


DWORD WINAPI b(LPVOID tName)
{
	WaitForSingleObject(sem[0], INFINITE);
	for (int i = 0; i < 3; i++)
	{
		WaitForSingleObject(lock, INFINITE);
		cout << "b";
		ReleaseMutex(lock);
		sleep_ms(SLEEP_TIME);
	}
	ReleaseSemaphore(sem[4], 2, NULL);
	return 1;
}

DWORD WINAPI g(LPVOID tName)
{
	WaitForSingleObject(sem[2], INFINITE);
	WaitForSingleObject(sem[4], INFINITE);
	for (int i = 0; i < 6; i++)
	{
		WaitForSingleObject(lock, INFINITE);
		cout << "g";
		ReleaseMutex(lock);
		sleep_ms(SLEEP_TIME);
	}
	ReleaseSemaphore(sem[5], 2, NULL);
	return 1;
}



DWORD WINAPI h(LPVOID tName)
{
	WaitForSingleObject(sem[2], INFINITE);
	WaitForSingleObject(sem[4], INFINITE);
	for (int i = 0; i < 9; i++)
	{
		WaitForSingleObject(lock, INFINITE);
		cout << "h";
		ReleaseMutex(lock);
		sleep_ms(SLEEP_TIME);
	}
	ReleaseSemaphore(sem[6], 1, NULL);
	return 1;
}


DWORD WINAPI f(LPVOID tName)
{
	WaitForSingleObject(sem[1], INFINITE);
	for (int i = 0; i < 3; i++)
	{
		WaitForSingleObject(lock, INFINITE);
		cout << "f";
		ReleaseMutex(lock);
		sleep_ms(SLEEP_TIME);
	}
	ReleaseSemaphore(sem[7], 2, NULL);
	return 1;
}

DWORD WINAPI i(LPVOID tName)
{
	WaitForSingleObject(sem[3], INFINITE);
	WaitForSingleObject(sem[5], INFINITE);
	WaitForSingleObject(sem[7], INFINITE);
	for (int i = 0; i < 3; i++)
	{
		WaitForSingleObject(lock, INFINITE);
		cout << "i";
		ReleaseMutex(lock);
		sleep_ms(SLEEP_TIME);
	}
	ReleaseSemaphore(sem[8], 1, NULL);
	return 1;
}


DWORD WINAPI k(LPVOID tName)
{
	WaitForSingleObject(sem[3], INFINITE);
	WaitForSingleObject(sem[5], INFINITE);
	WaitForSingleObject(sem[7], INFINITE);
	for (int i = 0; i < 3; i++)
	{
		WaitForSingleObject(lock, INFINITE);
		cout << "k";
		ReleaseMutex(lock);
		sleep_ms(SLEEP_TIME);
	}
	ReleaseSemaphore(sem[9], 1, NULL);
	return 1;
}

DWORD WINAPI m(LPVOID tName)
{
	WaitForSingleObject(sem[6], INFINITE);
	WaitForSingleObject(sem[8], INFINITE);
	WaitForSingleObject(sem[9], INFINITE);
	for (int i = 0; i < 3; i++)
	{
		WaitForSingleObject(lock, INFINITE);
		cout << "m";
		ReleaseMutex(lock);
		sleep_ms(SLEEP_TIME);
	}
	
	return 1;
}


int lab3_init()
{
	lock = CreateMutex(NULL, FALSE, NULL); 

	for (int i = 0; i < num_of_th; i++)
	{
		sem[i] = CreateSemaphore(NULL, 0, 9, NULL); 
		if (sem[i] == NULL)
		{
			
			cerr << "error semafor", GetLastError(); 
			return 1;
		}
	}

	
	DWORD thId;
	th[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)a, NULL, 0, &thId);
	th[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)d, NULL, 0, &thId);
	th[2] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)c, NULL, 0, &thId);
	th[3] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)e, NULL, 0, &thId);
	th[4] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)b, NULL, 0, &thId);
	th[5] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)g, NULL, 0, &thId);
	th[6] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)h, NULL, 0, &thId);
	th[7] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)f, NULL, 0, &thId);
	th[8] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)i, NULL, 0, &thId);
	th[9] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)k, NULL, 0, &thId);
	th[10] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)m, NULL, 0, &thId);


	for (int i = 0; i < 10; i++)
		if (th[i] == NULL)
		{
			
			cerr << "error th", GetLastError();
			return 1;

		}

	WaitForMultipleObjects(num_of_th, th, TRUE, INFINITE);

	for (int i = 0; i < num_of_th; i++)
	{
		CloseHandle(th[i]);     
		CloseHandle(sem[i]);
	}

	CloseHandle(lock); 
	
	return 0;
}

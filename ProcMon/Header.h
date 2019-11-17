using namespace std;

//This header file contains declarations for the types used by system-level calls to obtain file status or time information.
#include<sys/types.h>

//It contains declarations for all of the functions in the Windows API.
#include<windows.h>

//In contains stat related information.
#include<sys/stat.h>

//This header is part of the Input/output library.
#include<iostream>

//functions for manipulating arrays of characters.
#include<string.h>

//It takes a snapshot of currently executing processes in the system.
#include<tlHelp32.h>

//Standard Input and Output Functions.
#include<stdio.h>

//input and Output Purpose(File Handling).
#include<io.h>


typedef struct LogFile			// Structure Defined 
{
	// characteristics of Structure
	char ProcessName[100];
	unsigned int pid;
	unsigned int ppid;
	unsigned int thread_cnt;
}LOGFILE;


BOOL HardwareInfo();
void DisplayHelp();


class ThreadInfo
{
	private:			//Characteristics of Class
		DWORD PID;		//A DWORD is a 32-bit unsigned integer.
		HANDLE hThreadSnap;	//A Handle to an object.
		THREADENTRY32 te32;	//Describes an entry from a list of the threads executing in the system when a snapshot was taken.

	public:				//  behaviours of Class
		ThreadInfo(DWORD);	// Parameterized Constructor
		BOOL ThreadDisplay();

//	~ThreadInfo();
};

class DLLInfo
{
	private:			//Characteristics of Class
		DWORD PID;
		MODULEENTRY32 me32;	//Describes an entry from a list of the modules belonging to the specified process.
		HANDLE hProcessSnap;

	public:				//Behaviours of Class
		DLLInfo(DWORD);		// Parameterized Constructor
		BOOL DependentDLLDisplay();

//~DLLInfo();
};

class ProcessInfo
{
	private:			//Characteristics of Class
		DWORD PID;
		DLLInfo *pdobj;
		ThreadInfo *ptobj;
		HANDLE hProcessSnap;
		PROCESSENTRY32 pe32;	//Describes an entry from a list of the processes residing in the system address space when a snapshot was taken.

	public:				//behaviours of Class
		ProcessInfo();		//Default Constructor
		BOOL ProcessDisplay(char *);
		BOOL ProcessLog();
		BOOL ReadLog(DWORD,DWORD,DWORD,DWORD);
		BOOL ProcessSearch(char *);
		BOOL KillProcess(char *);

//~ProcessInfo();
};


#include"Header.h"

ThreadInfo :: ThreadInfo(DWORD No)
{
	PID = No;
	hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD , PID);
	if (hThreadSnap == INVALID_HANDLE_VALUE)
	{
		cout<<"Unable to create snapshot of current Thread Pool.."<<endl;
		return;
	}
	te32.dwSize = sizeof(THREADENTRY32);
}


BOOL ThreadInfo :: ThreadDisplay()
{
	if (!Thread32First(hThreadSnap , &te32))
	{
		cout<<"Error: In Getting First Thread.."<<endl;
		CloseHandle(hThreadSnap);
		return FALSE;
	}
	cout<<endl<<"Thread Of This Process.."<<endl;

	do
	{
		if (te32.th32OwnerProcessID == PID)
		{
			cout<<"\t Thread ID: "<<te32.th32ThreadID<<endl;
		}
	} while (Thread32Next(hThreadSnap , &te32));
	CloseHandle(hThreadSnap);
	return TRUE;
}


DLLInfo :: DLLInfo(DWORD No)
{
	PID = No;
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE , PID);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		cout<<"Error: Unable to create snapshot of current thread Pool.."<<endl;
		return;
	}
	me32.dwSize = sizeof(MODULEENTRY32);
}


BOOL DLLInfo :: DependentDLLDisplay()
{
	//char Arr[200];
	if (!Module32First(hProcessSnap , &me32))
	{
		cout<<"Failed to get DLL Information.."<<endl;
		CloseHandle(hProcessSnap);
		return FALSE;
	}
	cout<<"Dependent DLL of This Process.."<<endl;

	do
	{
		//wcstombs_s(NULL , Arr , 200 , me32.szModule , 200);
		cout<<me32.szModule<<endl;
	} while(Module32Next(hProcessSnap , &me32));
	CloseHandle(hProcessSnap);
	return TRUE;
}

ProcessInfo :: ProcessInfo()
{
	ptobj = NULL;
	pdobj = NULL;

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS , 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		cout<<"Error: Unable to create Snapshot of current runnig Process.."<<endl;
		return;
	}
	pe32.dwSize = sizeof(PROCESSENTRY32);
}


BOOL ProcessInfo :: ProcessLog()
{
	char *month[] = {"JAN" , "FEB" , "MAR" , "APR" , "MAY" , "JUN" , "JUL" , "AUG" , "SEP" , "OCT" , "NOV" , "DEC"};
	char FileName[50];
	int Ret = 0 , fd = 0 , count = 0;
	SYSTEMTIME it;
	LOGFILE fobj;
	FILE *fp;

	GetLocalTime(&it);

	sprintf_s(FileName , "G://Madhavi/Assi %02d_%02d_%02d %s.txt" , it.wHour , it.wMinute , it.wDay , month[it.wMonth - 1]);
	fp = fopen(FileName , "wb");
	if (fp == NULL)
	{
		cout<<"Unable to create Log File.."<<endl;
		return FALSE;
	}
	else
	{
		cout<<"Log File Successfully gets Created as.."<<FileName<<endl;
		cout<<"Time of Log File creation is->"<<it.wHour<<":"<<it.wMinute<<":"<<it.wDay<<"th"<<month[it.wMonth - 1]<<endl;
	}

	if (!Process32First(hProcessSnap , &pe32))
	{
		cout<<"Error: In finding the First Process.."<<endl;
		CloseHandle(hProcessSnap);
		return FALSE;
	}

	do
	{
		//wcstombs_s(NULL , Arr , 200 , pe32.szExeFile , 200);
		strcpy_s(fobj.ProcessName , pe32.szExeFile);
		fobj.pid = pe32.th32ProcessID;
		fobj.ppid = pe32.th32ParentProcessID;
		fobj.thread_cnt = pe32.cntThreads;
		fwrite(&fobj , sizeof(fobj) , 1 , fp);
	} while(Process32Next(hProcessSnap , &pe32));

	CloseHandle(hProcessSnap);
	fclose(fp);
	return TRUE;
}


BOOL ProcessInfo :: ProcessDisplay(char * option)
{
	//char Arr[200];

	if (!Process32First(hProcessSnap , &pe32))
	{
		cout<<"Error: In finding First Process.."<<endl;
		CloseHandle(hProcessSnap);
		return FALSE;
	}

	do
	{
		cout<<"***************************************";
		//wcstombs_s(NULL , Arr , 200 , pe32.szExeFile , 200);
		cout<<endl<<"Process Name: "<<pe32.szExeFile;
		cout<<endl<<"PID: "<<pe32.th32ProcessID;
		cout<<endl<<"Parent PID: "<<pe32.th32ParentProcessID;
		cout<<endl<<"No. of Thread: "<<pe32.cntThreads;

		if ((_stricmp(option , "-a") == 0) || 
			(_stricmp(option , "-d") == 0) ||
			(_stricmp(option , "-t")))
		{
			if ((_stricmp(option , "-t") == 0) ||
				(_stricmp(option , "-a") == 0))
			{
				ptobj = new ThreadInfo(pe32.th32ProcessID);
				ptobj->ThreadDisplay();
				delete ptobj;
			}

			if ((_stricmp(option , "-d") == 0) || 
				(_stricmp(option , "-a") == 0))
			{
				pdobj = new DLLInfo(pe32.th32ProcessID);
				pdobj->DependentDLLDisplay();
				delete pdobj;
			}
		}
		cout<<endl<<"****************************************";
	} while(Process32Next(hProcessSnap , &pe32));
	CloseHandle(hProcessSnap);
	return TRUE;
}


BOOL ProcessInfo :: ReadLog(DWORD hr , DWORD min , DWORD date , DWORD month)
{
	char FileName[50];
	char * monthArr[] = {"JAN" , "FEB" , "MAR" , "APR" , "MAY" , "JUN" , "JUL" , "AUG" , "SEP" , "OCT" , "NOV" , "DEC"};
	int Ret = 0 , count = 0;

	LOGFILE fobj;
	FILE *fp;

	sprintf_s(FileName , "G://Madhavi/Assi %02d_%02d_%02d %s.txt" , hr , min , date , monthArr[month - 1]);
	fp = fopen(FileName , "rb");

	if (fp == NULL)
	{
		cout<<"Error: Unable to open log file named as: "<<FileName<<endl;
		return FALSE;
	}

	while((Ret = fread(&fobj , 1 , sizeof(fobj) , fp)) != 0)
	{
		cout<<"*****************************************"<<endl;
		cout<<"Process Name: "<<fobj.ProcessName<<endl;
		cout<<"PID of Current Process: "<<fobj.pid<<endl;
		cout<<"Parent Process ID: "<<fobj.ppid<<endl;
		cout<<"Thread Count of Process: "<<fobj.thread_cnt<<endl;
	}
	return TRUE;
}


BOOL ProcessInfo :: ProcessSearch(char * name)
{
	//char Arr[200];
	BOOL flag = FALSE;

	if (!Process32First(hProcessSnap , &pe32))
	{
		CloseHandle(hProcessSnap);
		return FALSE;
	}

	do
	{
		//wcstombs_s(NULL , Arr , 200 , pe32.szExeFile , 200);
		if (_stricmp(pe32.szExeFile , name) == 0)
		{
			cout<<endl<<"Process Name: "<<pe32.szExeFile;
			cout<<endl<<"PID: "<<pe32.th32ProcessID;
			cout<<endl<<"Parent PID: "<<pe32.th32ParentProcessID;
			cout<<endl<<"No. of Thread: "<<pe32.cntThreads;
			flag = TRUE;
			break;
		}
	} while(Process32Next(hProcessSnap , &pe32));
	CloseHandle(hProcessSnap);
	return flag;
}


BOOL ProcessInfo :: KillProcess(char * name)
{
	//char Arr[200];
	int pid = -1;
	BOOL bRet;
	HANDLE hprocess;

	if(!Process32First(hProcessSnap , &pe32))
	{
		CloseHandle(hProcessSnap);
		return FALSE;
	}

	do
	{
		//wcstombs_s(NULL , Arr , 200 , pe32.szExeFile , 200);
		if(_stricmp(pe32.szExeFile , name) == 0)
		{
			pid = pe32.th32ProcessID;
			break;
		}
	} while(Process32Next(hProcessSnap , &pe32));
	CloseHandle(hProcessSnap);

	if (pid == -1)
	{
		cout<<"Error: There is No Such Process.."<<endl;
		return FALSE;
	}
	hprocess = OpenProcess(PROCESS_TERMINATE , FALSE , pid);

	if (hprocess == NULL)
	{
		cout<<"Error: There is no access to terminate.."<<endl;
		return FALSE;
	}

	bRet = TerminateProcess(hprocess , 0);

	if (bRet == FALSE)
	{
		cout<<"Error: Unable to terminate Process.."<<endl;
		return FALSE;
	}
}


BOOL HardwareInfo()
{
	//Contains information about the current computer system. This includes the architecture and type of the processor, 
	//the number of processors in the system, the page size, and other such information.
	SYSTEM_INFO siSysInfo;

	//Retrieves information about the current system.
	GetSystemInfo(&siSysInfo);

	//OEM for compatibility.
	cout<<"OEM ID: "<<siSysInfo.dwOemId<<endl;

	//The number of logical processors in current Processor.
	cout<<"Number of Processors: "<<siSysInfo.dwNumberOfProcessors<<endl;

	cout<<"Page Size: "<<siSysInfo.dwPageSize<<endl;

	//to determine the type of processor.
	cout<<"Processor Type: "<<siSysInfo.dwProcessorType<<endl;

	//A pointer to the lowest memory address accessible to applications and dynamic-link libraries (DLLs).
	cout<<"Minimum Application Addres: "<<siSysInfo.lpMinimumApplicationAddress<<endl;

	//A pointer to the highest memory address accessible to applications and DLLs.
	cout<<"Maximum Application Address: "<<siSysInfo.lpMaximumApplicationAddress<<endl;

	//A mask representing the set of processors configured into the system.
	cout<<"Active Processor Mask: "<<siSysInfo.dwActiveProcessorMask<<endl;

	return TRUE;
}


void DisplayHelp()
{
	cout<<"Developed by Marvellous Infosystem:"<<endl;
	cout<<"ps: Display all information of Process"<<endl;
	cout<<"ps -t: Display all information about Thread"<<endl;
	cout<<"ps -d: Display all information about DLL"<<endl;
	cout<<"cls: Clear the contents on Console"<<endl;
	cout<<"log: Creates log of current running Process on C Drive"<<endl;
	cout<<"readlog: Display all information from specified lof file"<<endl;
	cout<<"sysinfo: Display Current Hardware Configuration"<<endl;
	cout<<"search: Search and Display information of specific running process"<<endl;
	cout<<"exit: Terminate Marvellous ProcMon"<<endl;
}


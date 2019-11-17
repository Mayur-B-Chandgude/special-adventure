#include"Header.h"
//#include"CThreadPoolBase.h"

int main(int argc , char* argv[])
{
	BOOL bRet;
	char *ptr = NULL;
	ProcessInfo *ppobj = NULL;
	char command[4][80] , str[80];
	int count , min , date , month , hr;

	while (1)
	{
		//It`s purpose is to clear (or flush) the output buffer and move the buffered data to console .
		fflush(stdin);

		strcpy_s(str,"");

		cout<<endl<<"Marvellous ProcMon:>";

		//Get a string from a stream.
		fgets(str,80,stdin);

		//The sscanf_s function reads data from buffer into the location that's given by each argument.
		count = sscanf_s(str,"%s %s %s %s",command[0],command[1],command[2],command[3]);

		if (count == 1)
		{
			if (_stricmp(command[0],"ps") == 0)
			{
				ppobj = new ProcessInfo();
				bRet = ppobj->ProcessDisplay("-a");

				if (bRet == FALSE)
				{
					cout<<"ERROR: Unable to display process.."<<endl;
				}
				delete ppobj;
			}

			else if (_stricmp(command[0],"log") == 0)
			{
				ppobj = new ProcessInfo();
				bRet = ppobj->ProcessLog();
				
				if (bRet == FALSE)
				{
					cout<<"ERROR: Unable to create log file"<<endl;
				}
				delete ppobj;
			}

			else if (_stricmp(command[0],"sysinfo") == 0)
			{
				bRet = HardwareInfo();
				
				if (bRet == FALSE)
				{
					cout<<"ERROR: Unable to get hardware information"<<endl;
				}
				else
				{
					cout<<"Hardware information of current system is:"<<endl;
				}
			}

			else if (_stricmp(command[0],"readlog") == 0)
			{
				ProcessInfo *ppobj;
				ppobj = new ProcessInfo();

				cout<<"Enter log file details as:"<<endl;

				cout<<endl<<"Hour";
				cin>>hr;
				cout<<endl<<"Minute:";
				cin>>min;
				cout<<endl<<"Date:";
				cin>>date;
				cout<<endl<<"Month:";
				cin>>month;

				bRet = ppobj->ReadLog(hr , min , date , month);
				if (bRet == FALSE)
				{
					cout<<"ERROR: Unable to read specified log file"<<endl;
				}
				delete ppobj;
			}

			else if (_stricmp(command[0],"clear") == 0)
			{
				system("cls");
				continue;
			}

			else if (_stricmp(command[0],"help") == 0)
			{
				DisplayHelp();
				continue;
			}

			else if (_stricmp(command[0],"exit") == 0)
			{
				cout<<endl<<"Terminating the Marvellous ProcMon.."<<endl;
				break;
			}
			else
			{
				cout<<endl<<"ERROR: Command not Found !!"<<endl;
				continue;
			}
		}

		else if (count == 2)
		{
			if (_stricmp(command[0],"ps") == 0)
			{
				ppobj = new ProcessInfo();
				bRet = ppobj->ProcessDisplay(command[1]);
				if (bRet == FALSE)
				{
					cout<<"ERROR: Unable to Display Process information"<<endl;
				}
				delete ppobj;
			}

			else if (_stricmp(command[0],"search") == 0)
			{
				ppobj = new ProcessInfo();
				bRet = ppobj->ProcessSearch(command[1]);
				if (bRet == FALSE)
				{
					cout<<"ERROR: There is no such Process.."<<endl;
				}
				delete ppobj;
				continue;
			}

			else if (_stricmp(command[0],"kill") == 0)
			{
				ppobj = new ProcessInfo();
				bRet = ppobj->KillProcess(command[1]);
				if (bRet == FALSE)
				{
					cout<<"ERROR: There is no such Process.."<<endl;
				}
				else
				{
					cout<<command[1]<<"Terminated Successfully..."<<endl;
				}
				delete ppobj;
				continue;
			}
		}
		else
		{
			cout<<endl<<"ERROR: Command Not Found !!"<<endl;
			continue;
		}
	}

	return 0;
}


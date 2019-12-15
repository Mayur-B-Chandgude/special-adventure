#include "Header.h"

int main(int argc, char* argv[])
{
	int ip;
	char file_name[100];
	
	cout<<"Enter the name of file:";
	cin>>file_name;
	
	int fd = open(file_name, O_BINARY, _S_IREAD);
	if(fd == -1)
	{
		cout<<endl<<"Error: File not Found:"<<endl;
		return -1;
	}
	
	CalculateOffset(fd);
	
	do
	{
		ip = 0;
		
		cout<<endl<<"Enter your choice:"<<endl;
		cout<<"1.Dos Header:"<<endl;
		cout<<"2.File Header:"<<endl;
		cout<<"3.Optional Header:"<<endl;
		cout<<"4.Section Header:"<<endl;
		cout<<"5.Exit:"<<endl;
		cout<<"Your Choice:"<<endl;
		cin>>ip;
		
		switch(ip)
		{
			case 1:
			{
				dos_header dh(fd);
				dh.show_header();
				break;
			}
			
			case 2:
			{
				file_header dh(fd);
				dh.show_header();
				break;
			}
			
			case 3:
			{
				opt_header dh(fd);
				dh.show_header();
				break;
			}
			
			case 4:
			{
				sec_header dh(fd);
				dh.show_header();
				break;
			}
			
			case 5:
			{
				exit(0);
				break;
			}
			
			default : break;
		}
	}while(ip != 5);
	
	return 0;
}


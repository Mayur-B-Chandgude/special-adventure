#include "Packer.h"

BOOL FilePack(char *DirName , char *Filename)		// DirName madhe actual Directory cha nav asta ani Filename madhe saglya regular 
							// Combine kelelya files astat. 
{
	DIR  *dir;					// DIR hee ek structure ahe.
	
	struct dirent *entry;				// Ya madhe file cha navani ticha Inode asto.
	struct stat filestat;
	
	char name[100] = {'\0'};
	char buff[256] = {'\0'};
	
	char *ptr = NULL;

	int fd , fdread , retread , ret , fdnew , temp , icnt = 0;
	char key;
	
	FILEINFO obj;

	if((dir = opendir(DirName)) == NULL)
	{
		return ERR_DIR;
	}

	fd = creat(Filename , 0666);
	if(fd == -1)
	{
		return ERR_FILE;
	}

	key = strlen(Filename);				// File chya navacha count.
	
	write(fd , "Mayur5" , strlen("Mayur5"));
	write(fd , &key , 1);

	printf("Key Written\n");
	while((entry = readdir(dir)) != NULL)
	{
		sprintf(name , "%s/%s" , DirName , entry->d_name);	// sprintf ne path create hoto. DirName name madhe directorycha nav 										// asta ani entry->d_name madhe actual file cha nav milata.
		stat(name , &filestat);
		if(S_ISREG(filestat.st_mode))
		{
			fdread = open(name , O_RDONLY);
			strcpy(obj.name , entry->d_name);
			obj.size = filestat.st_size;

			write(fd , &obj , sizeof(obj));
			while((retread = read(fdread , buff , sizeof(buff))) != 0)
			{
				temp = retread;				// Jevdhya bytes read jalya tevdya retread variable madhe aalya.
				while(temp != 0)
				{
					buff[temp] += key;		//encryption
					temp--;
				}
				write(fd , buff , retread);		// retread madhe preserve keleli value.
			}
			close(fdread);
			icnt++;
		}
		
	}
	
	closedir(dir);
	printf("%d Files successfully combined\n" , icnt);
	return SUCCESS;
}


BOOL FileUnpack(char *filename)
{
	DIR *dir;
	
	struct dirent *entry;
	struct stat filestat;
	
	char name[100] = {'\0'};
	char buff[256] = {'\0'};
	
	char *ptr = NULL;
	
	int fd , fdread , ret , fdnew , temp , icnt = 0;
	char key;
	 
	FILEINFO obj;

	fd = open(filename , O_RDONLY);
	if(fd == -1)
	{
		return ERR_FILE;
	}

	ret = read(fd , buff , strlen("Mayur5"));
	if(ret <= 0)
	{
		return ERR_FILE;
	}

	if(strcmp(buff , "Mayur5") != 0)
	{
		return ERR_READ;
	}

	read(fd , &key , 1);
	while((ret = read(fd , &obj , sizeof(obj))) != 0)
	{
		fdnew = creat(obj.name , 0666);

		ptr = (char *) malloc(obj.size * sizeof(char));
		read(fd , ptr , obj.size);

		temp = obj.size;
		while(temp != 0)
		{
			ptr[temp] -= key;
			temp--;
		}

		write(fdnew , ptr , obj.size);
		close(fdnew);
		free(ptr);
		icnt++;
	}

	close(fd);
	printf("%d All files Successfully recreated\n" , icnt);

	return SUCCESS;
}


void DisplayHelp()
{
	printf("\n**************** File Packer Unpacker *****************\n");
	printf("Developed by - Mayur B Chandgude\n");
	printf("********************************\n\n");
	printf("Pack Files\n");
	printf("Exe_name -p Directory_name File_Name\n\n");
	printf("To Unpack files\n");
	printf("Exe_name -u Merge_File_Name\n\n");
}


void DisplayError(BOOL errcode)
{
	switch(errcode)
	{
		case ERR_FILE:
			printf("ERROR: Unable to open File\n");
			break;

		case ERR_MEMORY:
			printf("ERROR: Unable to Allocate Memory\n");
			break;

		case ERR_INPUT:
			printf("ERROR: Invalid Input\n");
			break;

		case ERR_READ:
			printf("ERROR: Unable to read File\n");
			break;

		case ERR_DIR:
			printf("ERROR: Unable to open Directory\n");
			break;

		case ERR_STAT:
			printf("ERROR: Error in Stat\n");
			break;

		default:
			printf("ERROR: Invalid ErrorCode\n");
	}
}


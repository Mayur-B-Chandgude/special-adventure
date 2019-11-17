#include "Header.h"

void man(char *name)
{
	if (name == NULL)
	{
		return;
	}

	if (_stricmp(name , "create") == 0)
	{
		printf("Description: Used to create new regular file..\n");
		printf("Usage: create File_name permission..\n");
	}
	else if (_stricmp(name , "read") == 0)
	{
		printf("Description: Used to read data from regular file..\n");
		printf("Usage: read File_name No_Of_Bytes_To_Read..\n");
	}
	else if (_stricmp(name , "write") == 0)
	{
		printf("Description: Used to write data into regular file..\n");
		printf("Usage: write File_name\n After this enter the data that we want to write..\n");
	}
	else if (_stricmp(name , "ls") == 0)
	{
		printf("Description: Used to list all information of files..\n");
		printf("Usage: ls..\n");
	}
	else if (_stricmp(name , "stat") == 0)
	{
		printf("Description: Used to display all information of file..\n");
		printf("Usage: stat File_name..\n");
	}
	else if (_stricmp(name , "fstat") == 0)
	{
		printf("Description: Used to display all information of file..\n");
		printf("Usage: stat File_Descriptor..\n");
	}
	else if (_stricmp(name , "truncate") == 0)
	{
		printf("Description: Used to remove data from file..\n");
		printf("Usage: truncate File_name..\n");
	}
	else if (_stricmp(name , "open") == 0)
	{
		printf("Description: Used to open existing file..\n");
		printf("Usage: open File_name mode..\n");
	}
	else if (_stricmp(name , "close") == 0)
	{
		printf("Description: Used to close opened file..\n");
		printf("Usage: close File_name..\n");
	}
	else if (_stricmp(name , "closeall") == 0)
	{
		printf("Description: Used to close all opened file..\n");
		printf("Usage: closeall..\n");
	}
	else if (_stricmp(name , "lseek") == 0)
	{
		printf("Description: Used to change the offset..\n");
		printf("Usage: lseek File_name ChangeOffset StartPoint..\n");
	}
	else if (_stricmp(name , "rm") == 0)
	{
		printf("Description: Used to delete the file..\n");
		printf("Usage: rm File_name..\n");
	}
	else
	{
		printf("ERROR: No manual entry available..\n");
	}
}


void DisplayHelp()
{
	printf("ls : To list out all files\n");
	printf("clear : To clear console\n");
	printf("close : To close the file\n");
	printf("closeall : To close all opened files\n");
	printf("read : To read the contents from file\n");
	printf("write : To write contents into file\n");
	printf("exit : To terminate the file system\n");
	printf("stat : To Display information of file using name\n");
	printf("fstat : To Display information of file using file Descriptor\n");
	printf("truncate : To remove all data from file\n");
	printf("rm : To delete the file\n");
}


int GetFDFromName(char *name)
{
	int i = 0;
	while (i < 50)
	{
		if (UFDTArr[i].ptrfilrtable != NULL)
		{
			if (_stricmp((UFDTArr[i].ptrfilrtable->ptrinode->FileName) , name) == 0)
			{
				break;
			}
		}
		i++;
	}
	if (i == 50)
		{
			return -1;
		}
		else
		{
			return i;
		}
}


PINODE Get_Inode(char *name)
{
	PINODE temp = head;

	if (name == NULL)
	{
		return NULL;
	}

	while (temp != NULL)
	{
		if (strcmp(name , temp->FileName) == 0)
		{
			break;
		}
		temp = temp->next; 
	}
	return temp;
}


void createDILB()
{
	PINODE newn = NULL;
	PINODE temp = head;
	int i = 1;

	while (i <= MAXINODE)
	{
		newn = (PINODE)malloc(sizeof(INODE));
		newn->LinkCount = newn->ReferenceCount = 0;
		newn->FileType = newn->FileSize = 0;
		newn->Buffer = NULL;
		newn->next = NULL;
		newn->InodeNumber = i;
		
		if (temp == NULL)
		{
			head = newn;
			temp = head;
		}
		else
		{
			temp->next = newn;
			temp = temp->next;
		}
		i++;
	}
}


void InitalizeSuperBlock()
{
	int i = 0;

	while (i < MAXINODE)
	{
		UFDTArr[i].ptrfilrtable = NULL;
		i++;
	}

	SUPERBLOCKobj.TotalInodes = MAXINODE;
	SUPERBLOCKobj.FreeInode = MAXINODE;
}


int CreateFile(char *name , int permission)
{
	int i = 0;
	PINODE temp = head;

	if ((name == NULL) || (permission == 0) || (permission > 3))
	{
		return -1;
	}

	if (SUPERBLOCKobj.FreeInode == 0)
	{
		return -2;
	}

	if (Get_Inode(name) != NULL)
	{
		return -3;
	}

	(SUPERBLOCKobj.FreeInode)--;

	while (temp != NULL)
	{
		if (temp->FileType == 0)
		{
			break;
		}
		temp = temp->next;
	}

	while (i < MAXINODE)
	{
		if (UFDTArr[i].ptrfilrtable == NULL)
		{
			break;
		}
		i++;
	}

	UFDTArr[i].ptrfilrtable = (PFILETABLE)malloc(sizeof(PFILETABLE));
	if (UFDTArr[i].ptrfilrtable == NULL)
	{
		return -4;
	}

	UFDTArr[i].ptrfilrtable->count = 1;
	UFDTArr[i].ptrfilrtable->mode = permission;
	UFDTArr[i].ptrfilrtable->readoffset = 0;
	UFDTArr[i].ptrfilrtable->writeoffset = 0;

	UFDTArr[i].ptrfilrtable->ptrinode = temp;
	strcpy_s(UFDTArr[i].ptrfilrtable->ptrinode->FileName , name);
	UFDTArr[i].ptrfilrtable->ptrinode->FileType = REGULAR;
	UFDTArr[i].ptrfilrtable->ptrinode->ReferenceCount = 1;
	UFDTArr[i].ptrfilrtable->ptrinode->LinkCount = 1;
	UFDTArr[i].ptrfilrtable->ptrinode->FileSize = MAXFILESIZE;
	UFDTArr[i].ptrfilrtable->ptrinode->ActualFileSize = 0;
	UFDTArr[i].ptrfilrtable->ptrinode->Permission = permission;
	UFDTArr[i].ptrfilrtable->ptrinode->Buffer = (char *)malloc(MAXFILESIZE);
	memset(UFDTArr[i].ptrfilrtable->ptrinode->Buffer , 0 , 1024);

	return i;
}


int rm_File(char *name)
{
	int fd = 0;

	fd = GetFDFromName(name);
	if (fd == -1)
	{
		return -1;
	}

	(UFDTArr[fd].ptrfilrtable->ptrinode->LinkCount)--;

	if (UFDTArr[fd].ptrfilrtable->ptrinode->LinkCount == 0)
	{
		UFDTArr[fd].ptrfilrtable->ptrinode->FileType = 0;
		free(UFDTArr[fd].ptrfilrtable);
	}

	UFDTArr[fd].ptrfilrtable = NULL;
	(SUPERBLOCKobj.FreeInode)++;
}


int ReadFile(int fd , char *Arr , int isize)
{
	int read_size = 0;

	if (UFDTArr[fd].ptrfilrtable == NULL)
	{
		return -1;
	}
	if ((UFDTArr[fd].ptrfilrtable->mode != READ) && (UFDTArr[fd].ptrfilrtable->mode != READ + WRITE))
	{
		return -2;
	}
	if ((UFDTArr[fd].ptrfilrtable->ptrinode->Permission != READ) && (UFDTArr[fd].ptrfilrtable->ptrinode->Permission != READ + WRITE))
	{
		return -2;
	}
	if (UFDTArr[fd].ptrfilrtable->readoffset == UFDTArr[fd].ptrfilrtable->ptrinode->ActualFileSize)
	{
		return -3;
	}
	if (UFDTArr[fd].ptrfilrtable->ptrinode->FileType != REGULAR)
	{
		return -4;
	}

	read_size = (UFDTArr[fd].ptrfilrtable->ptrinode->ActualFileSize) - (UFDTArr[fd].ptrfilrtable->readoffset);
	if (read_size < isize)
	{
		strncpy(Arr , (UFDTArr[fd].ptrfilrtable->ptrinode->Buffer) + (UFDTArr[fd].ptrfilrtable->readoffset) , read_size);
		UFDTArr[fd].ptrfilrtable->readoffset = UFDTArr[fd].ptrfilrtable->readoffset + read_size;
	}
	else
	{
			strncpy(Arr , (UFDTArr[fd].ptrfilrtable->ptrinode->Buffer) + (UFDTArr[fd].ptrfilrtable->readoffset) , isize);
			UFDTArr[fd].ptrfilrtable->readoffset = UFDTArr[fd].ptrfilrtable->readoffset + isize;
	}

	return isize;
}


int WriteFile(int fd , char *Arr , int isize)
{
	
	if ((UFDTArr[fd].ptrfilrtable->mode != WRITE) && 
	   (UFDTArr[fd].ptrfilrtable->mode != READ + WRITE))
	{
		return -1;
	}
	if ((UFDTArr[fd].ptrfilrtable->ptrinode->Permission != WRITE) && 
	   (UFDTArr[fd].ptrfilrtable->ptrinode->Permission != READ + WRITE))
	{
		return -1;
	}
	if (UFDTArr[fd].ptrfilrtable->writeoffset == MAXFILESIZE)
	{
		return -2;
	}
	if (UFDTArr[fd].ptrfilrtable->ptrinode->FileType != REGULAR)
	{
		return -3;
	}

	strncpy((UFDTArr[fd].ptrfilrtable->ptrinode->Buffer) + (UFDTArr[fd].ptrfilrtable->writeoffset) , Arr , isize);

	(UFDTArr[fd].ptrfilrtable->writeoffset = UFDTArr[fd].ptrfilrtable->writeoffset)+ isize;

	(UFDTArr[fd].ptrfilrtable->ptrinode->ActualFileSize) = (UFDTArr[fd].ptrfilrtable->ptrinode->ActualFileSize) + isize;

	return isize;
}


int OpenFile(char *name , int mode)
{
	int i = 0;
	PINODE temp = NULL;

	if ((name == NULL) || (mode > 0))
	{
		return -1;
	}

	temp = Get_Inode(name);
	if (temp == NULL)
	{
		return -2;
	}

	if (temp->Permission < mode)
	{
		return -3;
	}

	while (i < MAXINODE)
	{
		if (UFDTArr[i].ptrfilrtable == NULL)
		{
			break;
		}
		i++;
	}

	UFDTArr[i].ptrfilrtable = (PFILETABLE)malloc(sizeof(PFILETABLE));
	if (UFDTArr[i].ptrfilrtable == NULL)
	{
		return -1;
	}
	UFDTArr[i].ptrfilrtable->count = 1;
	UFDTArr[i].ptrfilrtable->mode = mode;

	if (mode == READ + WRITE)
	{
		UFDTArr[i].ptrfilrtable->readoffset = 0;
		UFDTArr[i].ptrfilrtable->writeoffset = 0;
	}
	else if (mode == READ)
	{
		UFDTArr[i].ptrfilrtable->readoffset = 0;
	}
	else if (mode == WRITE)
	{
		UFDTArr[i].ptrfilrtable->writeoffset = 0;
	}

	UFDTArr[i].ptrfilrtable->ptrinode = temp;
	(UFDTArr[i].ptrfilrtable->ptrinode->ReferenceCount)++;

	return i;
}


void CloseFileByFD(int fd)
{
	UFDTArr[fd].ptrfilrtable->readoffset = 0;
	UFDTArr[fd].ptrfilrtable->writeoffset = 0;
	(UFDTArr[fd].ptrfilrtable->ptrinode->ReferenceCount)--;
}


int CloseFileByName(char *name)
{
	int i = 0;

	i = GetFDFromName(name);
	if (i == -1)
	{
		return -1;
	}

	UFDTArr[i].ptrfilrtable->readoffset = 0;
	UFDTArr[i].ptrfilrtable->writeoffset = 0;
    (UFDTArr[i].ptrfilrtable->ptrinode->ReferenceCount)--;

	return 0;
}


void CloseAllFile()
{
	int i = 0;

	while (i < MAXINODE)
	{
		if (UFDTArr[i].ptrfilrtable != NULL)
		{
			UFDTArr[i].ptrfilrtable->readoffset = 0;
			UFDTArr[i].ptrfilrtable->writeoffset = 0;
			(UFDTArr[i].ptrfilrtable->ptrinode->ReferenceCount)--;
		}
		i++;
	}
}


void ls_File()
{
	PINODE temp = head;

	if (SUPERBLOCKobj.FreeInode == MAXINODE)
	{
		printf("ERROR: There are no files..\n");
		return;
	}

	printf("\nFile Name\nInode Number\nFile Size\nLink Count\n");
	printf("**********************\n");

	while (temp != NULL)
	{
		if (temp->FileType != 0)
		{
			printf("%s\t%d\t\t%d\t\t%d\n");
			temp->FileName , temp->InodeNumber , temp->ActualFileSize , temp->LinkCount;
		}
		temp = temp->next;
	}
	printf("*********************\n");
}


int fstat_File(int fd)
{
	PINODE temp = head;

	if (fd < 0)
	{
		return -1;
	}

	if (UFDTArr[fd].ptrfilrtable == NULL)
	{
		return -2;
	}

	temp = UFDTArr[fd].ptrfilrtable->ptrinode;

	printf("\n*********** Statistical Information about file *************\n");
	printf("File Name:%s\n", temp->FileName);
	printf("Inode Number:%d\n", temp->InodeNumber);
	printf("File Size:%d\n", temp->FileSize);
	printf("Actual File Size:%d\n", temp->ActualFileSize);
	printf("Link Count:%d\n", temp->LinkCount);
	printf("Reference Count:%d\n", temp->ReferenceCount);
	if (temp->Permission == 1)
	{
		printf("File Permission: Read Only\n");
	}
	else if (temp->Permission == 2)
	{
		printf("File Permission: Write Only\n");
	}
	else if (temp->Permission == 3)
	{
		printf("File Permission: Read And Write\n");
	}
	printf("************************\n\n");

	return 0;
}


int stat_File(char *name)
{
	PINODE temp = head;

	if (name == NULL)
	{
		return -1;
	}
	while (temp != NULL)
	{
		if (strcmp(name , temp->FileName) == 0)
		{
			break;
		}
		temp = temp->next;
	}
	
	if (temp == NULL)
	{
		return -2;
	}

	printf("\n*********** Statistical Information about file *************\n");
	printf("File Name:%s\n", temp->FileName);
	printf("Inode Number:%d\n", temp->InodeNumber);
	printf("File Size:%d\n", temp->FileSize);
	printf("Actual File Size:%d\n", temp->ActualFileSize);
	printf("Link Count:%d\n", temp->LinkCount);
	printf("Reference Count:%d\n", temp->ReferenceCount);
	if (temp->Permission == 1)
	{
		printf("File Permission: Read Only\n");
	}
	else if (temp->Permission == 2)
	{
		printf("File Permission: Write Only\n");
	}
	else if (temp->Permission == 3)
	{
		printf("File Permission: Read And Write\n");
	}
	printf("************************\n\n");

	return 0;
}


int truncate_File(char *name)
{
	int fd = GetFDFromName(name);

	if (fd == -1)
	{
		return -1;
	}

	memset(UFDTArr[fd].ptrfilrtable->ptrinode->Buffer , 0 , 1024);
	UFDTArr[fd].ptrfilrtable->readoffset = 0;
	UFDTArr[fd].ptrfilrtable->writeoffset = 0;
	UFDTArr[fd].ptrfilrtable->ptrinode->ActualFileSize = 0;
}


int LseekFile(int fd , int size , int from)
{
	if(fd < 0) || (from > 2)
	{
		return -1;		
	}
	
	if(UFDTArr[fd].ptrfiletable == NULL)
	{
		return -1;	
	}
	
	if((UFDTArr[fd].ptrfiletable->mode == READ) || (UFDTArr[fd].ptrfiletable->mode == READ + WRITE))
	{
		if(from == CURRENT)
		{
			if(((UFDTArr[fd].ptrfiletable->readoffset) + size) >
			(UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize))
			{
				return -1;
			}
			
			if(((UFDTArr[fd].ptrfiletable->readoffset) + size) < 0)
			{
				return -1;
			}
			
			(UFDTArr[fd].ptrfiletable->readoffset) = (UFDTArr[fd].ptrfiletable->readoffset) + size;
		}
		else if(from == START)
		{
			if(size > (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize))
			{
				return -1;
			}
			
			if(size < 0)
			{
				return -1;
			}
			
			(UFDTArr[fd].ptrfiletable->readoffset) = size;
		}
		else if(from == END)
		{
			if((UFDTArr[fd].ptrfiletable->ptrinde->FileActualSize) + size > MAXFILESIZE)
			{	
				return -1;
			}
			
			if(((UFDTArr[fd].ptrfiletable->readoffset) + size) < 0)
			{
				return -1;
			}
			
			(UFDTArr[fd].ptrfiletable->readoffset) = (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) + size;
		}
	}
	else if(UFDTArr[fd].ptrfiletable->mode == WRITE)
	{
		if(from == CURRENT)
		{
			if(((UFDTArr[fd].ptrfiletable->writeoffset) + size) > MAXFILESIZE)
			{
				return -1;
			}
			
			if(((UFDTArr[fd].ptrfiletable->writeoffset) + size) < 0)
			{
				return -1;
			}
			
			if(((UFDTArr[fd].ptrfiletable->writeoffset) + size) >
			  (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize))
			{
				(UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) = 
				(UFDTArr[fd].ptrfiletable->writeoffset) + size;
			}
			
			(UFDTArr[fd].ptrfiletable->writeoffset) = (UFDTArr[fd].ptrfiletable->writeoffset) + size;
		}
		else if(from == START)
		{
			if(size > MAXFILESIZE)
			{
				return -1;
			}
			
			if(size < 0)
			{
				return -1;
			}
			
			if(size > (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize))
			{
				(UFDTArr[fd].ptrfiletable->ptrinode->FileActuslSize) = size;
			}
			
			(UFDTArr[fd].ptrfiletable->writeoffset) = size;
		}
		else if(from == END)
		{
			if((UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) + size > MAXFILESIZE)
			{
				return -1;
			}
			
			if(((UFDTArr[fd].ptrfile->writeoffset) + size) < 0)
			{
				return -1;
			}
			
			(UFDTArr[fd].ptrfiletable->writeoffset) = (UFDTArr[fd].ptrfiletable->ptrinode->ActualSize) + size;
		}
	}
}


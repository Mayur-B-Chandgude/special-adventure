#include<dirent.h>		// Ya header file madhe directories cha internal format asto. 

#include<sys/types.h>		// Ya header file madhe different types che datatypes astat.

#include<stdio.h>		// Ya header file Input ani Output related functions astat.

#include<sys/stat.h>		// Ya header file madhe Files che Different attributes astat.

#include<fcntl.h>		// Ya header file madhe File Handling releted functions astat.

#include<unistd.h>		// Universal Standard Header File (Warning avoid krnyasathi system calls chya).

#include<stdlib.h>		// Standard Library Function (Memory Allocation ani Process Control).

#include<string.h>		// String releted Header file ahe.


#define ERR_FILE		0
#define ERR_MEMORY		1
#define ERR_INPUT		2
#define ERR_READ		3
#define SUCCESS			4
#define ERR_DIR			5
#define ERR_STAT		6


typedef int BOOL;


typedef struct
{
	char name[50];		// Name of file
	int size;		// size of file
}FILEINFO;


BOOL FilePack(char* , char*);

BOOL FileUnpack(char*);

void DisplayHelp();

void DisplayError(BOOL);


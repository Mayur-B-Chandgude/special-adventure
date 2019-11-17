#define _CRT_SECURE_NO_WARNINGS				// (fakt windows sathi) waring kadhanyasathi.
#define MAXINODE	50
#define READ		1
#define WRITE		2
#define MAXFILESIZE	1024
#define REGULAR		1
#define SPECIAL		2
#define START		0
#define CURRENT		1
#define END			2


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<io.h>


typedef struct superblock
{
	int TotalInodes;
	int FreeInode;
}SUPERBLOCK , *PSUPERBLOCK;


typedef struct inode
{
	char FileName[50];
	int InodeNumber;
	int FileSize;						//total file chi size
	int ActualFileSize;					//kiti vaparli tevdhi size
	int FileType;
	char *Buffer;
	int LinkCount;
	int ReferenceCount;
	int Permission;
	struct inode *next;
}INODE , *PINODE , **PPINODE;


typedef struct filetable
{
	int readoffset;
	int writeoffset;
	int count;
	int mode;
	PINODE ptrinode;
}FILETABLE , *PFILETABLE;


typedef struct ufdt
{
	PFILETABLE ptrfilrtable;
}UFDT;


//3 Global Variables.
UFDT UFDTArr[50];
SUPERBLOCK SUPERBLOCKobj;
PINODE head = NULL;


void man(char);
void DisplayHelp();
int GetFDFromName(char);
PINODE Get_Inode(char);
void createDILB();
void InitalizeSuperBlock();
int CreateFile(char , int);
int rm_File(char);
int ReadFile(int , char , int);
int WriteFile(int , char , int);
int OpenFile(char , int);
void CloseFileByFD(int);
int CloseFileByName(char);
void CloseAllFile();
int LseekFile(int , int , int);
void ls_File();
int fstat_File();
int stat_File(char);
int truncate_File(char);


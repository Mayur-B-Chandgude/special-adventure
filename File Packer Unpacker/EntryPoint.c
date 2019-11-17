#include "Packer.h"

int main(int argc , char *argv[])
{
	BOOL ret;

	if(argc < 2 || argc > 4)
	{
		printf("ERROR: Not Sufficient Arguments\n");
		return -1;
	}

	if((strcmp(argv[1] , "-p") == 0) || (strcmp(argv[1] , "-P") == 0))
	{
		ret = FilePack(argv[2] , argv[3]);
		if(ret != SUCCESS)
		{
			DisplayError(ret);
		}
	}

	else if((strcmp(argv[1] , "-u") == 0) || (strcmp(argv[1] , "-U") == 0))
	{
		ret = FileUnpack(argv[2]);
		if(ret != SUCCESS)
		{
			DisplayError(ret);
		}
	}

	else if((strcmp(argv[1] , "-h") == 0) || (strcmp(argv[1] , "-H") == 0))
	{
		DisplayHelp();
	}

	else
	{
		printf("ERROR: Incorrect Arguments\n");
	}

	return 0;
}


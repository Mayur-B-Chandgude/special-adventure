#include "Helper.h"

int main()
{
	void *p = NULL;
	SinglyLL *ptr = NULL;
	SinglyLL *(*fp)() = NULL;
	void (*fp2)(*SinglyLL) = NULL;
	
	p = dlopen("/home/marvellous/desktop/project/Helper.so", RTLD_LAZY);
	if(!p)
	{
		printf("Unable to load marvellous library\n");
	}
	
	fp1 = (SinglyLL*(*)())dlsym(p, "create");
	fp2 = (void(*)(SinglyLL*))dlsym(p, "destroy");
	
	ptr = fp1();
	
	ptr->InsertFirst(10);
	ptr->InsertAtPosition(70, 1);
	ptr->InsertAtPosition(80, 2);
	ptr->InsertLast(40);
	ptr->InsertFirst(50);
	ptr->Display();
	ptr->DeleteFirst();
	ptr->DeleteLast();
	ptr->DeleteAtPosition(4);
	
	fp2(ptr);
	
	dlclose(p);
	
	return 0;
} 


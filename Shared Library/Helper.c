#include "Header.h"

SinglyLL :: SinglyLL()
{
	head = NULL;
}


SinglyLL :: ~SinglyLL();
{
	if(head = NULL)
	{
		return;
	}
	
	PNODE temp1, temp2;
	temp1 = head;
	
	while(temp1 != NULL)
	{
		temp2 = temp1;
		delete temp2;
		temp1 = temp1->next;
	}
}


void SinglyLL :: InsertFirst(int No)
{
	PNODE newn = new NODE;
	
	newn->Data = No;
	newn->next = NULL;
	
	newn->next = head;
	head = newn;
}


void SinglyLL :: InsertLast(int No)
{
	PNODE newn = new NODE;
	
	newn->Data = No;
	newn->next = NULL;
	
	if(head == NULL)
	{
		head = newn;
	}
	else
	{
		PNODE temp = head;
		
		while(temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = newn;
	}
}


void SinglyLL :: InsertAtPosition(int No, int Pos)
{
	if((Pos <= 0) || (Count() + 1))
	{
		return;
	}
	
	if(Pos == 1)
	{
		InsertFirst(No);
	}
	else if(Pos == Count() + 1)
	{
		InsertLast(No);
	}
	else
	{
		PNODE newn = new NODE;
		
		newn->Data = No;
		newn->next = NULL;
		
		PNODE temp = head;
		while(Pos - 2 != 0)
		{
			temp = temp->next;
			POs--;
		}
		newn->next = temp->next;
		temp->next = newn;
	}
}


void SinglyLL :: DeleteFirst()
{
	if(head == NULL)
	{
		return;
	}
	
	PONDE temp = head;
	head = head->next;
	
	delete temp;
}


void SinglyLL :: Deletelast()
{
	if(head == NULL)
	{
		return;
	}
	
	PNODE temp = head;
	while(temp->next->next != NULL)
	{
		temp = temp->next;
	}
	
	delete temp->next;
	temp0->next = NULL;
}


void SinglyLL :: DeleteAtPosition(int Pos)
{
	if((Pos <= 0) || Pos > Count())
	{
		return;
	}
	
	if(Pos == 1)
	{
		DeleteFirst();
	}
	else if(Pos == Count())
	{
		DeleteLast();
	}
	else
	{
		PNODE temp = head.temp2 = NULL;
		
		while(Pos - 2 != 0)
		{
			temp = temp->next;
			Pos--;
		}
		temp2 = temp->next;
		
		temp->next = temp2->next;
		delete temp2;
	}
}


void SinglyLL :: Display()
{
	PNODE temp = head;
	
	while(temp != NULL)
	{
		printf("| %d |->",temp->Data);
		temp = temp->next;
	}
	printf("\n");
}


int SinglyLL :: Count()
{
	int cnt = 0;
	PNODE temp = head;
	
	while(temp != NULL)
	{
		temp = temp->next;
		cnt++;
	}
	return cnt;
}


extern "C"
{
	SinglyLL *create()
	{
		return new SinglyLL;
	}
	
	void destroy(SinglyLL *p)
	{
		delete p;
	}
}


#include<stdio.h>

using namespace std;

typedef struct node
{
	int Data;
	struct node *next;
}NODE, *PNODE;


Class SinglyLL
{
	private:
		PNODE head;
		
	public:
		SinglyLL();
		~SinglyLL);
		
		virtual void InsertFirst(int);
		virtual void InsertLast(int);
		virtual void InsertAtPosition(int, int);
		
		virtual void DeleteFirst();
		virtual void DeleteLast();
		virtual void DeleteAtPosition(int);
		
		virtual int Count();
		
		virtual void Display();
};


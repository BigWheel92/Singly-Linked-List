#include "LinkedList.h"

int main()
{
	LinkedList<int> list;

	list.sortedInsert(-34);
	list.sortedInsert(31);
	list.sortedInsert(-34);
	list.sortedInsert(444);
	list.sortedInsert(4);
	list.sortedInsert(-34);

	for (LinkedList<int>::Iterator it = list.begin(); it!= list.end(); it++)
	{
		cout << *it<<"    ";
	}

	system("pause");
	
}
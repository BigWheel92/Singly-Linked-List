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

	for (LinkedList<int>::Iterator it = list.begin(); it != list.end(); it++)
	{
		cout << *it << "    ";
	}
	cout << endl << endl;
	LinkedList<int> a, b;
	a.insertAtStart(1);
	a.insertAtEnd(5);
	a.insertAtEnd(100);
	a.insertAtEnd(100);
	b.insertAtEnd(2);
	b.insertAtEnd(7);

	a.mergeAlternatively(b);
	a.print();
	cout << "###########" << endl;
	b.print();
	system("pause");

}

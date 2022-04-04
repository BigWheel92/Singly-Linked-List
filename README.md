# Singly-Linked-List
Singly linked list with iterator.
The linked list supports the following operations:

LinkedList();

void insertAtStart(T const element); Inserts the element at the start (head) of the list

void insertAtEnd(T const element);  Inserts the element at the end of the list

void deleteAtStart(); deletes the element from the start (head) of the list 

void deleteAtEnd(); deletes the elements from the end of the list

void print() const; prints the contents of the linked list

bool search(T const element) const; searches for the element and returns true if found else false

void reverse(); reverses the contents of the linked list.

void deleteAllOccurancesOf(T const element); deletes all the occurrances of element from the linked list

void sort(); sorts the linked list using merge sort (ascending sort)

void sortedInsert(T const element); inserts the element in sorted order (ascending sort)

Iterator begin() const; returns an iterator that points to the start of the linked list.

Iterator end() const; returns an iterator that points to the end of the linked list.

void mergeAlternatively(LinkedList<T>const & that); merges the nodes of "that" into the list at alternative position. The list "that" remains unchanged.
  
~LinkedList(); destructor

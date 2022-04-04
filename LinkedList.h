#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
using namespace std;
#include <cassert>

template <typename T>
struct Node
{
	T element;
	Node* next;
};

template <typename T>
class LinkedList
{
private:
	Node<T>* mergeSort(Node<T>*);
	void breakList(Node<T>*, Node<T>*&, Node<T>*&);
	Node<T>* mergeLists(Node<T>*, Node<T>*);

	Node<T>* head;


public:
	class Iterator;
	LinkedList();
	void insertAtStart(T const element);
	void insertAtEnd(T const element);
	void deleteAtStart();
	void deleteAtEnd();
	void print() const;
	bool search(T const element) const;
	void reverse();
	void deleteAllOccurancesOf(T const element);
	void sort();
	void sortedInsert(T const element);
	Iterator begin() const;
	Iterator end() const;
	void mergeAlternatively(LinkedList<T>& that);
	~LinkedList();


};

template <typename T>
class LinkedList<T>::Iterator
{
private:
	Node<T>* curr;
	friend class LinkedList<T>;
public:
	Iterator()
	{
		curr = nullptr;
	}

	Iterator(LinkedList<T>::Iterator const& that)
	{

		this->curr = that.curr;
	}

	Iterator(LinkedList<T> const& list)
	{
		curr = list.head;
	}

	T& operator*()
	{
		assert(this->curr != nullptr);
		return this->curr->element;
	}

	bool operator!=(LinkedList<T>::Iterator that)const
	{
		return (this->curr != that.curr);

	}
	bool operator==(Iterator const& that) const
	{
		return (this->curr == that.curr);
	}

	Iterator& operator++()
	{
		assert(this->curr != nullptr);

		this->curr = curr->next;
		return *this;

	}
	LinkedList<T>::Iterator operator++(int)
	{
		assert(this->curr != nullptr);
		Iterator newIterator(*this);

		this->curr = curr->next;
		return newIterator;
	}
};


template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::begin() const
{
	LinkedList<T>::Iterator it(*this);
	return it;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::end() const
{
	Iterator it;
	it.curr = nullptr;
	return it;

}

template <typename T>
LinkedList<T>::LinkedList()
{
	this->head = nullptr;
}

template <typename T>
void LinkedList<T>::insertAtStart(T const element)
{
	//case 1: head is empty;
	if (this->head == nullptr)
	{
		this->head = new Node<T>();
		this->head->element = element;
		this->head->next = nullptr;
		return;
	}

	Node<T>* newHead = new Node<T>();
	newHead->element = element;
	newHead->next = this->head;
	this->head = newHead;
	return;
}

template <typename T>
void LinkedList<T>::insertAtEnd(T const element)
{
	//case 1: head is empty;
	if (this->head == nullptr)
	{
		this->head = new Node<T>();
		this->head->element = element;
		this->head->next = nullptr;
		return;
	}

	Node<T>* curr = this->head;
	while (curr->next != nullptr)
		curr = curr->next;

	//create new node
	Node<T>* newTailNode = new Node<T>;
	newTailNode->element = element;
	newTailNode->next = nullptr;
	curr->next = newTailNode;
}

template <typename T>
void LinkedList<T>::print() const
{
	Node<T>* curr = this->head;
	while (curr != nullptr)
	{
		cout << curr->element << endl;
		curr = curr->next;
	}

}

template <typename T>
bool LinkedList<T>::search(T const element) const
{
	Node<T>* curr = this->head;
	while (curr != nullptr)
	{
		if (curr->element == element)
			return true;
		curr = curr->next;
	}

	return false;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
	Node<T>* curr = this->head;
	while (curr != nullptr)
	{
		Node<T>* deleteNode = curr;
		curr = curr->next;
		delete deleteNode;
	}

}

template <typename T>
void LinkedList<T>::deleteAllOccurancesOf(T const element)
{
	Node<T>* ptr = this->head;
	Node<T>* prv = nullptr;
	Node<T>* temp;
	while (ptr != nullptr)
	{
		if (ptr->element == element)
		{

			if (prv == nullptr)
			{
				temp = ptr->next;
				delete ptr;
				ptr = temp;
				prv = nullptr;
			}

			else
			{
				temp = ptr->next;
				delete ptr;
				ptr = temp;
				prv->next = ptr;
			}
		}

		else
		{
			prv = ptr;
			ptr = ptr->next;
		}
	}
}


template <typename T>
void LinkedList<T>::deleteAtEnd()
{
	//there is no element in the list
	if (this->head == nullptr)
		return;

	Node<T>* curr = this->head;

	//there is only one element in the list
	if (curr->next == nullptr)
	{
		delete this->head;
		this->head = nullptr;
		return;
	}

	while (curr->next->next != nullptr)
	{
		curr = curr->next;
	}

	Node<T>* deleteNode = curr->next;
	curr->next = nullptr;
	delete deleteNode;
}


template <typename T>
void LinkedList<T>::deleteAtStart()
{
	if (this->head == nullptr)
		return;

	Node<T>* deleteNode = this->head;
	this->head = this->head->next;
	delete deleteNode;
}

template <typename T>
void LinkedList<T>::reverse()
{
	if (this->head == nullptr)
		return;

	Node<T>* curr = this->head,
		* prev = nullptr,
		* next = curr->next;

	while (next != nullptr)
	{
		curr->next = prev;
		prev = curr;
		curr = next;
		next = curr->next;
	}

	this->head = curr;
	this->head->next = prev;

}

template <typename T>
void LinkedList<T>::sort()
{
	this->head = this->mergeSort(this->head);


}

template <typename T>
Node<T>* LinkedList<T>::mergeSort(Node<T>* node)
{
	if (node == nullptr)
		return nullptr;
	else if (node->next == nullptr)
		return node;

	Node<T>* firstHalf;
	Node<T>* secondHalf;

	breakList(node, firstHalf, secondHalf);
	Node<T>* firstHalfSorted = mergeSort(firstHalf);
	Node<T>* secondHalfSorted = mergeSort(secondHalf);

	return mergeLists(firstHalfSorted, secondHalfSorted);
}

template <typename T>
void LinkedList<T>::breakList(Node<T>* list, Node<T>*& firstHalf, Node<T>*& secondHalf)
{

	Node<T>* firstPointer = list;
	Node<T>* secondPointer = list;
	Node<T>* prevToFirstPointer = nullptr;
	while (secondPointer != nullptr)
	{
		prevToFirstPointer = firstPointer;
		firstPointer = firstPointer->next;
		secondPointer = secondPointer->next;

		if (secondPointer != nullptr)
			secondPointer = secondPointer->next;
	}

	firstHalf = list;
	secondHalf = firstPointer;
	prevToFirstPointer->next = nullptr;

}


template <typename T>
Node<T>* LinkedList<T>::mergeLists(Node<T>* firstHalfSorted, Node<T>* secondHalfSorted)
{
	Node<T>* curr = nullptr;
	Node<T>* list;
	if (firstHalfSorted->element <= secondHalfSorted->element)
	{
		curr = firstHalfSorted;
		firstHalfSorted = firstHalfSorted->next;
	}
	else
	{
		curr = secondHalfSorted;
		secondHalfSorted = secondHalfSorted->next;

	}

	list = curr;
	while (firstHalfSorted != nullptr && secondHalfSorted != nullptr)
	{
		if (firstHalfSorted->element <= secondHalfSorted->element)
		{
			curr->next = firstHalfSorted;
			firstHalfSorted = firstHalfSorted->next;
			curr = curr->next;
		}
		else
		{
			curr->next = secondHalfSorted;
			secondHalfSorted = secondHalfSorted->next;
			curr = curr->next;
		}

	}

	if (firstHalfSorted == nullptr)
	{
		curr->next = secondHalfSorted;
	}
	else curr->next = firstHalfSorted;

	return list;
}

template <typename T>
void LinkedList<T>::sortedInsert(T const element)
{
	Node<T>* curr = this->head;
	Node<T>* prev = nullptr;

	while (curr != nullptr)
	{
		if (curr->element < element)
		{
			prev = curr;
			curr = curr->next;

		}
		else break;
	}

	Node<T>* newNode = new Node<T>();
	newNode->element = element;
	newNode->next = curr;

	//if the new element is to be inserted at head
	if (prev == nullptr)
	{
		this->head = newNode;
		return;
	}

	prev->next = newNode;
}


template <typename T>
void LinkedList<T>::mergeAlternatively(LinkedList<T>& that)
{
	Node<T>* curr1 = this->head;
	Node<T>* curr2 = that.head;
	if (!curr1 || !curr2)
		return;

	while (true)
	{
		Node<T>* backUp = curr1->next;
		if (curr2 != nullptr)
		{
			curr1->next = new Node<T>;
			curr1->next->element = curr2->element;
			curr1->next->next = nullptr;
			curr1 = curr1->next;
			curr2 = curr2->next;
		}
		else break;

		if (backUp != nullptr)
		{
			curr1->next = backUp;
			curr1 = curr1->next;
		}
		else break;
	}
	while (curr2)
	{
		curr1->next = new Node<T>;
		curr1->next->element = curr2->element;
		curr1->next->next = nullptr;
		curr1 = curr1->next;
		curr2 = curr2->next;
	}
}

#endif

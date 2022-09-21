#include <iostream>
#include "List.h"

template<typename T>
inline List<T>::List()
{
	this->length = 0;
	this->pAnchor = nullptr;
}

template<typename T>
List<T>::~List()
{
	if (pAnchor) {
		Node<T>* temp = pAnchor;
		do {
			Node<T>* next = temp->next;
			delete temp;
			temp = next;
		} while (temp);
	}
}

template<typename T>
int List<T>::getLength()
{
	return length;
}

template<typename T>
inline void List<T>::add(T value)
{	
	Node<T>* temp = pAnchor;
	if (!temp) {
		temp = pAnchor = new Node<T>;
	}
	else {
		while (temp->next) temp = temp->next;
		temp->next = new Node<T>;
		temp = temp->next;
	}
	temp->value = value;
	temp->next = nullptr;
	length++;
}

template<typename T>
void List<T>::remove(std::string value)
{
	if (!pAnchor) throw std::exception("Item not found");

	Node<T>* temp = nullptr;
	if ((*pAnchor->value) == value) {
		temp = pAnchor;
		pAnchor = pAnchor->next;
	}

	Node<T>* prev = pAnchor;
	while (prev->next && !temp) {
		if ((*prev->next->value) == value) {
			temp = prev->next;
			prev->next = prev->next->next;
			break;
		}
		prev = prev->next;
	}

	if (!temp) throw std::exception("Item not found");

	delete temp;
	length--;
}

template<typename T>
T List<T>::find(std::string value)
{
	if (!pAnchor) throw std::exception("Item not found");

	Node<T>* temp = pAnchor;
	do {
		if ((*temp->value) == value) return temp->value;
		temp = temp->next;
	} while (temp);

	throw std::exception("Item not found");
}

template<typename T>
T List<T>::operator[](int index)
{
	int idx = index < 0 ? length + index : index;

	if (idx < 0 || idx >= length) throw std::exception("Index out of range");

	Node<T>* temp = pAnchor;
	for (int i = 0; i < idx; i++) temp = temp->next;
	return temp->value;
}
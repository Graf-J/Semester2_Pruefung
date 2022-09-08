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
		Node<T>* current = pAnchor;
		while (true) {
			Node<T>* next = current->next;
			delete current;
			if (!next) break;
			current = next;
		}
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
	if (!this->pAnchor) {
		this->pAnchor = new Node<T>;
		this->pAnchor->value = value;
		this->pAnchor->next = nullptr;
	}
	else {
		Node<T>* current = pAnchor;
		while (current->next) current = current->next;
		current->next = new Node<T>;
		current->next->value = value;
		current->next->next = nullptr;
	}
	length++;
}

template<typename T>
void List<T>::remove(std::string value)
{
	if (!pAnchor) throw std::exception("Item not found");

	if (*(pAnchor->value) == value) {
		Node<T>* tmp = pAnchor->next;
		delete pAnchor;
		pAnchor = tmp;
		length--;
		return;
	}

	bool foundValue = false;
	Node<T>* prev = pAnchor;
	while ((prev->next)) {
		if (*(prev->next->value) == value) {
			foundValue = true;
			break;
		}
		prev = prev->next;
	};

	if (!foundValue) throw std::exception("Item not found");

	Node<T>* tmp = prev->next->next;
	delete prev->next;
	prev->next = tmp;
	length--;
}

template<typename T>
T List<T>::find(std::string value)
{
	if (!pAnchor) throw std::exception("Item not found");

	if (*(pAnchor->value) == value) return pAnchor->value;

	bool foundValue = false;
	Node<T>* current = pAnchor;
	while (current->next) {
		current = current->next;
		if (*(current->value) == value) {
			foundValue = true;
			break;
		};
	}
	
	if (foundValue) return current->value;

	throw std::exception("Item not found");
}

template<typename T>
T List<T>::operator[](int index)
{
	int idx = index < 0 ? length + index : index;

	if (idx < 0 || idx >= length) throw std::exception("Index out of range");

	Node<T>* current = pAnchor;
	for (int i = 0; i < idx; i++) current = current->next;
	return current->value;
}
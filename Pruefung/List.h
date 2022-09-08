#pragma once

template <typename T> struct Node {
	T value;
	Node<T>* next;
};

template<typename T> class List
{
private:
	Node<T>* pAnchor;
	int length;

public:

	List();
	~List();

	int getLength();
	void add(T value);
	void remove(std::string value);
	T find(std::string value);
	T operator[](int index);
};

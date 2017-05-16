#pragma once
#include "stdafx.h"
#include <string>
using namespace std;

template <typename T>
class Fibonacci
{
private:
	friend class const_iterator;

	const int defaultFirstNumber = 0;
	const int defaultSecondNumber = 1;

	const string defaultFirstString = "a";
	const string defaultSecondString = "b";

	T first, second;
	int containerSize;

public:
	class const_iterator : public iterator<bidirectional_iterator_tag, T> {
	public: 
		const_iterator& operator--();
		const_iterator& operator++();

		const_iterator& operator-=(difference_type count);
		const_iterator& operator+=(difference_type count);

		reference operator*();
		pointer operator->();

		const_iterator(Fibonacci<T> const& container, int _index);

	private:
		friend class Fibonacci<T>;

		void makeValueDefault();

		void increment();
		void decrement();

		void advance(difference_type count);

		Fibonacci<T> *cont;
		T* value;
		int index;
	};
	
	Fibonacci(int _size);
	Fibonacci(int _size, T const& _first, T const& _second);

	T at(int index) const;

	const_iterator cbegin() const;
	const_iterator cend() const;

	void resize(int newSize);
	int size() const;

	~Fibonacci();
};

template <typename T>
Fibonacci<T>::Fibonacci(int _size)
{
	containerSize = _size;
	if (is_same<T, string>::value) {
		first = defaultFirstString;
		second = defaultSecondString;
	}
	else {
		first = defaultFirstNumber;
		second = defaultSecondNumber;
	}
}
template <typename T>
Fibonacci<T>::Fibonacci(int _size, T const& _first, T const& _second) 
{
	containerSize = _size;
	first = _first;
	second = _second;
}
template <typename T>
Fibonacci<T>::~Fibonacci()
{
}

template <typename T>
T Fibonacci<T>::at(int index) const 
{
	if (index >= size())
		throw "Index out of range!";

	if (index == 0)
		return first;
	if (index == 1)
		return second;

	return at(index - 2) + at(index - 1);
}
template <typename T>
void Fibonacci<T>::resize(int newSize)
{
	if (newSize < 2)
		return;

	containerSize = newSize;
}
template <typename T>
int Fibonacci<T>::size() const
{
	return containerSize;
}

template <typename T>
Fibonacci<T>::const_iterator Fibonacci<T>::cbegin() const
{
	return const_iterator::const_iterator(this, 0);
}
template <typename T>
Fibonacci<T>::const_iterator Fibonacci<T>::cend() const
{
	return const_iterator::const_iterator(this, size());
}

template <typename T>
Fibonacci<T>::const_iterator::const_iterator(Fibonacci<T> const& container, int _index) {
	cont = container;
	index = _index;
	makeValueDefault();
}
template <typename T>
void Fibonacci<T>::const_iterator::makeValueDefault() {
	value = NULL;
}

template <typename T>
bool operator<(const Fibonacci<T>::const_iterator& lhs, const Fibonacci<T>::const_iterator& rhs)
{
	return rhs.index > lhs.index;
}
template <typename T>
bool operator>(const Fibonacci<T>::const_iterator& lhs, const Fibonacci<T>::const_iterator& rhs)
{
	return rhs < lhs;
}
template <typename T>
bool operator<=(const Fibonacci<T>::const_iterator& lhs, const Fibonacci<T>::const_iterator& rhs)
{
	return !(lhs > rhs);
}
template <typename T>
bool operator>=(const Fibonacci<T>::const_iterator& lhs, const Fibonacci<T>::const_iterator& rhs)
{
	return !(lhs < rhs);
}
template <typename T>
bool operator==(const Fibonacci<T>::const_iterator& lhs, const Fibonacci<T>::const_iterator& rhs) 
{
	return rhs.index == lhs.index;
}
template <typename T>
bool operator!=(const Fibonacci<T>::const_iterator& lhs, const Fibonacci<T>::const_iterator& rhs)
{
	return !(lhs == rhs);
}

template <typename T>
const_iterator& operator+(Fibonacci<T>::const_iterator::difference_type count, const Fibonacci<T>::const_iterator iter)
{
	return iter + count;
}
template <typename T>
const_iterator& operator+(const Fibonacci<T>::const_iterator iter, Fibonacci<T>::const_iterator::difference_type count)
{
	iter += count;
	return iter;
}
template <typename T>
const_iterator& operator-(Fibonacci<T>::const_iterator::difference_type count, const Fibonacci<T>::const_iterator iter)
{
	return iter - count;
}
template <typename T>
const_iterator& operator-(const Fibonacci<T>::const_iterator iter, Fibonacci<T>::const_iterator::difference_type count)
{
	iter -= count;
	return iter;
}

template <typename T>
void Fibonacci<T>::const_iterator::increment() 
{
	index++;
	makeValueDefault();
}
template <typename T>
void Fibonacci<T>::const_iterator::decrement()
{
	index--;
	makeValueDefault();
}
template <typename T>
void Fibonacci<T>::const_iterator::advance(difference_type count)
{
	index += count;
	makeValueDefault();
}

template <typename T>
Fibonacci<T>::const_iterator& Fibonacci<T>::const_iterator::operator--() {
	decrement();
	
	return this;
}
template <typename T>
Fibonacci<T>::const_iterator& Fibonacci<T>::const_iterator::operator++() {
	increment();

	return this;
}
template <typename T>
Fibonacci<T>::const_iterator& Fibonacci<T>::const_iterator::operator-=(Fibonacci<T>::const_iterator::difference_type count) {
	return this += -n;
}
template <typename T>
Fibonacci<T>::const_iterator& Fibonacci<T>::const_iterator::operator+=(Fibonacci<T>::const_iterator::difference_type count) {
	advance(count);

	return this;
}

template <typename T>
Fibonacci<T>::const_iterator::reference Fibonacci<T>::const_iterator::operator*() {
	if (value == NULL) {
		value = cont->at(index);
	}

	return value;
}
template <typename T>
Fibonacci<T>::const_iterator::pointer Fibonacci<T>::const_iterator::operator->() {
	if (value == NULL) {
		value = cont->at(index);
	}

	return &value;
}
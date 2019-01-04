#pragma once
#include "stdafx.h"
#include <iterator>
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

		const_iterator(const Fibonacci<T> *container, int _index);
		const_iterator(const_iterator const& copyFrom);

		friend bool operator<(const_iterator& lhs, const_iterator& rhs)
		{
			return rhs.index > lhs.index;
		}
		friend bool operator>(const_iterator& lhs, const_iterator& rhs)
		{
			return rhs < lhs;
		}
		friend bool operator<=(const_iterator& lhs, const_iterator& rhs)
		{
			return !(lhs > rhs);
		}
		friend bool operator>=(const_iterator& lhs, const_iterator& rhs)
		{
			return !(lhs < rhs);
		}
		friend bool operator==(const_iterator& lhs, const_iterator& rhs)
		{
			return rhs.index == lhs.index;
		}
		friend bool operator!=(const_iterator& lhs, const_iterator& rhs)
		{
			return !(lhs == rhs);
		}

		friend typename Fibonacci<T>::const_iterator operator+(difference_type count, const_iterator iter)
		{
			return iter + count;
		}
		friend typename Fibonacci<T>::const_iterator operator+(const_iterator iter, difference_type count)
		{
			iter += count;
			return iter;
		}
		friend typename Fibonacci<T>::const_iterator operator-(difference_type count, const_iterator iter)
		{
			return iter - count;
		}
		friend typename Fibonacci<T>::const_iterator operator-(const_iterator iter, difference_type count)
		{
			iter -= count;
			return iter;
		}
	private:
		friend class Fibonacci<T>;

		void makeValueDefault();

		void increment();
		void decrement();

		void advance(difference_type count);

		const Fibonacci<T> *cont;
		
		bool isCalculated;
		T value;
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
	first = defaultFirstNumber;
	second = defaultSecondNumber;
}
template <>
Fibonacci<string>::Fibonacci(int _size)
{
	containerSize = _size;
	first = (defaultFirstString);
	second = (defaultSecondString);
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
typename Fibonacci<T>::const_iterator Fibonacci<T>::cbegin() const
{
	return  Fibonacci<T>::const_iterator::const_iterator(this, 0);
}
template <typename T>
typename Fibonacci<T>::const_iterator Fibonacci<T>::cend() const
{
	return Fibonacci<T>::const_iterator::const_iterator(this, size());
}

template <typename T>
Fibonacci<T>::const_iterator::const_iterator(const Fibonacci<T> *container, int _index) {
	cont = &(*container);
	index = _index;
	makeValueDefault();
}
template <typename T>
Fibonacci<T>::const_iterator::const_iterator(typename Fibonacci<T>::const_iterator const& copyFrom) {
	cont = &(*(copyFrom.cont));
	index = copyFrom.index;
	makeValueDefault();
}
template <typename T>
void Fibonacci<T>::const_iterator::makeValueDefault() {
	value = T();
	isCalculated = false;
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
void Fibonacci<T>::const_iterator::advance(typename Fibonacci<T>::const_iterator::difference_type count)
{
	index += count;
	makeValueDefault();
}

template <typename T>
typename Fibonacci<T>::const_iterator& Fibonacci<T>::const_iterator::operator--() {
	decrement();
	
	return *this;
}
template <typename T>
typename Fibonacci<T>::const_iterator& Fibonacci<T>::const_iterator::operator++() {
	increment();

	return *this;
}
template <typename T>
typename Fibonacci<T>::const_iterator& Fibonacci<T>::const_iterator::operator-=(typename Fibonacci<T>::const_iterator::difference_type count) {
	advance(-count);

	return *this;
}
template <typename T>
typename Fibonacci<T>::const_iterator& Fibonacci<T>::const_iterator::operator+=(typename Fibonacci<T>::const_iterator::difference_type count) {
	advance(count);

	return *this;
}

template <typename T>
typename Fibonacci<T>::const_iterator::reference Fibonacci<T>::const_iterator::operator*() {
	if (!isCalculated) {
		value = cont->at(index);
		isCalculated = true;
	}

	return value;
}
template <typename T>
typename Fibonacci<T>::const_iterator::pointer Fibonacci<T>::const_iterator::operator->() {
	if (!isCalculated) {
		value = cont->at(index);
		isCalculated = true;
	}

	return &value;
}
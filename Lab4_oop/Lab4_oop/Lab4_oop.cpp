// Lab4_oop.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include "Fibonacci.h"
using namespace std;

const int fibonacciSequenceSize = 30;

typedef Fibonacci<int>::const_iterator iter;

int main()
{
	cout << "Input x: " << endl;
	int x = 0;
	cin >> x;

	Fibonacci<int> fib = Fibonacci<int>(fibonacciSequenceSize);
	vector<int> vect = vector<int>();

	for (Fibonacci<int>::const_iterator iter = fib.cend() - x; iter != fib.cbegin() + x; iter -= 1)
	{
		
		vect.push_back(*iter);
	}

	sort(vect.begin(), vect.end());



    return 0;
}


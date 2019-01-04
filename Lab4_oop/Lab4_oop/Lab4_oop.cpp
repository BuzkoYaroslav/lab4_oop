// Lab4_oop.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <string>
#include "Fibonacci.h"
using namespace std;

const int fibonacciSequenceSize = 12;

typedef Fibonacci<int>::const_iterator iter;

int main()
{
	cout << "Input x: " << endl;
	int x = 0;
	cin >> x;

	Fibonacci<string> fib = Fibonacci<string>(fibonacciSequenceSize, "l", "o");
	vector<string> vect = vector<string>();

	vect.insert(vect.end(), fib.cbegin() + x, fib.cend() - x);/*for (Fibonacci<string>::const_iterator iter = fib.cend() - x - 1; iter != fib.cbegin() + x - 1; iter -= 1)
	{
		
		vect.push_back(*iter);
	}*/

	sort(vect.begin(), vect.end());

	//(fib.cbegin(), fib.cend(), 6);

    return 0;
}


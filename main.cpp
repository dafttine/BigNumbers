#include "stdafx.h"
#include "BigNumbers.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

int main() {
	BigNumbers a("12346567");
	BigNumbers b("1234567");
	BigNumbers c = (a + b);
	BigNumbers  d = (a - b);
	BigNumbers  e = (b - a);
	cout << a.print() << " + " << b.print() << " = " << c.print() << endl;
	cout << a.print() << " - " << b.print() << " = " << d.print() << endl;
	cout << b.print() << " - " << a.print() << " = " << e.print() << endl;
	cout<< "Multiplication Status: WIP. Multiplication works, but trying to figure out how to add products" <<endl;
	cout << "Division Status: Haven't figured it out yet." << endl;
	cout << "Module Status:Hypothetically complete, but requires division which is not complete." << endl;
	return 0;
}
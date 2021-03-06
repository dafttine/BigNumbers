// BigNumbers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BigNumbers.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

BigNumbers::BigNumbers(string bnstr) {
	if ((bnstr.length() > 10001 && bnstr.at(0)!='-') || (bnstr.length() > 10000) && (bnstr.at(0) != '-')) {
		cout << "That number is too large to be stored." << endl;
	}
	else {
		for (int i = 0; i < bnstr.length(); i++) {
			bn.push_back(bnstr.at(i));
		}
	}
}

BigNumbers::BigNumbers() {
	vector<char> bn(10000,'0');
	this->bn = bn;
}

BigNumbers::BigNumbers(vector<char> bn) {
	this->bn = bn;
}

BigNumbers BigNumbers::operator+ (const BigNumbers &other) const {
	vector <char> result;
	vector<int> str;
	vector<int> str2;

	//addition of positive values

	//making int arrays
	str.empty();
	str2.empty();

	for (int i = 0; i < bn.size(); i++) {
		str.push_back((int)(bn.at(i))-48);
	}
	for (int i = 0; i < other.bn.size(); i++) {
		str2.push_back(static_cast<int>(other.bn.at(i))-48);
	}

	int rhssize = str2.size() - 1;
	int lhssize = str.size() - 1;

	//adding values starting from far right

	int sum = 0;
	int carry = 0;

	while ((lhssize > -1) && (rhssize > -1)) {
		sum = carry + str[lhssize] + str2[rhssize];
		carry = 0;
		if (sum > 9) {
			carry = sum / 10;
			sum = sum % 10;
		}		
		result.push_back(static_cast<char>(sum + 48));
		--rhssize;
		--lhssize;
	}
	
	//if one vector is too long and there are no more numbers to add, then the rest of the numbers will be added
	if (lhssize > -1) {
		while (lhssize > -1) {
			result.push_back(static_cast<char>(str[lhssize]+48));
			--lhssize;
		}
	}
	else if (rhssize > -1) {
		while (rhssize > -1) {
			result.push_back(static_cast<char>(str[rhssize] + 48));
			--rhssize;
		}
	}
	reverse(result.begin(), result.end());
	BigNumbers r(result);
	return r;
}

BigNumbers BigNumbers::operator- (const BigNumbers &other)  {
	vector <char> result;
	vector<int> str;
	vector<int> str2;
	bool rhsislarger, lhsislarger;

	//making strings and determining the need of a sign
	for (int i = 0; i < bn.size(); i++) {
		str.push_back(static_cast<int>(bn[i])-48);
	}
	
	for (int i = 0; i < other.bn.size(); i++) {
		str2.push_back(static_cast<int>(other.bn[i]) - 48);
	}
	
	if (str.size() > str2.size()) {
		lhsislarger = true;
		rhsislarger = false;
	}

	else if (str.size() < str2.size()) {
		rhsislarger = true;
		lhsislarger = false;
		
	}
	
	else if (str.size() == str2.size()) {
		bool temp = true;
		int templhs = 0;
		int temprhs = 0;
		int counter = 0;
		while (temp) {
			if (str.size()-templhs > str2.size() -temprhs) {
				lhsislarger = true;
				rhsislarger = false;
				temp = false;
			}
			else if (str.size() - templhs < str2.size() - temprhs) {
				rhsislarger = true;
				lhsislarger = false;
				temp = false;
			}
			
			if ((str.size() == str2.size()) && (counter < str.size())) {
				templhs++;
				temprhs++;
				counter++;
			}
			else if ((str.size() == str2.size()) && (counter == str.size())) {
				temp = false;
				result.push_back('0');
				cout << "done" << endl;
				BigNumbers r(result);
				return r;
			}
		}
	}
	
	int rhscount = str2.size() - 1;
	int lhscount = str.size() - 1;
	int diff = 0;
	int borrow = 0;
	
	
	//subtration when the rhs < lhs
	if (lhsislarger) {
		//stubracts until rhs has no more number to subtract with
		while (rhscount >= 0) {
			if (str[lhscount] < str2[rhscount]) {
				diff = borrow + (str[lhscount] + 10) - str2[rhscount];
				borrow = -1;
			}
			else if (str[lhscount] > str2[rhscount]) {
				diff = (borrow + str[lhscount]) - str2[rhscount];
				borrow = 0;
			}
			result.push_back(static_cast<char>(diff)+48);
			--lhscount;
			--rhscount;
		}
		while (lhscount >= 0) {
			result.push_back(static_cast<char>(borrow + str[lhscount])+48);
			borrow = 0;
			--lhscount;
		}
		reverse(result.begin(), result.end());
		BigNumbers r(result);
		return r;
	}
	

	//subtraction when the lhs < rhs
	else if (rhsislarger) {
		while (lhscount >= 0) {
			if (str2[rhscount] > str[lhscount]) {
				diff = (borrow + str2[rhscount]) - str[lhscount];
				borrow = 0;
			}
			else if (str[lhscount] > str2[rhscount]) {
				diff = borrow + (str2[rhscount] + 10) - str[lhscount];
				borrow = -1;
			}
			result.push_back(static_cast<char>(diff) + 48);
			--lhscount;
			--rhscount;
		}
		while (rhscount >= 0) {
			result.push_back(static_cast<char>(borrow + str2[rhscount]) + 48);
			borrow = 0;
			--rhscount;
		}
		result.push_back('-');
		reverse(result.begin(), result.end());
		BigNumbers r(result);
		return r;
	}
	
}

BigNumbers BigNumbers::operator* (const BigNumbers &other) {


	BigNumbers sum;
	vector <char> result;
	vector<int> str;
	vector<int> str2;
	int recoil = 0, subtract = 0;

	for (int i = 0; i < bn.size(); i++) {
		str.push_back(static_cast<int>(bn[i]) - 48);
	}

	for (int i = 0; i < other.bn.size(); i++) {
		str2.push_back(static_cast<int>(other.bn[i]) - 48);
	}

	//rhs * lhs
	vector <int> productsTemp;
	vector <int> vec1 = {0};
	vector <int> vec2;
	vector <int> finalSum;
	vector <char> realFinal;
	int lhscounter = str.size() - 1;
	int rhscounter = str2.size() - 1;
	int counter = 0;
	int carry = 0;
	int product = 0;
	int zeros = 0;
	BigNumbers finalTotal, b;

	for (int i = rhscounter; i >= 0; i--) {
		//0's after multiplying for one number
		for (int a = 0; a < zeros; a++) {
			productsTemp.push_back(0);
		}

		//multiplication
		for (int j = lhscounter; j >= 0; j--) {
			product = 0;
			product = (str2[i] * str[j]) + carry;

			if (product > 9) {
				carry = product / 10;
				product = product % 10;
				productsTemp.push_back(product);
			}
			else {
				productsTemp.push_back(product);
				carry = 0;
			}

		}


		//add two vectors together
		reverse(productsTemp.begin(), productsTemp.end());
		vec2 = productsTemp;
		productsTemp.clear();

		int vec2counter = vec2.size() - 1;
		int vec1counter = vec1.size() - 1;
		int finalcount = 0;
		for (int a = vec1counter; a > -1; a--) {
			//cout << vec2[vec2counter] + vec1[vec1counter] << endl;
			finalSum.push_back(vec2[vec2counter] + vec1[vec1counter]);
			cout << finalSum[finalcount];
			finalcount++;
			vec1counter--;
			vec2counter--;
		}

		if (vec2counter >= 0) {
			finalSum.push_back(vec2[vec2counter]);
			vec2counter--;
		}

		for (int i = 0; i < finalSum.size(); i++) {
			cout << finalSum[i] << endl;
		}


		reverse(finalSum.begin(), finalSum.end());
		vec1.clear();
		for (int i = 0; i < finalSum.size(); i++) {
			vec1.push_back(finalSum[i]);
		}
		

		vec2.clear();
		finalSum.clear();
		zeros++;
	}
	for (int i = 0; i < vec1.size(); i++) {
		realFinal.push_back(static_cast<char> (vec1[i]) + 48);
	}
	finalTotal.bn = realFinal;
	return finalTotal;
}

/*
BigNumbers BigNumbers::operator/ (const BigNumbers &other) {
	//divide by the first n values
	//divide by the module with the attatchment of n+1 value
	//continue until n+1 == to the numerator's last value
	vector <char> result;
	vector<int> num;
	vector<int> denom;
	string rhs = "";
	string lhs = "";


	for (int i = 0; i < bn.size(); i++) {
		num[i] = (static_cast<int>(bn[i]));
	}
	for (int i = 0; i < other.bn.size(); i++) {
		denom[i] = (static_cast<int>(other.bn[i]));
	}

	for (int i = 0; i < bn.size(); i++) {
		lhs += bn[i];
	}

	for (int i = 0; i < other.bn.size(); i++) {
		rhs += other.bn[i];
	}

	if (lhs._Equal(rhs)) {
		bn.empty();
		bn.push_back('1');
		return *this;
	}

	if (num.size() < denom.size()) {
		bn.empty();
		bn.push_back('0');
		return *this;
	}

	//num is bn and demon is other
	else if (num.size() > denom.size()) {
		//will be back
	}

}




BigNumbers BigNumbers::operator% (const BigNumbers &other) {

	if (bn.size() < other.bn.size()) {
		return BigNumbers(0);
	}
	BigNumbers dividedValue = (*this / other);

	BigNumbers remainder = *this - dividedValue;

	return remainder;
}
*/

BigNumbers BigNumbers::operator= (const BigNumbers &other)  {
	bn = other.bn;
	return *this;
}

string BigNumbers::print() {
	string str;
	for (int i = 0; i < bn.size(); i++) {
		str+= bn[i];
	}
	return str;

}
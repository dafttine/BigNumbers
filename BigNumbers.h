#pragma once
#include <vector>
#include <string>
using namespace std;

class BigNumbers {
public:
	vector<char> bn;
	BigNumbers();
	BigNumbers(string bn);
	BigNumbers(vector<char> bn);
	BigNumbers operator+ (const BigNumbers&) const ;
	BigNumbers operator- (const BigNumbers&) ;
	BigNumbers operator* (const BigNumbers&) ;
	//BigNumbers operator/ (const BigNumbers&) ;
	//BigNumbers operator% (const BigNumbers&) ;
	BigNumbers operator= (const BigNumbers&) ;
	string print();
};
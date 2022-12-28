#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

char to_char(int x) {
	return '0' + x;
}

int to_int(char c) {
	return c - '0';
}

string GetSum(const string &firstNumber, const string &secondNumber) {
	string sum_str;
	int carry = 0;

	auto smallNum_rptr = firstNumber.rbegin();
	auto bigNum_rptr = secondNumber.rbegin();
	auto smallNum_rend = firstNumber.rend();
	auto bigNum_rend = secondNumber.rend();
	if (firstNumber.size() > secondNumber.size()) {
		swap(smallNum_rptr, bigNum_rptr);
		swap(smallNum_rend, bigNum_rend);
	}

 
	while (smallNum_rptr != smallNum_rend) {
		int sum = to_int(*smallNum_rptr) + to_int(*bigNum_rptr) + carry; 
		carry = sum/2;
		sum_str.push_back(to_char(sum%2));
		smallNum_rptr++;
		bigNum_rptr++;
	}

	while (bigNum_rptr != bigNum_rend) {
		int sum = to_int(*bigNum_rptr) + carry;
		carry = sum/2;
		sum_str.push_back(to_char(sum%2));
		smallNum_rptr++;
		bigNum_rptr++;
	}

	if (carry == 1) {
		sum_str.push_back(to_char(carry));
	}

	reverse(sum_str.begin(), sum_str.end());
	return sum_str;
}

void print(const string &result) {
	cout << result << endl;
}

int main() {
	string firstNumber, secondNumber;
	cin >> firstNumber >> secondNumber;
	print(GetSum(firstNumber, secondNumber));
}
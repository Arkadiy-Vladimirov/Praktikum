#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string ToBinary(int number) {
	string binary;

	if (number == 0) {
		binary.push_back('0');
		return binary;
	}

	while (number != 0) {
		binary.push_back('0' + number % 2);
		number = number/2;
	}
	
	reverse(binary.begin(), binary.end());
	return binary;
}

void print(const string &result) {
	cout << result << endl;
}

int main() {
	int number;
	cin >> number;
	print(ToBinary(number));
}
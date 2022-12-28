#include <iostream>

using namespace std;

bool IsPowerOfFour(int number) {
	while (number != 1) {
		if ((number%4) != 0) {
			return false;
		} else {
			number = number/4;
		}
	}

	return true;
}

void print(bool result) {
	if (result)
		cout << "True";
	else
		cout << "False";
	cout << endl;
}

int main() {
	int number;
	cin >> number;
	print(IsPowerOfFour(number));
}
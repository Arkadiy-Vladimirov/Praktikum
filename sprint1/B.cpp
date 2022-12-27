#include <iostream>

using namespace std;

int mod2(int x) {
	return (x%2)*(x%2);
}

bool CheckParity(int a, int b, int c) {
	if ((mod2(a) == mod2(b)) && (mod2(a) == mod2(c))) {
		return true;
	}

	return false;
}

void print(bool result) {
	if (result)
		cout << "WIN" << endl;
	else
		cout << "FAIL" << endl;
}

int main() {
	int a, b, c;
	cin >> a >> b >> c;
	print(CheckParity(a, b, c));
}
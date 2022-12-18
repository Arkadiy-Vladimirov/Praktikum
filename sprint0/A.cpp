#include <iostream>

using namespace std;

int GetSum(int a, int b) {
	return a + b;

}

int main() {
	int a, b;
	cin >> a >> b;
	cout << GetSum(a, b);
}
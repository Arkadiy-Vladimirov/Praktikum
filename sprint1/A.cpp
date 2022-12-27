#include <iostream>

using namespace std;

int EvaluateFunction(int a, int b, int c, int x) {
	return a*x*x + b*x + c;
}

void print(int result) {
	cout << result << endl;
}

int main() {
	int a, x, b, c;
	cin >> a >> x >> b >> c;
	print(EvaluateFunction(a, b, c, x));
}
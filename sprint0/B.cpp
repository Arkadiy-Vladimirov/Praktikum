#include <iostream>
#include <vector>

using namespace std;

vector <int> Zip(const vector <int> &a, const vector <int> &b) {
    int n = a.size();
	vector<int> ziped(2*n);

    for (int i = 0; i < n; ++i) {
        ziped[2*i] = a[i];
        ziped[2*i+1] = b[i];
    }
    
    return ziped;
}

void print(const vector <int> &result) {
	for (int x : result)
		cout << x << " ";
	cout << endl;
}

int main() {
	int n;
	cin >> n;
	vector <int> a(n), b(n);
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	for (int i = 0; i < n; ++i)
		cin >> b[i];
	print(Zip(a, b));
}
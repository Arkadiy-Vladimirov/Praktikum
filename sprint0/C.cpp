#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

vector <double> MovingAverage(const vector <int> &arr, int windowSize) {
    int n = arr.size();
    int k = windowSize;
	vector <double> mov_av;

    double sum = accumulate(arr.begin(), arr.begin()+k, 0);
    mov_av.push_back(sum/k);

    for (int i = 0; i < n-k; ++i) {
        sum += arr[k+i] - arr[i];
        mov_av.push_back(sum/k);
    }

    return mov_av;
}

void print(const vector <double> &result) {
	for (double x : result)
		cout << x << " ";
	cout << endl;
}

int main() {
	int n, windowSize;
	cin >> n;
	vector <int> arr(n);
	for (int i = 0; i < n; ++i)
		cin >> arr[i];
	cin >> windowSize;
	print(MovingAverage(arr, windowSize));
}
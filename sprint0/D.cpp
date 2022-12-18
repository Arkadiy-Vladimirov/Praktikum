#include <iostream>
#include <vector>

using namespace std;

vector <int> TwoSum(const vector <int> &arr, int targetSum) {
	int n = arr.size();
	vector <int> out;
	for (int i = 0; i < n; ++i) {
		for (int j = i+1; j < n; ++j) {
			if ((arr[i] + arr[j]) == targetSum) {
				out.push_back(arr[i]);
				out.push_back(arr[j]);
				return out;
			}
		}
	}
	return out;
}

void print(const vector <int> &result) {
	if (result.size() != 2)
		cout << "None" << endl;
	else
		cout << result[0] << " " << result[1] << endl;
}

int main() {
	int n, targetSum;
	cin >> n;
	vector <int> arr(n);
	for (int i = 0; i < n; ++i)
		cin >> arr[i];
	cin >> targetSum;
	print(TwoSum(arr, targetSum));
}
#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector <int> TwoSum(const vector <int> &sortedArr, int targetSum) {
	auto left_ptr = sortedArr.begin();
	auto right_ptr = sortedArr.end()-1;
	int sampleSum;
	vector <int> out;

	while (left_ptr < right_ptr) {
		sampleSum = *left_ptr + *right_ptr;
				if (sampleSum < targetSum) {
			++left_ptr;
		} else 	if (sampleSum > targetSum) {
			--right_ptr;
		} else {
			out.push_back(*left_ptr);
			out.push_back(*right_ptr);
			return out;
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
	vector <int> sortedArr(n);
	for (int i = 0; i < n; ++i)
		cin >> sortedArr[i];
	cin >> targetSum;
	print(TwoSum(sortedArr, targetSum));
}
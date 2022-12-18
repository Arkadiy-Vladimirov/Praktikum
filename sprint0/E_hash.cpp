#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector <int> TwoSum(const vector <int> &sortedArr, int targetSum) {
	int n = sortedArr.size();
	multiset <int> arr_elements(sortedArr.begin(), sortedArr.end());
	vector <int> out;

	for (auto p = sortedArr.begin(); p != sortedArr.end(); ++p) {
		if ((targetSum - *p) == *p) {
			if (arr_elements.count(targetSum - *p) > 1) {
				out.push_back(*p);
				out.push_back(targetSum - *p);
				return out;
			}
		} else {
			if (arr_elements.count(targetSum - *p) > 0) {
				out.push_back(*p);
				out.push_back(targetSum - *p);
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
	vector <int> sortedArr(n);
	for (int i = 0; i < n; ++i)
		cin >> sortedArr[i];
	cin >> targetSum;
	print(TwoSum(sortedArr, targetSum));
}
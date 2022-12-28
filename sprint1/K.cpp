#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector <int> GetNumberList(int k) {
	vector <int> numberList;
	if (k == 0) {
		numberList.push_back(0);
	}
	while (k != 0) {
		numberList.push_back(k%10);
		k = k/10;
	}

	reverse(numberList.begin(), numberList.end());
	return numberList;
}

vector <int> GetSum(const vector <int> &numberList, int k) {
	const vector <int> &K = GetNumberList(k);
	vector <int> sum_list;


	auto smallNum_rptr = numberList.rbegin();
	auto bigNum_rptr = K.rbegin();
	auto smallNum_rend = numberList.rend();
	auto bigNum_rend = K.rend();
	if (numberList.size() > K.size()) {
		swap(smallNum_rptr, bigNum_rptr);
		swap(smallNum_rend, bigNum_rend);
	}

	int carry = 0;
 
	while (smallNum_rptr != smallNum_rend) {
		int sum = *smallNum_rptr + *bigNum_rptr + carry; 
		carry = sum / 10;
		sum_list.push_back(sum%10);
		smallNum_rptr++;
		bigNum_rptr++;
	}

	while (bigNum_rptr != bigNum_rend) {
		int sum = *bigNum_rptr + carry;
		carry = sum/10;
		sum_list.push_back(sum%10);
		smallNum_rptr++;
		bigNum_rptr++;
	}

	if (carry == 1) {
		sum_list.push_back(carry);
	}

	reverse(sum_list.begin(), sum_list.end());
	return sum_list;

}

void print(const vector <int> &result) {
	for (int x : result)
		cout << x << " ";
	cout << endl;
}

int main() {
	int n;
	cin >> n;
	vector <int> numberList(n);
	for (int i = 0; i < n; ++i)
		cin >> numberList[i];
	int k;
	cin >> k;
	print(GetSum(numberList, k));
}
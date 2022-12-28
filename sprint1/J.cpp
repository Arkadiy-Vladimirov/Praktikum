#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector <int> GetPrimes(int n) {
	vector<int> primes;
	vector<bool> nums(n+1,true);
	nums[0] = false;
	nums[1] = false;

	for (int i = 2; i < n+1; i++) {
		if (nums[i] == true) {
			int p = i;
			for (int j = p*p; j < n+1; j+=p) {
				nums[j] = false;
			}
			primes.push_back(p);
		}
	}

	return primes;
}

vector <int> Factorize(int number) {
	vector<int> primes = GetPrimes(round(sqrt(number)));
	vector<int> factorization;
	auto ptr = primes.begin();

	while (ptr != primes.end()) {
		if (number%(*ptr) == 0) {
			factorization.push_back(*ptr);
			number = number/(*ptr);
		} else {
			ptr++;
		}
	}
	
	if (number != 1) {
		factorization.push_back(number);
	}

	return factorization;
}

void print(const vector <int> &result) {
	for (int x : result)
		cout << x << " ";
	cout << endl;
}

int main() {
	int number;
	cin >> number;
	print(Factorize(number));
}
#include <iostream>
#include <vector>

using namespace std;

int GetWeatherRandomness(const vector <int> &temperatures) {
	int n = temperatures.size();
	int accum = 0;

	for (int i = 0; i < n; ++i) {

		bool left_check = false;
		bool right_check = false;

		try { if (temperatures.at(i-1) < temperatures[i])
				left_check = true;
		} catch(out_of_range const& exc) { left_check = true;}

		try { if (temperatures[i] > temperatures.at(i+1))
				right_check = true;
		} catch(out_of_range const& exc) { right_check = true;}

		if (left_check && right_check) {
			accum++;
		}
	}

	return accum;
}

void print(int result) {
	cout << result << endl;
}

int main() {
	int n;
	cin >> n;
	vector <int> temperatures(n);
	for (int i = 0; i < n; ++i)
		cin >> temperatures[i];
	print(GetWeatherRandomness(temperatures));
}
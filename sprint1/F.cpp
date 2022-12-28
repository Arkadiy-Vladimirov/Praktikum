#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string Parse(const string &line) {
	string result;
	for (unsigned char ch :line) {
		if (isalpha(ch)) {
			result.push_back(tolower(ch));
		}
	}
	return result;
}

bool IsPalindrome(const string &line) {
	string good_line = Parse(line);
	int n = good_line.size();
	for (int i = 0; i < n/2; ++i) {
		if (good_line[i] != good_line[n-1-i]) {
			return false;
		}
	}

	return true ;
}

void print(bool result) {
	if (result)
		cout << "True";
	else
		cout << "False";
	cout << endl;
}

int main() {
	string line;
	getline(cin, line);
	print(IsPalindrome(line));
}
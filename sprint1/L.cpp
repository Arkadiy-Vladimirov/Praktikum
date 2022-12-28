#include <iostream>
#include <string>
#include <set>
#include <map>

using namespace std;

set<char> GetAlphabet() {
	set<char> alphabet;
	for (char c = 'a'; c <= 'z'; c++) {
		alphabet.insert(c);
	}
	return alphabet;
}

map<char, int> InitStrMap() {
	auto alphabet = GetAlphabet();
	map<char, int> nullStrMap;
	for (char c : alphabet) {
		nullStrMap[c] = 0;
	}
	return nullStrMap;
}

map<char, int> GetStrMap(const string &str) {
	map<char, int> strMap = InitStrMap();
	for (char c : str) {
		strMap[c]++;
	}
	return strMap;
}

char GetExcessiveLetter(const string &shorter, const string &longer) {
	auto alphabet = GetAlphabet();
	map<char,int> map1 = GetStrMap(shorter), map2 = GetStrMap(longer);

	for (char c : alphabet) {
		if (map1[c] != map2[c]) {
			return c;
		}
	}
	return '0';
}

void print(char result) {
	cout << result << endl;
}

int main() {
	string shorter, longer;
	cin >> shorter >> longer;
	print(GetExcessiveLetter(shorter, longer));
}
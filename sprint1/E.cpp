#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;


string GetLongestWord(const string &line) {
	stringstream ss(line);
	string word;
	vector<string> words;

	while (getline(ss, word, ' ')) {
		words.push_back(word);
	}


	string longest_word;
	int greatest_size = 0;

	for (string word : words) {
		if (word.size() > greatest_size) {
			longest_word = word;
			greatest_size = word.size();
		}
	}
	return longest_word;
}

void print(const string &result) {
	cout << result << endl << result.length() << endl;
}

int main() {
	int n;
	cin >> n;
	string line;
	getline(cin, line);
	getline(cin, line);
	print(GetLongestWord(line));
}

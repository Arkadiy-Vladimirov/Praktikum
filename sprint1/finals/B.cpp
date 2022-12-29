//accepted parcel ID: 80157494

//idea:
//  input: mat M(4,4), int k -> {O(1)} -> map: digit to cardinal -> 
//  -> count(map[i] <= 2k) = output.

//code:

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

int GetScore(const std::vector<std::vector<char>>& field, int k) {
    std::set<char> digits;
    std::map<char, int> digit_count;
    
    //counting digits
    for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
        char fig = field[i][j];
        if (fig != '.') {

            if (digits.find(fig) != digits.end()) { //if already seen then increase the counter
                digit_count[fig]++;
            } else {                                //if not initialise with 1
                digits.insert(fig);
                digit_count[fig] = 1;
            }
        
        }
    }
    }

    //evaluating the answer
    int score = 0;

    for (int digit : digits) {
        if (digit_count[digit] <= 2*k) {
            score++;
        }
    }

    return score;
}


int main() {
    int k;
    std::vector<std::vector<char>> field(4, std::vector<char> (4));
    std::string row;    

    std::cin >> k;
    std::getline(std::cin, row);// read the endl

    for (int i = 0; i < 4; ++i) {
        std::getline(std::cin, row);
        for (int j = 0; j < 4; ++j) {
            field[i][j] = row[j];
    }
    }

    std::cout << GetScore(field, k) << std::endl;
    return 0;
}
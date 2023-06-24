// find and replace all occurencies of a string in a text

#include <iostream>
#include <string>
#include <vector>

class Text {
    std::string text;
public:
    Text(std::string txt = "") : text(txt) {};
    std::vector<int> find(std::string &pattern);
    std::string replace(std::string &deleted, std::string &inserted);
};

int main() {
    std::string text, str_to_replace, str_to_replace_with;
    std::getline(std::cin, text);
    std::getline(std::cin, str_to_replace);
    std::getline(std::cin, str_to_replace_with);

    std::cout << Text(text).replace(str_to_replace, str_to_replace_with);
    std::cout << std::endl;

    return 0;
}

std::vector<int> Text::find(std::string &pattern) {
    std::vector<int> start_pos;
    std::string str = pattern + '#' + text;

    std::vector<int> pi(str.size() + 1);    // prefix function
    pi[0] = -1; pi[1] = 0;

    for (int i = 1; i < str.size(); ++i) {  // go through str, adding new 
                                            // elements one by one
        int k = pi[i];
        while ((str[i] != str[k]) && (k != 0)) {
            k = pi[k];  //iterate over k - the size of maximum prefix/suffix
        }               //that may be concat with s[i] to get a new one

        pi[i+1] = k + int(str[i] == str[k]);

        if (pi[i+1] == pattern.size()) {
            start_pos.push_back(i - 2 * pattern.size());
        }
    }

    return start_pos;
}

std::string Text::replace(std::string &deleted, std::string &inserted) {
    std::string out;
    std::vector<int> found = find(deleted);

    int pos = 0;
    for (int start : found) {
        out.append(text.substr(pos, start - pos));
        out.append(inserted);
        pos = start + deleted.size();
    }

    if (pos != text.size()) {
        out.append(text.substr(pos));
    }
       
    return out;
}
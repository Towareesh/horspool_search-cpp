#include <iostream>
#include <map>
#include <string>

using namespace std;

map<char, int> preprocess(string pattern) {
    /*Preprocesses pattern to create a table containing
    for each character in alphabet number of characters
    that can be safely skipped.*/

    map<char, int> skip_tbl;

    for (size_t indx = 0; indx < pattern.length(); indx++) {
        skip_tbl[pattern[indx]] = pattern.length() - indx - 1;
    }
    return skip_tbl;
}


bool same(string piece_string, string pattern) {
    /*Compares two strings, up to the first len characters.*/

    int offset = pattern.length() - 1;

    while (piece_string[offset] == pattern[offset]) {
        if (offset == 0) {
            return true;
        }
        offset -= 1;
    }
    return false;
}


bool horspool_search(string str, string pattern) {
    /*The algorithm works best with long needle chains
    when it consistently finds a mismatched character
    in last byte of current position in
    or near haystack, and last byte of needle does
    not occur elsewhere inside needle*/

    if (pattern.length() > str.length()) {
        return false;
    }
    map<char, int> skip_tbl = preprocess(pattern);
    int offset = 0;

    while ((str.length() - offset) >= pattern.length()) {
        if (same(str.substr(offset, -1), pattern)) {
            return true;
        }

        int skip_value = skip_tbl.count(str[offset + pattern.length() - 1]);

        if (skip_value) {
            offset += skip_value;
        }
        else {
            offset += 1;
        }
    }
    return false;
}

int main() {
    cout << horspool_search("hello world", "world");
}

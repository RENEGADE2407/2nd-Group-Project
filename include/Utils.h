// Purpose: Shared string helpers (trim, case-insensitive compare, field split)
//          Header-only so no extra .cpp is needed.
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

using namespace std;

namespace Utils {

// True for space, tab, \r,  newline.
inline bool isWhitespace(char c) {
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

// Removes whitespace from both ends
inline string trim(const string& s) {
    size_t start = 0;
    while (start < s.size() && isWhitespace(s[start])) ++start;
    size_t end = s.size();
    while (end > start && isWhitespace(s[end - 1])) --end;
    return s.substr(start, end - start);
}

// ASCII-only lowercase copy.
inline string toLower(const string& s) {
    string r = s;
    for (size_t i = 0; i < r.size(); ++i)
        if (r[i] >= 'A' && r[i] <= 'Z') r[i] = static_cast<char>(r[i] - 'A' + 'a');
    return r;
}

// ASCII-only uppercase copy.
inline string toUpper(const string& s) {
    string r = s;
    for (size_t i = 0; i < r.size(); ++i)
        if (r[i] >= 'a' && r[i] <= 'z') r[i] = static_cast<char>(r[i] - 'a' + 'A');
    return r;
}

// Case-insensitive equality
inline bool equalsIgnoreCase(const string& a, const string& b) {
    return toLower(a) == toLower(b);
}

// A line is skippable if it is blank, or its first non-whitespace char is '#'.
inline bool isBlankOrComment(const string& line) {
    string t = trim(line);
    return t.empty() || t[0] == '#';
}

// Splits on '|' and trims every field.
inline vector<string> splitFields(const string& line) {
    vector<string> fields;
    string current;
    for (size_t i = 0; i < line.size(); ++i) {
        if (line[i] == '|') {
            fields.push_back(trim(current));
            current.clear();
        } else {
            current += line[i];
        }
    }
    fields.push_back(trim(current));
    return fields;
}

} // namespace Utils

#endif

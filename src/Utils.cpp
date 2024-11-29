#include "Utils.h"
#include <algorithm>
#include <sstream>
#include <fstream>
#include <cctype>

string Utils::toLower(const string& str) {
    string lowerStr = str;
    transform(str.begin(), str.end(), back_inserter(lowerStr), ::tolower);
    return lowerStr;
}

vector<string> Utils::split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    stringstream ss(str);

    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

vector<vector<string>> Utils::readCSV(const string& filepath) {
    vector<vector<string>> data;
    ifstream file(filepath);

    if (!file.is_open()) {
        throw runtime_error("No se pudo abrir el archivo: " + filepath);
    }

    string line;
    while (getline(file, line)) {
        vector<string> row = Utils::split(line, ',');
        data.push_back(row);
    }

    file.close();
    return data;
}

string Utils::trim(const string& str) {
    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");

    if (first == string::npos || last == string::npos) {
        return "";
    }

    return str.substr(first, (last - first + 1));
}

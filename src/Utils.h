#ifndef PROYECTOPROGRA3_UTILS_H
#define PROYECTOPROGRA3_UTILS_H

#include <string>
#include <vector>
using namespace std;

class Utils {
public:

    static string toLower(const string& str);


    static vector<string> split(const string& str, char delimiter);

    static vector<vector<string>> readCSV(const string& filepath);

    static string trim(const string& str);
};

#endif

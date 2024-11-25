#include <iostream>
#include <fstream>
#include <vector>
#include <codecvt>
using namespace std;
int main() {
    string data = "mpst_full_data.csv";
    string output = "data_corregida.csv";
    ifstream file(data);
    ofstream out(output);
    vector<string> lineas_corregidas;
    string encabezado;
    if (getline(file, encabezado)) {
        lineas_corregidas.push_back(encabezado);
    }
    string line;
    string currline;
    while (getline(file, line)) {
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);
        if (line.rfind("tt", 0) == 0) {
            if (!currline.empty()) {
                lineas_corregidas.push_back(currline);
            }
            currline = line;
        } else {
            currline += " " + line;
        }
    }
    if (!currline.empty()) {
        lineas_corregidas.push_back(currline);
    }
    for(const auto& correctedLine : lineas_corregidas) {
        out << correctedLine << endl;
    }
    file.close();
    out.close();
    
    return 0;
}

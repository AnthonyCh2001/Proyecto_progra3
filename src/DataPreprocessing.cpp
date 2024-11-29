#include "DataPreprocessing.h"
#include <fstream>
#include <iostream>
#include <vector>

void preprocessData(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream file(inputFile);
    std::ofstream out(outputFile);


    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de entrada: " << inputFile << std::endl;
        return;
    }

    if (!out.is_open()) {
        std::cerr << "Error: No se pudo crear el archivo de salida: " << outputFile << std::endl;
        return;
    }

    std::vector<std::string> lineasCorregidas;
    std::string line, currline;

    while (std::getline(file, line)) {
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        if (line.rfind("tt", 0) == 0) {
            if (!currline.empty()) {
                lineasCorregidas.push_back(currline);
            }
            currline = line;
        } else {
            currline += " " + line;
        }
    }

    if (!currline.empty()) {
        lineasCorregidas.push_back(currline);
    }

    for (const auto& correctedLine : lineasCorregidas) {
        out << correctedLine << std::endl;
    }

    file.close();
    out.close();
}

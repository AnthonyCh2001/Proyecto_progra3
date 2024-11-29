#ifndef PROYECTOPROGRA3_SEARCHALGORITHMS_H
#define PROYECTOPROGRA3_SEARCHALGORITHMS_H

#include "MovieTree.h"
#include <string>
#include <vector>

using namespace std;

class SearchAlgorithms {
public:

    static vector<Movie> searchByKeyword(const MovieTree& movieTree, const string& keyword);


    static vector<Movie> searchByPhrase(const MovieTree& movieTree, const string& phrase);


    static vector<Movie> searchByTag(const MovieTree& movieTree, const string& tag);
};

#endif

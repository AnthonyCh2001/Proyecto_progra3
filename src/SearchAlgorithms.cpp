#include "SearchAlgorithms.h"
#include "MovieTree.h"
#include "Utils.h"
#include <algorithm>

int calculateRelevance(const Movie& movie, const string& keyword) {
    int score = 0;
    string lowerKeyword = Utils::toLower(keyword);
    string lowerTitle = Utils::toLower(movie.title);
    string lowerSynopsis = Utils::toLower(movie.synopsis);

    size_t pos = lowerTitle.find(lowerKeyword);
    while (pos != string::npos) {
        score += 10;
        pos = lowerTitle.find(lowerKeyword, pos + 1);
    }

    pos = lowerSynopsis.find(lowerKeyword);
    while (pos != string::npos) {
        score += 5;
        pos = lowerSynopsis.find(lowerKeyword, pos + 1);
    }

    return score;
}

void sortResultsByRelevance(vector<Movie>& results, const string& keyword) {
    sort(results.begin(), results.end(), [&keyword](const Movie& a, const Movie& b) {
        return calculateRelevance(a, keyword) > calculateRelevance(b, keyword);
    });
}


vector<Movie> SearchAlgorithms::searchByKeyword(const MovieTree& movieTree, const string& keyword) {
    vector<Movie> results = movieTree.search(keyword);
    if (results.empty()) return results;

    sortResultsByRelevance(results, keyword);
    return results;
}

vector<Movie> SearchAlgorithms::searchByPhrase(const MovieTree& movieTree, const string& phrase) {
    vector<Movie> results = movieTree.search(phrase);
    if (results.empty()) return results;

    string lowerPhrase = Utils::toLower(phrase);

    results.erase(remove_if(results.begin(), results.end(),
                            [&lowerPhrase](const Movie& movie) {
                                return Utils::toLower(movie.title).find(lowerPhrase) == string::npos &&
                                       Utils::toLower(movie.synopsis).find(lowerPhrase) == string::npos;
                            }), results.end());

    sortResultsByRelevance(results, phrase);
    return results;
}

vector<Movie> SearchAlgorithms::searchByTag(const MovieTree& movieTree, const string& tag) {
    vector<Movie> results = movieTree.search(tag);
    if (results.empty()) return results;

    string lowerTag = Utils::toLower(tag);

    results.erase(remove_if(results.begin(), results.end(),
                            [&lowerTag](const Movie& movie) {
                                for (const string& movieTag : movie.tags) {
                                    if (Utils::toLower(movieTag) == lowerTag) return false;
                                }
                                return true;
                            }), results.end());

    sortResultsByRelevance(results, tag);
    return results;
}





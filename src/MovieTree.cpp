#include "MovieTree.h"
#include "Utils.h"
#include <algorithm>
#include <iostream>
#include <cctype>

Movie::Movie(const string& title, const string& synopsis, const vector<string>& tags)
        : title(title), synopsis(synopsis), tags(tags) {}

TreeNode::TreeNode(char key)
        : key(key), left(nullptr), right(nullptr) {}

MovieTree::MovieTree() : root(nullptr) {}

MovieTree::~MovieTree() {
    deleteTree(root);
}

void MovieTree::deleteTree(TreeNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

void MovieTree::insert(TreeNode*& node, const string& title, const Movie& movie) {
    if (title.empty()) {
        cerr << "Advertencia: No se puede insertar una película con título vacío." << endl;
        return;
    }

    char key = tolower(title[0]);
    if (!node) {
        node = new TreeNode(key);
    }

    if (key < node->key) {
        insert(node->left, title, movie);
    } else if (key > node->key) {
        insert(node->right, title, movie);
    } else {
        node->movies.push_back(movie);
    }
}

void MovieTree::insert(const string& title, const Movie& movie) {
    insert(root, title, movie);
}

vector<Movie> MovieTree::search(const string& keyword) const {
    vector<Movie> results;
    search(root, keyword, results);
    return results;
}

void MovieTree::search(TreeNode* node, const string& keyword, vector<Movie>& results) const {
    if (!node) return;

    string lowerKeyword = Utils::toLower(keyword);

    for (const auto& movie : node->movies) {
        string lowerTitle = Utils::toLower(movie.title);
        string lowerSynopsis = Utils::toLower(movie.synopsis);

        if (lowerTitle.find(lowerKeyword) != string::npos || lowerSynopsis.find(lowerKeyword) != string::npos) {
            results.push_back(movie);
        }
    }

    search(node->left, keyword, results);
    search(node->right, keyword, results);
}

void MovieTree::addToLiked(const Movie& movie) {
    likedMovies.push_back(movie);
}

void MovieTree::addToWatchLater(const Movie& movie) {
    watchLaterMovies.push_back(movie);
}

vector<Movie> MovieTree::getLikedMovies() const {
    return likedMovies;
}

vector<Movie> MovieTree::getWatchLaterMovies() const {
    return watchLaterMovies;
}

vector<Movie> MovieTree::getSimilarMovies() const {
    vector<Movie> similarMovies;

    for (const auto& likedMovie : likedMovies) {
        for (const auto& tag : likedMovie.tags) {
            vector<Movie> tagResults = search(tag);
            for (const auto& movie : tagResults) {
                if (find(similarMovies.begin(), similarMovies.end(), movie) == similarMovies.end()) {
                    similarMovies.push_back(movie);
                }
            }
        }
    }
    return similarMovies;
}

#ifndef MOVIETREE_H
#define MOVIETREE_H

#include <string>
#include <vector>

using namespace std;

class Movie {
public:
    string title;
    string synopsis;
    vector<string> tags;

    Movie(const string& title, const string& synopsis, const vector<string>& tags);

    bool operator==(const Movie& other) const {
        return title == other.title &&
               synopsis == other.synopsis &&
               tags == other.tags;
    }
};


class TreeNode {
public:
    char key;
    vector<Movie> movies;
    TreeNode* left;
    TreeNode* right;

    TreeNode(char key);
};

class MovieTree {
private:
    TreeNode* root;
    vector<Movie> likedMovies;
    vector<Movie> watchLaterMovies;

    void insert(TreeNode*& node, const string& title, const Movie& movie);
    void search(TreeNode* node, const string& keyword, vector<Movie>& results) const;
    void deleteTree(TreeNode* node);

public:

    MovieTree();
    ~MovieTree();

    void insert(const string& title, const Movie& movie);  // Inserta una película en el árbol
    vector<Movie> search(const string& keyword) const;     // Busca películas por palabra clave
    void addToLiked(const Movie& movie);                   // Agrega una película a la lista de "Like"
    void addToWatchLater(const Movie& movie);              // Agrega una película a la lista de "Ver más tarde"
    vector<Movie> getLikedMovies() const;                  // Devuelve la lista de películas con "Like"
    vector<Movie> getWatchLaterMovies() const;             // Devuelve la lista de películas "Ver más tarde"
    vector<Movie> getSimilarMovies() const;                // Devuelve las películas similares basadas en tags
};

#endif

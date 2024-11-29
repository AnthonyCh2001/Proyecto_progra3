#include "DataPreprocessing.h"
#include "MovieTree.h"
#include "Utils.h"
#include "SearchAlgorithms.h"
#include <iostream>
#include <filesystem>

using namespace std;

void displayResultsWithPagination(const vector<Movie>& results) {
    size_t pageSize = 5;
    size_t totalPages = (results.size() + pageSize - 1) / pageSize;

    for (size_t page = 0; page < totalPages; ++page) {
        cout << "\n=== Pagina " << page + 1 << " de " << totalPages << " ===\n";
        size_t start = page * pageSize;
        size_t end = min(start + pageSize, results.size());

        for (size_t i = start; i < end; ++i) {
            cout << i + 1 << ". " << results[i].title << " (Tags: ";
            for (const auto& tag : results[i].tags) cout << tag << " ";
            cout << ")\n";
        }

        if (page < totalPages - 1) {
            cout << "Presiona Enter para mostrar mas resultados...\n";
            cin.ignore();
        }
    }
}

void displaySavedMovies(const MovieTree& tree) {
    cout << "\nPelículas en 'Ver mas tarde':\n";
    for (const auto& movie : tree.getWatchLaterMovies()) {
        cout << " - " << movie.title << "\n";
    }

    cout << "\nPeliculas similares a las que te gustaron:\n";
    for (const auto& movie : tree.getSimilarMovies()) {
        cout << " - " << movie.title << "\n";
    }
}

int main() {
    string inputFile = "../data/mpst_full_data.csv";
    string outputFile = "../data/data_corregida1.csv";

    // Preprocesar archivo
    if (!std::filesystem::exists(outputFile)) {
        cout << "Preprocesando datos..." << endl;
        preprocessData(inputFile, outputFile);
    }

    try {
        vector<vector<string>> data = Utils::readCSV(outputFile);
        MovieTree movieTree;

        for (const auto& row : data) {
            if (row.size() < 3 || row[0].empty() || row[1].empty()) continue;
            string title = Utils::trim(row[0]);
            string synopsis = Utils::trim(row[1]);
            vector<string> tags = Utils::split(row[2], '|');

            Movie movie(title, synopsis, tags);
            movieTree.insert(title, movie);
        }

        cout << "Arbol de películas cargado correctamente." << endl;

        while (true) {
            cout << "\n=== Plataforma de Streaming ===\n";
            cout << "1. Buscar pelicula por palabra clave\n";
            cout << "2. Buscar pelicula por frase\n";
            cout << "3. Buscar pelicula por tag\n";
            cout << "4. Mostrar peliculas guardadas\n";
            cout << "5. Salir\n";
            cout << "Elige una opcion: ";
            int opcion;
            cin >> opcion;

            if (opcion == 5) break;

            cin.ignore();
            string query;
            cout << "Ingresa tu busqueda: ";
            getline(cin, query);

            vector<Movie> resultados;
            switch (opcion) {
                case 1:
                    resultados = SearchAlgorithms::searchByKeyword(movieTree, query);
                    break;
                case 2:
                    resultados = SearchAlgorithms::searchByPhrase(movieTree, query);
                    break;
                case 3:
                    resultados = SearchAlgorithms::searchByTag(movieTree, query);
                    break;
                case 4:
                    displaySavedMovies(movieTree);
                    continue;
                default:
                    cout << "Opcion no valida.\n";
                    continue;
            }

            if (resultados.empty()) {
                cout << "No se encontraron peliculas.\n";
            } else {
                displayResultsWithPagination(resultados);

                cout << "\nSelecciona una pelicula para ver más detalles o 0 para salir: ";
                int choice;
                cin >> choice;

                if (choice > 0 && choice <= resultados.size()) {
                    const Movie& selectedMovie = resultados[choice - 1];
                    cout << "\nTitulo: " << selectedMovie.title
                         << "\nSinopsis: " << selectedMovie.synopsis << "\n";

                    cout << "1. Like\n2. Ver mas tarde\nElige una opcion: ";
                    int action;
                    cin >> action;

                    if (action == 1) movieTree.addToLiked(selectedMovie);
                    if (action == 2) movieTree.addToWatchLater(selectedMovie);
                }
            }
        }
    } catch (const std::exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {

    // get the file input
    if(argc != 2) {
        cout << "Usage: " << argv[0] << " <input_file>" << endl;
        exit(1);
    }


    ifstream input(argv[1]);
    if(!input) {
        cout << "Error opening file" << endl;
        exit(1);
    }

    vector< vector<char> > mat;
    while(true)
    {
    // Finche' non arrivo alla fine del file
        if(!input.eof()) {
            vector<char> row;
            char value;
            // Inserisco valori nella matrice ...
            while(input >> value) {
                row.push_back(value);
                // Finché non arrivo a capo
                if(input.get() == '\n') break;
            }
            // Se il vettore non e' vuoto, lo inserisco nella matrice
            if(!row.empty())
                mat.push_back(row);

        } else {
            break;
        }
    }

    for(int i = 0; i < mat.size(); i++) {
        for(int j = 0; j < mat[i].size(); j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }

}

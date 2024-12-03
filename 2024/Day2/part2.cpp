#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

bool isSafe(vector<int> v);
bool isSafeWithoutDampener(vector<int> v);

int main(int argc, char **argv) {

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

    // declare the two vectors to store the values
    vector< vector<int> > mat;

    while(true)
    {
    // Finche' non arrivo alla fine del file
        if(!input.eof()) {
            vector<int> row;
            int value;
            // Inserisco valori nella matrice ...
            while(input >> value) {
                row.push_back(value);
                // Finché non arrivo a capo
                if(input.get() == '\n') break;
            }
            // Se il vettore non e' vuoto, lo inserisco nella matrice
            if(!row.empty()) mat.push_back(row);

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

    int countSafe = 0;
    for(int i = 0; i < mat.size(); i++) {
        if(isSafe(mat[i])) countSafe++;
    }

    cout << "Safe levels: " << countSafe << endl;

    // close the file
    input.close();

    return 0;
}

bool isSafe(vector<int> v) {
    bool increasing = (v[0] < v[1]);
    for(int i = 0; i < v.size() - 1; i++) {
        if(increasing) {
            if(v[i] >= v[i+1] || abs((v[i+1] - v[i])) > 3)
            {
                vector<int> temp = v; // temp = { 1, 2, 9, 3}
                for(int j = 0; j < temp.size(); j++) {
                    temp.erase(temp.begin()+j);
                    if(isSafeWithoutDampener(temp)) return true;
                    temp.clear();
                    temp = v;
                }

                return false;
            }
        }else{
            if(v[i] <= v[i+1] || abs(v[i] - v[i+1]) > 3)
            {
                vector<int> temp = v;
                for(int j = 0; j < temp.size(); j++) {
                    temp.erase(temp.begin()+j);
                    if(isSafeWithoutDampener(temp)) return true;
                    temp.clear();
                    temp = v;
                }

                return false;
            }
        }
    }

    return true;
}


bool isSafeWithoutDampener(vector<int> v) {
    bool increasing = (v[0] < v[1]);
    // Goes through the vector and checks if the levels are increasing or decreasing
    for(int i = 0; i < v.size() - 1; i++) {
        if(increasing) {
            // if the levels are increasing and the next level is greater OR equal than the current one
            // or the difference between the two levels is greater than 3, return false
            if(v[i] >= v[i+1] || abs((v[i+1] - v[i])) > 3)
                return false;
        } else if(!increasing) {
            // if the levels are decreasing and the next level is smaller OR equal than the current one
            // or the difference between the two levels is greater than 3, return false
            if(v[i] <= v[i+1] || abs(v[i] - v[i+1]) > 3)
                return false;
        }
    }
    return true;
}

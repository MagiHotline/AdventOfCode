#include <cmath>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>
#include <iostream>
using namespace std;

bool findXMASDiagonalRight(int, int, vector<string>);
bool findXMASDiagonalLeft(int, int, vector<string>);

bool isWithinBounds(int x, int y, int rows, int cols) {
    return x >= 0 && y >= 0 && x < rows && y < cols;
}

bool isWithinBounds(int x, int rows) {
    return x >= 0 && x < rows;
}


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

    // vector of strings or a vector of a vector of chars
    // char* argv[] is a vector of strings
    vector<string> ws;
    int countXMAS = 0;
    while(true)
    {
    // Finche' non arrivo alla fine del file
        if(!input.eof()) {
            string row;
            char value;
            // Inserisco valori nella matrice ...
            getline(input, row);

            if(!row.empty())
                ws.push_back(row);

        } else {
            break;
        }
    }

    // Prints char by char
    for(int i = 0; i < ws.size(); i++) {
        for(int j = 0; j < ws[i].size(); j++) {
            cout << ws[i][j] << " ";
        }
        cout << endl;
    }

    int sol = 0;

    for(int i = 0; i < ws.size(); i++) {
        for(int j = 0; j < ws[i].size(); j++) {
            if(ws[i][j] == 'A') {
                if(findXMASDiagonalLeft(i, j, ws) && findXMASDiagonalRight(i, j, ws))
                    sol++;
            }
        }
    }

    cout << "Soluzione: " << sol << endl;

    return 0;
}


// Takes the point where the X is and checks if the word XMAS is in the matrix
bool findXMASDiagonalLeft(int x, int y, vector<string> ws) {
    string wordtoCheck = "";

    // Check the diagonal left
    for(int move = -1; move <= 1; move++) {
        // If its out of bounds, we dont want to append
        // If its in bounds, we want to append
        if(isWithinBounds(x+move, y+move, ws.size(), ws[x].size())) {
            wordtoCheck += ws[x + move][y + move];
        }
    }

    cout << wordtoCheck << endl;
    if((wordtoCheck.find("MAS") != string::npos) || (wordtoCheck.find("SAM") != string::npos)) {
        return true;
    }

    return false;
}


bool findXMASDiagonalRight(int x, int y, vector<string> ws) {
    string wordtoCheck = "";

    // Check the diagonal right
    for (int move = -1; move <= 1; move++) {
         if(isWithinBounds(x+move, y-move, ws.size(), ws[x].size())) {
            wordtoCheck += ws[x + move][y - move];
        }
    }

    cout << wordtoCheck << endl;
    if((wordtoCheck.find("MAS") != string::npos) || (wordtoCheck.find("SAM") != string::npos)) {
        return true;
    }

    return false;
}

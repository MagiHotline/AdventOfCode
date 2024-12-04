#include <cmath>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>
#include <iostream>
using namespace std;

// Take the point where the X is and checks if the word XMAS is in the matrix
int findXMASHorizontal(int, int, vector<string>);
int findXMASVertical(int, int, vector<string>);
int findXMASDiagonalRight(int, int, vector<string>);
int findXMASDiagonalLeft(int, int, vector<string>);

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
            if(ws[i][j] == 'X') {
                sol += findXMASVertical(i, j, ws) + findXMASHorizontal(i, j, ws)
                    + findXMASDiagonalLeft(i, j, ws) + findXMASDiagonalRight(i, j, ws);
            }
        }
    }

    cout << "Soluzione: " << sol << endl;

    return 0;
}

// Takes the point where the X is and checks if the word XMAS is in the matrix
int findXMASHorizontal(int x, int y, vector<string> ws) {
    int countXMAS = 0;
    string wordtoCheck = "";

    // Check the horizontal
    for(int move = -3; move <= 3; move++) {
        // If its out of bounds, we dont want to append
        // If its in bounds, we want to append
        if(isWithinBounds(y+move, ws[x].size())) {
            wordtoCheck += ws[x][y + move];
        }
    }

    cout << wordtoCheck << endl;

    // Checks if the word contains XMAS
    if(wordtoCheck.find("XMAS") != string::npos) {
        countXMAS++;
    }

    // Checks if the word contains SAMX
    if(wordtoCheck.find("SAMX") != string::npos) {
        countXMAS++;
    }

    return countXMAS;
}

// Takes the point where the X is and checks if the word XMAS is in the matrix
int findXMASVertical(int x, int y, vector<string> ws) {
    int countXMAS = 0;
    string wordtoCheck = "";

    // Check the vertical
    for(int move = -3; move <= 3; move++) {
        // If its out of bounds, we dont want to append
        // If its in bounds, we want to append
        if(isWithinBounds(x+move, ws.size())) {
            wordtoCheck += ws[x + move][y];
        }
    }

    cout << wordtoCheck << endl;

    if(wordtoCheck.find("XMAS") != string::npos) {
        countXMAS++;
    }

    if(wordtoCheck.find("SAMX") != string::npos) {
        countXMAS++;
    }

    return countXMAS;
}

// Takes the point where the X is and checks if the word XMAS is in the matrix
int findXMASDiagonalLeft(int x, int y, vector<string> ws) {
    int countXMAS = 0;
    string wordtoCheck = "";

    // Check the diagonal left
    for(int move = -3; move <= 3; move++) {
        // If its out of bounds, we dont want to append
        // If its in bounds, we want to append
        if(isWithinBounds(x+move, y+move, ws.size(), ws[x].size())) {
            wordtoCheck += ws[x + move][y + move];
        }
    }


    cout << wordtoCheck << endl;

    if(wordtoCheck.find("XMAS") != string::npos) {
        countXMAS++;

    }

    if(wordtoCheck.find("SAMX") != string::npos) {
        countXMAS++;
    }

    return countXMAS;
}

// Takes the point where the X is and checks if the word XMAS is in the matrix
int findXMASDiagonalRight(int x, int y, vector<string> ws) {
    int countXMAS = 0;
    string wordtoCheck = "";

    // Check the diagonal right
    for (int move = -3; move <= 3; move++) {
         if(isWithinBounds(x+move, y-move, ws.size(), ws[x].size())) {
            wordtoCheck += ws[x + move][y - move];
        }
    }

    cout << wordtoCheck << endl;

    if(wordtoCheck.find("XMAS") != string::npos) {
        countXMAS++;

    }

    if(wordtoCheck.find("SAMX") != string::npos) {
        countXMAS++;
    }

    return countXMAS;
}

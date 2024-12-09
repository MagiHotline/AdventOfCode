#include <cstdio>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <set>
#include <unordered_map>
#include <unistd.h>

using namespace std;

struct Point {
    int x, y;

    // Constructor
    Point(int x, int y) : x(x), y(y) {}

    // Comparison operator for use in std::set
    bool operator<(const Point& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

vector<string> scanAntennas(vector<string>, int, int, char, int&);
void printMatrix(vector<string>);
void displayMatrix(vector<string>, int);
bool isWithinBounds(Point, vector< string >);

int main(int argc, char* argv[]) {

  if(argc != 2) {
        cout << "Usage: " << argv[0] << " <input.txt>" << endl;
        exit(1);
    }

    ifstream input(argv[1]);
    if(!input) {
        cout << "Error opening file" << endl;
        exit(1);
    }

    // get the matrix
    vector< string > roof;
    while(!input.eof()) {
        string line;
        getline(input, line);
        if(!line.empty()) roof.push_back(line);
    }

    int count = 0;
    for(int i = 0; i < roof.size(); i++) {
        for(int j = 0; j < roof.size(); j++) {
            if(roof[i][j] != '.' && roof[i][j] != '#') {
                char tofind = roof[i][j];
                // Search in the border of twice the distance
                // if found, then we can place the antenna
                // if not found, then we can't place the antenna
                roof = scanAntennas(roof, i, j, tofind, count);
            }
        }
    }

    printMatrix(roof);

    for(int i = 0; i < roof.size(); i++) {
        for(int j = 0; j < roof.size(); j++) {
            if(roof[i][j] != '#' && roof[i][j] != '.') {
                count++;
            }
        }
    }

    cout << "Solution: " << count << endl;
    input.close();
}

vector<string> scanAntennas(vector<string> roof, int row, int col, char tofind, int &count) {
    for (int k = 2; k < roof.size(); k++) { // Distance range
        for (int i = row - k; i <= row + k; i++) { // Rows in range
            for (int j = col - k; j <= col + k; j++) { // Columns in range
                if (!isWithinBounds(Point(i, j), roof) || (i == row && j == col)) continue;

                // Check if the character matches
                if (roof[i][j] == tofind) {
                    //displayMatrix(roof, count);

                    int dx = i - row;
                    int dy = j - col;

                    // Start at the point beyond the current match
                    int newI = i + dx;
                    int newJ = j + dy;
                    while (isWithinBounds(Point(newI, newJ), roof)) {
                        Point newPoint(newI, newJ);
                        if (roof[newI][newJ] == '.') {
                            // Place antinode
                            roof[newI][newJ] = '#';
                            count++;
                        }

                        // Move further in the same direction
                        newI += dx;
                        newJ += dy;
                    }
                }
            }
        }
    }


    return roof;
}


// We pass the point and the matrix
bool isWithinBounds(Point p, vector< string > prison) {
    return p.x >= 0 && p.y >= 0 && p.x < prison.size() && p.y < prison[p.x].size();
}

void displayMatrix(vector<string> prison, int cont) {
    for (string row : prison) {
        cout << row << endl; // Each row of the matrix
    }

    cout << "Antinode placed: " << cont << endl;

    usleep(0*1000);
    system("clear");
}

void printMatrix(vector<string> roof) {
    for (int i = 0; i < roof.size(); i++) {
        cout << roof[i] << endl; // Each row of the matrix
    }
}

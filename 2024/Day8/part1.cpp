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
void displayMatrix(vector<string>);
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
                cout << "Searching for " << tofind << " at " << i << " " << j << endl;
                // Search in the border of twice the distance
                // if found, then we can place the antenna
                // if not found, then we can't place the antenna
                roof = scanAntennas(roof, i, j, tofind, count);
            }
        }
    }

    printMatrix(roof);
    /*for(int i = 0; i < roof.size(); i++) {
        for(int j = 0; j < roof.size(); j++) {
            if(roof[i][j] == '#') count++;
        }
    }*/

    cout << "Solution: " << count << endl;
    input.close();
}

int saveX, saveY;

vector<string> scanAntennas(vector<string> roof, int row, int col, char tofind, int &count) {
    // We need to scan the 5x5 matrix around the point
    // if we find the character, then we can place the antenna
    // if we don't find the character, then we can't place the antenna
    // We need to check the bounds of the matrix
    set < Point > visited;
    bool checked = false;
    for (int k = 2; k < roof.size(); k++) {
        for (int i = row - k; i <= row + k; i++) {
            for (int j = col - k; j <= col + k; j++) {
                // If the point is out of bounds or the point is the same as the current point, continue
                if (!isWithinBounds(Point(i, j), roof) || (i == row && j == col)) continue;

                // I found the character
                if (roof[i][j] == tofind) {

                    // Calculate the relative offset between (i, j) and (row, col)
                    Point newPoint(i, j);

                    if(visited.find(newPoint) == visited.end()) {
                        visited.insert(newPoint);
                    }

                    int dx = i - row;
                    int dy = j - col;

                    // Compute the new position using the same offset
                    int newI = i + dx;
                    int newJ = j + dy;

                    // If its within bounds and the point is empty, place the antinode
                    if (isWithinBounds(Point(newI, newJ), roof) && roof[newI][newJ] == '.' ) {
                        roof[newI][newJ] = '#';
                        count++;
                    }
                    // If the antinode would replace an antenna, count the antinode but don't remove the antenna
                    else if (isWithinBounds(Point(newI, newJ), roof)
                        && roof[newI][newJ] != '#'
                        && roof[newI][newJ] != tofind
                        && !checked) {
                        count++;
                        checked = true;
                        cout << "Antinode would replace another antenna in " << newI << " " << newJ << endl;
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

void displayMatrix(vector<string> prison) {
    for (string row : prison) {
        cout << row << endl; // Each row of the matrix
    }

    usleep(50*1000);
    system("clear");
    cout << flush; // Ensure output is flushed (optional here)
}

void printMatrix(vector<string> roof) {
    for (int i = 0; i < roof.size(); i++) {
        cout << roof[i] << endl; // Each row of the matrix
    }
}

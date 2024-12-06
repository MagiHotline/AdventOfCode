#include <cmath>
#include <cstdio>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <unordered_set>
#include <vector>
#include <regex>
#include <iostream>
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

void displayMatrix(vector<string> prison);
bool isWithinBounds(Point, vector< string >);
enum direction {UP, DOWN, LEFT, RIGHT};

int main(int argc, char* argv[]) {

  if(argc != 2) {
        cout << "Usage: " << argv[0] << " <input_updates>" << endl;
        exit(1);
    }

    ifstream input(argv[1]);
    if(!input) {
        cout << "Error opening file" << endl;
        exit(1);
    }

    // get the matrix
    vector< string > prison;
    while(!input.eof()) {
        string line;
        getline(input, line);
        if(!line.empty())
            prison.push_back(line);
    }

    set< Point > points;

    // 1) Search where the guard is
    // 2) While we are in bounds of the matrix continue the algorithm
    // 3) Step forward and continue until the position over the guard is an obstacle.
    // 4) If the above position/cell is an obstacle,
    // 5) Create a set of points and everytime we step on a point we put it in the set.

    Point guard(0, 0);
    // Find point where the guard is
    for(int i = 0; i < prison.size(); i++) {
        for(int j = 0; j < prison[i].size(); j++) {
            if(prison[i][j] == '^') {
                guard.x = i;
                guard.y = j;
            }
            cout << prison[i][j];
        }
        cout << endl;
    }

    //int steps = 0;
    while(isWithinBounds(guard, prison)) {
        //displayMatrix(prison);
        // Add the point to the set
        points.insert(guard);
        // Check if the next position is an obstacle based on the direction the guard is facing
        switch(prison[guard.x][guard.y]) {
            case '^': {
                // If theres a block above, move right
                if(prison[guard.x-1][guard.y] == '#') {
                    prison[guard.x][guard.y] = '.';
                    prison[guard.x][guard.y+1] = '>';
                    guard.y++;
                } else {
                // Else just continue
                    prison[guard.x-1][guard.y] = '^';
                    prison[guard.x][guard.y] = '.';
                    guard.x--;
                }
                break;
            }
            case 'v': {
                if(prison[guard.x+1][guard.y] == '#') {
                    prison[guard.x][guard.y] = '.';
                    prison[guard.x][guard.y-1] = '<';
                    guard.y--;
                } else {
                    prison[guard.x+1][guard.y] = 'v';
                    prison[guard.x][guard.y] = '.';
                    guard.x++;
                }
                break;
            }
            case '<': {
                if(prison[guard.x][guard.y-1] == '#') {
                    prison[guard.x][guard.y] = '.';
                    prison[guard.x-1][guard.y] = '^';
                    guard.x--;
                } else {
                    prison[guard.x][guard.y-1] = '<';
                    prison[guard.x][guard.y] = '.';
                    guard.y--;
                }
                break;
            }
            case '>': {
                if(prison[guard.x][guard.y+1] == '#') {
                    prison[guard.x][guard.y] = '.';
                    prison[guard.x+1][guard.y] = 'v';
                    guard.x++;
                } else {
                    prison[guard.x][guard.y+1] = '>';
                    prison[guard.x][guard.y] = '.';
                    guard.y++;
                }
                break;
            }
        }
        //steps++;
    }

    cout << "Position of the guard: " << guard.x << " " << guard.y << endl;
    cout << "Solution: " << points.size() << endl;
    input.close();
    return 0;
}


// We pass the point and the matrix
bool isWithinBounds(Point p, vector< string > prison) {
    return p.x >= 0 && p.y >= 0 && p.x < prison.size() && p.y < prison[p.x].size();
}

void displayMatrix(vector<string> prison) {
    for (string row : prison) {
        cout << row << endl; // Each row of the matrix
    }
    cout << flush; // Ensure output is flushed (optional here)
}

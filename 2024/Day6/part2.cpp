#include <cstdio>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <iostream>
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

void displayMatrix(vector<string> prison);
bool isWithinBounds(Point, vector< string >);


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



    Point guard(0, 0);
    int xguard, yguard;
    int countCycles = 0;
    // Find point where the guard is
    for(int i = 0; i < prison.size(); i++) {
        for(int j = 0; j < prison[i].size(); j++) {
            if(prison[i][j] == '^') {
                xguard = guard.x = i;
                yguard = guard.y = j;
            }
        }
    }

    set< Point > points;
    unordered_map<string, set < Point > > check;

    while(isWithinBounds(guard, prison)) {
       // displayMatrix(prison);
        // Add the point to the set
        points.insert(guard);
        // Check if the next position is an obstacle based on the direction the guard is facing
        switch(prison[guard.x][guard.y]) {
            case '^': {
                if(!isWithinBounds(Point(guard.x-1, guard.y), prison)) {
                    prison[guard.x][guard.y] = '.';
                    guard.x--;
                    break;
                }
                if(prison[guard.x-1][guard.y] == '#') {
                    prison[guard.x][guard.y] = '>';
                } else {
                // Else just continue
                    prison[guard.x-1][guard.y] = '^';
                    prison[guard.x][guard.y] = '.';
                    guard.x--;
                }
                break;
            }
            case 'v': {
                if(!isWithinBounds(Point(guard.x+1, guard.y), prison)) {
                    prison[guard.x][guard.y] = '.';
                    guard.x++;
                    break;
                }
                if(prison[guard.x+1][guard.y] == '#') {
                    prison[guard.x][guard.y] = '<';
                } else {
                    prison[guard.x+1][guard.y] = 'v';
                    prison[guard.x][guard.y] = '.';
                    guard.x++;
                }
                break;
            }
            case '<': {
                if(!isWithinBounds(Point(guard.x, guard.y-1), prison)) {
                    prison[guard.x][guard.y] = '.';
                    guard.y--;
                    break;
                }
                if(prison[guard.x][guard.y-1] == '#') {
                    prison[guard.x][guard.y] = '^';
                } else {
                    prison[guard.x][guard.y-1] = '<';
                    prison[guard.x][guard.y] = '.';
                    guard.y--;
                }
                break;
            }
            case '>': {
                if(!isWithinBounds(Point(guard.x, guard.y+1), prison)) {
                    prison[guard.x][guard.y] = '.';
                    guard.y++;
                    break;
                }
                if(prison[guard.x][guard.y+1] == '#') {
                    prison[guard.x][guard.y] = 'v';
                } else {
                    prison[guard.x][guard.y+1] = '>';
                    prison[guard.x][guard.y] = '.';
                    guard.y++;
                }
                break;
            }
        }
    }

    int countSameSpot = 0;
    for (Point p : points) {
        // Place the obstacle
        prison[p.x][p.y] = '#';
        check.clear();          // Reset visited states
        set<string> visitedStates; // Track unique visited states for this trial

        // Reset the guard's position
        guard.x = xguard;
        guard.y = yguard;
        prison[xguard][yguard] = '^';

        bool validCycle = false; // Track if a valid cycle is found

        // Simulate guard movement
        while (isWithinBounds(guard, prison)) {
            // Create a unique state key
            string stateKey = to_string(guard.x) + "," + to_string(guard.y) + "," + prison[guard.x][guard.y];

            // Check if this state has been visited
            if (visitedStates.count(stateKey) > 0) {
                // If revisiting the same state, mark as a valid cycle
                validCycle = true;
                break;
            } else {
                visitedStates.insert(stateKey); // Mark state as visited
            }

            // Move the guard based on direction
            switch (prison[guard.x][guard.y]) {
                case '^': {
                    if (!isWithinBounds(Point(guard.x - 1, guard.y), prison)) break;
                    if (prison[guard.x - 1][guard.y] == '#') {
                        prison[guard.x][guard.y] = '>';
                    } else {
                        prison[guard.x - 1][guard.y] = '^';
                        prison[guard.x][guard.y] = '.';
                        guard.x--;
                    }
                    break;
                }
                case 'v': {
                    if (!isWithinBounds(Point(guard.x + 1, guard.y), prison)) break;
                    if (prison[guard.x + 1][guard.y] == '#') {
                        prison[guard.x][guard.y] = '<';
                    } else {
                        prison[guard.x + 1][guard.y] = 'v';
                        prison[guard.x][guard.y] = '.';
                        guard.x++;
                    }
                    break;
                }
                case '<': {
                    if (!isWithinBounds(Point(guard.x, guard.y - 1), prison)) break;
                    if (prison[guard.x][guard.y - 1] == '#') {
                        prison[guard.x][guard.y] = '^';
                    } else {
                        prison[guard.x][guard.y - 1] = '<';
                        prison[guard.x][guard.y] = '.';
                        guard.y--;
                    }
                    break;
                }
                case '>': {
                    if (!isWithinBounds(Point(guard.x, guard.y + 1), prison)) break;
                    if (prison[guard.x][guard.y + 1] == '#') {
                        prison[guard.x][guard.y] = 'v';
                    } else {
                        prison[guard.x][guard.y + 1] = '>';
                        prison[guard.x][guard.y] = '.';
                        guard.y++;
                    }
                    break;
                }
            }
        }

        // Increment cycle count if a valid cycle was detected
        if (validCycle) {
            countCycles++;
        }

        // Reset the obstacle for the next trial
        prison[p.x][p.y] = '.';
    }

    check.clear();
    points.clear();

    //cout << "Position of the guard: " << guard.x << " " << guard.y << endl;
    cout << "Solution: " << countCycles << endl;
    input.clear();
    input.close();
    return 0;
}


// We pass the point and the matrix
bool isWithinBounds(Point p, vector< string > prison) {
    return p.x >= 0 && p.y >= 0 && p.x < prison.size() && p.y < prison[p.x].size();
}

void displayMatrix(vector<string> prison) {
    for(int i = 0; i < prison.size(); i++) {
        cout << prison[i] << endl; // Each row of the matrix
    }

    usleep(50*1000);
    system("clear");
    cout << flush; // Ensure output is flushed (optional here)
}

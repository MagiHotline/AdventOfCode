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

    unordered_map<char, set < Point > > check;

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
    }


    for(Point p : points) {
        // SET THE PRISON FOR THE TRYOUT
        prison[p.x][p.y] = '#'; // SET THE OBSTACLE
        check.clear(); // Clear the map
        int countSameSpot = 0; // Reset the counter for same spot
        prison[guard.x][guard.y] = '.'; // remove the guard beofre from the prison
        // Reset the guard position
        guard.x = xguard;
        guard.y = yguard;
        prison[xguard][yguard] = '^'; // Reset the guard in the matrix
            // ALGORITMO
            while(isWithinBounds(guard, prison)) {
            //displayMatrix(prison);
            // Detect if the guard is stuck
                bool canMove = false;
                if (isWithinBounds(Point(guard.x - 1, guard.y), prison) && prison[guard.x - 1][guard.y] != '#') canMove = true;
                if (isWithinBounds(Point(guard.x + 1, guard.y), prison) && prison[guard.x + 1][guard.y] != '#') canMove = true;
                if (isWithinBounds(Point(guard.x, guard.y - 1), prison) && prison[guard.x][guard.y - 1] != '#') canMove = true;
                if (isWithinBounds(Point(guard.x, guard.y + 1), prison) && prison[guard.x][guard.y + 1] != '#') canMove = true;

                if (!canMove) {
                    //cout << "Guard is stuck" << endl;
                    // When it ends, remove the guard from the prison
                    prison[guard.x][guard.y] = '.';
                    countCycles++; // Increment the cycles
                    prison[p.x][p.y] = '.'; // Reset the obstacle
                    break;
                }
                if(check[prison[guard.x][guard.y]].find(guard) != check[prison[guard.x][guard.y]].end()) {
                    countSameSpot++;
                }

                // Insert the new point in the set of the associated directions
                check[prison[guard.x][guard.y]].insert(guard);

                // If I stepped in the same spot two times facing the same direction
                // then its a cycles
                if(countSameSpot > 1) {
                    //cout << "Cycle detected" << endl;
                    // When it ends, remove the guard from the prison
                    prison[guard.x][guard.y] = '.';
                    countCycles++; // Increment the cycles
                    prison[p.x][p.y] = '.'; // Reset the obstacle
                    break;
                }

                // Check the next position: if it's an obstacle, turn 90 degrees to the right
                switch(prison[guard.x][guard.y]) {
                    case '^': {
                        // If theres a block above, move right
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
                //cout << guard.x << " " << guard.y << endl;
            }
            // Reset the obstacle position after the cycle
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

    usleep(0*1000);
    system("clear");
    cout << flush; // Ensure output is flushed (optional here)
}

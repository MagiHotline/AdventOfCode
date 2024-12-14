#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <vector>
#include <fstream>
#include <set>
#include <map>

using namespace std;

// A Point is a pair of integers
struct Point {
    int x, y;

    // Constructor
    Point(int x, int y) : x(x), y(y) {}

    // Comparison operator for use in std::set
    bool operator<(const Point& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

// A Plot is a block who has a point and a number of sides
class Plot {
    public:
        Point p;
        int sides;
        Plot(int x, int y) : p(x, y), sides(4) {}

        bool operator<(const Plot& other) const {
                return p < other.p; // Define the ordering based on the point
        }
};

// A Region is a set of plots of the same character
class Region {
    public:
        char character;
        set < Plot > plots;
        int perimeter;
        int area;
        Region(char character) {
            this->character = character;
            this->perimeter = 4;
            this->area = 1;
        }
};

// We pass the point and the matrix
bool isWithinBounds(Point p, vector< string > map) {
    return p.x >= 0 && p.y >= 0 && p.x < map.size() && p.y < map[p.x].size();
}

// Trying to find all the areas recursively given a starting point and a character
// And we try to return a region
Region findRegion(Point p, vector < string > map, Region region, char character) {
    // If the point is not within bounds or the character is not the same as the one we are looking for
    if(!isWithinBounds(p, map) || map[p.x][p.y] != character) {
        return region;
    }

    // If the plot is already in the region
    if(region.plots.find(Plot(p.x, p.y)) != region.plots.end()) {
        return region;
    }

    // Add the plot to the region
    region.plots.insert(Plot(p.x, p.y));
    region.area++;

    // Check the 4 sides of the point
    Point left(p.x, p.y - 1);
    Point right(p.x, p.y + 1);
    Point up(p.x - 1, p.y);
    Point down(p.x + 1, p.y);

    // If the point is on the border, we decrease the perimeter
    // We gotta check for every path if it is within bounds

    // Recursively check the 4 sides
    if(isWithinBounds(left, map))
        region = findRegion(left, map, region, character);

    if(isWithinBounds(right, map))
        region = findRegion(right, map, region, character);

    if(isWithinBounds(up, map))
        region = findRegion(up, map, region, character);

    if(isWithinBounds(down, map))
        region = findRegion(down, map, region, character);

    return region;
}

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

    string line;
    vector < string > map;
    // Get the map
    while(getline(input, line)) {
        map.push_back(line);
    }

    for(string s : map) {
        cout << s << endl;
    }

    vector < Region > regions;

    for(int i = 0; i < map.size(); i++) {
        for(int j = 0; j < map[i].size(); j++) {
            bool found = false;
            // Check if the plot is already in a region
            for(Region& r : regions) {
                if(r.plots.find(Plot(i, j)) != r.plots.end()) {
                    found = true;
                    break;
                }
            }
            // If the plot is already in a region, we skip it
            if(found) {
                continue;
            }

            // Otherwise we find the region
            Region region = findRegion(Point(i, j), map, Region(map[i][j]), map[i][j]);
            regions.push_back(region);
        }
    }

    int prices = 0;
    for(Region r : regions) {
        prices += (r.area * r.perimeter);
    }

    cout << prices << endl;


}

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char **argv) {

    // get the file input
    ifstream input("input.txt");
    if(!input) {
        cout << "Error opening file" << endl;
        exit(1);
    }

    // declare the two vectors to store the values
    vector<int> a;
    vector<int> b;
    while(!input.eof()) {
        int x, y;
        input >> x >> y;
        a.push_back(x);
        b.push_back(y);
    }

    for(int i = 0; i < a.size(); i++) {
        cout << a[i] << "   " << b[i] << endl;
    }

    // close the file
    input.close();

    return 0;
}

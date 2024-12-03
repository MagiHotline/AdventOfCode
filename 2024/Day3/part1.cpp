#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>
#include <iostream>
using namespace std;

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

    // Checks for puttern
    regex pattern("mul\\(([0-9]{1,3}),([0-9]{1,3})\\)");


    string line;
    int counter = 0;
    int a; int b;
    while(getline(input, line)) {
        smatch m;
        regex_search(line, m, pattern);
        auto start = line.cbegin();
        auto end = line.cend();
        while(regex_search(start, end, m, pattern)) {
            a = stoi(m[1]);
            b = stoi(m[2]);
            counter += a*b;
            cout << m[0] << " " << m[1] << " " << m[2] << endl;
            start += (m.length(0) + m.position(0));
        }
    }




    cout << "Counter: " << counter << endl;



    //cout << "Counter: " << counter << endl;


}

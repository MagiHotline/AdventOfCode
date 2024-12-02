#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <string>

using namespace std;

// Swaps two elements
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int solve(vector<int>, vector<int>);

int main(int argc, char **argv) {

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
    // declare the two vectors to store the values
    vector<int> a;
    vector<int> b;
    while(1) {
        int x, y;
        input >> x >> y;
        if(!input.eof()) {
            a.push_back(x);
            b.push_back(y);
        } else {
            break;
        }
    }

    for(int i = 0; i < a.size(); i++) {
        cout << a[i] << "   " << b[i] << endl;
    }
    int result = solve(a, b);

    cout << "The total distance is: " << result << endl;

    // close the file
    input.close();

    return 0;
}

int solve(vector<int> a, vector<int> b) {

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    printf("Sorted list: \n");
    for(int i = 0; i < a.size(); i++) {
        cout << a[i] << "   " << b[i] << endl;
    }
    // declare the result variable
    int result = 0;
    for(int i = 0; i < a.size(); i++) {
        result += abs((b[i] - a[i]));
        cout << "Distance: " <<  abs((b[i] - a[i])) << endl;
    }
    return result;
}

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
    regex enable("((do\\(\\))(.*?\\s*?)(don't\\(\\)))");
    string line;
    int counter = 0;
    int a; int b;
    bool isMulActive;
    string cumLine = "";
    while(getline(input, line)) {
        cumLine += line;
    }

    smatch matchValues;
    smatch matchEnable;
    smatch m;
    cumLine = "do()" + cumLine + "don't()";
    auto startLine = cumLine.cbegin();
    auto endLine = cumLine.cend();
    while(regex_search(startLine, endLine, matchEnable, enable)) {
        string stringtobeMatched = matchEnable.str(3);
        cout << "String to be matched: " << stringtobeMatched << endl;
        auto startText = stringtobeMatched.cbegin();
        auto endText = stringtobeMatched.cend();
        while(regex_search(startText, endText, matchValues, pattern)) {
            a = stoi(matchValues[1]);
            b = stoi(matchValues[2]);
            counter += a*b;
            cout << matchValues[0] << " " << matchValues[1] << " " << matchValues[2] << endl;
            startText += (matchValues.length(0) + matchValues.position(0));
        }

        startLine += (matchEnable.length(0) + matchEnable.position(0));
    }

    cout << "Soluzione: " << counter << endl;
    //cout << "Counter: " << counter << endl;
}

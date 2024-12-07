#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

long long evaluate(const string&);
bool calibrate(const vector<long long>&, size_t, const string&, long long);
long long concatenate(long long, long long);

int main(int argc, char* argv[]) {
    if(argc != 2) {
        cout << "Usage : " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream inputFile(argv[1]);

    string line;
    long long totalCalibrationResult = 0;

    // Parsing of the file
    while (getline(inputFile, line)) {
        size_t colonPos = line.find(':');

        // Take the target value and the numbers
        long long target = stoll(line.substr(0, colonPos)); // String to long long
        string valuesPart = line.substr(colonPos + 1);

        istringstream iss(valuesPart);
        vector<long long> numbers;
        long long num;
        while (iss >> num) {
            numbers.push_back(num);
        }

        if (calibrate(numbers, 1, to_string(numbers[0]), target)) {
            // match found
            totalCalibrationResult += target;
        }
    }

    cout << totalCalibrationResult << endl;

    return 0;
}
// Backtracking function to generate all possible expressions and check against the target
/*
numbers: the list of numbers to use
index: the current index in the numbers list
currentExpression: the current expression being built
target: the target value to match
*/
bool calibrate(const vector<long long>& numbers, size_t index, const string& currentExpression, long long target) {
    // If the index reaches the numbers size, evaluate the expression
    if (index == numbers.size()) {
        //cout << target << " = " << currentExpression << endl;
        long long value = evaluate(currentExpression);
        // Return true if the expression evaluates to the target
        return value == target;
    }

    // Generates further recursive calls and may return true or false.
    // The OR operator is used to short-circuit the evaluation if a match is found.
    // The only way that the backtrack functions returns false is that all three options return false.
    return calibrate(numbers, index + 1, currentExpression + "+" + to_string(numbers[index]), target)
    | calibrate(numbers, index + 1, currentExpression + "*" + to_string(numbers[index]), target)
    | calibrate(numbers, index + 1, currentExpression + "|" + to_string(numbers[index]), target);
}

// Concatenate function
long long concatenate(long long a, long long b) {
    string s = to_string(a) + to_string(b);
    return stoll(s);
}

// Function to evaluate an expression left-to-right, ignoring operator precedence
long long evaluate(const string& expression) {
    istringstream iss(expression);
    long long result, num;
    char op;

    iss >> result;
    while (iss >> op >> num) {
        if (op == '+') {
            result += num;
        } else if (op == '*') {
            result *= num;
        } else if(op == '|') {
            result = concatenate(result, num);
        }
    }

    return result;
}

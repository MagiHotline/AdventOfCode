#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;
long long concatenate(long long a, long long b) {
    string s = to_string(a) + to_string(b);
    return stoll(s);
}
// Function to evaluate an expression left-to-right
long long eval(const string& expression) {
    istringstream iss(expression);

    long long result, num;
    char op;

    iss >> result;
    while (iss >> op) {
        if (op == '|') {
            char next;
            iss >> next;
            if (next == '|') {
                iss >> num;
                result = concatenate(result, num);
            }
        } else {
            iss >> num;
            if (op == '+') {
                result += num;
            } else if (op == '*') {
                result *= num;
            }
        }
    }

    return result;
}

// Backtracking function to generate all possible expressions and check against the target
bool calibrate(const vector<long long>& numbers, size_t index, const string& currentExpression, long long target) {
    if (index == numbers.size()) {
        long long value = eval(currentExpression);
        return value == target;
    }

    return calibrate(numbers, index + 1, currentExpression + "+" + to_string(numbers[index]), target)
    | calibrate(numbers, index + 1, currentExpression + "*" + to_string(numbers[index]), target)
    | calibrate(numbers, index + 1, currentExpression + "||" + to_string(numbers[index]), target);
}

int main() {
    ifstream inputFile("input.txt");

    string line;
    long long totalCalibrationResult = 0;

    while (getline(inputFile, line)) {
        size_t colonPos = line.find(':');

        long long target = stoll(line.substr(0, colonPos));
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

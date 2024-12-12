#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <set>
#include <unordered_map>
#include <unistd.h>
#include <functional>

using namespace std;

typedef unsigned long long ull;

ull applyRuleOne(ull);
void applyRuleTwo(ull, ull&, ull&);
ull applyRuleThree(ull);

ull applyRuleOne(ull stone) {
    return stone + 1;
}

ull applyRuleThree(ull stone) {
    return stone * 2024;
}

int countDigit(ull stone) {
    if(stone < 10) {
        return 1;
    } else {
        return 1 + countDigit(stone/10);
    }
}

void applyRuleTwo(ull stone, ull &left, ull &right) {
    int digits = countDigit(stone);
    int half = digits/2;

    left = stone / pow(10, half);
    right = stone % (ull)pow(10, half);
}

unordered_map<ull, ull> blink(unordered_map<ull, ull> stones) {
    unordered_map<ull, ull> newStones;
    for (auto stone : stones) {
        ull stoneValue = stone.first;
        ull stoneCount = stone.second;

        if (stoneValue == 0) {
            ull newValue = applyRuleOne(stoneValue);
            if (newStones.find(newValue) != newStones.end()) {
                newStones[newValue] += stoneCount; // Increment the count
            } else {
                newStones[newValue] = stoneCount; // Insert with initial count
            }
        } else if (countDigit(stoneValue) % 2 == 0) {
            ull left, right;
            applyRuleTwo(stoneValue, left, right);

            if (newStones.find(left) != newStones.end()) {
                newStones[left] += stoneCount; // Increment the count for left
            } else {
                newStones[left] = stoneCount; // Insert left with initial count
            }

            if (newStones.find(right) != newStones.end()) {
                newStones[right] += stoneCount; // Increment the count for right
            } else {
                newStones[right] = stoneCount; // Insert right with initial count
            }
        } else {
            ull newValue = applyRuleThree(stoneValue);
            if (newStones.find(newValue) != newStones.end()) {
                newStones[newValue] += stoneCount; // Increment the count
            } else {
                newStones[newValue] = stoneCount; // Insert with initial count
            }
        }
    }

    return newStones;
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

    // Take the stones
    unordered_map< ull, ull > stones;

    string line;
    getline(input, line);
    istringstream iss(line);
    ull value;
    while(iss >> value) {
        stones[value] = 1;
    }

    ull sumUp = 0;
    // Modify the map at every link
    for(int blinks = 1; blinks <= 75; blinks++) {
        stones = blink(stones);
        cout << "Blinks: " <<  blinks << "/75" << endl;
    }

    for(auto stone : stones) {
        sumUp += stone.second;
    }

    cout << "Soluzione: " << sumUp << endl;

    input.close();
}

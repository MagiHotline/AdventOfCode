#include <cstddef>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <vector>
#include <fstream>
#include <string>
#include <set>
#include <unordered_map>
#include <unistd.h>

using namespace std;

typedef unsigned long long ull;

ull applyRuleOne(ull);
void applyRuleTwo(ull, ull&, ull&);
ull applyRuleThree(ull);

ull applyRuleOne(ull stone) {
    return stone + 1;
}

void applyRuleTwo(ull stone, ull &left, ull &right) {
    string stringStone = to_string(stone);

    string stringLeft = stringStone.substr(0, stringStone.length()/2);
    string stringRight = stringStone.substr(stringStone.length()/2, stringStone.length());

    left = stoull(stringLeft);
    right = stoull(stringRight);
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

    vector < size_t > stones;

    string line;
    getline(input, line);
    istringstream iss(line);
    ull value;
    while(iss >> value) {
        stones.push_back(value);
    }

    for(int blinks = 25; blinks > 0; blinks--) {
        for(int i = 0; i < stones.size(); i++) {
            if(stones[i] == 0) {
                stones[i] = applyRuleOne(stones[i]);
            } else if(countDigit(stones[i]) % 2 == 0) {
                ull left, right;
                applyRuleTwo(stones[i], left, right);
                stones.erase(stones.begin()+i);
                stones.insert(stones.begin()+i, left);
                stones.insert(stones.begin()+i+1, right);
                i++;
            } else {
                stones[i] = applyRuleThree(stones[i]);
            }
        }

        for(ull stone : stones) cout << stone << " ";
        system("clear");
        cout << flush;
    }


    cout << "Solution: " << stones.size() << endl;
    input.close();
}

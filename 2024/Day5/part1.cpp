#include <cmath>
#include <cstdio>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <vector>
#include <regex>
#include <iostream>
using namespace std;
typedef struct Rule {
    int prec;
    int succ;
}rule;

int returnMiddleValueinUpdate(vector<int>);
bool isWellCorrected(vector<rule>, vector<int>);

int main(int argc, char* argv[]) {

  if(argc != 3) {
        cout << "Usage: " << argv[0] << " <input_rules> <input_updates>" << endl;
        exit(1);
    }

    // get the files
    FILE *inputRules = fopen(argv[1], "r");
    ifstream inputUpdates(argv[2]);
    if(!inputRules || !inputUpdates) {
        cout << "Error opening file" << endl;
        exit(1);
    }

    // get the rules
    vector<rule> rules;
    while(!feof(inputRules))
    {
        rule r;
        fscanf(inputRules, "%d|%d\n", &r.prec, &r.succ);
        rules.push_back(r);
    }

    // get the updates
    vector< vector<int> > updates;
    while(!inputUpdates.eof()) {
        vector<int> update;
        int value;
        while(inputUpdates >> value) {
            update.push_back(value);
            if(inputUpdates.get() == '\n') break;
        }

        if(!update.empty()) updates.push_back(update);
    }

    int sol = 0;

    for(int i = 0; i < updates.size(); i++) {
        if(isWellCorrected(rules, updates[i]))
            sol += returnMiddleValueinUpdate(updates[i]);
    }


    cout << "Soluzione: " << sol << endl;

    fclose(inputRules);
    inputUpdates.close();
    return 0;
}

int returnMiddleValueinUpdate(vector<int> arr) {
    return arr[arr.size()/2];
}

// Checls for every update[i] in r.succ and check for the update
bool isWellCorrected(vector<rule> rules, vector<int> update) {
    unordered_set<int> check;
    // Insert the element in the set to check if it is present
    for(int i = 0; i < update.size(); i++) check.insert(update[i]);

    for(int i = 0; i < update.size(); i++) {
        // Check if we find something like this -> x|update[i]
        for(int j = 0; j < rules.size(); j++) {
            if(rules[j].succ == update[i]) {
                // If it find something x|update[i] in the rules
                if(check.find(rules[j].prec) != check.end()) {
                    bool found = false;
                    for(int k = 0; k < i && !found; k++) {
                        if(update[k] == rules[j].prec) {
                            found = true;
                        }
                    }
                    // If it doesn't find the prec in the sub range of the update
                    // then return false
                    if(!found) return false;
                }
            }
        }
    }

    return true;
}

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
int fixUpdate(vector<rule>, vector<int>);
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(int argc, char* argv[]) {

  if(argc != 3) {
        cout << "Usage: " << argv[0] << " <input_rules> <input_updates>" << endl;
        exit(1);
    }

    // Get the files
    FILE *inputRules = fopen(argv[1], "r");
    ifstream inputUpdates(argv[2]);
    if(!inputRules || !inputUpdates) {
        cout << "Error opening file" << endl;
        exit(1);
    }

    // GEt the rules
    vector<rule> rules;
    while(!feof(inputRules))
    {
        rule r;
        fscanf(inputRules, "%d|%d\n", &r.prec, &r.succ);
        rules.push_back(r);
    }

    // Get the updates
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
        // Take the incorrected updates...
        if(!isWellCorrected(rules, updates[i])) {
            // And fix them!
            sol += fixUpdate(rules, updates[i]);
        }
    }

    cout << "Soluzione: " << sol << endl;

    fclose(inputRules);
    inputUpdates.close();
    return 0;
}

// Function that returns the middle value of the vector
int returnMiddleValueinUpdate(vector<int> arr) {
    return arr[arr.size()/2];
}

// Function that fixes the update based on the rules
int fixUpdate(vector<rule> rules, vector<int> update) {
    vector<int> fixedUpdate;
    int savePos = 0;
    unordered_set<int> check;
    // Insert the element in the set to check if it is present
    for(int i = 0; i < update.size(); i++) check.insert(update[i]);
    bool swapped;

    while(!isWellCorrected(rules, update)) {
        for(int i = 0; i < update.size(); i++) {
            swapped = false;
            // Check if there are rules like x|update[i]
            for(int j = 0; j < rules.size(); j++) {
                if(rules[j].succ == update[i]) {
                    // CHECK FOR EVERY RULE WHERE UPDATE[I] APPEARS AS A SUCC, AND SEARCH PREC INTO THE UPDATE
                    if(check.find(rules[j].prec) != check.end()) {
                        for(int k = i+1; k < update.size() && !swapped; k++) {
                            // IF THE ELEMENT THAT SHOULD BE BEFORE IS AFTER, THEN I SWAP
                            if(update[k] == rules[j].prec) {
                                swap(update[i], update[k]);
                                swapped = true;
                            }
                        }
                    }
                }
            }
        }
    }

    // Return the middle value of the fixed update
    return returnMiddleValueinUpdate(update);
}

// Checls for every update[i] in r.succ and check for the update]
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

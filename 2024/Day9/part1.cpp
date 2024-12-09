#include <cstddef>
#include <cstdio>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <set>
#include <unordered_map>
#include <unistd.h>

using namespace std;

typedef struct File {
    long long id;
    long long size;
    long long freespace;
}File;

void displayFiles(vector< File > files);
string fileToString(vector < File > files);
bool isFinished(string compactDisk);
string defrag(string memory);

// Returns the index of the first file with free space
int getFirstFileWithFreeSpace(vector < File > files) {
    for(int i = 0; i < files.size(); i++) {
        // return the file with the first free space
        if(files[i].freespace > 0) {
            return i;
        }
    }
    return 0;
}

// Returns the index of the last file with free space
int getLastFileWithFreeSpace (vector < File > files) {
    for(int i = files.size()-1; i >= 0; i--) {
        // return the file with the first free space
        if(files[i].freespace > 0) {
            return i;
        }
    }

    return 0;
}

long long checksum(vector < File > files) {
    long long checksum = 0;
    long long counter = 0;
    for(long long i = 0; i < files.size(); i++) {
        for(long long j = 0; j < files[i].size; j++) {
            checksum += files[i].id * counter;
            //cout << "\n"<< files[i].id << " * " << counter << " = " << checksum << endl;
            counter++;
        }
    }

    return checksum;
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

    // get the matrix
    vector< File > files;
    string line;
    getline(input, line);

    // For every 2 digit numbers push it as the size and freespace of the file
    // in the vector

    long long id = 0;
    for(int i = 0; i <= line.size(); i+=2) {
        File f;
        f.id = id++;
        f.size = line[i] - '0';
        f.freespace = line[i+1] - '0';
        if(f.freespace < 0) {
            f.freespace = 0;
        }

        files.push_back(f);
    }

    displayFiles(files);

    // [0,1,2] [1,3,4] [2,5,0]
    //     ->[2,2,0]
    // [0,1,0] [2,2,0] [2,3,2]

    //File firstFile = getFirstFileWithFreeSpace(files);
    //File lastFile = getLastFileWithFreeSpace(files);
    bool valid = false;

    // [0,1,2]j [1,3,4] [2,5,0]i ->
    // -> 1) Viene creato un nuovo file -> [2,0,2]x
    // -> 2) Se [0,1,2] (2) > 0 && [2,5,0] (5) > 0 allora continua il loop
    // -> 3) -> Si entra nel loop
    //         -> [2,4,1]i -> [0,1,1]j -> [2,1,1]x si rientra nel loop
    //         -> [2,3,2]i -> [0,1,0]j -> [2,2,0] si esce dal loop poiché j.freespace == 0
    //        [0,1,0] [2,2,0] [1,3,4] [2,3,2]
    //        022111....222..
    // [0,1,2] [1,3,4] [2,5,0]

    // Takes the index of the file that has to be compacted
    int fileToGetOrdered = files.size()-1;
    // Takes the index of the first file with free space
    int firstEmptyFile = getFirstFileWithFreeSpace(files);
    do {
        while(files[fileToGetOrdered].size > 0) {
            valid = false;
            File newFile;
            newFile.id = files[fileToGetOrdered].id;
            newFile.size = 0;
            newFile.freespace = files[firstEmptyFile].freespace;

            while(files[firstEmptyFile].freespace > 0 && files[fileToGetOrdered].size > 0) {
                    files[fileToGetOrdered].freespace++;
                    files[fileToGetOrdered].size--;
                    files[firstEmptyFile].freespace--;

                    newFile.size++;
                    newFile.freespace--;
                    valid = true;
            }

            while(files[firstEmptyFile].freespace > 0) {
                files[firstEmptyFile].freespace--;
            }

            if(valid == true) {
                files.insert(files.begin()+firstEmptyFile+1, newFile);
                firstEmptyFile = getFirstFileWithFreeSpace(files);
                fileToGetOrdered = getLastFileWithFreeSpace(files);
            }

            //displayFiles(files);
        }
        fileToGetOrdered--;
    } while(fileToGetOrdered > firstEmptyFile);

    cout << "Checksum: " << checksum(files) << endl;

}

void displayFiles(vector< File > files) {
    for(File f : files) {
        for(int i = 0; i < f.size; i++) {
            cout << f.id;
        }

        for(int i = 0; i < f.freespace; i++) {
            cout << '.';
        }
    }
    cout << endl;
}

string fileToString(vector < File > files) {
    string s = "";
    for(int i = 0; i < files.size(); i++) {
        for(int j = 0; j < files[i].size; j++) {
            s += to_string(i);
        }

        for(int j = 0; j < files[i].freespace; j++) {
            s += ".";
        }
    }

    return s;
}

bool isFinished(string compactDisk) {
    for(int i = 0; i < compactDisk.size(); i++) {
        if(compactDisk[i+1] == '.') {
            for(int j = i+1; j < compactDisk.size(); j++) {
                if(compactDisk[j] != '.') {
                    return false;
                }
            }
        }
    }

    return true;
}

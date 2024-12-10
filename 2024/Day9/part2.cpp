#include <cstddef>
#include <cstdio>
#include <iostream>
#include <ratio>
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
void displayFilesNormally(vector < File > files);
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

// Returns the index of the first file with free space
int getFirstFileWithFreeSpace(vector < File > files, int offset) {
    for(int i = offset+1; i < files.size(); i++) {
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

// Returns the index of the last file with free space
int getLastFileWithFreeSpace (vector < File > files, int offset) {
    for(int i = files.size()-1-offset; i >= 0; i--) {
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
            cout << "\n"<< files[i].id << " * " << counter << " = " << checksum << endl;
            counter++;
        }

        if(files[i].freespace > 0) {
            counter += files[i].freespace;
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

    displayFilesNormally(files);
    //Takes the index of the file that has to be compacted
    int fileToGetOrdered = files.size()-1;
    bool inserted;
    // Takes the index of the first file with free space
    int firstEmptyFile = getFirstFileWithFreeSpace(files);
    do {
        //inserted = false;
        while(files[fileToGetOrdered].size > 0) {
            // If size is greater than freespace than move to the next first empty space
            if(files[fileToGetOrdered].size > files[firstEmptyFile].freespace) {
                if(firstEmptyFile >= fileToGetOrdered) {
                    // If I have tried every single combination
                    firstEmptyFile = getFirstFileWithFreeSpace(files);
                    //inserted = false;
                    break;
                }
                firstEmptyFile = getFirstFileWithFreeSpace(files, firstEmptyFile);
                //inserted = false;
                //[2,5,0](idx=2) >= [0,1,2](idx=0) ->  5>=2 FEF=0 -> search from 0+1
                //[2,5,0] >= [1,3,4]->  5>=4
                // so if the size of the file I wanna insert is bigger, go to the next empty file
            } else {
                // instead if theres enough space in the empty file, insert the file
                File newFile;
                newFile.id = files[fileToGetOrdered].id;
                newFile.size = files[fileToGetOrdered].size;
                newFile.freespace = files[firstEmptyFile].freespace - files[fileToGetOrdered].size;

                // Move the file to the first empty file
                files[firstEmptyFile].freespace = 0; // Set the file where im putting the file as 0
                files[fileToGetOrdered].freespace = files[fileToGetOrdered].size + files[fileToGetOrdered].freespace; // The freespace becomes the size
                files[fileToGetOrdered].size = 0; // The size then is set to 0

                files.insert(files.begin()+firstEmptyFile+1, newFile);
                //inserted = true;
                firstEmptyFile = getFirstFileWithFreeSpace(files);
                fileToGetOrdered = getLastFileWithFreeSpace(files, 1);
            }
            //displayFiles(files);
            displayFilesNormally(files);
        }
        fileToGetOrdered--;
    } while(fileToGetOrdered > firstEmptyFile);

    cout << "Checksum: " << checksum(files) << endl;

}

void displayFiles(vector< File > files) {
    for(File f : files) {
        for(int i = 0; i < f.size; i++) {
            cout << "⬜";
        }

        for(int i = 0; i < f.freespace; i++) {
            cout << " ";
        }
    }
    cout << endl;
    usleep(50*1000);
    system("clear");
    cout << flush;
}

void displayFilesNormally(vector< File > files) {
    for(File f : files) {
        for(int i = 0; i < f.size; i++) {
            cout << f.id;
        }

        for(int i = 0; i < f.freespace; i++) {
            cout << ".";
        }
    }
    cout << endl;
}

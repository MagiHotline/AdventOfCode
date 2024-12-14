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

void showFiles(vector < File > files) {
    for(File f : files) {
        cout << "[" << f.id << " " << f.size << " " << f.freespace <<  "] ";
    }
}


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
            //cout << "\n"<< files[i].id << " * " << counter << " = " << checksum << endl;
            counter++;
        }

        if(files[i].freespace > 0) {
            counter += files[i].freespace;
        }
    }

    return checksum;
}

int main(int argc, char* argv[]) {

//1111111111111111 -> 106
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
    //
    for(int i = 0; i < line.size(); i+=2) {
        File f;
        f.id = id++;
        f.size = line[i] - '0';
        f.freespace = line[i+1] - '0';
        if(f.freespace < 0) {
            f.freespace = 0;
        }

        files.push_back(f);
    }

    showFiles(files);
    displayFilesNormally(files);
    //Takes the index of the file that has to be compacted
    int fileToGetOrdered = files.size()-1;
    //vector <File> currentOrder = files;
    // Takes the index of the first file with free space
    bool hasFound = false;
    int firstEmptyFile = getFirstFileWithFreeSpace(files);
    do {
        while (files[fileToGetOrdered].size > 0 || firstEmptyFile == fileToGetOrdered-1) {
            // If size is greater than freespace, move to the next first empty space
            if (files[fileToGetOrdered].size > files[firstEmptyFile].freespace) {
                if (firstEmptyFile >= fileToGetOrdered) {
                    // If I have tried every single combination
                    firstEmptyFile = getFirstFileWithFreeSpace(files);
                    break;
                }

                if(firstEmptyFile == fileToGetOrdered-1) {
                    // If I have tried every single combination
                    firstEmptyFile = getFirstFileWithFreeSpace(files);
                    fileToGetOrdered--;
                    break;
                } else {
                    firstEmptyFile = getFirstFileWithFreeSpace(files, firstEmptyFile);
                }
            } else {
                // If there is enough space in the empty file, insert the file
                File newFile;
                newFile.id = files[fileToGetOrdered].id; //
                newFile.size = files[fileToGetOrdered].size; //
                newFile.freespace = files[firstEmptyFile].freespace - files[fileToGetOrdered].size;
                // The previous should get the freespace and size of the file that is being moved
                files[fileToGetOrdered-1].freespace += files[fileToGetOrdered].freespace + files[fileToGetOrdered].size;
                // Move the file to the first empty file
                files[firstEmptyFile].freespace = 0; // Set the file where I'm putting the file as 0

                files.erase(files.begin()+fileToGetOrdered); // Its not sure if the files that has to be removed is the last

                files.insert(files.begin() + firstEmptyFile + 1, newFile); // Insert the file in the first empty file
                // Update the file indices and stop processing the current fileToGetOrdered
                firstEmptyFile = getFirstFileWithFreeSpace(files);
                break; // Exit the while loop to process the next fileToGetOrdered
            }
        }
        showFiles(files);
        displayFilesNormally(files);
        cout << files[fileToGetOrdered].id << " " << files[firstEmptyFile].id << endl;
        // Controllare il termine della funzione
    } while (getFirstFileWithFreeSpace(files) != getLastFileWithFreeSpace(files) && fileToGetOrdered != firstEmptyFile);
    cout << "Checksum: " << checksum(files) << endl;

}

void displayFiles(vector< File > files) {
    for(File f : files) {
        for(int i = 0; i < f.size; i++) {
            cout << "█";
        }

        for(int i = 0; i < f.freespace; i++) {
            cout << " ";
        }
    }
    cout << endl;
    usleep(3*1000);
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

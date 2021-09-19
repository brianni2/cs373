#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

const int SIZE = 1001;

struct states {
    vector<char> input;
    vector<int> moveState;
};

int main(int argc, char* argv[]) {
    string fileName = argv[1];
    string strInput = argv[2];
    states automata[SIZE];
    string readState;
    int numState;
    string specState;
    char readInput;
    int readMoveState;
    
    int startState;
    vector<int> acceptState;
    
    ifstream inFS;
    inFS.open(fileName);
    
    inFS >> readState;
    inFS >> numState;
    while(!inFS.fail()) {
        if(readState.find("state") != string::npos) {
            getline(inFS, specState);
            if(specState.find("start") != string::npos) {
                startState = numState;
            }
            if(specState.find("accept") != string::npos) {
                acceptState.push_back(numState);
                //cout << acceptState.at(acceptState.size() - 1);
            }
        }
        if(readState.find("transition") != string::npos) {
            inFS >> readInput;
            inFS >> readMoveState;
            automata[numState].input.push_back(readInput);
            automata[numState].moveState.push_back(readMoveState);
        }
        inFS >> readState;
        inFS >> numState;
    }
    inFS.close();
    
    int currState = startState;
    vector<int> acceptInput;
    vector<int> rejectInput;
    
    for(int z = 0; z < strInput.length(); z++) {
        for(int i = 0; i < automata[currState].input.size(); i++) {
            if(automata[currState].input.at(i) == strInput[z]) {
                if(automata[currState].moveState.at(i) == currState) {
                    int vecSize = acceptState.size();
                    for(int j = 0; j < acceptState.size(); j++) {
                        if(currState == acceptState.at(j)) {
                            acceptInput.push_back(currState);
                            acceptState.erase(std::remove(acceptState.begin(), acceptState.end(), currState), acceptState.end());
                            break;
                        }
                    }
                    if(acceptState.size() == vecSize) {
                        rejectInput.push_back(currState);
                    }
                }
                currState = automata[currState].moveState.at(i);
            }
        }
    }

    if(acceptInput.empty()) {
        cout << "reject ";
        for(int b = 0; b < rejectInput.size(); b++) {
            cout << rejectInput.at(b) << " ";
        }
    }
    if(!acceptInput.empty()) {
        cout << "accept ";
        for(int b = 0; b < acceptInput.size(); b++) {
            cout << acceptInput.at(b) << " ";
        }
    }
    cout << endl;
    
    return 0;
}

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

    while(inFS.is_open()) {
        cin >> readState;
        cin >> numState;
        if(readState.find("state") == true) {
            getline(cin, specState);
            if(specState.find("start") == true) {
                startState = numState;
            }
            if(specState.find("accept") == true) {
                acceptState.push_back(numState);
            }
        }
        
        if(readState.find("transition") == true) {
            cin >> readInput;
            cin >> readMoveState;
            automata[numState].input.push_back(readInput);
            automata[numState].moveState.push_back(readMoveState);
        }
    }
    
    int currState = startState;
    
    for(int z = 0; z < strInput.length(); z++) {
        for(int i = 0; i < automata[currState].input.size(); i++) {
            if(automata[currState].input.at(i) == strInput[z]) {
                for(int j = 0; j < acceptState.size(); j++) {
                    if(currState == acceptState.at(j)) {
                        if(automata[currState].moveState.at(i) == currState) {
                            acceptState.erase(std::remove(acceptState.begin(), acceptState.end(), currState), acceptState.end());
                        }
                    }
                }
            }
        }
    }
    
    cout << "reject " << acceptState << endl;
    
    return 0;
}

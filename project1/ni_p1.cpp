#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

const int SIZE = 1001;

struct Transition {
    char input;
    int moveState;
    Transition(char in, int mo) {      
        input = in;      
        moveState = mo;      
    }
};

struct Node {
    vector<Transition> transitions;
    bool start = false;
    bool accept = false;
};

int main(int argc, char* argv[]) {
    string fileName = argv[1];
    string strInput = argv[2];
    Node NFA[SIZE];
    
    string readState;
    int numState;
    
    string specState;
    
    char readInput;
    int readMoveState;
    
    int startState;
    vector<int> acceptStates;
    
    ifstream inFS;
    inFS.open(fileName);
    while(!inFS.fail()) {
        inFS >> readState;
        inFS >> numState;
        //cout << readState << "\t" << numState << "\t";
        if(readState.find("state") != string::npos) {
            inFS >> specState;
            //cout << specState << endl;
            if(specState.find("start") != string::npos) {
                startState = numState;
                NFA[numState].start = true;
            }
            if(specState.find("accept") != string::npos) {
                acceptStates.push_back(numState);
                NFA[numState].accept = true;
            }
        }
        if(readState.find("transition") != string::npos) {
            inFS >> readInput;
            inFS >> readMoveState;
            //cout << readInput << "\t" << readMoveState << endl;
            int tSize = NFA[numState].transitions.size();
            struct Transition transit = Transition(readInput, readMoveState);
            NFA[numState].transitions.push_back(transit);
        }
    }
    
    int currState;
    vector<int> selfStates;
    vector<int> nextState;
    vector<int> accepted;
    vector<int> rejected;
    vector<int> temp;
    bool repeat;
    temp.push_back(startState);
    for(int i = 0; i < strInput.size(); i++) {
        nextState = temp;
        temp.clear();
        /*cout << "\nnextState: ";
        for(int f = 0; f < nextState.size(); f++) {
            cout << nextState.at(f);
        }
        cout << endl;*/
        while(!nextState.empty()) { 
            currState = nextState.at(nextState.size()-1);
            //cout << "currState: " << currState << "\ttransitions: " << NFA[currState].transitions.size();
            nextState.pop_back();
            for(int h = 0; h < NFA[currState].transitions.size(); h++) {         //# of transits that node has
                if(NFA[currState].transitions.at(h).input == strInput[i]) {
                    //cout << "\ninput: " << NFA[currState].transitions.at(h).input;
                    /*
                    if(NFA[currState].transitions.at(h).moveState == currState and NFA[currState].accept) {
                        repeat = false;
                        for(int r = 0; r < accepted.size(); r++) {
                            if(accepted.at(r) == currState) {
                                repeat = true;
                            }
                        }
                        if(!repeat) {
                            accepted.push_back(currState);
                        }
                    }
                    */
                    if(i == strInput.size()-1) {
                        if(NFA[NFA[currState].transitions.at(h).moveState].accept) {
                            repeat = false;
                            for(int r = 0; r < accepted.size(); r++) {
                                if(accepted.at(r) == NFA[currState].transitions.at(h).moveState) {
                                    repeat = true;
                                }
                            }
                            if(!repeat) {
                                accepted.push_back(NFA[currState].transitions.at(h).moveState);
                            }
                        }
                        if(!NFA[NFA[currState].transitions.at(h).moveState].accept) {
                            repeat = false;
                            for(int r = 0; r < rejected.size(); r++) {
                                if(rejected.at(r) == NFA[currState].transitions.at(h).moveState) {
                                    repeat = true;
                                }
                            }
                            if(!repeat) {
                                rejected.push_back(NFA[currState].transitions.at(h).moveState);
                            }
                        }
                    }
                    //cout << "\tmoveTo: " << NFA[currState].transitions.at(h).moveState << endl;
                    temp.push_back(NFA[currState].transitions.at(h).moveState);
                    
                }
            }
        }
    }
    if(accepted.empty()) {
        cout << "reject ";
        for(int b = 0; b < rejected.size(); b++) {
            cout << rejected.at(b) << " ";
        }
    }
    
    else {
        cout << "accept ";
        for(int b = 0; b < accepted.size(); b++) {
            cout << accepted.at(b) << " ";
        }
    }
    return 0;
}
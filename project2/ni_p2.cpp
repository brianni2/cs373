#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

char toggleGate(char gate, char input) {        //toggles x1
    if(input == '0') {                          //0 = L -> R -> C -> L
        if(gate == 'L') {
            return 'R';
        }
        if(gate == 'R') {
            return 'C';
        }
        if(gate == 'C') {
            return 'L';
        }
    }
    if(input == '1') {                          //1 = L -> C -> R -> L
        if(gate == 'L') {
            return 'C';
        }
        if(gate == 'C') {
            return 'R';
        }
        if(gate == 'R') {
            return 'L';
        }
    }
    else {
        return gate;
    }
}

char toggleSwitch(char gate, char input) {      //toggle x2, x3, and x4
    if(input == '0') {                          //0 = L -> R -> L
        if(gate == 'L') {
            return 'R';
        }
        if(gate == 'R') {
            return 'L';
        }
    }
    if(input == '1') {                          //1 = L -> R -> L
        if(gate == 'L') {
            return 'R';
        }
        if(gate == 'R') {
            return 'L';
        }
    }
    else {
        return gate;
    }
}

int main(int argc, char* argv[]) {
    string fileName = argv[1];
    ifstream inFS;
    inFS.open(fileName);
    string config;
    string input;
    inFS >> config;
    inFS >> input;
    
    int size = input.size();
    cout << config << "->";
    for(int i = 0; i < size - 1; i++) {
        if(config[0] == 'L') {                                  //toggle x2
            config[1] = toggleSwitch(config[1], input[i]);
        }
        if(config[0] == 'C') {                                  //toggle x3
            config[2] = toggleSwitch(config[2], input[i]);
        }
        if(config[0] == 'R') {                                  //toggle x4
            config[3] = toggleSwitch(config[3], input[i]);
        }
        config[0] = toggleGate(config[0], input[i]);
        cout << config << "->";
    }
    
    string output;
    if(config[0] == 'L') {                                      //final toggle x2
        if(config[1] == 'L') {
            output = "B";
        }
        else {
            output = "C";
        }
        config[1] = toggleSwitch(config[1], input[size-1]);
    }
    if(config[0] == 'C') {                                      //final toggle x3
        if(config[2] == 'L') {
            output = "C";
        }
        else {
            output = "D";
        }
        config[2] = toggleSwitch(config[2], input[size-1]);
    }
    if(config[0] == 'R') {                                      //final toggle x4
        if(config[3] == 'L') {
            output = "D";
        }
        else {
            output = "E";
        }
        config[3] = toggleSwitch(config[3], input[size-1]);
    }
    config[0] = toggleGate(config[0], input[size-1]);
    cout << config << " " << output << endl;
    return 0;
}

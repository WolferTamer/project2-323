#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <stack>
#include <map>

using namespace std;

stack<char> pile;
string input = "";
int token = 0;
map<std::pair<char,char>,string> table;

bool isTerminal(char t) {
    char terminals[] = {'a','+','-','*','/','(',')'};
    for(char term: terminals) {
        if(t == term) {
            return true;
        }
    }
    return false;
}

void fillTable() {
    table[make_pair('E','a')] = "TQ";
    table[make_pair('E','(')] = "TQ";
    table[make_pair('Q','+')] = "+TQ";
    table[make_pair('Q','-')] = "-TQ";
    table[make_pair('T','a')] = "FR";
    table[make_pair('T','(')] = "FR";
    table[make_pair('R','+')] = "";
    table[make_pair('R','-')] = "";
    table[make_pair('R','*')] = "*FR";
    table[make_pair('R','/')] = "/FR";
    table[make_pair('R',')')] = "";
    table[make_pair('R','$')] = "";
    table[make_pair('Q',')')] = "";
    table[make_pair('Q','$')] = "";
    table[make_pair('F','a')] = "a";
    table[make_pair('F','(')] = "(E)";
}

void E() {

}

void T() {

}

void Q() {

}

void F(){

}

bool driver() {
    while(pile.top() != '$') {
        char t = pile.top();
        char i = input[token];
        cout<<t<<','<<i<<'\n';
        if(isTerminal(t)) {
            if(t == i) {
                pile.pop();
                token++;
            } else {
                cout << "terminal doesnt match" << '\n';
                return false;
            }
        } else {
            if(table.count(make_pair(t,i)) == 1) {
                pile.pop();
                string val = table[make_pair(t,i)];
                for(int j = val.size()-1; j >= 0; j--) {
                    pile.push(val.at(j));
                }
            } else {
                cout << "no table exists" << '\n';
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    pile.push('$');
    pile.push('E');
    for(int i = 1; i < argc; i++) {
        input += argv[i];
        cout << input << '\n';
    }
    fillTable();
    cout << driver() << '\n';
}
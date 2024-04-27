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

void printStack(stack<char> s)
{
    if (s.empty())
        return;
    
    char x = s.top();
    s.pop();
    cout << x << ' ';
    printStack(s);
    s.push(x);
}
 

bool driver() {
    while(pile.top() != '$') {
        char t = pile.top();
        char i = input[token];
        if(isTerminal(t)) {
            if(t == i) {
                pile.pop();
                token++;
                cout << "Input: " << input.substr(token) << '\n'; 
                cout << "Stack: [";
                printStack(pile);
                cout << "]\n";
            } else {
                return false;
            }
        } else {
            if(table.count(make_pair(t,i)) == 1) {
                string val = table[make_pair(t,i)];
                pile.pop();
                for(int j = val.size()-1; j >= 0; j--) {
                    pile.push(val.at(j));
                }

                cout << "Input: " << input.substr(token) << '\n'; 
                cout << "Stack: [";
                printStack(pile);
                cout << "]\n";
                
            } else {
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
    }
    if(input.size() == 0) {
        cout << "Please provide a string argument in the file call.\n";
        return 0; 
    }

    cout << "Input: " << input << '\n';
    cout << "Stack: ";
    printStack(pile);
    cout << '\n';

    fillTable();
    bool output = driver();
    cout << "Output: ";
    if(output) {
        cout << "The input is accepted/valid.";
    } else {
        cout << "The input is not accepted/invalid.";
    }
    cout << "\n";

}
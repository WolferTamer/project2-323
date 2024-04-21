#include <iostream>
#include <string>
#include <stack>
#include <map>

using namespace std;

stack<char> pile;
string input = "";
map<pair<char, char>, string> table;

bool isTerminal(char t) {
    char terminals[] = { 'a', '+', '-', '*', '/', '(', ')' };
    for (char term : terminals) {
        if (t == term) {
            return true;
        }
    }
    return false;
}

void fillTable() {
    table[make_pair('E', 'a')] = "TQ";
    table[make_pair('E', '(')] = "TQ";
    table[make_pair('Q', '+')] = "+TQ";
    table[make_pair('Q', '-')] = "-TQ";
    table[make_pair('T', 'a')] = "FR";
    table[make_pair('T', '(')] = "FR";
    table[make_pair('R', '+')] = "";
    table[make_pair('R', '-')] = "";
    table[make_pair('R', '*')] = "*FR";
    table[make_pair('R', '/')] = "/FR";
    table[make_pair('R', ')')] = "";
    table[make_pair('R', '$')] = "";
    table[make_pair('Q', ')')] = "";
    table[make_pair('Q', '$')] = "";
    table[make_pair('F', 'a')] = "a";
    table[make_pair('F', '(')] = "(E)";
}

bool driver() {
    while (!pile.empty()) {
        char t = pile.top();
        if (input.empty()) {
            return false; // No more input
        }
        char i = input.front();
        input.erase(input.begin());
        cout << t << ',' << i << '\n';
        if (isTerminal(t)) {
            if (t == i) {
                pile.pop();
            }
            else {
                cout << "Terminal doesn't match\n";
                return false;
            }
        }
        else {
            if (table.count(make_pair(t, i)) == 1) {
                pile.pop();
                string val = table[make_pair(t, i)];
                for (int j = val.size() - 1; j >= 0; j--) {
                    pile.push(val.at(j));
                }
            }
            else {
                cout << "No table entry exists\n";
                return false;
            }
        }
    }
    return true;
}

int main() {
    fillTable();
    cout << "Enter your string: ";
    cin >> input;
    pile.push('$');
    pile.push('E');
    if (driver()) {
        cout << "Input string is valid.\n";
    }
    else {
        cout << "Input string is invalid.\n";
    }
    return 0;
}

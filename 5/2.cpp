#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>
using namespace std;

string line;
vector<pair<char, char>> alphabet_list;
string alphabet = "abcd"; //efghijklmnopqrstuvwxyz

void setup() {
    ifstream file("input.txt");
    if (!file.is_open()) return;

    getline(file, line);
    
    for (char ch : alphabet) {
        alphabet_list.push_back({ch, toupper(ch)});
    }
}

bool is_upper(char ch1, char ch2) {
    return (ch1 == toupper(ch2) && tolower(ch1) == ch2);
}

void solve() {
    int minimum = line.length();

    for (auto letter : alphabet_list) {
        int i = 0, j = 1;
        string cline = line;

        while (j < cline.length()) {
            if (cline[j] == letter.first || cline[j] == letter.second) {
                cline.erase(j, 1);
            } else if (is_upper(cline[i], cline[j]) || is_upper(cline[j], cline[i])) {
                cline.erase(i, j-i+1);
                if (i != 0) {
                    j = i;
                    i--;
                }
            } else {
                i++, j++;
            }
        }
        int len = cline.length();
        if (len < minimum) {
            minimum = len;
        }
    }

    cout << minimum << endl;
}

int main() {
    auto start_time = std::chrono::high_resolution_clock::now();

    setup();
    solve();
    
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
    cout << "Clock time: " << duration.count() / (double)1000000 << " s" << endl;

    return 0;
}
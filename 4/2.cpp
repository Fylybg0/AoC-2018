#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

struct LogEntry {
    int year, month, day, hour, minute;
    string event1, event2;
};

vector<LogEntry> logs;
map<int, vector<int>> sleep;

LogEntry parse_line(string line) {
    LogEntry entry;

    auto closeBracketPos = line.find(']');

    entry.year = stoi(line.substr(1, 5));
    entry.month = stoi(line.substr(6, 8));
    entry.day = stoi(line.substr(9, 11));
    entry.hour = stoi(line.substr(12, 14));
    entry.minute = stoi(line.substr(15, 17));

    string event = line.substr(closeBracketPos + 2, line.length() - 1);
    auto spacePos = event.find(' ');
    entry.event1 = event.substr(0, spacePos);

    string ev = event.substr(spacePos + 1, event.length() - 1);
    auto spacePos2 = ev.find(' ');
    entry.event2 = ev.substr(0, spacePos2);
    
    return entry;
}

void setup() {
    ifstream file("input.txt");
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        LogEntry log = parse_line(line);
        logs.push_back(log);
    }
}

bool compareStruckts(const LogEntry &a, const LogEntry &b) {
    int a_compared_values[5] = {a.year, a.month, a.day, a.hour, a.minute};
    int b_compared_values[5] = {b.year, b.month, b.day, b.hour, b.minute}; 

    for (int i = 0; i < 5; i++) {
        if (a_compared_values[i] < b_compared_values[i]) return true;
        else if (a_compared_values[i] > b_compared_values[i]) return false;
    }
    return true;
}

vector<int> get_array_of_zeroes() {
    vector<int> zeroes;
    for (int i = 0; i < 60; i++) zeroes.push_back(0);
    return zeroes;
}

pair<int, int> get_guard_with_highest_value(map<int, vector<int>> sl) {
    pair<int, int> max_key = {0, 0};
    int max_idx;
    for (auto el : sl) {
        for (int x = 0; x < 60; x++) {
            if (el.second[x] > max_key.second) max_key.first = el.first, max_key.second = el.second[x], max_idx = x;
        }
    }
    return {max_key.first, max_idx};
}

void solve() {
    sort(logs.begin(), logs.end(), compareStruckts);
    
    int current_guard, asleep_time;

    for (LogEntry log : logs) {
        if (log.event1 == "Guard") {
            current_guard = stoi(log.event2.substr(1, log.event2.length() - 1));
        } else if (log.event1 == "falls") {
            asleep_time = log.minute;
        } else if (log.event1 == "wakes") {
            if (sleep.find(current_guard) == sleep.end()) {
                sleep.insert({current_guard, get_array_of_zeroes()});
            }
            for (int i = asleep_time; i < log.minute; i++) {
                sleep[current_guard][i] += 1;
            }
        }
    }

    pair<int, int> guard = get_guard_with_highest_value(sleep);

    int result = guard.first * guard.second;

    cout << result << endl;;
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
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <list>
#include <string>
#include <deque>
#include <fstream>
#include <utility>
#include <bits/stdc++.h>
using namespace std;

enum Turn {LEFT, STRAIGHT, RIGHT};
enum Dir {N, S, W, E};

using Pos = pair<int, int>;
map<char, Dir> dirs {{'^', N}, {'v', S}, {'<', W}, {'>', E}};
map<char, map<Dir, Dir>> change_dir_by_slash {{'\\', {{N, W}, {W, N}, {S, E}, {E, S}}},
                                              {'/', {{N, E}, {E, N}, {S, W}, {W, S}}}};
map<Dir, pair<int, int>> axes {{N, {-1, 0}}, {S, {1, 0}}, {W, {0, -1}}, {E, {0, 1}}};
map<Dir, map<Turn, Dir>> change_dir {{N, {{LEFT, W}, {STRAIGHT, N}, {RIGHT, E}}}, 
                                     {S, {{LEFT, E}, {STRAIGHT, S}, {RIGHT, W}}}, 
                                     {W, {{LEFT, S}, {STRAIGHT, W}, {RIGHT, N}}},
                                     {E, {{LEFT, N}, {STRAIGHT, E}, {RIGHT, S}}}};
map<Turn, Turn> change_turn {{LEFT, STRAIGHT}, {STRAIGHT, RIGHT}, {RIGHT, LEFT}};
map<Pos*, pair<Dir, Turn>> carts;
vector<Pos> cart_poses;
map<Pos, char> turnings;



void setup () {
    ifstream file("2017day15.txt");

    if (!file.is_open()) return;

    string line;
    int r = 0;
    while (getline(file, line)) {
        for (int c = 0; c < line.size(); c++) {
            if (line[c] == '/' || line[c] == '\\' || line[c] == '+') {
                turnings.insert({{r, c}, line[c]});
            } else if (line[c] == '<' || line[c] == '>' || line[c] ==  '^' || line[c] ==  'v') {
                cout << r << ',' << c << ' ';
                cart_poses.push_back({r, c});
                carts.insert({&cart_poses[cart_poses.size() - 1], {dirs[line[c]], LEFT}});
            }
        }
        r++;
    }
    cout << cart_poses.size() << endl;
    for (pair<pair<int, int>*, pair<Dir, Turn>> i : carts) {
        cout << i.first->first << endl;
    }
    cout << endl;

}


void solve () {
    int i = 0;
    while (i < 3) {
        i++;
        if (cart_poses.size() == 1) {
            cout << cart_poses.at(0).first << ',' << cart_poses.at(0).second << endl;
            return;
        }
        cout << cart_poses.size() << endl;

        vector<int> to_erase;
        for (auto it = cart_poses.begin(); it < cart_poses.end(); it++) {
            Pos* cart_pos = &*it;
            int q = cart_pos->first + axes[carts[cart_pos].first].first, p = cart_pos->second + axes[carts[cart_pos].first].second;
            
            cout << cart_pos->first << ',' << cart_pos->second << ' ' << q << "," << p << ' ' << carts[cart_pos].first << endl;

            auto idx1 = find(cart_poses.begin(), cart_poses.end(), (Pos){q, p});
            auto idx2 = find(cart_poses.begin(), cart_poses.end(), *cart_pos);
            if (idx1 != cart_poses.end()) {
                to_erase.push_back(idx1 - cart_poses.begin());
                to_erase.push_back(idx2 - cart_poses.begin());
                continue;
            } else if (turnings[{q, p}] == '/' || turnings[{q, p}] == '\\') {
                carts[cart_pos].first = change_dir_by_slash[turnings[{q, p}]][carts[cart_pos].first];
            } else if (turnings[{q, p}] == '+') {
                carts[cart_pos].first = change_dir[carts[cart_pos].first][carts[cart_pos].second];
                carts[cart_pos].second = change_turn[carts[cart_pos].second];
            }

            cart_pos->first = q;
            cart_pos->second = p;
        }
        cout << "woeeewo ";
        sort(to_erase.rbegin(), to_erase.rend());

        for (int it : to_erase) cout << it << ' ';
        for (int it : to_erase) cart_poses.erase(cart_poses.begin() + it);

        map<Pos, pair<Dir, Turn>> carts_without_pointers;

        for (auto& entry : carts) carts_without_pointers[*entry.first] = entry.second;

        sort(cart_poses.begin(), cart_poses.end(), less<Pos>());

        map<Pos*, pair<Dir, Turn>> updated_carts;

        for (auto& entry : carts_without_pointers) {
            auto old_ptr = entry.first;
            auto direction_pair = entry.second;
            for (auto& pos : cart_poses) {
                if (pos == old_ptr) {
                    updated_carts[&pos] = direction_pair;
                    break;
                }
            }
        }

        /*cout << cart_poses.size() << endl;
        for (Pos x : cart_poses) {
            cout << x.first << ',' << x.second << endl;
        }*/
        cout << endl;

        carts.swap(updated_carts);
    }
}   

int main() {

    setup();
    solve();

    return 1;
}
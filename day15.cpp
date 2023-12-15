#include <bits/stdc++.h>

#define ll long long
#define pl pair<long, long>

using namespace std;

ll res1 = 0, res2 = 0;
vector<string> input;

void parse_input() {
    FILE *fp=freopen("input15.txt","r",stdin);
    string line;
    getline(cin, line);
    fclose(fp);

    stringstream ss(line);
    string token;
    while(getline(ss, token, ',')) {
        input.push_back(token);
    }
}

int ascii(char c) {
    return int(c);
}

int hash_fct(string s) {
    int ans = 0;
    for (char c: s) {
        ans += ascii(c); ans *= 17; ans %= 256;
    }
    return ans;
}

void solve1() {
    for (string s: input)
        res1 += hash_fct(s);
}


void solve2() {
    vector<map<string, pl>> mp(256);
    for (string s: input) {
        string string_to_hash = (s[s.size()-1] == '-') ? s.substr(0, s.size()-1) : s.substr(0, s.size()-2);
        int box = hash_fct(string_to_hash);
        if (s[s.size()-1] == '-') {
            // if it exists to be safe
            if (mp[box].find(string_to_hash) != mp[box].end()) {
                pl value = mp[box][string_to_hash];
                ll idx = value.second;
                for (auto& [key, val] : mp[box])
                    if (val.second > idx)
                        val.second--;
            }
            mp[box].erase(string_to_hash);
        }

        else {
            char c = s[s.size()-1];
            ll focal_len = ascii(c) - 48;
            if (mp[box].find(string_to_hash) != mp[box].end()) {
                mp[box][string_to_hash].first = focal_len;
            }
            else {
                ll new_ind = mp[box].size();
                mp[box].insert({string_to_hash, {focal_len, new_ind}});
            }
        }
    }
    for (int box = 0; box < 256; box++) {
        int nb = box + 1;
        for (auto& [str, val]: mp[box]) {
            int idx = val.second + 1;
            int focal = val.first;
            res2 += nb*idx*focal;
        }
    }
}

int main() {
    parse_input();
    solve1();
    cout << res1 << endl;
    solve2();
    cout << res2 << endl;
}
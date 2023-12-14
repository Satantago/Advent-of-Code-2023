#include <bits/stdc++.h>

#define ll long long

using namespace std;

vector<vector<string>> input;
ll res1 = 0, res2 = 0;
ll a = 911382323;
ll b = 972663749;


void parse_input() {
    freopen("input13.txt", "r", stdin);

    string line;
    vector<string> group;
    while (getline(cin, line)) {
        if (line == "") {
            input.push_back(group);
            group.clear();
        }
        else
            group.push_back(line);
    }
}

vector<string> reverse_row(vector<string> group) {
    vector<string> reverse_group;
    for (string row: group) {
        reverse(row.begin(), row.end());
        reverse_group.push_back(row);
    }
    return reverse_group;
}


int ascii(char c) {
    return int(c);
}

vector<vector<ll>> hash_all(vector<string> group) {
    int n = group.size(), m = group[0].size();
    vector<vector<ll>> hash_group(n, vector<ll>(m, 0));

    for (int i = 0; i < n; i++) {
        hash_group[i][0] = ascii(group[i][0]);
        for (int j = 1; j < m; j++) {
            hash_group[i][j] = (a*hash_group[i][j-1] + ascii(group[i][j])) % b;
        }
    }
    return hash_group;
}

vector<vector<ll>> construct_p(vector<string>& group) {
    ll n = group.size(), m = group[0].size();
    vector<vector<ll>> p(n, vector<ll>(m, 0));

    for (ll i = 0; i < n; i++) {
        p[i][0] = 1;
        for (ll j = 1; j < m; j++) {
            p[i][j] = (a * p[i][j-1]) % b;
        }
    }
    return p;
}

ll res_columns(vector<string> group, ll old) {
    ll ans = 0;
    vector<vector<ll>> hash_group = hash_all(group);
    vector<vector<ll>> p1 = construct_p(group);

    vector<string> reverse_group = reverse_row(group);
    vector<vector<ll>> hash_reverese_group = hash_all(reverse_group);
    vector<vector<ll>> p2 = construct_p(reverse_group);

    ll m = group[0].size(), n = group.size();
    for (ll j = 0; j < m - 1; j++) {
        bool possible = true;

        ll len = min(j+1, m-j-1);

        ll right_a = j+1;
        ll right_b = right_a + len - 1;

        ll left_a_reverse = m-j-1;
        ll left_b_reverse = left_a_reverse + len - 1;

        for (ll i = 0; i < n; i++) {
            vector<ll> h1(hash_group[i]);
            vector<ll> pp1(p1[i]);
            vector<ll> h2(hash_reverese_group[i]);
            vector<ll> pp2(p2[i]);

            ll hash_right;
            if (right_a == 0) hash_right = h1[right_b];
            else              hash_right = (h1[right_b] - h1[right_a-1]*pp1[right_b-right_a+1]) % b;
            if (hash_right < 0) hash_right += b;
        
            ll hash_left;
            if (left_a_reverse == 0) hash_left = h2[left_b_reverse];
            else                     hash_left = (h2[left_b_reverse] - h2[left_a_reverse-1]*pp2[left_b_reverse-left_a_reverse+1]) % b;
            if (hash_left < 0) hash_left += b;

            if (hash_left != hash_right) {
                possible = false;
                break;
            }
        }
        
        if (possible) {
            ll column_to_add = (j+1);
            if (column_to_add != old)
                ans += column_to_add;
        }
    }
    return ans;
}

vector<string> transpose(vector<string> group) {
    vector<string> new_group;
    int n = group.size(), m = group[0].size();
    for (int j = 0; j < m; j++) {
        string s = "";
        for (int i = 0; i < n; i++) {
            s = s + group[i][j];
        }
        new_group.push_back(s);
    }
    return new_group;
}

ll res_rows(vector<string> group, ll old_row) {
    vector<string> new_group = transpose(group);
    return res_columns(new_group, old_row);
}

char oppose(char c) {
    if (c == '.') return '#';
    else if (c == '#') return '.';
    return 'x';
}

ll part2(vector<string> group, ll old_col, ll old_row) {
    int n = group.size(), m = group[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0 && j == 4) 
                int x = 0;

            if (i == 1 && j == 4) {
                int x = 0;
            }
            group[i][j] = oppose(group[i][j]);
            ll new_col = res_columns(group, old_col);
            ll new_row = res_rows(group, old_row);
            if (new_col != 0 && new_col != old_col)
                return new_col;
            else if (new_row != 0 && new_row != old_row)
                return 100*new_row;
            group[i][j] = oppose(group[i][j]);
        }
    }
    return 0;
}

int main() {
    parse_input();
    int i = 0;
    for (auto group: input) {
        
        ll col = res_columns(group, -1);
        res1 += col;
        ll row = res_rows(group, -1);
        res1 += 100*row;

        res2 += part2(group, col, row);
        i++;
    }

    cout << res1 << endl; // had to add an empty line in the end of input to process last group
    cout << res2 << endl;
}
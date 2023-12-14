// #include <bits/stdc++.h>

// #define ll long long

// using namespace std;

// ll res = 0;

// void backtrack(vector<int>& lengths, int id_len, int i, int actual_len, string line) {
//     if (i == line.size()) {
//         if (id_len == lengths.size()-1  && actual_len == lengths[id_len]) res++;
//         if (id_len == lengths.size()) res++;
//         return;
//     }

//     if (line[i] == '?') {
//         if (id_len < lengths.size()) {
//             if (lengths[id_len] == actual_len)
//                 backtrack(lengths, id_len+1, i+1, 0, line);
//             else {
//                 backtrack(lengths, id_len, i+1, actual_len + 1, line);
//                 if (actual_len == 0) backtrack(lengths, id_len, i+1, 0, line);
//             }
//         }
//         else
//             backtrack(lengths, id_len, i+1, 0, line);
//     }

//     else if (line[i] == '#') {
//         if (id_len >= lengths.size() || (id_len < lengths.size() && actual_len+1 > lengths[id_len]))
//             return; // not possible so no need for further check to ++
//         else
//             backtrack(lengths, id_len, i+1, actual_len+1, line);
//     }

//     else if (line[i] == '.') {
//         if (id_len < lengths.size()) {
//             if (lengths[id_len] == actual_len)
//                 backtrack(lengths, id_len+1, i+1, 0, line);
//             else {
//                 if (actual_len == 0) backtrack(lengths, id_len, i+1, 0, line);
//                 else return;
//             }
//         }
//         else
//             backtrack(lengths, id_len, i+1, 0, line);
//     }
// }
// vector<string> input;
// vector<vector<int>> lengths;
// void parse_input() {
//     freopen("input13.txt", "r", stdin);
//     string full_line;

//     while (getline(cin, full_line)) {
//         stringstream ss(full_line);
//         string line, lens;
//         ss >> line >> lens;
//         input.push_back(line);
//         vector<int> l;
//         int i = 0, n = lens.size();
//         string cur = "";
//         while (i < n) {
//             while (i < n && lens[i] != ',') {
//                 cur = cur + lens[i];
//                 i++;
//             }
//             i++;
//             l.push_back(stoi(cur));
//             cur = "";
//         }
//         lengths.push_back(l);
//     }
// }
// int main() {
    
//     // string line;
//     // cin >> line;
//     // vector<int> len;
//     // int l;
//     // while (cin >> l)
//     //     len.push_back(l);
//     // backtrack(len, 0, 0, 0, line);
//     // cout << res << endl;

//     parse_input();
//     for (int i = 0; i < input.size(); i++)
//         backtrack(lengths[i], 0, 0, 0, input[i]);
//     cout << res << endl;
// }


#include <bits/stdc++.h>

#define ll long long

using namespace std;

ll res = 0;

vector<string> input;
vector<vector<int>> lengths;

void parse_input_part_one() {
    freopen("input13.txt", "r", stdin);
    string full_line;

    while (getline(cin, full_line)) {
        stringstream ss(full_line);
        string line, lens;
        ss >> line >> lens;
        input.push_back(line);
        vector<int> l;
        int i = 0, n = lens.size();
        string cur = "";
        while (i < n) {
            while (i < n && lens[i] != ',') {
                cur = cur + lens[i];
                i++;
            }
            i++;
            l.push_back(stoi(cur));
            cur = "";
        }
        lengths.push_back(l);
    }
}

void backtrack(vector<int>& lengths, int id_len, int i, int actual_len, string line) {
    if (i == line.size()) {
        if (id_len == lengths.size()-1  && actual_len == lengths[id_len]) res++;
        if (id_len == lengths.size()) res++;
        return;
    }

    if (line[i] == '?') {
        if (id_len < lengths.size()) {
            if (lengths[id_len] == actual_len)
                backtrack(lengths, id_len+1, i+1, 0, line);
            else {
                backtrack(lengths, id_len, i+1, actual_len + 1, line);
                if (actual_len == 0) backtrack(lengths, id_len, i+1, 0, line);
            }
        }
        else
            backtrack(lengths, id_len, i+1, 0, line);
    }

    else if (line[i] == '#') {
        if (id_len >= lengths.size() || (id_len < lengths.size() && actual_len+1 > lengths[id_len]))
            return; // not possible so no need for further check to ++
        else
            backtrack(lengths, id_len, i+1, actual_len+1, line);
    }

    else if (line[i] == '.') {
        if (id_len < lengths.size()) {
            if (lengths[id_len] == actual_len)
                backtrack(lengths, id_len+1, i+1, 0, line);
            else {
                if (actual_len == 0) backtrack(lengths, id_len, i+1, 0, line);
                else return;
            }
        }
        else
            backtrack(lengths, id_len, i+1, 0, line);
    }
}



void parse_input_part_two() {
    freopen("input13.txt", "r", stdin);
    string full_line;

    while (getline(cin, full_line)) {
        stringstream ss(full_line);
        string line, lens;
        ss >> line >> lens;
        line = line + "?" + line + "?" + line + "?" + line + "?" + line;
        input.push_back(line);
        vector<int> l;
        int i = 0, n = lens.size();
        string cur = "";
        while (i < n) {
            while (i < n && lens[i] != ',') {
                cur = cur + lens[i];
                i++;
            }
            i++;
            l.push_back(stoi(cur));
            cur = "";
        }
        int m = l.size();
        for (int i = 0; i< 4; i++) {
            for (int j = 0; j < m; j++) {
                l.push_back(l[j]);
            }
        }
        lengths.push_back(l);
    }
}

int ways(string s, vector<int> runs) {
    runs.push_back(0);
    int max_run = *max_element(runs.begin(), runs.end());
    s = s + ".";

    int n = s.size();
    int m = runs.size();
    vector<vector<vector<ll>>> dp(n, vector<vector<ll>>(m, vector<ll>(max_run+1, 0)));

    for (int i = 0; i < n; i++) {
        char x = s[i];
        for (int j = 0; j < m; j++) {
            for (int k = 0; k <= runs[j]; k++) {
                if (i == 0) {
                    if (j != 0) {
                        dp[i][j][k] = 0;
                        continue;
                    }
                    // j == 0
                    if (x == '#') {
                        if (k != 1) {
                            dp[i][j][k] = 0;
                            continue;
                        }
                        dp[i][j][k] = 1;
                        continue;
                    }

                    if (x == '.') {
                        if (k != 0) {
                            dp[i][j][k] = 0;
                            continue;
                        }
                        dp[i][j][k] = 1;
                        continue;
                    }

                    if (x == '?') {
                        if (k != 0 && k != 1) {
                            dp[i][j][k] = 0;
                            continue;
                        }
                        dp[i][j][k] = 1;
                        continue;
                    }
                }

                ll ans_dot = 0;
                if (k != 0)
                    ans_dot = 0;
                else if (j > 0)
                    ans_dot = dp[i-1][j-1][runs[j-1]] + dp[i-1][j][0];
                else
                    ans_dot = (s.substr(0, i).find("#") == std::string::npos) ? 1 : 0;
                

                ll ans_pound = 0;
                if (k != 0)
                    ans_pound = dp[i-1][j][k-1];
                
                if (x == '.')       dp[i][j][k] = ans_dot;
                else if (x == '#')  dp[i][j][k] = ans_pound;
                else                dp[i][j][k] = ans_dot + ans_pound;
            }
        }
    }
    if (dp[n-1][m-1][0] < 0) cout << dp[n-1][m-1][0] << endl;
    res += dp[n-1][m-1][0];
    return dp[n-1][m-1][0];
}

int main() {
    parse_input_part_two();
    for (int i = 0; i < input.size(); i++)
        ways(input[i], lengths[i]);
    cout << res << endl;
}
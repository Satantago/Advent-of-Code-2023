#include <bits/stdc++.h>

#define ll long long

using namespace std;

ll res1 = 0, res2 = 0;
vector<string> input;

void parse_input() {
    FILE *fp=freopen("input14.txt","r",stdin);
    string line;
    while (getline(cin, line)) {
        input.push_back(line);
    }
    fclose(fp);
}


void clear(queue<int> &q ){
   std::queue<int> empty;
   std::swap(q, empty);
}

vector<string> create_new_map() {
    vector<string> new_map;

    int n = input.size(), m = input[0].size();
    new_map.push_back(input[0]);
    vector<queue<int>> northernmost(m);
    for (int j = 0; j < m; j++) {
        if (input[0][j] == '.') northernmost[j].push(0);
    }

    for (int i = 1; i < n; i++) {
        string new_line = input[i];
        for (int j = 0; j < m; j++) {
            if (new_line[j] == '.') {
                northernmost[j].push(i);
            }
            else if (new_line[j] == '#') {
                clear(northernmost[j]);
            }
            else {
                if (!northernmost[j].empty()) {
                    int x = northernmost[j].front(); northernmost[j].pop();
                    new_line[j] = '.';
                    new_map[x][j] = 'O';
                    northernmost[j].push(i);
                }
            }
        }
        new_map.push_back(new_line);
    }
    return new_map;
}

void solve1(vector<string>& map) {
    int n = map.size(), m = map[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (map[i][j] == 'O')
                res1 += n-i;
        }
    }
}

int main() {
    parse_input();
    vector<string> new_map = create_new_map();
    solve1(new_map);
    cout << res1 << endl;
}
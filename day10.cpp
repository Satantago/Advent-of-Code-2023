#include <bits/stdc++.h>

#define pi pair<int, int>

using namespace std;


vector<pi> get_neighbors(int i, int j, vector<string>& input) {
    switch (input[i][j]) {
        case 'F':   return {{i + 1, j}, {i, j + 1}};
        case '-':   return {{i, j - 1}, {i, j + 1}};
        case 'L':   return {{i - 1, j}, {i, j + 1}};
        case '7':   return {{i + 1, j}, {i, j - 1}};
        case 'J':   return {{i - 1, j}, {i, j- 1}};
        case '|':   return {{i - 1, j}, {i + 1, j}};
        default:    throw exception();
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("input.txt", "r", stdin);

    vector<string> input;

    string line;
    int xs = -1, ys = -1;
    while (getline(cin, line))
        input.push_back(line);
    
    int n = input.size(), m = input[0].size();
    for (int i = 0; i < n && xs == -1; i++) {
        for (int j = 0; j < m; j++) {
            if (input[i][j] == 'S') {
                xs = i;
                ys = j;
                input[i][j] = 'F';   // look at input and adapt it, otherwise automate it
                break;
            }
        }
    }

    // PART ONE
    queue<pi> q;
    q.push({xs, ys});

    vector<vector<int>> dis(n, vector<int>(m, INT_MAX));
    dis[xs][ys] = 0;

    int res1 = 0;

    while (!q.empty()) {
        int x = q.front().first, y = q.front().second;
        q.pop();
        for (pi p: get_neighbors(x, y, input)) {
            int xp = p.first, yp = p.second;
            if (xp >= 0 && xp < n && yp >= 0 && yp < m && input[xp][yp] != '.' && dis[xp][yp] > dis[x][y] + 1) {
                dis[xp][yp] = dis[x][y] + 1;
                res1 = max(res1, dis[xp][yp]);
                q.push(p);
            }
        }
    }
    printf("res1 = %d \n", res1);


    // PART TWO: Ray Casting algorithm (Point polygon)
    int res2 = 0;
    for (int i = 0; i < n; i++) {
        int left_edge = 0;
        for (int j = 0; j < m; j++) {
            if ((left_edge & 1) && dis[i][j] == INT_MAX) res2++;
            // F ---- J   equal to up right up        -> should be counted only one edge not two
            // L ---- 7   equal to down right down    -> should be counted only one edge not two
            // so  either J & L or F & 7
            if ((dis[i][j] < INT_MAX) && (input[i][j] == '|' || input[i][j] == '7' || input[i][j] == 'F')) left_edge++;
        }
    }
    printf("res2 = %d \n", res2);
}

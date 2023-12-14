// #include <bits/stdc++.h>

// #define ll long long
// #define pi pair<int, int>

// using namespace std;

// vector<string> input;
// vector<int> empty_rows;
// vector<int> empty_columns;
// map<int, pi> pos;
// int n, m;
// int id = 0;

// void index_empty_rows() {
//     for (int i = 0; i < input.size(); i++) {
//         bool empty = true;
//         for (int j = 0; j < input[0].size(); j++) {
//             if (input[i][j] != '.') {
//                 empty = false;
//                 break;
//             }
//         }
//         if (empty) empty_rows.push_back(i);
//     }
// }


// void index_empty_columns() {
//     for (int j = 0; j < input[0].size(); j++) {
//         bool empty = true;
//         for (int i = 0; i < input.size(); i++) {
//             if (input[i][j] != '.') {
//                 empty = false;
//                 break;
//             }
//         }
//         if (empty) empty_columns.push_back(j);
//     }
// }

// vector<string> create_new_map() {
//     n = input.size() + empty_rows.size();
//     m = input[0].size() + empty_columns.size();

//     string new_line(m, '.');
//     vector<string> new_map(n, new_line);

//     vector<int> prefix_row(input.size(), 0);
//     for (int index: empty_rows) prefix_row[index]++;

//     for (int i = 1; i < prefix_row.size(); i++)
//         prefix_row[i] += prefix_row[i-1];
    
//     vector<int> prefix_column(input[0].size(), 0);
//     for (int index: empty_columns) prefix_column[index]++;

//     for (int j = 1; j < prefix_column.size(); j++)
//         prefix_column[j] += prefix_column[j-1];

//     for (int i = 0; i < input.size(); i++) {
//         for (int j = 0; j < input[0].size(); j++) {
//             if (input[i][j] == '#') {
//                 int x = i + prefix_row[i];
//                 int y = j + prefix_column[j];
//                 new_map[x][y] = '#';
//                 pos[id] = {x, y};
//                 id++;
//             }
//         }
//     }
//     return new_map;
// }

// vector<pi> get_neighbors(int x, int y) {
//     vector<pi> res;
//     if (x-1 >= 0) res.push_back({x-1, y});
//     if (y-1 >= 0) res.push_back({x, y-1});
//     if (x+1 < n)  res.push_back({x+1, y});
//     if (y+1 < m)  res.push_back({x, y+1});
//     return res;
// }

// int main() {
//     freopen("input11.txt", "r", stdin);

//     string line;
//     while (getline(cin, line))
//         input.push_back(line);
    
//     index_empty_rows();
//     index_empty_columns();

//     vector<string> new_map = create_new_map();

//     int res = 0;
//     for (int i = 0; i < id; i++) {
//         vector<vector<bool>> visited(n, vector<bool>(m, false));
//         vector<vector<int>> dis(n, vector<int>(m, INT_MAX));

//         pi p = pos[i];
//         dis[p.first][p.second] = 0;

//         queue<pi> q;
//         q.push(p);

//         int d = 0;
//         while (!q.empty()) {
//             int size = q.size();
//             for (int k = 0; k < size; k++) {
//                 pi node = q.front(); q.pop();
//                 int x = node.first, y = node.second;
//                 visited[x][y] = true;
//                 for (pi neighbor: get_neighbors(x, y)) {
//                     int xx = neighbor.first, yy = neighbor.second;
//                     if (!visited[xx][yy] && d + 1 < dis[xx][yy]) {
//                         dis[xx][yy] = d + 1;
//                         q.push({xx, yy});
//                         if (new_map[xx][yy] == '#') res += d + 1;
//                     }
//                 }
//             }
//             d++;
//         }
//     }
    
//     cout << res / 2 << endl;
// }



#include <bits/stdc++.h>

#define ll long long
#define pi pair<int, int>

using namespace std;

vector<string> input;
set<int> empty_rows;
set<int> empty_columns;
int factor = 1e6;
map<int, pi> pos;
int n, m;
int id = 0;

void index_empty_rows() {
    for (int i = 0; i < input.size(); i++) {
        bool empty = true;
        for (int j = 0; j < input[0].size(); j++) {
            if (input[i][j] != '.') {
                empty = false;
                break;
            }
        }
        if (empty) empty_rows.insert(i);
    }
}


void index_empty_columns() {
    for (int j = 0; j < input[0].size(); j++) {
        bool empty = true;
        for (int i = 0; i < input.size(); i++) {
            if (input[i][j] != '.') {
                empty = false;
                break;
            }
        }
        if (empty) empty_columns.insert(j);
    }
}

vector<pi> get_neighbors(int x, int y) {
    vector<pi> res;
    if (x-1 >= 0) res.push_back({x-1, y});
    if (y-1 >= 0) res.push_back({x, y-1});
    if (x+1 < n)  res.push_back({x+1, y});
    if (y+1 < m)  res.push_back({x, y+1});
    return res;
}

bool move_is_slow(pi start, pi end) {
    int x1 = start.first, y1 = start.second;
    int x2 = end.first, y2 = end.second;

    if (x2 - x1 == 1 && empty_rows.find(x1) != empty_rows.end()) return true;
    if (y2 - y1 == 1 && empty_columns.find(y1) != empty_columns.end()) return true;
    
    if (x2 - x1 == -1 && empty_rows.find(x2) != empty_rows.end()) return true;
    if (y2 - y1 == -1 && empty_columns.find(y2) != empty_columns.end()) return true;

    return false;
}

void solve() {
    // For part one, change factor to 2
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[0].size(); j++) {
            if (input[i][j] == '#') {
                pos[id] = {i, j};
                id++;
            }
        }
    }

    n = input.size();
    m = input[0].size();

    ll res = 0;
    for (int i = 0; i < id; i++) {
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        vector<vector<int>> dis(n, vector<int>(m, INT_MAX));

        pi p = pos[i];
        dis[p.first][p.second] = 0;

        queue<pi> q;
        q.push(p);

        while (!q.empty()) {
            pi node = q.front(); q.pop();
            int x = node.first, y = node.second;
            for (pi neighbor: get_neighbors(x, y)) {
                int xx = neighbor.first, yy = neighbor.second;
                int new_dis = dis[x][y] + (factor-1) * move_is_slow({x,y}, {xx,yy}) + 1;
                if (new_dis < dis[xx][yy]) {
                    dis[xx][yy] = new_dis;
                    q.push({xx, yy});
                    if (input[xx][yy] == '#') res += new_dis;
                }
            }
        }
    }

    std::cout << res / 2 << endl;
}


int main() {
    freopen("input.txt", "r", stdin);

    string line;
    while (getline(cin, line))
        input.push_back(line);
    
    index_empty_rows();
    index_empty_columns();

    solve();
}
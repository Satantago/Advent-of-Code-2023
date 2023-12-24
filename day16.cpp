#include <bits/stdc++.h>

#define ll long long
#define pl pair<long, long>

using namespace std;

enum Direction {
    LEFT = 0,
    RIGHT = 1,
    UP = 2,
    DOWN = 3
};

struct cell {
    int x;
    int y;
    char c;
    map<Direction, int> mp;

    cell(int x_val, int y_val,  char c_val)
        : x(x_val), y(y_val), c(c_val), mp({{LEFT, 0}, {RIGHT, 0}, {UP, 0}, {DOWN, 0}}) {
    }
    
} typedef cell;


vector<Direction> directions{LEFT, RIGHT, UP, DOWN};
vector<vector<cell>> input;

void parse_input() {
    FILE *fp=freopen("input16.txt","r",stdin);
    string line;
    int i = 0;
    while (getline(cin, line)) {
        vector<cell> row;
        for (int j = 0; j < line.size(); j++)
            row.emplace_back(i, j, line[j]);
        input.push_back(row);
    }
    fclose(fp);
}


void forward(vector<vector<cell>>& grid, int i, int j, Direction dir) {
    // STOP
    int n = grid.size(), m = grid[0].size();
    if (i < 0 || i >= n || j < 0 || j >= m) return;
    if ((grid[i][j].mp)[dir] > 0) return;

    (grid[i][j].mp)[dir]++;

    int x = i, y = j;
    if (dir == RIGHT)     y++;
    else if (dir == LEFT) y--;
    else if (dir == DOWN) x++;
    else if (dir == UP)   x--;

    char c = grid[i][j].c;
    if (c == '.') {
        forward(grid, x, y, dir);
        return;
    }
    else if (c == '|') {
        if (dir == UP || dir == DOWN) {
            (grid[i][j].mp)[dir]++;
            forward(grid, x, y, dir);
            return;
        }
        else {
            forward(grid, i+1, j, DOWN);
            forward(grid, i-1, j, UP);
            return;
        }
    }
    else if (c == '-') {
        if (dir == LEFT || dir == LEFT) {
            (grid[i][j].mp)[dir]++;
            forward(grid, x, y, dir);
            return;
        }
        else {
            forward(grid, i, j-1, LEFT);
            forward(grid, i, j+1, RIGHT);
            return;
        }
    }
    else if (c == '\\') {
        if (dir == LEFT) {
            forward(grid, i-1, j, UP);
        }
        else if (dir == RIGHT) {
            forward(grid, i+1, j, DOWN);
        }
        else if (dir == DOWN) {
            forward(grid, i, j+1, RIGHT);
        }
        else if (dir == UP) {
            forward(grid, i, j-1, LEFT);
        }
        return;
    }
    else if (c == '/') {
        if (dir == LEFT) {
            forward(grid, i+1, j, DOWN);
        }
        else if (dir == RIGHT) {
            forward(grid, i-1, j, UP);
        }
        else if (dir == DOWN) {
            forward(grid, i, j-1, LEFT);
        }
        else if (dir == UP) {
            forward(grid, i, j+1, RIGHT);
        }
        return;
    }
}

int count(vector<vector<cell>>& grid) {
    int res = 0;
    int n = grid.size(), m = grid[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cell c = grid[i][j];
            for (auto dir: directions) {
                if ((c.mp)[dir] > 0) {
                    res++;
                    break;
                }
            }
        }
    }
    return res;
}

int solve2(vector<vector<cell>> grid) {
    int n = grid.size(), m = grid[0].size();
    int res = 0;
    // top row
    for (int j = 0; j < m; j++) {
        vector<vector<cell>> copie(grid);
        forward(copie, 0, j, DOWN);
        res = max(res, count(copie));
    }

    // bottom row
    for (int j = 0; j < m; j++) {
        vector<vector<cell>> copie(grid);
        forward(copie, n-1, j, UP);
        res = max(res, count(copie));
    }

    // leftmost column
    for (int i = 0; i < n; i++) {
        vector<vector<cell>> copie(grid);
        forward(copie, i, 0, RIGHT);
        res = max(res, count(copie));
    }

    // rightmost column
    for (int i = 0; i < n; i++) {
        vector<vector<cell>> copie(grid);
        forward(copie, i, m-1, LEFT);
        res = max(res, count(copie));
    }

    return res;
}

int main() {
    parse_input();
    forward(input, 0, 0, RIGHT);
    cout << count(input) << endl;
    cout << solve2(input) << endl;
}
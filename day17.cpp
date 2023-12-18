#include <bits/stdc++.h>

#define ll long long
#define pl pair<long, long>
#define pi pair<int, int>

enum Direction {
    LEFT = 0,
    RIGHT = 1,
    UP = 2,
    DOWN = 3
};

using namespace std;

int nb_moves = 10;
int min_moves = 4;

vector<vector<int>> input;
int n, m;

void parse_input() {
    FILE *fp = freopen("input17.txt","r",stdin);
    string line;
    vector<string> lines;
    while (getline(cin, line)) {
        lines.push_back(line);
    }

    for (string s: lines) {
        // cout << s << endl;
        vector<int> intline;
        for (int i = 0; i < s.size(); i++)
            intline.push_back(int(s[i]) - int('0'));
        input.push_back(intline);
        intline.clear();
    }

    n = input.size();
    m = input[0].size();
    fclose(fp);
}

ll solve() {
    vector<Direction> directions{LEFT, RIGHT, UP, DOWN};
    ll d[n][m][4][nb_moves];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < 4; k++) {
                for (int p = 0; p < nb_moves; p++) {
                    d[i][j][k][p] = INT_MAX;
                }
            }
        }
    }
    for (int k = 0; k < 4; k++)
        for (int p = 0; p < nb_moves; p++)
            d[0][0][k][p] = 0;

    d[0][min_moves][RIGHT][min_moves-1] = 0;
    d[min_moves][0][DOWN][min_moves-1] = 0;
    for (int l = 1; l <= min_moves; l++) {
        d[0][min_moves][RIGHT][min_moves-1] += input[0][l];
        d[min_moves][0][DOWN][min_moves-1] += input[l][0];
    }

    bool went_back = true;
    while (went_back) {
        went_back = false;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i == 0 && j == 0) continue;
                // LET'S GO LEFT
                if (j-1 >= 0) {
                    for (int k = 0; k < nb_moves-1; k++) {
                        if (d[i][j-1][LEFT][k+1] > d[i][j][LEFT][k] + input[i][j-1]) {
                            went_back = true;
                            d[i][j-1][LEFT][k+1] = d[i][j][LEFT][k] + input[i][j-1];
                        }
                    }
                    vector<Direction> direc{DOWN, UP};
                    for (auto dir: direc) {
                        for (int k = min_moves-1; k < nb_moves; k++) {
                            if (j-min_moves >= 0) {
                                ll new_val = d[i][j][dir][k];
                                for (int l = 1; l <= min_moves; l++)
                                    new_val += input[i][j-l];
                                if (d[i][j-min_moves][LEFT][min_moves-1] > new_val) {
                                    went_back = true;
                                    d[i][j-min_moves][LEFT][min_moves-1] = new_val;
                                }
                            }
                        }
                    }
                }

                // LET'S GO RIGHT
                if (j+1 < m) {
                    for (int k = 0; k < nb_moves-1; k++) {
                        if (d[i][j+1][RIGHT][k+1] > d[i][j][RIGHT][k] + input[i][j+1]) {
                            went_back = true;
                            d[i][j+1][RIGHT][k+1] = d[i][j][RIGHT][k] + input[i][j+1];
                        }
                    }
                    vector<Direction> direc{DOWN, UP};
                    for (auto dir: direc) {
                        for (int k = min_moves-1; k < nb_moves; k++) {
                            if (j+min_moves < m) {
                                ll new_val = d[i][j][dir][k];
                                for (int l = 1; l <= min_moves; l++)
                                    new_val += input[i][j+l];
                                if (d[i][j+min_moves][RIGHT][min_moves-1] > new_val) {
                                    went_back = true;
                                    d[i][j+min_moves][RIGHT][min_moves-1] = new_val;
                                }
                            }
                        }
                    }
                }

                // LET'S GO DOWN
                if (i+1 < n) {
                    for (int k = 0; k < nb_moves-1; k++) {
                        if (d[i+1][j][DOWN][k+1] > d[i][j][DOWN][k] + input[i+1][j]) {
                            went_back = true;
                            d[i+1][j][DOWN][k+1] = d[i][j][DOWN][k] + input[i+1][j];
                        }
                    }
                    vector<Direction> direc{LEFT, RIGHT};
                    for (auto dir: direc) {
                        for (int k = min_moves-1; k < nb_moves; k++) {
                            if (i+min_moves < n) {
                                ll new_val = d[i][j][dir][k];
                                for (int l = 1; l <= min_moves; l++)
                                    new_val += input[i+l][j];
                                if (d[i+min_moves][j][DOWN][min_moves-1] > new_val) {
                                    went_back = true;
                                    d[i+min_moves][j][DOWN][min_moves-1] = new_val;
                                }
                            }
                        }
                    }
                }
                

                // LET'S GO UP
                if (i-1 >= 0) {
                    for (int k = 0; k < nb_moves-1; k++) {
                        if (d[i-1][j][UP][k+1] > d[i][j][UP][k] + input[i-1][j]) {
                            went_back = true;
                            d[i-1][j][UP][k+1] = d[i][j][UP][k] + input[i-1][j];
                        }
                    }
                    vector<Direction> direc{LEFT, RIGHT};
                    for (auto dir: direc) {
                        for (int k = min_moves-1; k < nb_moves; k++) {
                            if (i-min_moves >= 0) {
                                ll new_val = d[i][j][dir][k];
                                for (int l = 1; l <= min_moves; l++)
                                    new_val += input[i-l][j];
                                if (d[i-min_moves][j][UP][min_moves-1] > new_val) {
                                    went_back = true;
                                    d[i-min_moves][j][UP][min_moves-1] = new_val;
                                }
                            }
                        }
                    }
                }
                
            }
        }
    }

    ll res = INT_MAX; 
    for (auto dir: directions) {
        for (int k = min_moves-1; k < nb_moves; k++) {
            res = min(res, d[n-1][m-1][dir][k]);
        }
    }
    return res;
}



int main() {
    parse_input();
    min_moves = 1;
    nb_moves = 3;
    cout << solve() << endl;
    min_moves = 4;
    nb_moves = 10;
    cout << solve() << endl;
}
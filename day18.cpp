#include <bits/stdc++.h>

#define ll long long
#define pl pair<long, long>
#define pi pair<int, int>
#define pc pair<char, int>

using namespace std;

vector<pl> input;
int p = 0;
bool part2 = true;

void parse_input() {
    FILE *fp = freopen("input18.txt","r",stdin);
    string line;

    char c; int k; string color;

    int cur_x = 0, cur_y = 0;
    while (cin >> c >> k >> color) {
        if (part2) {
            k = stoll(color.substr(2,5), 0, 16);
            p += k;
            if (color[7] == '0') c = 'R';
            else if (color[7] == '1') c = 'D';
            else if (color[7] == '2') c = 'L';
            else  c = 'U';
        }
        if (c == 'U') cur_x -= k;
        else if (c == 'D') cur_x += k;
        else if (c == 'R') cur_y += k;
        else if (c == 'L') cur_y -= k;
        input.emplace_back(cur_x, cur_y);
    }
    fclose(fp);
}

ll compute_area(vector<pl>& inp) {
    ll res = 0;
    for (int i = 0; i < inp.size(); i++) {
        pl a = (i == 0) ? inp[inp.size()-1] : inp[i-1];
        pl b = inp[i];
        res += (a.first - b.first) * (a.second + b.second);
    }
    return abs(res) / 2;
}


int main() {
    parse_input();
    cout << compute_area(input) + p / 2 + 1 << endl;
}

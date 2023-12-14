#include <bits/stdc++.h>

#define ll long long

using namespace std;

ll nb_cycles = 1000000000;
vector<string> inp;

void parse_input() {
    FILE *fp=freopen("input14.txt","r",stdin);
    string line;
    while (getline(cin, line)) {
        inp.push_back(line);
    }
    fclose(fp);
}


void clear(queue<int> &q ){
   std::queue<int> empty;
   std::swap(q, empty);
}

vector<string> create_new_map(vector<string> input) {
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


vector<string> rotate_south(vector<string> v) {
    vector<string> ans;
    int n = v.size();
    for (int i = n-1; i >= 0; i--) 
        ans.push_back(v[i]);
    return ans;
}
vector<string> south(vector<string> v) {
    vector<string> new_v = rotate_south(v);
    vector<string> new_map_v = create_new_map(new_v);
    return rotate_south(new_map_v);
}

vector<string> rotate_west(vector<string> v) {
    int n = v.size(), m = v[0].size();
    string s(n, '.');
    vector<string> new_v(m, s);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int new_i = j;
            int new_j = n-1-i;
            new_v[new_i][new_j] = v[i][j];
        }
    }
    return new_v;
}
vector<string> west(vector<string> v) {
    vector<string> new_v = rotate_west(v);
    vector<string> new_map_v = create_new_map(new_v);
    return rotate_west(rotate_west(rotate_west(new_map_v)));
}

vector<string> rotate_east(vector<string> v) {
    return rotate_west(rotate_west(rotate_west(v)));
}
vector<string> east(vector<string> v) {
    vector<string> new_v = rotate_east(v);
    vector<string> new_map_v = create_new_map(new_v);
    return rotate_west(new_map_v);
}

vector<string> cycle(vector<string> input) {
    return east(south(west(create_new_map(input))));
}

ll solve(vector<string>& map) {
    ll ans = 0;
    int n = map.size(), m = map[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (map[i][j] == 'O')
                ans += n-i;
        }
    }
    return ans;
}

struct CompareVectors {
    bool operator()(const std::vector<std::string>& lhs, const std::vector<std::string>& rhs) const {
        return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }
};

struct VectorWithIndex {
    vector<string> vec;
    ll index;

    bool operator<(const VectorWithIndex& other) const {
        return std::lexicographical_compare(vec.begin(), vec.end(), other.vec.begin(), other.vec.end());
    }
};


ll solve2() {
    set<VectorWithIndex> set_cycles;
    VectorWithIndex v{inp, 0};
    set_cycles.insert(v);
    
    ll i = 1;
    vector<string> cur_cycle = cycle(inp);
    VectorWithIndex cur_cycle_ind{cur_cycle, i};
    while (set_cycles.find(cur_cycle_ind) == set_cycles.end()) {
        set_cycles.insert(cur_cycle_ind);
        i++;
        cur_cycle = cycle(cur_cycle);
        cur_cycle_ind = VectorWithIndex{cur_cycle, i};
    }

    VectorWithIndex old_matched = *set_cycles.find(cur_cycle_ind);

    nb_cycles -= old_matched.index;
    ll len_cycle = cur_cycle_ind.index - old_matched.index;
    nb_cycles = nb_cycles % len_cycle;
    
    for (int k = 0; k < nb_cycles; k++) {
        cur_cycle = cycle(cur_cycle);
    }

    ll ans = solve(cur_cycle);
    return ans;
}

int main() {
    parse_input();
    vector<string> new_map = create_new_map(inp);
    ll res1 = solve(new_map);
    cout << res1 << endl;

    ll res2 = solve2();
    cout << res2 << endl;
}
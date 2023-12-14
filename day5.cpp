#include <bits/stdc++.h>

#define ll long long
#define pi pair<int,int>
#define tl tuple<ll, ll, ll>

using namespace std;


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    freopen("input5.txt", "r", stdin);
    string line;

    getline(cin, line);
    stringstream ss(line);
    string tmp; ss >> tmp;

    vector<ll> seeds;
    ll seed;
    while (ss >> seed)
        seeds.push_back(seed);

    vector<tl> tuples;
    vector<ll> cur(seeds);

    getline(cin, line);
    while (getline(cin, line)) {
        if (line == "") {     
            // kan mochkil hna, 3mro kaydkhl bach y updati "cur" fach "\n"
            // kan aussi makayprocessich akhir level, so zedt ster khawi f lkhr d file
            // process the level
            vector<ll> new_numbers;
            for (ll nb: cur) {
                bool mapped = false;
                for (tl t: tuples) {
                    ll dest = get<0>(t), src = get<1>(t), range = get<2>(t);
                    if (nb >= src && nb < src + range) {
                        new_numbers.push_back(dest + (nb - src));
                        mapped = true;
                        break;
                    }
                }
                if (!mapped) new_numbers.push_back(nb);
            }

            // empty it for next
            tuples.clear();
            copy(new_numbers.begin(), new_numbers.end(), cur.begin());
        }

        else if (line[line.size()-1] == ':') {
            continue;
        }

        else {
            stringstream xyz(line);
            ll x,y,z;
            xyz >> x >> y >> z;
            tuples.push_back(make_tuple(x, y, z));
        }
    }
    cout << *min_element(cur.begin(), cur.end()) << endl;
}

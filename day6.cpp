#include <bits/stdc++.h>

#define ll long long
#define pl pair<long, long>

using namespace std;

ll ways(ll ti, ll di) {
    ll ans = 0;
    for (int i = 1; i <= ti; i++)
        if ((ti - i) > di / i)
            ans++;
    return ans;
}

ll solve(vector<ll> t, vector<ll> d) {
    ll res = 1;
    for (int i = 0; i < t.size(); i++)
        res *= ways(t[i], d[i]);
    return res;
}

int main() {
    vector<ll> t{44, 70, 70, 80};
    vector<ll> d{283, 1134, 1134, 1491};
    cout << solve(t, d) << endl;
    t = {44707080};
    d = {283113411341491ll};
    cout << solve(t, d) << endl;
}
#include <bits/stdc++.h>

#define ll long long

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    freopen("input99.txt", "r", stdin);

    string line;
    int res = 0, res2 = 0;
    while (getline(cin, line)) {
        stringstream ss(line);

        vector<int> nb;
        int number;

        while (ss >> number)
            nb.push_back(number);
        
        vector<int> mjhol;
        bool zero = false;
        // instanciation -> deep copy, assignment -> shallow copy
        vector<int> diff = nb;
        
        mjhol.push_back(diff[diff.size()-1]);

        res2 += diff[0];;
        int p = 1;
        while (!zero) {
            vector<int> new_diff(diff.size()-1, 0);
            for (int i = 0; i < diff.size() - 1; i++) {
                new_diff[i] = diff[i+1] - diff[i];
                if (new_diff[i] != 0) zero = true;
            }
            if (zero) {
                zero = false;
                mjhol.push_back(new_diff[new_diff.size()-1]);

                diff.pop_back();
                copy(new_diff.begin(), new_diff.end(), diff.begin());
                int m = p % 2;
                res2 += diff[0] * pow(-1, m);
                p++;
            }
            else break;
        }
        res += accumulate(mjhol.begin(), mjhol.end(), 0);
    }

    cout << "res1 = " << res << endl;
    cout << "res2 = " << res2 << endl;
}
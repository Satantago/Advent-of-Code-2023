#include <bits/stdc++.h>
// #include <sstream>

using namespace std;

unordered_set<int> readWinning(stringstream &ss) {
    unordered_set<int> winning;
    string tmp;
    while (ss >> tmp) {
        if (tmp == "|") break;
        winning.insert(stoi(tmp));
    }
    return winning;
}

int readCountRightGuesses(stringstream &ss, unordered_set<int> &winning) {
    int cnt = 0;
    int guess;
    while (ss >> guess) {
        cnt += winning.count(guess);
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    freopen("input4.txt", "r", stdin);

    string line;
    unordered_set<int> winning;
    int res = 0, res2 = 0;
    unordered_map<int, int> numberOfCopies;
    while (getline(cin, line)) {
        stringstream ss(line);  //instantiate
        string id;
        ss >> id >> id;
        int id_num = stoi(id);

        res2 += numberOfCopies[id_num] + 1;

        auto winning = readWinning(ss);
        int cnt = readCountRightGuesses(ss, winning);
        
        res += (cnt > 0 ? (1 << (cnt - 1)) : 0);

        for (int i = 1; i <= cnt; i++) {
            numberOfCopies[id_num + i] += numberOfCopies[id_num] + 1;
        }
    }
    cout << res << endl;
    cout << res2 << endl;

}



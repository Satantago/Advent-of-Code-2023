#include <bits/stdc++.h>

#define ll long long

using namespace std;

const string cards = "23456789TJQKA";
const string cards2 = "J23456789TQKA";

vector<pair<string, ll>> input;

int getRank(const string &hand) {
    map<char, int> cardCount;
    for (char card : hand) {
        cardCount[card]++;
    }

    if (cardCount.size() == 1) {
        return 6;  // 5 of a kind
    } else if (cardCount.size() == 2) {
        if (cardCount[hand[0]] == 4 || cardCount[hand[1]] == 4) {
            return 5;  // 4 of a kind
        }
        return 4;  // Full house
    } else if (cardCount[hand[0]] == 3 || cardCount[hand[1]] == 3 || cardCount[hand[2]] == 3) {
        return 3;  // 3 of a kind
    } else if (cardCount.size() == 3) {
        return 2;  // 2 pairs
    } else if (cardCount.size() == 4) {
        return 1;  // 1 pair
    }
    return 0;
}

int tryAllPossibilities(string &hand, int index) {
    if (index == 5) {
        return getRank(hand);
    }

    if (hand[index] != 'J') {
        return tryAllPossibilities(hand, index + 1);
    }

    int result = -1;
    for (int j = 1; j < cards2.length(); ++j) {
        hand[index] = cards2[j];
        result = max(result, tryAllPossibilities(hand, index + 1));
    }
    hand[index] = 'J';
    return result;
}

bool compareCards(const string &a, const string &b, const string &cardSet) {
    for (int i = 0; i < 5; ++i) {
        if (a[i] != b[i]) {
            return cardSet.find(a[i]) < cardSet.find(b[i]);
        }
    }
    return false;
}

bool compareHands(pair<string, ll> &a, pair<string, ll> &b, const string &cardSet) {
    int rankA = getRank(a.first), rankB = getRank(b.first);
    return (rankA != rankB) ? (rankA < rankB) : compareCards(a.first, b.first, cardSet);
}

bool compareHandsTryit(pair<string, ll> &a, pair<string, ll> &b, const string &cardSet) {
    int rankA = tryAllPossibilities(a.first, 0), rankB = tryAllPossibilities(b.first, 0);
    return (rankA != rankB) ? (rankA < rankB) : compareCards(a.first, b.first, cardSet);
}

ll calculateScore() {
    ll result = 0;
    for (int i = 0; i < input.size(); ++i) {
        result += input[i].second * (i + 1);
    }
    return result;
}

void parse_input() {
    string hand;
    ll handValue;
    while (cin >> hand >> handValue) {
        input.emplace_back(hand, handValue);
    }
}

int main() {
    FILE *fp = freopen("input7.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);

    parse_input();

    sort(input.begin(), input.end(), bind(compareHands, placeholders::_1, placeholders::_2, cards));
    cout << calculateScore() << "\n";

    sort(input.begin(), input.end(), bind(compareHandsTryit, placeholders::_1, placeholders::_2, cards2));
    cout << calculateScore() << "\n";

    fclose(fp);
}

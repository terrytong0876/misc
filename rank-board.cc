#include <iostream>
#include <set>
#include <unordered_map>
#include <utility>
using namespace std;

class Board {
    multiset<pair<int, int>> multiset;  // (score, id)
    unordered_map<int, int> hashmap;  // (id, score)
public:
    int addUser(int id, int score) {
        if (hashmap.find(id) != hashmap.end()) {
            int oldScore = hashmap[id];
            multiset.erase(multiset.find(make_pair(oldScore, id)));
        }
        hashmap[id] = score;
        auto itor = multiset.emplace(score, id);
        return distance(itor, multiset.end());
    }

    int findByRank(int rank) {
        if (rank <= 0 || rank > multiset.size()) {
            return -1;
        }
        auto itor = multiset.rbegin();
        for (int i = 0; i < rank - 1; ++i) {
            ++itor;
        }
        return itor->second;
    }
};


void test() {
    Board board;
    cout << board.addUser(1, 100);
    cout << board.addUser(1, 50);
    cout << board.addUser(3, 98);
    cout << board.findByRank(2);
}

int main() {
    test();
    cout << endl << "press ENTER to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return 0;
}

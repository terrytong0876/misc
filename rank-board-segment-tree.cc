#include <iostream>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <utility>
using namespace std;

struct SegmentTreeNode {
    int start, end, count;
    unordered_set<int> ids;
    SegmentTreeNode *left{nullptr}, *right{nullptr};

    SegmentTreeNode(int start, int end, int count)
        : start(start), end(end), count(count) {}
    
    virtual ~SegmentTreeNode() {
        delete left, left = nullptr;
        delete right, right = nullptr;
    }
};

class Board {
    SegmentTreeNode* root{nullptr};
    unordered_map<int, int> hashmap;  // (id, score)
    int minScore, maxScore;
public:
    const int kInvalidId{numeric_limits<int>::min()};

    Board(int minScore, int maxScore) 
        : minScore(minScore), maxScore(maxScore) {
        root = build(minScore, maxScore);
    }
    virtual ~Board() {
        delete root, root = nullptr;
    }

    int addUser(int id, int score) {
        if (score < minScore || maxScore < score) {
            return -1;
        }
        if (hashmap.count(id) != 0) {
            int oldScore = hashmap[id];
            modify(root, oldScore, -1, id);
        }
        hashmap[id] = score;
        modify(root, score, 1, id);
        return queryRank(root, score, maxScore);
    }

    int findByRank(int rank) {
        if (rank < 1 || rank > hashmap.size()) {
            return kInvalidId;
        }
        return queryIdWithRank(root, rank); 
    }
private:
    SegmentTreeNode* build(int start, int end) {
        if (start > end) {
            return nullptr;
        }
        auto root = new SegmentTreeNode(start, end, 0);
        if (start == end) {
            return root;
        }
        int mid = start + (end - start) / 2;
        root->left = build(start, mid);
        root->right = build(mid + 1, end);
        return root;
    }

    void modify(SegmentTreeNode* root, int score, int count, int id) {
        if (!root || score < root->start || root->end < score) {
            return;
        }
        if (root->start == score && root->end == score) {
            root->count += count;
            if (count > 0) {
                root->ids.emplace(id);
            } else if (count < 0) {
                root->ids.erase(id);
            }
            return;
        }
        modify(root->left, score, count, id);
        modify(root->right, score, count, id);
        int left = root->left ? root->left->count : 0;
        int right = root->right ? root->right->count : 0;
        root->count = left + right;
    }

    int queryRank(SegmentTreeNode* root, int start, int end) {
        if (!root || end < root->start || root->end < start) {
            return 0;
        }
        if (start <= root->start && root->end <= end) {
            return root->count;
        }
        int left = queryRank(root->left, start, end);
        int right = queryRank(root->right, start, end);
        return left + right;
    }

    int queryIdWithRank(SegmentTreeNode* root, int rank) {
        if (!root) {
            return kInvalidId;
        }
        if (root->start == root->end && rank <= root->count) {
            return !root->ids.empty() ? *root->ids.begin() : kInvalidId;
        }
        int right = root->right ? root->right->count : 0;
        if (root->right && rank <= right) {
            return queryIdWithRank(root->right, rank);
        }
        return queryIdWithRank(root->left, rank - right);
    }
};


void test() {
    Board board(0, 100);
    cout << board.addUser(2, 100) << endl;
    cout << board.addUser(1, 89) << endl;
    cout << board.addUser(3, 98) << endl;
    cout << board.findByRank(2) << endl;
}

int main() {
    test();
    cout << endl << "press ENTER to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return 0;
}

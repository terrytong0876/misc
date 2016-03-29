#include <list>
#include <stack>
#include <iostream>
#include <stdexcept>
#include <limits>
using namespace std;

struct NaryTreeNode {
    list<NaryTreeNode*> children;
    char val;
    NaryTreeNode(char val) : val(val) {}
    virtual ~NaryTreeNode() {
        for (auto& child : children) {
            delete child;
        }
    }
};

class Solution {
public:
    // construct NaryTree from string: "[A[B][C][D]]"
    NaryTreeNode* build(const string& str) {
        if (str.empty()) {
            return nullptr;
        }

        stack<pair<char, int>> tokenStack;  // (token, level)
        stack<pair<NaryTreeNode*, int>> nodeStack;  // (node, level)
        int level = 0;
        for (const char& token : str) {
            if (token == '[') {
                ++level;
                tokenStack.emplace(token, level);
            } else if (token == ']') {
                --level;
                if (!tokenStack.empty() && tokenStack.top().first == '[') {
                    tokenStack.pop();  // []
                    continue;
                }
                if (tokenStack.empty() || tokenStack.top().first == '[') {
                    throw runtime_error("invalid input");
                }
                auto root = new NaryTreeNode(tokenStack.top().first);
                int rootLevel = tokenStack.top().second;
                tokenStack.pop();  // A
                tokenStack.pop();  // [
                while (!nodeStack.empty() && nodeStack.top().second > rootLevel) {
                    NaryTreeNode* child = nodeStack.top().first;
                    nodeStack.pop();
                    root->children.emplace_front(child);
                }
                nodeStack.emplace(root, rootLevel);
            } else {  // A
                tokenStack.emplace(token, level);
            }
        }

        if (tokenStack.empty() && nodeStack.size() == 1) {
            return nodeStack.top().first;
        } else {
            throw runtime_error("invalid input");
        }
        return nullptr;
    }
};

void print(NaryTreeNode* root) {
    if (!root) {
        return;
    }

    cout << root->val << ": ";
    for (const auto& child : root->children) {
        if (!child) {
            continue;
        }
        cout << child->val << " ";
    }
    cout << endl;
    for (const auto& child : root->children) {
        print(child);
    }
}

void test() {
    Solution solution;
    auto root = solution.build("[A[B[E][F[X[Y][Z]]][G]][C][D][]]");
    print(root);
    delete root;
}

int main() {
    test();
    cout << endl << "press ENTER to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return 0;
}

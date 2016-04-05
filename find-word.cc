#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <limits>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<string> findWord(vector<vector<char>>& matrix, unordered_set<string>& dict) {
        if (matrix.empty() || dict.empty()) {
            return {};
        }
        vector<string> result;
        unordered_map<string, unordered_set<int>> hashmap;
        init(hashmap, matrix);
        for (const auto& word : dict) {
            if (memorySearch(matrix, word, hashmap)) {
                result.emplace_back(word);
            }
        }
        return result;
    }

    void init(unordered_map<string, unordered_set<int>>& hashmap, vector<vector<char>>& matrix) {
        for (int x = 0; x < matrix.size(); ++x) {
            for (int y = 0; y < matrix.size(); ++y) {
                hashmap[string(1, matrix[x][y])].emplace(x * matrix.size() + y);
            }
        }
    }

    bool memorySearch(vector<vector<char>>& matrix, const string& word, unordered_map<string, unordered_set<int>>& hashmap) {
        if (hashmap.count(word) != 0) {
            return true;
        }
        // 012
        // aab
        //   i
        int width = matrix.size();
        static const vector<int> dx{ 0, 0, 1, -1, 1, 1, -1, -1 };
        static const vector<int> dy{ 1, -1, 0, 0, 1, -1, 1, -1 };
        for (int i = (int)word.length() - 1; i >= 0; --i) {
            string postfix = word.substr(i);
            if (hashmap.count(postfix) == 0) {
                return false;
            }
            if (i - 1 < 0) {
                continue;
            }
            string nextPostfix = word.substr(i - 1);
            for (const auto& index : hashmap[postfix]) {
                int x = index / width;
                int y = index % width;
                for (int j = 0; j < dx.size(); ++j) {
                    int nx = x + dx[j];
                    int ny = y + dy[j];
                    if (nx < 0 || nx >= width || ny < 0 || ny >= width) {
                        continue;
                    }
                    if (matrix[nx][ny] == word[i - 1]) {
                        hashmap[nextPostfix].emplace(nx * width + ny);
                    }
                }  // for j
            }  // for index
        }  // for i
        return true;
    }
};

void test() {
    Solution solution;
    vector<vector<char>> matrix = {
        { 'a', 'b' }, {'a', 'c'}
    };
    unordered_set<string> dict = { "aaab", "cd", "a", "" };
    auto result = solution.findWord(matrix, dict);
    for (const auto& word : result) {
        cout << "\"" << word << "\" ";
    }
}

int main() {
    test();
    cout << endl << "press ENTER to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return 0;
}

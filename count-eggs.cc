#include <vector>
#include <iostream>
#include <limits>
#include <algorithm>
#include <tuple>
#include <queue>
using namespace std;

class Solution {
    int getNum(const tuple<int, int, int>& tuple) {
        return get<0>(tuple);
    }
    int getIndex(const tuple<int, int, int>& tuple) {
        return get<1>(tuple);
    }
    int getFactor(const tuple<int, int, int>& tuple) {
        return get<2>(tuple);
    }
public:
    // solution 1
    int getNumEggs() {
        static const vector<int> factors{3, 7, 9};
        int size = factors.size();
        vector<int> result;
        result.emplace_back(1);  // result[0]
        // (num, index, factor)
        static auto compare = [this](const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
            return getNum(a) > getNum(b);
        };
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, decltype(compare)> minheap(compare);
        for (const auto& factor : factors) {
            minheap.emplace(factor, 1, factor);
        }
        for (int i = 1; ; ++i) {
            result.emplace_back(getNum(minheap.top()));  // result[i]
            if (isValid(result[i])) {
                return result[i];
            }
            while (getNum(minheap.top()) == result[i]) {
                auto current = minheap.top();
                minheap.pop();
                minheap.emplace(getFactor(current) * result[getIndex(current)],
                                getIndex(current) + 1,
                                getFactor(current));
            }
        }
        return -1;
    }

    // solution 2
    int getNumEggs2() {
        static const vector<int> factors{3, 7, 9};  // bug: 1不能放进去
        int size = factors.size();
        vector<int> result, index(size);
        result.emplace_back(1);  // result[0]
        for (int i = 1; ; ++i) {
            result.emplace_back(INT_MAX);  // result[i]
            for (int j = 0; j < size; ++j) {
                result[i] = min(result[i], result[index[j]] * factors[j]);
            }
            for (int j = 0; j < size; ++j) {
                if (result[i] == result[index[j]] * factors[j]) {
                    ++index[j];
                }
            }
            if (isValid(result[i])) {
                return result[i];
            }
        }
        return -1;
    }
private:
    bool isValid(int num) {
        return num % 2 == 1 && num % 4 == 1 && num % 5 == 3 &&
            num % 6 == 3 && num % 8 == 1;
    }
};

void test() {
    Solution solution;
    cout << "num of eggs = " << solution.getNumEggs() << endl;
}

int main() {
    test();
    cout << endl << "press ENTER to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return 0;
}

#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <set>
#include <functional>
#include <cstdlib>
#include <stack>
#include <cctype>
#include <string>
#include <iostream>
#include <sstream>
#include <queue>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <map>
#include <ctime>
#include <mutex>
#include <set>
#include <thread>
#include <iostream>
#include <memory>
#include <vector>
#include <list>
using namespace std;

class Solution {
public:
    vector<string> binaryWatch() {
        vector<string> result;

        string watch = "0000000000";
        search(result, 0, watch, 0);

        return result;
    }
private:
    void search(vector<string>& result, int numOnes, string& watch, int pos) {
        if (numOnes == 3 && isValid(watch)) {
            result.emplace_back(watch);
            return;
        }
        if (pos >= watch.length() || numOnes >= 3) {
            return;
        }

        for (int i = pos; i < watch.length(); ++i) {
            watch[i] = '1';
            search(result, numOnes + 1, watch, i + 1);
            watch[i] = '0';
        }
    }

    bool isValid(const string& watch) {
        int hour = stoi(watch.substr(0, 4), nullptr, 2);
        int minute = stoi(watch.substr(4), nullptr, 2);

        return 1 <= hour && hour <= 12 && 
               0 <= minute && minute <= 59;
    }
};

void test() {
    Solution solution;
    auto result = solution.binaryWatch();
    for (const auto& str : result) {
        cout << str << endl;
    }
}

int main() {
    test();
    cout << endl << "press ENTER to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return 0;
}

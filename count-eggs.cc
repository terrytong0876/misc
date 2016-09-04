#include <iostream>
#include <limits>
using namespace std;

class Solution {
public:
    int getNumEggs() {
        // 63是3，7，9的最小公倍数(least common multiple)
        for (int i = 0; ; i += 63) {
            if (isValid(i)) {
                return i;
            }
        }
    }
    
    bool isValid(int num) {
        return num % 1 == 0 && num % 2 == 1 && num % 4 == 1 && 
            num % 5 == 4 && num % 6 == 3 && num % 8 == 1 && 
            num % 3 == 0 && num % 7 == 0 && num % 9 == 0;
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

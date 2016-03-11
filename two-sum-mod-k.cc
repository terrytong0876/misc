#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
  int twoSumModK(vector<int>& nums, int k) {
    if (nums.size() < 2 || 0 == k) {
      return 0;
    }

    transform(nums.begin(), nums.end(), nums.begin(), [k](int num) -> int {
      return num % k;
    });

    unordered_map<int, unordered_set<int>> hashmap;
    for (int i = 0; i < nums.size(); ++i) {
      hashmap[nums[i]].emplace(i);
    }

    int result = 0;

    auto twoSum = [&nums, &hashmap, &result](int target) {
      for (int i = 0; i < nums.size(); ++i) {
        if (hashmap.count(target - nums[i]) != 0) {
          for (int index : hashmap[target - nums[i]]) {
            if (i < index) {
              ++result;
            }
          }  // for index
        }
      }  // for i
    };

    twoSum(0);
    twoSum(k);

    return result;
  }
};

int main()
{
  Solution solution;
  auto test = [&solution](vector<int> nums, int k) {
    cout << "nums = { ";
    for (int num : nums) {
      cout << num << " ";
    }
    cout << "}, k = " << k << endl;
    cout << "num of pairs divisible by k in given array = " << solution.twoSumModK(nums, k) << endl << endl;
  };

  test({ -2, 1, 4 }, 0);
  test({ -2, 1, 4 }, 1);
  test({ -2, 1, 4 }, 2);

  return 0;
}

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
public:
	int twoSumModK(vector<int>& nums, int k) {
		if (nums.size() < 2 || 0 == k) {
			return 0;
		}

    // override array with mod k value
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

	int twoSumModKBrutalForce(vector<int>& nums, int k) {
		if (nums.size() < 2 || 0 == k) {
			return 0;
		}

		int result = 0;
		for (int i = 0; i < nums.size(); ++i) {
			for (int j = i + 1; j < nums.size(); ++j) {
				if ((nums[i] + nums[j]) % k == 0) {
					++result;
				}
			}
		}

		return result;
	}
};

int main() {
	Solution solution;

	auto test = [&solution](vector<int> nums, int k) {
		int result = solution.twoSumModK(nums, k);
		int resultBrutalForce = solution.twoSumModKBrutalForce(nums, k);
		cout << "nums = { ";
		for (int num : nums) {
			cout << num << " ";
		}
		cout << "}, k = " << k << endl;
		cout << "num of pairs divisible by k in given array = "
			   << result << endl;
		cout << "brutal force result = "
			   << resultBrutalForce << endl << endl;
		assert(result == resultBrutalForce);
	};

	test({ -2, 1, 4 }, 0);
	test({ -2, 1, 4 }, 1);
	test({ -2, 1, 4 }, 2);

	return 0;
}

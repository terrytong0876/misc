#include <iostream>
#include <sstream>
#include <deque>
#include <queue>
#include <vector>
#include <stdexcept>
#include <limits>
using namespace std;

class Queue {
  queue<double> queue;
public:
  Queue(const vector<double>& data) {
    for (const auto& num : data) {
      queue.emplace(num);
    }
  }
  double getNext() {
    double result = queue.front();
    queue.pop();
    return result;
  }
  bool hasNext() {
    return !queue.empty();
  }
};

class Timestamp {
public:
  vector<pair<double, double>> calculate(Queue& queue1, Queue& queue2) {
    vector<pair<double, double>> result;
    deque<double> deque1, deque2;
    auto checkNext = [&result](deque<double>& deque1, deque<double>& deque2, Queue& queue) -> bool {
      if (!queue.hasNext()) {
        return false;
      }
      double val = queue.getNext();
      deque1.emplace_back(val);
      while (!deque2.empty() && 
        deque2.front() < val &&
        val - deque2.front() >= 1.f) {
        deque2.pop_front();
      }
      for (const auto& timestamp : deque2) {
        if (fabs(val - timestamp) < 1.f) {
          result.emplace_back(val, timestamp);
        }
      }
      return true;
    };
    bool flip = true;
    bool hasNext = true;
    while (hasNext) {
      if (flip) {
        hasNext = checkNext(deque1, deque2, queue1) ||
                  checkNext(deque2, deque1, queue2);
      } else {
        hasNext = checkNext(deque2, deque1, queue2) ||
                  checkNext(deque1, deque2, queue1);
      }
      flip = !flip;
    }
    return result;
  }
};

void test() {
  Queue queue1({.2f, 1.4f, 3.f}), queue2({1.f, 1.1f, 3.5f});
  Timestamp timestamp;
  auto result = timestamp.calculate(queue1, queue2);
  for (const auto& pair : result) {
    cout << "(" << pair.first << ", " << pair.second << ") ";
  }
  cout << endl;
}

int main() {
  test();
  cout << endl << "press ENTER to continue...";
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  return 0;
}

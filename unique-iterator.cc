#include <vector>
#include <unordered_set>
#include <iostream>
#include <string>
#include <limits>
using namespace std;

template<class T>
class UniqueIterator {
    vector<T>& dataRef;
    unordered_set<T> history;
    typename vector<T>::iterator itor;
public:
    UniqueIterator(vector<T>& data)
        : dataRef(data) {
        itor = dataRef.begin();
    }
    bool hasNext() {
        while (itor != dataRef.end() && history.count(*itor) != 0) {
            ++itor;
        }
        return itor != dataRef.end();
    }
    T next() {
        T result = *itor++;
        history.emplace(result);
        return result;
    }
};

class MyUniqueIterator {
    UniqueIterator<string> itor1, itor2;
    unordered_set<string> history;
    bool hasNextItem{false};
    string nextItem;
public:
    MyUniqueIterator()
        : itor1(vector<string>()), itor2(vector<string>()) {}
    MyUniqueIterator(vector<string>& data1, vector<string>& data2)
        : itor1(data1), itor2(data2) {
        prepareNext();
    }
    virtual ~MyUniqueIterator() {}

    bool hasNext() {
        prepareNext();
        return hasNextItem;
    }

    string next() {
        string result = nextItem;
        hasNextItem = false;
        prepareNext();
        return result;
    }
private:
    void prepareNext() {
        if (hasNextItem) {
            return;
        }
        static auto prepare = [this](UniqueIterator<string>& itor) {
            while (!hasNextItem && itor.hasNext()) {
                nextItem = itor.next();
                if (history.count(nextItem) == 0) {
                    hasNextItem = true;
                    history.emplace(nextItem);
                }
            }
        };
        prepare(itor1);
        prepare(itor2);
    }
};


void test() {
    vector<string> strs1{"a", "b", "c"};
    vector<string> strs2{"a", "d", "c", "b"};
    MyUniqueIterator itor(strs1, strs2);
    while (itor.hasNext()) {
        cout << itor.next() << " ";
    }
}

int main() {
    test();
    cout << endl << "press ENTER to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return 0;
}

#include <list>

class WebLogger {
    list<int> history;
public:
    WebLogger() {}

    /**
     * @param timestamp an integer
     * @return void
     */
    void hit(int timestamp) {
        history.emplace_back(timestamp);
    }

    /**
     * @param timestamp an integer
     * @return an integer
     */
    int get_hit_count_in_last_5_minutes(int timestamp) {
        auto itor = lower_bound(history.begin(), history.end(), timestamp - 300 + 1);
        history.erase(history.begin(), itor);
        return history.size();
    }
};

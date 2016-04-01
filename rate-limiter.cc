class RateLimiter {
    // (event-key, (timestamp, count))
    unordered_map<string, map<int, int>> cache;
public:
    /**
     * @param timestamp the current timestamp
     * @param event the string to distinct different event
     * @param rate the format is [integer]/[s/m/h/d]
     * @param increment whether we should increase the counter
     * @return true of false to indicate the event is limited or not
     */
    bool isRatelimited(int timestamp, string& event, string& rate, bool increment) {
        int limit, lowerBound;
        if (!parseRate(timestamp, rate, limit, lowerBound)) {
            return false;
        }
        bool passed = countHistory(event, lowerBound) < limit;
        if (passed && increment) {
            ++cache[event][timestamp];  // add count for this time
        }
        return passed;
    }
private:
    bool parseRate(const int timestamp, const string& rate, int& limit, int& lowerBound) {
        static const unordered_map<char, int> k_time{
            {'s', 1}, {'m', 60}, {'h', 60 * 60}, {'d', 60 * 60 * 24}
        };
        auto pos = rate.find('/');
        if (pos == string::npos) {
            return false;
        }
        limit = stoi(rate.substr(0, pos));
        if (pos + 1 >= rate.length() || k_time.count(rate[pos + 1]) == 0) {
            return false;
        }
        lowerBound = timestamp - k_time.at(rate[pos + 1]) + 1;
        
        return true;
    }
    
    int countHistory(const string& event, const int lowerBound) {
        if (cache.count(event) == 0) {
            return 0;
        }
        int result = 0;
        const auto& time_count_bst = cache.at(event);
        auto itor = time_count_bst.lower_bound(lowerBound);
        for (; itor != time_count_bst.end(); ++itor) {
            result += itor->second;
        }
        return result;
    }
};

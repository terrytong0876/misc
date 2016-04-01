/**
 * Definition of Column:
 * class Column {
 * public:
 *     int key;
 *     String value;
 *     Column(int key, string value) {
 *         this->key = key;
 *         this->value = value;
 *    }
 * }
 */
class MiniCassandra {
    // (raw-key, (column-key, column-value))
    unordered_map<string, map<int, string>> data;
public:
    MiniCassandra() {}
    
    /**
     * @param raw_key a string
     * @param column_start an integer
     * @param column_end an integer
     * @return void
     */
    void insert(string raw_key, int column_key, string column_value) {
        data[raw_key][column_key] = column_value;
    }

    /**
     * @param raw_key a string
     * @param column_start an integer
     * @param column_end an integer
     * @return a list of Columns
     */
    vector<Column> query(string raw_key, int column_start, int column_end) {
        if (data.count(raw_key) == 0) {
            return {};
        }
        vector<Column> result;
        auto begin = data.at(raw_key).lower_bound(column_start);
        auto end = data.at(raw_key).upper_bound(column_end);
        for (auto itor = begin; itor != end; ++itor) {
            result.emplace_back(itor->first, itor->second);
        }
        return result;
    }
};

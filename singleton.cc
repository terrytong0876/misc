class Solution {
public:
    /**
     * @return: The same instance of this class every time
     */
    static Solution* getInstance() {
        static Solution* instance = nullptr;
        if (!instance) {
            instance = new Solution();
        }
        return instance;
    }
};

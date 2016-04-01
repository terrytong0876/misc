class Solution {
    int totalShards, shardsPerMachine;
    vector<int> shard_machine;
public:
    // @param n a positive integer
    // @param k a positive integer
    // @return a Solution object
    static Solution create(int totalShards, int shardsPerMachine) {
        static Solution* instance = nullptr;
        if (!instance) {
            instance = new Solution();
        }
        instance->totalShards = totalShards;
        instance->shardsPerMachine = shardsPerMachine;
        instance->shard_machine = move(vector<int>(totalShards, -1));
        return *instance;
    }

    // @param machine_id an integer
    // @return a list of shard ids
    vector<int> addMachine(int machine_id) {
        vector<int> result;
        for (int i = 0; i < shardsPerMachine; ) {
            int num = rand() % totalShards;
            if (shard_machine[num] == -1) {
                ++i;
                shard_machine[num] = machine_id;
                result.emplace_back(num);
            }
        }
        return result;
    }

    // @param hashcode an integer
    // @return a machine id
    int getMachineIdByHashCode(int hashcode) {
        while (true) {
            hashcode %= totalShards;
            if (shard_machine[hashcode] != -1) {
                return shard_machine[hashcode];
            }
            ++hashcode;
        }
    }
};

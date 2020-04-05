class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> powerSet;
        Generate(nums, 0, new vector<int>, powerSet);
        
        return powerSet;
    }
    
private:
    void Generate(vector<int>& set, int select, vector<int>* selected, vector<vector<int>>& powerSet){
        if(select == set.size()){
            powerSet.emplace_back(*selected);
            return;
        }
        
        Generate(set, select + 1, selected, powerSet);
        
        selected->emplace_back(set[select]);
        Generate(set, select + 1, selected, powerSet);
        selected->pop_back();
    }
};
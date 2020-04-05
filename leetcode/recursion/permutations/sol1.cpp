class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>>permutations;
        Generate(0, nums, permutations);
        
        return permutations;
    }
    
private:
    void Generate(int i, vector<int>& permutation, vector<vector<int>>& permutations){
        if(i == permutation.size() - 1){
            permutations.emplace_back(permutation);
            return;
        }
        
        for(int j = i; j < permutation.size(); j++){
            swap(permutation[i], permutation[j]);
            Generate(i + 1, permutation, permutations);
            swap(permutation[i], permutation[j]);
        }
    }
};
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        if(strs.empty()){
            return {};
        }
        auto cmp = [](const string& lhs, const string& rhs){
            string s1 = lhs, s2 = rhs;
            sort(s1.begin(), s1.end());
            sort(s2.begin(), s2.end());
            
            return s1 < s2;
        };
        sort(strs.begin(), strs.end(), cmp);
        
        vector<vector<string>> groups;
        vector<string> group = {strs[0]};
        for(int i = 0; i < strs.size() - 1; i++){
            if(cmp(strs[i], strs[i + 1])){
                groups.emplace_back(group);
                group.clear();
                group.emplace_back(strs[i + 1]);
            }else{
                group.emplace_back(strs[i + 1]);
            }
        }
        groups.emplace_back(group);
        group.clear();
        
        return groups;
    }
};
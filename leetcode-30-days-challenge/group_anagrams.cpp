// Solution 1
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

// Solution 2
class Solution {
private:
    string string_to_key(const string& s){
        vector<int> count(26);
        
        for(const char& ch : s){
            count[ch - 'a']++;
        }
        
        string key = "";
        for(int i = 0; i < 26; i++){
            key += to_string(count[i]) + "#";
        }
        return key;
    }
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        if(strs.empty()){
            return {};
        }
        unordered_map<string, vector<string>>map;
        
        for(const string& s : strs){
            map[string_to_key(s)].emplace_back(s);
        }
        
        vector<vector<string>> groups;
        for(const auto& pair : map){
            groups.emplace_back(pair.second);
        }
        
        return groups;
    }
};

// Solution 3
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        if(strs.empty()){
            return {};
        }
        unordered_map<string, vector<string>>map;
        
        for(const string& s : strs){
            string s_copy = s;
            sort(s_copy.begin(), s_copy.end());
            map[s_copy].emplace_back(s);
        }
        
        vector<vector<string>> groups;
        for(const auto& pair : map){
            groups.emplace_back(pair.second);
        }
        
        return groups;
    }
};
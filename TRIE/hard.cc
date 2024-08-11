#include <bits/stdc++.h>
using namespace std;

// construct string with minimum costs.
// https://leetcode.com/problems/construct-string-with-minimum-cost/description/
class Node_trie {
    public:
        Node_trie* links[26] = {nullptr};
        vector<int> flag;

        bool check_alpha(char ch) {
            return links[ch - 'a'] != nullptr;
        }

        void put_node(char ch) {
            links[ch - 'a'] = new Node_trie;
        }

        Node_trie* get_node(char ch) {
            return links[ch - 'a'];
        }

        vector<int>& get_vector() {
            return flag;
        }

        void node_end(int indx) {
            flag.push_back(indx);
        }
};

class Trie {
    public:
        Node_trie* root;
        Trie() {
            root = new Node_trie;
        }

        void insert(const string& word, int indx) {
            Node_trie* node = root;
            for (char ch : word) {
                if (!node->check_alpha(ch)) {
                    node->put_node(ch);
                }
                node = node->get_node(ch);
            }
            node->node_end(indx);
        }
};

int minimumCost(string target, vector<string>& words, vector<int>& costs) {
        ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
        Trie obj;
        int n = target.size();
        for (int i = 0; i < words.size(); i++) {
            obj.insert(words[i], i);
        }

        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;

        for (int i = 0; i < n; i++) {
            if (dp[i] == INT_MAX) continue;
            Node_trie* node = obj.root;
            for (int j = i; j < n; j++) {
                if (!node->check_alpha(target[j])) break;
                node = node->get_node(target[j]);
                for (int indx : node->get_vector()) {
                    int l = words[indx].size();
                    if (i + l <= n) dp[i + l] = min(dp[i + l], dp[i] + costs[indx]);
                }
            }
        }

        return dp[n] == INT_MAX ? -1 : dp[n];
}
//==============================================================================================================


//

//============================================================================================================
int main(){
    string target="abcdef"; 
    vector<string> words={"abdef","abc","d","def","ef"}; 
    vector<int> costs={100,1,1,10,5};

    cout<<minimumCost(target,words,costs);

}
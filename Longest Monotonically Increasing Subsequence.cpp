#include<bits/stdc++.h>
using namespace std;

// 回溯尋找所有的遞增子序列，且按順序儲存
void findLIS(vector<int>& arr, vector<int>& dp, vector<int>& seq, int idx, int len, vector<vector<int>>& results) {
    if (len == 0) 
	{
        results.push_back(seq);
        return;
    }
    
    for (int i = idx; i >= 0; --i) 
	{
        if (dp[i] == len && (seq.empty() || arr[i] < seq.back())) 
		{
            seq.push_back(arr[i]);
            findLIS(arr, dp, seq, i-1, len-1, results);
            seq.pop_back();
        }
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
        }

        // dp array to store the length of LIS ending at each position
        vector<int> dp(n, 1);

        // Fill dp array
        for (int i = 1; i < n; ++i) 
		{
            for (int j = 0; j < i; ++j) 
			{
                if (arr[i] > arr[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }

        // Find the maximum length of LIS
        int maxLength = *max_element(dp.begin(), dp.end());

        // Collect all LIS of maximum length
        vector<vector<int>> results;
        vector<int> seq;
        for (int i=n-1; i>=0; i--) {
            if (dp[i] == maxLength) 
			{
                seq.push_back(arr[i]);
                findLIS(arr, dp, seq, i-1, maxLength-1, results);
                seq.pop_back();
            }
        }

        // Sort results lexicographically and reverse to match output order
        for (auto& res : results) 
		{
            reverse(res.begin(), res.end());
        }
        sort(results.begin(), results.end());

        // Output the result
        cout << results.size() << endl;
        for (auto& res : results) {
            for (int i = 0; i < res.size(); i++) 
			{
                cout << res[i];
				if(i == res.size()-1) cout << endl;
				else cout << " ";
            }
        }
    }
    return 0;
}


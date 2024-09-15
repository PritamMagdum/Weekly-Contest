class Solution
{
public:
    long long maxScore(vector<int> &a, vector<int> &b)
    {
        int n = b.size();
        vector<vector<long long>> dp(5, vector<long long>(n + 1, LLONG_MIN));

        dp[0][0] = 0; // Base case: no elements chosen, score is 0

        for (int j = 1; j <= 4; j++)
        {
            long long maxVal = LLONG_MIN;
            for (int i = j; i <= n; i++)
            {
                maxVal = max(maxVal, dp[j - 1][i - 1]);
                dp[j][i] = max(dp[j][i], maxVal + (long long)a[j - 1] * b[i - 1]);
            }
        }

        long long result = LLONG_MIN;
        for (int i = 4; i <= n; i++)
        {
            result = max(result, dp[4][i]);
        }

        return result;
    }
};
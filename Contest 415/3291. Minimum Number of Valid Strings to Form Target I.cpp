void next_function(char S[], int n, int next[])
{
    next[0] = n;
    int j = 0, k = 1;
    while (1 + j < n && S[j] == S[1 + j])
        j++;
    next[1] = j;
    for (int i = 2; i < n; ++i)
    {
        int len = k + next[k] - 1;
        int l = next[i - k];
        if (l < len - i + 1)
            next[i] = l;
        else
        {
            int j = max(0, len - i + 1);
            while (S[i + j] == S[j] && i + j < n)
                j++;
            next[i] = j;
            k = i;
        }
    }
}
void extend_kmp(char S[], int n, char T[], int m, int next[], int lcp[])
{
    next_function(T, m, next);
    int j = 0, k = 0;
    while (j < min(n, m) && T[j] == S[j])
        ++j;
    lcp[0] = j;
    for (int i = 1; i < n; ++i)
    {
        int len = k + lcp[k] - 1;
        int l = next[i - k];
        if (l < len - i + 1)
            lcp[i] = l;
        else
        {
            int j = max(0, len - i + 1);
            while (i + j < n && j < m && S[i + j] == T[j])
                j++;
            lcp[i] = j;
            k = i;
        }
    }
}

const int N = 100007;

vector<int> lcp(string s, string t)
{
    static char S[N], T[N];
    static int next[N], lcp[N];
    int n = s.size();
    for (int i = 0; i < n; ++i)
    {
        S[i] = s[i];
    }
    int m = t.size();
    for (int i = 0; i < m; ++i)
    {
        T[i] = t[i];
    }
    extend_kmp(S, n, T, m, next, lcp);
    return vector<int>(lcp, lcp + n);
}

const int INF = 0x3F3F3F3F;
int a[N];

void add(int x, int y)
{
    ++x;
    while (x < N)
    {
        a[x] = min(a[x], y);
        x += x & -x;
    }
}

int getMin(int x)
{
    ++x;
    int ret = INF;
    while (x)
    {
        ret = min(ret, a[x]);
        x -= x & -x;
    }
    return ret;
}

class Solution
{
public:
    int minValidStrings(vector<string> &words, string target)
    {
        int n = words.size();
        vector<vector<int>> common(n);
        for (int i = 0; i < n; ++i)
        {
            common[i] = lcp(target, words[i]);
        }

        int len = target.size();
        for (int i = 0; i <= len + 10; ++i)
        {
            a[i] = INF;
        }
        vector<int> dp(len + 1, INF);
        dp[len] = 0;
        add(len, 0);
        for (int i = len - 1; i >= 0; --i)
        {
            int res = 0;
            for (int j = 0; j < n; ++j)
            {
                res = max(res, common[j][i]);
            }

            dp[i] = min(dp[i], getMin(i + res) + 1);
            assert(i + res <= len);
            add(i, dp[i]);
        }
        return dp[0] >= INF ? -1 : dp[0];
    }
};
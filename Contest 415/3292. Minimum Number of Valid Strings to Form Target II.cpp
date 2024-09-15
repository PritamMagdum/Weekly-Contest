#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops")
#define ALL(v) v.begin(), v.end()
#define For(i, _) for (int i = 0, i##end = _; i < i##end; ++i)             // [0,_)
#define FOR(i, _, __) for (int i = _, i##end = __; i < i##end; ++i)        // [_,__)
#define Rep(i, _) for (int i = (_) - 1; i >= 0; --i)                       // [0,_)
#define REP(i, _, __) for (int i = (__) - 1, i##end = _; i >= i##end; --i) // [_,__)
typedef long long ll;
typedef unsigned long long ull;
#define V vector
#define pb push_back
#define pf push_front
#define qb pop_back
#define qf pop_front
#define eb emplace_back
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
#define fi first
#define se second
const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}, inf = 0x3f3f3f3f, mod = 1e9 + 7;
const ll infl = 0x3f3f3f3f3f3f3f3fll;
template <class T>
inline bool ckmin(T &x, const T &y) { return x > y ? x = y, 1 : 0; }
template <class T>
inline bool ckmax(T &x, const T &y) { return x < y ? x = y, 1 : 0; }
int init = []()
{ return cin.tie(nullptr)->sync_with_stdio(false), 0; }();

vector<int> z_function(string s)
{
    int n = (int)s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i)
    {
        if (i <= r && z[i - l] < r - i + 1)
        {
            z[i] = z[i - l];
        }
        else
        {
            z[i] = max(0, r - i + 1);
            while (i + z[i] < n && s[z[i]] == s[i + z[i]])
                ++z[i];
        }
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

class Solution
{
public:
    int minValidStrings(vector<string> &a, string t)
    {
        int n = a.size();
        V<V<int>> z(n);
        For(i, n) z[i] = z_function(a[i] + '#' + t), z[i].erase(z[i].begin(), z[i].end() - t.size());
        int m = t.size();
        V<int> l(m + 1);
        iota(ALL(l), 0);
        For(i, m) For(j, n) ckmin(l[i + z[j][i]], i);
        Rep(i, m) ckmin(l[i], l[i + 1]);
        V<int> f(m + 1, inf);
        f[0] = 0;
        FOR(i, 1, m + 1)
        {
            if (l[i] == i)
                return -1;
            f[i] = f[l[i]] + 1;
        }
        return f.back();
    }
};
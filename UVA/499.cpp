#include <bits/stdc++.h>
using namespace std;

template<typename A, typename B>
ostream& operator<<(ostream& os, const pair<A, B>& p) {
    return os << '(' << p.first << ',' << p.second << ')';
}

template<
    typename Tc,
    typename T = typename enable_if<
        !is_same<string, Tc>::value,
        typename Tc::value_type
    >::value
>
ostream& operator<<(ostream& os, const Tc& v) {
    os << '{';
    for(auto& x : v) os << v << ',';
    return os << '}';
}

void dbg_out() {cerr << endl;}
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cerr << ' ' << H;
    dbg_out(T...);
}

#ifdef DEBUG
    #define dbg(...) cerr << "(" << #__VA_ARGS__ << "):"; dbg(__VA_ARGS__);
#else
    #define dbg(...)
#endif

#define all(x) x.begin(), x.end()
#define forn(i, n) for(int i = 0; i < n; i++)
#define MOD(n) (((n) % mod + mod) % mod)

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pii> vp;

const ll LN = 0, LM = 0, mod = 1;

void Solve() {
    string S;
    while (getline(cin, S)) {
        vi bucket(100);
        for(auto& s: S) {
            if ('A' <= s && s <= 'Z')
                bucket[s - 'A']++;
            if ('a' <= s && s <= 'z')
                bucket[s - 'a' + 26]++;
        }
        
        int max_freq = 0;
        for (auto& bi: bucket)
            max_freq = max(bi, max_freq);
        for (int i = 0; i < 26; i++)
            if (max_freq == bucket[i])
                cout << (char) (i + 'A');
        for (int i = 0; i < 26; i++)
            if (max_freq == bucket[i + 26])
                cout << (char) (i + 'a');
        cout << ' ' << max_freq << '\n';
    }
}

int main() {
    #ifdef DEBUG
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #else
        ios_base::sync_with_stdio(0); cin.tie(0);
    #endif

    int tc = 1;
    // cin >> tc;
    forn(i, tc)
        Solve();

    return 0;
}
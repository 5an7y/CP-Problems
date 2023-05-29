#include <bits/stdc++.h>
using namespace std;

template<typename A, typename B>
ostream& operator<<(ostream& os, const pair<A, B>& v) {
    return os << '(' << v.first << ',' << v.second << ')';
}

template <
    typename Tc,
    typename T = typename enable_if<
        !is_same<Tc, string>::value,
        typename Tc::value_type
    >::value
>
ostream& operator<<(ostream& os, const Tc& v) {
    os << '{';
    for (auto& x : v) os << v << ',';
    return os << '}';
}

void dbg_out() {cerr << endl;}
template<typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cerr << ' ' << H;
    dbg_out(T...);
}

#ifdef DEBUG
    #define dbg(...) cerr << '(' << #__VA_ARGS__ << "):"; dbg_out(__VA_ARGS_)
#else
    #define dbg(...)
#endif

#define forn(i, n) for(int i = 0; i < n; i++)
#define all(x) x.begin(), x.end()
#define MOD(x) (((x) % mod + mod) % mod)

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pii> vp;

const ll LN = 0, LM = 0, mod = 1;

void Solve() {
    int N, K;
    cin >> N >> K;
    vector<string> names(N);
    vl freq(N);
    priority_queue<pll, vector<pll>, greater<pll>> times;
    forn(i, N) {
        cin >> names[i] >> freq[i];
        times.push({freq[i], i}); 
    }

    while (K--) {
        auto[t, pos] = times.top();
        times.pop();
        cout << t << ' ' << names[pos] << '\n';
        times.push({t + freq[pos], pos});
    }
    return;
}

int main() {
    #ifdef DEBUG
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #else
        ios_base::sync_with_stdio(0); cin.tie(0);
    #endif

    int tc = 1;
    cin >> tc;
    forn(i, tc)
        Solve();
    return 0;
}
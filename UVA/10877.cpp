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
    >::type
>
ostream& operator<<(ostream& os, const Tc& v) {
    os << '{';
    for(auto& x : v) os << x << ',';
    return os << '}';
}

void dbg_out() {cerr << endl;}
template<typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cerr << ' ' << H;
    dbg_out(T...);
}

#ifdef DEBUG
    #define dbg(...) cerr << "(" << #__VA_ARGS__ << "):"; dbg_out(__VA_ARGS__) 
#else
    #define dbg(...)
#endif

#define forn(i, n) for(int i = 0; i < n; i++)
#define all(x) x.begin(),x.end()
#define MOD(x) (((x) % mod + mod) % mod)

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pii> vp;

const ll LN = 0, LM = 0, mod = 1;

void Solve(int caso) {
    int N, M;
    cin >> N >> M;
    cin.ignore();
    vector<string> A(N), B(M);
    for (auto& s : A) getline(cin, s);
    for (auto& s : B) getline(cin, s);
    
    vector<string> all_s(N * M);
    int i = 0;
    for (auto& s1 : A)
        for(auto& s2 : B)
            all_s[i++] = s1 + s2;
    sort(all(all_s));

    int count = 1;
    for (int i = 1; i < N * M; i++)
        count += all_s[i] != all_s[i - 1];
    
    cout << "Case " << caso+1 << ": " << count << '\n';
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
    forn(i, tc) Solve(i);

    return 0;
}
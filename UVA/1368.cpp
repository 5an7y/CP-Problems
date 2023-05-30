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

void dbg_out(){cerr << endl;}

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
#define all(x) x.begin(), x.end()
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
    int N, M;
    cin >> N >> M;
    vector<string> vec(N);
    for (auto& v : vec)
        cin >> v;

    ll error = 0;
    forn(i, M) {
        vi bucket(4);
        int maxi = 0;

        forn(j, N) {
            switch (vec[j][i]) {
                case 'A':
                    maxi = max(maxi, ++bucket[0]);
                    break;
                case 'T':
                    maxi = max(maxi, ++bucket[1]);
                    break;
                case 'G':
                    maxi = max(maxi, ++bucket[2]);
                    break;
                case 'C':
                    maxi = max(maxi, ++bucket[3]);
                    break;
            }
        }

        if (maxi == bucket[0]) cout << 'A';
        else if(maxi == bucket[3]) cout << 'C';
        else if(maxi == bucket[2]) cout << 'G';
        else cout << 'T';
        error += N - maxi;
    }

    cout << '\n' << error << '\n';
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
    forn(i, tc) Solve();


    return 0;
}
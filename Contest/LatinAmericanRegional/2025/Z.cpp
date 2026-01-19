#include <bits/stdc++.h>
using namespace std;

// --------------------------- Defines ------------------------------------- //
template < typename A, typename B>
ostream & operator <<( ostream &os , const pair <A, B> &p) {
    return os << '(' << p. first << "," << p. second << ')';
}

template <typename Tc ,
          typename T = typename enable_if <!is_same <Tc , string >::value,
                                              typename Tc::value_type>::type >
ostream & operator <<( ostream &os , const Tc &v) {
    os << '{';
    for ( const T &x : v) os << x << ',';
    return os << '}';
}

void dbg_out () { cerr << endl ; }
template < typename Head , typename ... Tail > void dbg_out ( Head H, Tail ... T) { cerr << ' ' << H; dbg_out (T...) ; }

#ifdef DEBUG
    #define dbg(...) cerr << "(" << #__VA_ARGS__ << "): ", dbg_out(__VA_ARGS__)
#else
    #define dbg(...) ((void)0)
#endif

#define all(x) (x).begin(), (x).end()
#define forn(i, n) for(int i = 0; i < n; i++)
#define MOD(n) ( ( ((n) % mod) + mod ) % mod)

typedef long long ll;
typedef long double ld;
typedef pair <int ,int > pii;
typedef pair <ll ,ll > pll;
typedef vector <int > vi;
typedef vector <ll > vl;
typedef vector <pii > vp;

// --------------------------- Constants ----------------------------------- //
const ll LN = 2000001, 
         LM = 0, 
         mod = (ll)(998244353);
// ------------------------- Your code ---------------------------------- //
struct ST {
    ST *l, *r;
    map<int, ll> qnty;
    bool pending;
    int pending_price, pending_time; 
    ll pending_qnty;

    ST() : l(nullptr), r(nullptr), pending(false) {}

    ~ST() {
        delete l;  
        delete r;
    }

    void propagate_pending() {
        ll prev = 0;
        if (!qnty.empty()) {
            auto it = qnty.end();
            it--;
            prev = it->second;
        }
        qnty[pending_time] = prev + pending_qnty;
    }
} *root;

int n, timer = 0;
vector<vi> tree;
vi tin, tout;
vp products;
vector<vi> LCA_table;

void add_st(
    ST *node, int l, int r,
    int price, ll quantity, int time
) {
    ll prev = 0;
    if (!(node->qnty).empty()) {
        auto it = (node -> qnty).end();
        it--;
        prev = it->second;
    }
    (node->qnty)[time] = prev + quantity;
    
    if (l == r) {
        return;
    }

    int m = (l + r) / 2;
    if (price <= m) {
        if (node -> l == nullptr) node -> l = new ST();
        add_st(node->l, l, m, price, quantity, time);
    } else {
        if (node -> r == nullptr) node -> r = new ST();
        add_st(node->r, m+1, r, price, quantity, time);
    }
}

ll get_quant_at_time(
    ST *node, int l, int r,
    int time, int price_l, int price_r
) {
    if (node == nullptr) return 0;
    if (price_l <= l && r <= price_r) {
        auto it = (node->qnty).upper_bound(time);
        if (it == (node->qnty).begin()) return 0;
        it--;
        return it -> second;
    }
    if (price_r < l || r < price_l) return 0;
    int m = (l + r) / 2;
    return get_quant_at_time(node->l, l, m, time, price_l, price_r)
    + get_quant_at_time(node->r, m + 1, r, time, price_l, price_r);
}

void init_dfs(int u, int p) {
    LCA_table[u][0] = p;
    tin[u] = ++timer;
    add_st(root, 1, 1000000000, products[u].second, products[u].first, timer);
    for (auto& it : tree[u]) if (it != p) init_dfs(it, u);
    tout[u] = ++timer;
    add_st(root, 1, 1000000000, products[u].second, -products[u].first, timer);
    return;
}

int get_kth_parent(int node, int k) {
    int d = 0;
    while (k) {
        if (k % 2 == 1) node = LCA_table[node][d];
        k /= 2;
        d++;
    }
    return node;
}

void Solve () {
    cin >> n;
    
    tree.resize(n);
    tin.resize(n);
    tout.resize(n);

    forn(i, n-1) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        tree[x].push_back(y);
        tree[y].push_back(x);
    }
    products.resize(n);
    for (auto& [x, y]: products)
        cin >> x >> y;

    root = new ST();
    const int logn = log2(n) + 2;
    LCA_table.resize(n, vi(logn));

    init_dfs(0, 0);

    for (int dist = 1; dist < logn; dist++) {
        for (int u = 0; u < n; u++) {
            LCA_table[u][dist] = LCA_table[LCA_table[u][dist-1]][dist-1];
        }
    }

    int q; cin >> q;
    ll ans = 0;
    while (q--) {
        ll _node, _dist, _price_lower, _price_upper;
        cin >> _node >> _dist >> _price_lower >> _price_upper;
        _node = (_node + ans) % n;
        _dist = (_dist + ans) % n;
        _price_lower = (_price_lower + ans) % 1000000000 + 1;
        _price_upper = (_price_upper + ans) % 1000000000 + 1;
        if (_price_upper < _price_lower) swap(_price_lower, _price_upper);

        int _kth_node = get_kth_parent(_node, _dist);
        int t_ini = tin[_kth_node] - 1;
        int t_out = tin[_node];
        ans = get_quant_at_time(root, 1, 1000000000, t_out, _price_lower, _price_upper)
            - get_quant_at_time(root, 1, 1000000000, t_ini, _price_lower, _price_upper);
        cout << ans << '\n';
    }

}

// --------------------------------------------------------------------- //
int main () {

#ifdef DEBUG
    freopen ("1input.txt", "r", stdin);
    freopen ("1output.txt", "w", stdout);
#else
    ios_base::sync_with_stdio(0);cin.tie(0);
#endif

    int Tc = 1;
    //cin >> Tc;
    forn (i, Tc)
        Solve ();
    
    return 0;
}
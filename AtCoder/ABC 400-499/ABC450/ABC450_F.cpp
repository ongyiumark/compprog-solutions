/* https://atcoder.jp/contests/abc450/tasks/abc450_f */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vll;

template <typename T, auto M>
struct ModInt {
  using V = conditional_t<sizeof(T) <= 4, uint64_t, __uint128_t>;
  static V inv(V x, V m) { 
    for (V a = exchange(x, 1), b = exchange(m, 0); b; a = exchange(b, a % b)) {
      x = exchange(m, x - (a / b) * m);
    }
    return x >= m ? x + m : x;
  }
  make_unsigned_t<T> x;
  ModInt() : x(0) {}
  ModInt(auto y) : x(y % M) { x >= M ? x += M : x; }
  operator T() const { return x; }
  ModInt operator-() const { return ModInt() -= *this; }
  ModInt operator+(auto rhs) const { return ModInt(*this) += rhs; }
  ModInt operator-(auto rhs) const { return ModInt(*this) -= rhs; }
  ModInt operator*(auto rhs) const { return ModInt(*this) *= rhs; }
  ModInt operator/(auto rhs) const { return ModInt(*this) /= rhs; }
  ModInt operator+=(ModInt rhs) { return (x += rhs.x) >= M ? x -= M : x, *this; }
  ModInt operator-=(ModInt rhs) { return (x -= rhs.x) >= M ? x += M : x, *this; }
  ModInt operator*=(ModInt rhs) { return x = x * V(rhs.x) % M, *this; }
  ModInt operator/=(ModInt rhs) { return x = x * inv(rhs.x, M) % M, *this; }
};

typedef ModInt<ll, 998244353> mint;

struct Edge {
  int u, v; ll w;
  Edge(int u, int v) : u(u), v(v), w(0) {}
  Edge(int u, int v, ll w) : u(u), v(v), w(w) {}
  Edge reverse() const { return Edge(v, u, w); }
};


struct SegmentTree {
  int n; vector<mint> st, lazy;
  SegmentTree(int n) : n(n), st(4*n), lazy(4*n, mint(1)) {}
  void pull(int p) { st[p] = st[p<<1] + st[p<<1|1]; } // addition query
  void push(int p, int i, int j) {
    if (lazy[p] != mint(1)) {
      st[p] *= lazy[p]; // multiplication update
      if (i != j) {
        lazy[p<<1] *= lazy[p];
        lazy[p<<1|1] *= lazy[p]; 
      } 
      lazy[p] = 1;
    }
  }
  void multiply(int l, int r, mint v) {
    multiply(l, r, v, 1, 0, n-1);
  }
  void multiply(int l, int r, mint v, int p, int i, int j) {
    push(p, i, j);
    if (l <= i && j <= r) {
      lazy[p] *= v;
      push(p, i, j);
    }
    else if (j < l || r < i) {}
    else {
      int k = (i+j)/2;
      multiply(l, r, v, p<<1, i, k);
      multiply(l, r, v, p<<1|1, k+1, j);
      pull(p);
    }
  } 
  void add(int idx, mint v) {
    add(idx, v, 1, 0, n-1);
  }
  void add(int idx, mint v, int p, int i, int j) {
    push(p, i, j);
    if (i == idx && j == idx) {
      st[p] += v;
      push(p, i, j);
    }
    else if (j < idx || idx < i) {}
    else {
      int k = (i+j)/2;
      add(idx, v, p<<1, i, k);
      add(idx, v, p<<1|1, k+1, j);
      pull(p);
    }
  }

  mint query(int l, int r) { return query(l, r, 1, 0, n-1); }
  mint query(int l, int r, int p, int i, int j) {
    push(p, i, j);
    if (l <= i && j <= r) { return st[p]; }
    else if (j < l || r < i) { return 0; }
    else {
      int k = (i+j)/2;
      return query(l, r, p<<1, i, k) + query(l, r, p<<1|1, k+1, j);
    } 
  }
};


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);


  int n, m; cin >> n >> m;
  vector<Edge> edges;
  for (int i = 0; i < m; i++) {
    int x, y; cin >> x >> y;
    edges.emplace_back(Edge(x, y));
  }
  sort(edges.begin(), edges.end(), [&](const Edge &lhs, const Edge& rhs){
    if (lhs.u == rhs.u) return lhs.v < rhs.v;
    return lhs.u < rhs.u; 
  });

  /*
    dp[i][r] = number of ways to choose edges from the first i such that the maximum vertex reachable from 1 is r
      = 2*dp[i-1][r], if r < u (choosing or not choosing the edge does not change the outcome)
      = dp[i-1][r], if u <= r < v (cannot choose this edge)
      = dp[i-1][r] + sum_{k=u}^{v} dp[i-1][k], if r = v (choosing this edge makes all u <= k <= v reachable)
      = 2*dp[i-1][r], if r > v (choosing or not choosing the edge does not change the outcome)
  */

  SegmentTree segtree(n+1);
  segtree.add(1, 1); // maximum reachable is 1 with no edges

  for (int j = 0; j < m; j++) {
    int u = edges[j].u, v = edges[j].v;
    if (1 <= u-1) segtree.multiply(1, u-1, 2); // multiply [1 ... u-1] by 2
    mint range_sum = segtree.query(u, v); // query sum [u ... v] and add to [v]
    segtree.add(v, range_sum);
    if (v+1 <= n) segtree.multiply(v+1, n, 2); // multiply [v+1 ... n] by 2
  }
  cout << segtree.query(n, n) << "\n";

  
  return 0;
}
/* https://atcoder.jp/contests/abc450/tasks/abc450_g */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vll;

// https://codeforces.com/blog/entry/134789
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

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n; cin >> n;
  vll A(n);
  for (ll &x : A) cin >> x;

  vector<mint> P(n), Q(n);
  for (ll &x : A) {
    P[n-1] += x;
    Q[n-1] += mint(x)*x; // sum of squares
  }
  P[n-1] = P[n-1]*P[n-1]; // square of sums

  for (ll i = n; i >= 2; i--) {
    P[i-2] = (mint(1)-mint(4)/i)*P[i-1];
    P[i-2] += mint(4)/i*Q[i-1];

    Q[i-2] = (mint(1)+mint(2)/i/(i-1))*Q[i-1];
    Q[i-2] -= mint(2)/i/(i-1)*P[i-1];
  }
  cout << P[0] << "\n";

  return 0;
}
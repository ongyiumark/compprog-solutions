/* https://atcoder.jp/contests/abc453/tasks/abc453_e */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vll;

const ll M = 998244353;
ll mod_pow(ll b, ll e) {
  ll ans = 1;
  while(e) {
    if (e&1) ans = ans*b%M;
    b = b*b%M;
    e >>= 1;
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n; cin >> n;
  vll fact(n+1), ifact(n+1);
  fact[0] = 1;
  for (int i = 1; i <= n; i++) fact[i] = i*fact[i-1]%M;

  ifact[n] = mod_pow(fact[n], M-2);
  for (int i = n-1; i >= 0; i--) ifact[i] = (i+1)*ifact[i+1]%M;


  vi L(n), R(n);
  for (int i = 0; i < n; i++) {
    cin >> L[i] >> R[i];
  }

  vi count_both(n+1), count_single(n+1);
  for (int i = 0; i < n; i++) {
    count_single[L[i]]++;
    count_single[R[i]+1]--;

    int x = max(L[i], n-R[i]);
    if (2*x > n) continue;

    count_both[x]++;
    count_both[n-x+1]--;
  }
  for (int i = 1; i <= n; i++) {
    count_single[i] += count_single[i-1];
    count_both[i] += count_both[i-1];
  }

  auto perm = [&](int n, int k) {
    return fact[n]*ifact[n-k]%M;
  };
  auto comb = [&](int n, int k) {
    if (n < k) return 0LL;
    return perm(n, k)*ifact[k]%M;
  };
  ll total = 0;
  for (int i = 1; i < n; i++) {
    int a = count_single[i];
    int b = count_both[i];
    int c = count_single[n-i];

    if (a < i) continue;
    if (c < n-i) continue;
    if (a+c-b < n) continue;
    total = (total + comb(b,i-(a-b)))%M;
  }
  cout << total << "\n";
  
  return 0;
}
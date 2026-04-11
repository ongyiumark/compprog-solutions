/* https://atcoder.jp/contests/abc453/tasks/abc453_c */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vll;

int count(vll &moves, int mask) {
  int n = moves.size();
  ll pos = 1;
  int cnt = 0;
  for (int i = 0; i < n; i++) {
    ll npos = pos;
    if ((mask >> i)&1) npos -= moves[i];
    else npos += moves[i];

    if (pos > 0 && npos <= 0) cnt++;
    if (pos <= 0 && npos > 0) cnt++;
    pos = npos;
  }
  return cnt;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n; cin >> n;
  vll L(n);
  for (ll &l : L) cin >> l;
  
  int ans = 0;
  for (int mask = 0; mask < (1 << n); mask++) {
    ans = max(ans, count(L, mask));
  }
  cout << ans << "\n";
  
  return 0;
}
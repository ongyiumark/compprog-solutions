/* https://codeforces.com/contest/2220/problem/C */
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vll;

void testcase() {
  int p, q; cin >> p >> q;
  bool valid = false;
  int ans_n = 0, ans_m = 0;
  for (int n = 1; n*(n+1) <= q+p/2; n++) {
    // n x n;
    int q_used = min(n*(n+1), q);
    int q_rem = q-q_used;

    int p_used = (n*(n+1)-q_used)*2;
    int p_rem = p-p_used;

    int cols = q_rem/n;
    p_rem -= q_rem/n;
    q_rem %= n;

    if (p_rem < 0) continue;
    if ((2*q_rem + p_rem)%(2*n+1) != 0) continue;
    valid = true;
    ans_n = n;
    ans_m = n+cols+(2*q_rem+p_rem)/(2*n+1);
    break;
  }

  if (!valid) cout << -1 << "\n";
  else cout << ans_n << " " << ans_m << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int t; cin >> t;
  while (t--) testcase();
  
  return 0;
}
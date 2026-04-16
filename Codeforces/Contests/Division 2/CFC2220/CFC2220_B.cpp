/* https://codeforces.com/contest/2220/problem/B */
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vll;

void testcase() {
  int n, m; cin >> n >> m;
  vi A(n);
  for (int &a : A) cin >> a;
  int consec = 0, curval = m;
  int longest = 0;
  for (int i = 0; i < n; i++) {
    if (A[i] == curval) consec++;
    else consec = 1;
    curval = A[i];
    longest = max(longest, consec);
  }

  if (longest >= m) cout << "NO\n";
  else cout << "YES\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int t; cin >> t;
  while (t--) testcase();
  
  return 0;
}
/*https://atcoder.jp/contests/abc453/tasks/abc453_b*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vll;


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int t, x; cin >> t >> x;
  vi A(t+1);
  for (int &a : A) cin >> a;
  vector<pair<int,int>> ans;
  ans.emplace_back(make_pair(0, A[0]));

  for (int i = 1; i <= t; i++) {
    if (abs(ans.back().second-A[i]) >= x) {
      ans.emplace_back(make_pair(i, A[i]));
    }
  }

  for (auto &[time, val] : ans) {
    cout << time << " " << val << "\n";
  }
  
  return 0;
}
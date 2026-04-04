/* https://atcoder.jp/contests/abc450/tasks/abc450_e */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vll;

const ll LIMIT = 1e18;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string x, y; cin >> x >> y;
  ll x_len = x.size(), y_len = y.size();
  
  vll fib;
  fib.emplace_back(x_len); fib.emplace_back(y_len);
  while (fib.back() < LIMIT) {
    ll next_fib = fib[(int)fib.size()-2] + fib[(int)fib.size()-1];
    fib.emplace_back(next_fib);
  }
  int fib_sz = fib.size();

  vector<vll> memo(26, vll(fib_sz));
  for (char c = 'a'; c <= 'z'; c++) {
    memo[c-'a'][0] = count(x.begin(), x.end(), c);
    memo[c-'a'][1] = count(y.begin(), y.end(), c);
    for (int i = 2; i < fib_sz; i++) {
      memo[c-'a'][i] = memo[c-'a'][i-1] + memo[c-'a'][i-2];
    }
  }

  int max_sz = 1e4;
  vector<string> starter = {x, y};
  vector<vector<vll>> memo2(26, vector(2, vll(max_sz+1)));
  for (char c = 'a'; c <= 'z'; c++) {
    for (int i = 0; i < 2; i++) {
      for (int j = 1; j <= starter[i].size(); j++) {
        memo2[c-'a'][i][j] = memo2[c-'a'][i][j-1] + (starter[i][j-1] == c);
      }
    }
  }


  function<ll(ll, char, int)> solve = [&](ll j, char c, int i) {
    if (j <= 0) return 0LL;
    if (j == fib[i]) return memo[c-'a'][i];
    if (i <= 1) return memo2[c-'a'][i][j];
    
    if (j <= fib[i-1]) return solve(j, c, i-1);
    else return solve(fib[i-1], c, i-1) + solve(j-fib[i-1], c, i-2);
  };
  
  int q; cin >> q;
  for (int j = 0; j < q; j++) {
    ll l, r; char c;
    cin >> l >> r >> c;
    cout << solve(r, c, fib_sz-1)-solve(l-1, c, fib_sz-1) << "\n";
  }



  return 0;
}
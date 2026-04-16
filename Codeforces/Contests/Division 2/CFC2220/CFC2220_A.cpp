/* https://codeforces.com/contest/2220/problem/A */
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vll;

void testcase() {
  int n; cin >> n;
  vi A(n);
  for (int &a : A) cin >> a;
  sort(A.begin(), A.end());
  reverse(A.begin(), A.end());
  bool valid = true;
  for (int i = 1; i < n; i++)
    if (A[i] == A[i-1]) valid = false;

  if (!valid) {
    cout << -1 << "\n";
    return;
  }

  for (int i = 0; i < n; i++) {
    cout << A[i] << " \n"[i+1==n];
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int t; cin >> t;
  while (t--) testcase();
  
  return 0;
}
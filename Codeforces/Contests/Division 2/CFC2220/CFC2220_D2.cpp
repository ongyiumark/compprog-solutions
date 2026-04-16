/* https://codeforces.com/contest/2220/problem/D2 */
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vll;

int query(const vi &s) {
  cout << "? " << s.size();
  for (int i = 0; i < (int)s.size(); i++) {
    cout << " " << s[i]+1;
  }
  cout << endl;

  int res; cin >> res;
  return res;
}

vi range(int l, int r) {
  vi res(r-l+1);
  for (int i = 0; i < r-l+1; i++) {
    res[i] = l+i;
  }
  return res;
}

int find_single(int l, int r, int n, bool is_left) {
  // if is_left is true, the remaining pair is in [r+1, 2*n]
  while (l < r) {
    int k = (l+r)>>1;
    if (is_left) {
      vi s = range(k+1, 2*n);
      int res = query(s);
      if (res == -1) return -1;
      int dup = (int)s.size()-res;
      
      if (dup&1) l = k+1; // single is in [k+1, r]
      else r = k;
    }
    else {
      vi s = range(0, k);
      int res = query(s);
      if (res == -1) return -1;
      int dup = (int)s.size()-res;

      if (dup&1) r = k; // single is in [l, k]
      else l = k+1;
    }
  }
  return l;
}

int find_last(int l, int r, int n, int first, int second) {
  while (l < r) {
    int k = (l+r)>>1;
    vi s = range(l, k);
    s.emplace_back(first);
    s.emplace_back(second);
    int res = query(s);
    if (res == -1) return -1;
    int dup = (int)s.size()-res;
    if (dup&1) r = k;
    else l = k+1;
  }

  return l;
}

pair<int,int> find_pair(int l, int r, int n, bool is_left, int first) {
  // if is_left is true, the single is in [0, l-1]
  while (l < r) {
    int k = (l+r)>>1;
    if (is_left) {
      vi sl = range(0, k);
      int resl = query(sl);
      if (resl == -1) return {-1, -1};
      int dupl = (int)sl.size()-resl;

      vi sr = range(k+1, 2*n);
      sr.emplace_back(first);
      int resr = query(sr);
      if (resr == -1) return {-1, -1};
      int dupr = (int)sr.size()-resr;

      if (dupl&1) r = k; // pair is in [l, k]
      else if (dupr&1) l= k+1; // pair is in [k+1, r]
      else {
        // pair is split between [l, k] and [k+1, r]
        int second = find_single(k+1, r, n, false);
        if (second == -1) return {-1, -1};
        int third = find_last(l, k, n, first, second);
        if (third == -1) return {-1, -1};
        return {second, third};
      }
    }
    else {
      vi sr = range(k+1, 2*n);
      int resr = query(sr);
      if (resr == -1) return {-1, -1};
      int dupr = (int)sr.size()-resr;

      vi sl = range(0, k);
      sl.emplace_back(first);
      int resl = query(sl);
      if (resl == -1) return {-1, -1};
      int dupl = (int)sl.size()-resl;

      if (dupr&1) l = k+1; // pair is in [k+1, r]
      else if (dupl&1) r = k; // pair is in [l, k]
      else {
        // pair is split between [l, k] and [k+1, r]
        int second = find_single(l, k, n, true);
        if (second == -1) return {-1, -1};
        int third = find_last(k+1, r, n, first, second);
        if (third == -1) return {-1, -1};
        return {second, third};
      }
    }
  }

  return {-1, -1};
}

int testcase() {
  int n; cin >> n;
  int l = 0, r = 2*n;
  
  // find triple
  while (l < r) {
    int k = (l+r)>>1;

    vi sl = range(0, k);
    int resl = query(sl);
    if (resl == -1) return -1;

    vi sr = range(k+1, 2*n);
    int resr = query(sr);
    if (resr == -1) return -1;

    int dupl = (k-0+1)-resl;
    int dupr = (2*n-(k+1)+1)-resr;

    if (dupl&1) r = k; // all three triplets are in [l, k]
    else if (dupr&1) l = k+1; // all three triplets are in [k+1, r]
    else {
      assert(resl != resr);
      // if resl > resr, one is in [l, k] and two are in [k+1, r]
      int first = (resl > resr ? find_single(l, k, n, true) : find_single(k+1, r, n, false));
      if (first == -1) return -1;
      pair<int,int> res_pair = (resl > resr ? find_pair(k+1, r, n, true, first) : find_pair(l, k, n, false, first));
      if (res_pair.first == -1) return -1;

      auto [second, third] = res_pair;
      cout << "! " << first+1 << " " << second+1 << " " << third+1 << endl;
      break;
    }
  }


  return 0;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int response = testcase();
    if (response == -1) break;
  }
  return 0;
}
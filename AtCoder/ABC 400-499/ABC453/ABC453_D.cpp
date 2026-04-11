/* https://atcoder.jp/contests/abc453/tasks/abc453_d */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vll;

const int MAXHW = 1000;
char grid[MAXHW][MAXHW];
const int di[4] = {0, 0, -1, 1};
const int dj[4] = {-1, 1, 0, 0};
const string dstr = "LRUD";
tuple<int,int,int> p[4][MAXHW][MAXHW]; // dir, i, j
bool vis[4][MAXHW][MAXHW];


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int h, w; cin >> h >> w;
  int si, sj, ti, tj, tk = -1;
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      cin >> grid[i][j];
      if (grid[i][j] == 'S') tie(si, sj) = {i, j};
      if (grid[i][j] == 'G') tie(ti, tj) = {i, j};
    }
  }

  // bfs
  queue<tuple<int,int,int>> q;
  q.push({0, si, sj});
  memset(p, -1, sizeof p);
  memset(vis, 0, sizeof vis);
  for (int k = 0; k < 4; k++) vis[k][si][sj] = true;

  while (!q.empty()) {
    auto [pk, ci, cj] = q.front();
    q.pop();
    if (ci == ti && cj == tj) {
      tk = pk;
      break;
    }

    // explore
    for (int k = 0; k < 4; k++) {
      if (grid[ci][cj] == 'o' && pk != k) continue;
      if (grid[ci][cj] == 'x' && pk == k) continue;

      int ni = ci+di[k];
      int nj = cj+dj[k];
      if (ni < 0 || ni >= h || nj < 0 || nj >= w) continue;
      if (grid[ni][nj] == '#' || vis[k][ni][nj]) continue;
      vis[k][ni][nj] = true;
      p[k][ni][nj] = {pk, ci, cj};
      q.push({k, ni, nj});
    }
  }

  if (tk == -1) {
    cout << "No\n";
    return 0;
  }

  tuple<int,int,int> state = {tk, ti, tj};
  string ans = "";
  while (!(get<1>(state) == si && get<2>(state) == sj)) {
    auto [ck, ci, cj] = state;
    tuple<int,int,int> pstate = p[ck][ci][cj];
    ans += dstr[ck];

    state = pstate;
  }
  reverse(ans.begin(), ans.end());
  cout << "Yes\n";
  cout << ans << "\n";
  
  return 0;
}
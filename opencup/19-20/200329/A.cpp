#include <bits/stdc++.h>
#define long long long int
using namespace std;

// @author: pashka

vector<int> f;

void init(int n) {
  f.assign(n + 1, 0);
}

long sum(int r) { // exclusive
  if (r == 0)
    return 0;
  r--;
  long result = 0;
  for (; r >= 0; r = (r & (r + 1)) - 1)
    result += f[r];
  return result;
}

void inc(int i) {
  for (; i < (int)f.size(); i = (i | (i + 1)))
    f[i] ++;
}

int sum(int l, int r) {
  return (r - l + 1) - (sum(r) - sum(l - 1));
}

vector<vector<int>> g;
vector<int> c;
vector<int> c2;
bool ok;

void dfs(int x, int s, int cc) {
  if (c[x] != -1) {
    if (c[x] != s) ok = false;
    return;
  }
  c[x] = s;
  c2[x] = cc;
  for (int y : g[x]) {
    if (y < 0) {
      dfs(-y, 1 - s, cc);
    } else {
      dfs(y, s, cc);
    }
  }
}

void solve_test() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> A(n, vector<int>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> A[i][j];
      A[i][j]--;
    }
  }
  int N = n * m;
  g.assign(N, vector<int>(0));
  for (int i = 0; i < n - 1; i++) {
    vector<int> &a = A[i];
    vector<int> &b = A[i + 1];
    vector<int> pa(m);
    vector<int> pb(m);
    for (int j = 0; j < m; j++) {
      pa[a[j]] = j;
      pb[b[j]] = j;
    }
    vector<bool> used(m);
    int k = 0;
    int l = 0;
    init(m);
    for (int j = 0; j < m; j++) {
      int x = pb[a[j]];
      used[x] = true;
      if (sum(x) > 0) {
        int u = i * m + j;
        int v = (i + 1) * m + x;
//                cout << u << " " << v << "\n";
        g[u].push_back(v);
        g[v].push_back(u);
      }
      inc(x);
      while (k < m && used[k]) k++;
//            cout << j << " " << x << " " << k << "\n";
      if (k < x) {
        int u = i * m + pa[b[k]];
        int v = (i + 1) * m + x;
//                cout << u << " " << v << " -- \n";
        g[u].push_back(-v);
        g[v].push_back(-u);
        while (l < m && used[l]) l++;
        while (l < x) {
          int ll = l + 1;
          while (ll < m && used[ll]) ll++;
          if (ll >= x) break;
          int u = i * m + pa[b[l]];
          int v = i * m + pa[b[ll]];
//                    cout << u << " " << v << "\n";
          g[u].push_back(v);
          g[v].push_back(u);
          l = ll;
        }
      }
    }
  }
  c.assign(N, -1);
  c2.assign(N, -1);
  long cnt = 1;
  ok = true;
  int cc = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 1; j < m; j++) {
      int x = i * m + j;
      if (c[x] == -1) {
        cnt = (cnt * 2) % 1000000007;
        dfs(x, 0, cc++);
      }
    }
  }
  if (!ok) {
    cout << 0 << "\n";
    return;
  }
  cout << cnt << "\n";
  vector<int> p(m);
  vector<int> &a = A[0];
  for (int j = 0; j < m; j++) {
    p[a[j]] = j;
  }
  vector<int> st(cc, -1);
  int l = m;
  vector<int> res(m);
  while (l > 0) {
    vector<int> stb(cc, -1);
    int best = -1;
    for (int i = l - 1; i >= 0; i--) {
      bool ok = true;
      if (i > 0) {
        if (st[c2[i]] != -1) {
          if (st[c2[i]] != c[i]) {
            ok = false;
          }
        }
        if (stb[c2[i]] != -1) {
          if (stb[c2[i]] != c[i]) {
            ok = false;
          }
        }
      }
      if (ok) {
        if (best == -1 || a[i] < a[best]) best = i;
      }

      ok = true;
      if (i > 0) {
        if (st[c2[i]] != -1) {
          if (st[c2[i]] != 1 - c[i]) {
            ok = false;
          }
        }
        if (stb[c2[i]] != -1) {
          if (stb[c2[i]] != 1 - c[i]) {
            ok = false;
          }
        }
      }
      if (ok) {
        stb[c2[i]] = 1 - c[i];
      } else {
        break;
      }
    }
//        cout << best << "\n";

    if (best > 0) {
      st[c2[best]] = c[best];
    }
    for (int i = best + 1; i < l; i++) {
      st[c2[i]] = 1 - c[i];
      res[i] = 1;
    }
    l = best;
  }
//    for (int x : res) cout << x << " ";
//    cout << "\n";

  vector<int> left;
  vector<int> right;
  for (int i = 0; i < m; i++) {
    if (res[i]) {
      right.push_back(a[i]);
    } else {
      left.push_back(a[i]);
    }
  }
  reverse(left.begin(), left.end());
  for (int x : left) cout << x + 1 << " ";
  for (int x : right) cout << x + 1 << " ";
  cout << "\n";

}

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
#endif
  ios::sync_with_stdio(false);

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    solve_test();
  }

  return 0;
}

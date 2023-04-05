#include <cstdio>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <cassert>

#define MIN_INT -2147483648
#define MAX_INT 2147483647
#define MIN_LONG -9223372036854775808L
#define MAX_LONG 9223372036854775807L
#define PI 3.141592653589793238462643383279502884L

#define long long long int

using std::vector;
using std::map;
using std::set;
using std::string;
using std::pair;
using std::cin;
using std::cout;
using std::cerr;

// @author: pashka

vector<vector<int>> g;
vector<bool> z;

int size(int x, int p) {
  int res = 1;
  for (int y : g[x]) {
    if (y != p && !z[y]) {
      res += size(y, x);
    }
  }
  return res;
}

int centroid;

int find_centroid(int x, int p, int n) {
  int res = 1;
  bool ok = true;
  for (int y : g[x]) {
    if (y != p && !z[y]) {
      int s = find_centroid(y, x, n);
      if (s > n / 2) ok = false;
      res += s;
    }
  }
  if (res < n / 2) ok = false;
  if (ok) {
    centroid = x;
  }
  return res;
}

vector<vector<pair<int, int>>> c;

int build_centroid(int x, int p) {
  int n = size(x, p);
  find_centroid(x, p, n);

  x = centroid;
//  cerr << "!!! " << x << std::endl;

  z[x] = true;

  for (int y : g[x]) {
    if (!z[y]) {
//      cerr << x << "-" << y << std::endl;
      c[x].push_back({y, build_centroid(y, x)});
    }
  }
  return x;
}

vector<int> s;

void calc_size(int x) {
  s[x] = 1;
  for (auto y : c[x]) {
    calc_size(y.second);
    s[x] += s[y.second];
  }
}

int main() {
  std::ios::sync_with_stdio(false);

  int n;
  cin >> n;

//  c.resize(n);
  g.resize(n);
  for (int i = 0; i < n - 1; i++) {
    int x, y;
    cin >> x >> y;
    x--;
    y--;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  z.resize(n);
  c.resize(n);
  int root = build_centroid(0, -1);

  s.resize(n);
  calc_size(root);

  int cnt = 0;
  int x = root;

  int q = 0;
  int p = 1;
  while (p < n) {
    p *= 2;
    q++;
  }
  q *= 4;

  while (true) {

    std::sort(c[x].begin(), c[x].end(), [](const pair<int, int> &a, const pair<int, int> &b) {
        return s[a.second] < s[b.second];
    });

    int nn = c[x].size();
    vector<int> ps(nn + 1);
    for (int i = 0; i < nn; i++) {
      ps[i + 1] = ps[i] + s[c[x][i].second];
    }

    if (c[x].size() == 0) {
      cout << "! " << x + 1 << std::endl;
      break;
    }

    cnt++;
    assert(cnt <= q);
    cout << "? " << nn << " " << (x + 1);
    for (int i = 0; i < nn; i++) {
      cout << " " << c[x][i].first + 1;
    }
    cout << std::endl;
    int ans;
    cin >> ans;
    if (ans == 1) {
      cout << "! " << x + 1 << std::endl;
      break;
    }

    int l = 0;
    int r = nn;
    while (r > l + 1) {
      int L = ps[l];
      int R = ps[r];
      int M = (L + R) / 2;
      int m = l + 1;
      for (int i = l + 1; i < r; i++) {
        if (abs(ps[i] - M) < abs(ps[m] - M)) m = i;
      }
      cnt++;
      assert(cnt <= q);
      cout << "? " << m << " " << (x + 1);
      for (int i = 0; i < m; i++) {
        cout << " " << c[x][i].first + 1;
      }
      cout << std::endl;
      int ans;
      cin >> ans;
      if (ans == 1) {
        l = m;
      } else {
        r = m;
      }
    }
    x = c[x][l].second;
  }

  return 0;
}

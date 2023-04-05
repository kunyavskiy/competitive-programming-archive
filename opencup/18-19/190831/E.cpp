#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <bitset>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl


using namespace std;

typedef long long ll;
typedef long double ld;

const int MAX = 65536;

vector<int> mx(MAX * 2), sz(MAX * 2);

void build(int n, int d, int l, int r) {
  double q = 1.0 / 6 + 5.0 / 6 * d / 16;
  mx[n] = ceil(q * (r - l));
  if (r - l > 1) {
    int m = (l + r) / 2;
    build(2 * n + 1, d + 1, l, m);
    build(2 * n + 2, d + 1, m, r);
  }
}

int bd, bdl, bdr;

bool add(int x, int n, int l, int r, int dd) {
  if (r - l > 1) {
    int m = (l + r) / 2;
    bool ok = true;
    if (x < m) {
      ok &= add(x, 2 * n + 1, l, m, dd);
    } else {
      ok &= add(x, 2 * n + 2, m, r, dd);
    }
    if (!ok) {
      bd = n;
      bdl = l;
      bdr = r;
    }
  }
  sz[n] += dd;
  return sz[n] <= mx[n];
}

int find(int k, int n, int l, int r) {
  if (r - l == 1)
    return l;
  int m = (l + r) / 2;
  if (k < sz[2 * n + 1]) {
    return find(k, 2 * n + 1, l, m);
  } else {
    return find(k - sz[2 * n + 1], 2 * n + 2, m, r);
  }
}

void iterate(vector<int> &res, int n, int l, int r) {
  if (sz[n] == 0) return;
  if (r - l == 1) {
    res.push_back(l);
    if (sz[n] > 1) {
      res.push_back(l);
    }
    return;
  }
  int m = (l + r) / 2;
  iterate(res, 2 * n + 1, l, m);
  iterate(res, 2 * n + 2, m, r);
}

int qqq = 0;
int mmm = 0;

void insert(int k) {
  int x = k;//find(k, 0, 0, MAX);
  bd = -1;
  add(x, 0, 0, MAX, 1);
  vector<int> a;
  int n = bd;
  int l = bdl;
  int r = bdr;
  iterate(a, n, l, r);
  for (int t: a) {
    add(t, 0, 0, MAX, -1);
  }
  vector<int> from;
  vector<int> to;
  for (int i = 0; i < (int)a.size(); i++) {
    from.push_back(a[i]);
    to.push_back(l + (r - l) * i / a.size());
    add(l + (r - l) * i / a.size(), 0, 0, MAX, 1);
  }
  int xx = 0;
  for (int i = 1; i < (int)from.size(); i++) {
    if (from[i] == x && from[i - 1] == x) {
      xx = to[i];
      from.erase(from.begin() + i, from.begin() + i + 1);
      to.erase(to.begin() + i, to.begin() + i + 1);
    }
  }
  int nn = 0;
  for (int i = 0; i < (int)from.size(); i++) {
    if (from[i] != to[i]) {
      nn++;
    }
  }
  cout << xx << " " << nn << " ";
  for (int i = 0; i < (int)from.size(); i++) {
    if (from[i] != to[i]) {
      cout << from[i] << " " << to[i] << " ";
    }
  }
  qqq += nn;

  mmm++;
  assert(qqq <= 100 * mmm);

  cout << endl;
}

int main() {

  build(0, 0, 0, MAX);

  add(0, 0, 0, MAX, 1);
//  for (int i = 0; i < 10000; i++) {
//    insert(0);
//  }
  while (true) {
    int x = 0;
    cin >> x;
    if (x == -1) break;
    insert(x);
  }
  return 0;
}

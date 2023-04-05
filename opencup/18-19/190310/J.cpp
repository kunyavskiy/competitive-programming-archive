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

#ifdef LOCAL

static struct __timestamper {
  string what;

  __timestamper(const char *what) : what(what) {};

  __timestamper(const string &what) : what(what) {};

  ~__timestamper() {
    TIMESTAMPf("%s", what.data());
  }
} __TIMESTAMPER("end");

#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

vector<int> z_function(const vector<int> &s) {
  int n = (int) s.size();
  vector<int> z(n);
  for (int i = 1, l = 0, r = 0; i < n; ++i) {
    if (i <= r)
      z[i] = min(r - i + 1, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]])
      ++z[i];
    if (i + z[i] - 1 > r)
      l = i, r = i + z[i] - 1;
  }
  return z;
}

void output_tandem(const vector<int>&s, int shift, bool left, int cntr, int l, int l1, int l2) {
  int pos;
  if (left)
    pos = cntr - l1;
  else
    pos = cntr - l1 - l2 - l1 + 1;
  cout << "[" << shift + pos << ".." << shift + pos + 2 * l - 1 << "] = [";
  for (int i = 0; i < 2 * l; i++) {
    cout << s[pos + i];
  }
  cout << "]" << endl;
}

struct seg {
  int l, r, k;
};

vector<seg> ss;

void output_tandems(const vector<int> &s, int shift, bool left, int cntr, int l, int k1, int k2) {
  int ll = 1;
  int rr = l;
  if (left) {
    rr--;
  }
  ll = max(ll, l - k2);
  rr = min(rr, k1);
//
//  ss.push_back({ll, rr, k});

//  l1 = ll .. rr
//  l2 = l - l1
//  int pos;
//  if (left)
//    pos = cntr - l1;
//  else
//    pos = cntr - l1 - l2 - l1 + 1;

  for (int l1 = ll; l1 <= rr; ++l1) {
    output_tandem(s, shift, left, cntr, l, l1, l - l1);
  }
}

inline int get_z(const vector<int> &z, int i) {
  return 0 <= i && i < (int) z.size() ? z[i] : 0;
}

vector<int> substr(vector<int> &a, int l, int s) {
  vector<int> res(s);
  for (int i = 0; i < s; i++) {
    res[i] = a[l + i];
  }
  return res;
}

vector<int> concat(vector<int> &a, vector<int> &b) {
  vector<int> res(a.size() + b.size() + 1);
  for (int i = 0; i < (int)a.size(); i++) {
    res[i] = a[i];
  }
  res[a.size()] = -1;
  for (int i = 0; i < (int)b.size(); i++) {
    res[a.size() + 1 + i] = b[i];
  }
  return res;
}

vector<int> reverse(vector<int> &a) {
  vector<int> res = a;
  reverse(res.begin(), res.end());
  return res;
}

void find_tandems(vector<int> s, int shift = 0) {
  int n = (int) s.size();
  if (n == 1) return;

  int nu = n / 2, nv = n - nu;
  vector<int> u = substr(s, 0, nu);
  vector<int> v = substr(s, nu, nv);

  vector<int> ru = reverse(u);
  vector<int> rv = reverse(v);

  find_tandems(u, shift);
  find_tandems(v, shift + nu);

  vector<int> z1 = z_function(ru),
    z2 = z_function(concat(v, u)),
    z3 = z_function(concat(ru, rv)),
    z4 = z_function(v);
  for (int cntr = 0; cntr < n; ++cntr) {
    int l, k1, k2;
    if (cntr < nu) {
      l = nu - cntr;
      k1 = get_z(z1, nu - cntr);
      k2 = get_z(z2, nv + 1 + cntr);
    } else {
      l = cntr - nu + 1;
      k1 = get_z(z3, nu + 1 + nv - 1 - (cntr - nu));
      k2 = get_z(z4, (cntr - nu) + 1);
    }
    if (k1 + k2 >= l)
      output_tandems(s, shift, cntr < nu, cntr, l, k1, k2);
  }
}

void solve_test() {
  int n;
  scanf("%d", &n);
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  find_tandems(a);
}

int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    solve_test();
  }

  return 0;
}

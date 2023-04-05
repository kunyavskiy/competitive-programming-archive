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
#include <iomanip>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl


using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char* what) : what(what){};
  __timestamper(const string& what) : what(what){};
  ~__timestamper(){
    TIMESTAMPf("%s", what.data());
	}
} __TIMESTAMPER("end");
#else 
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

struct SuffixArray {

  string s;
  int n;
  vector<int> c, cc, p, pp, cnt, lcp;

  void sort() {
    fill(cnt.begin(), cnt.end(), 0);
    for (int i = 0; i < n; i++) {
      cnt[c[i] + 1]++;
    }
    for (int i = 1; i < (int)cnt.size(); i++) {
      cnt[i] += cnt[i - 1];
    }
    for (int i = 0; i < n; i++) {
      pp[cnt[c[p[i]]]++] = p[i];
    }
    p.swap(pp);
  }

  SuffixArray(string _s) {
    s = _s + "$";
    n = s.length();
    c.resize(n);
    p.resize(n);
    cc.resize(n);
    pp.resize(n);
    cnt.resize(max(n, 256) + 1);
    for (int i = 0; i < n; i++) {
      p[i] = i;
      c[i] = s[i];
    }
    sort();
    for (int k = 1; k < n; k *= 2) {
      for (int i = 0; i < n; i++) {
        p[i] -= k;
        if (p[i] < 0) p[i] += n;
      }
      sort();
      int cl = 0;
      for (int i = 0; i < n; i++) {
        if (i > 0) {
          int x1 = p[i - 1];
          int y1 = p[i];
          int x2 = x1 + k;
          if (x2 >= n) x2 -= n;
          int y2 = y1 + k;
          if (y2 >= n) y2 -= n;
          if (c[x1] < c[y1] || (c[x1] == c[y1] && c[x2] < c[y2]))
            cl++;
        }
        cc[p[i]] = cl;
      }
      c.swap(cc);
    }
    // Kasai
    lcp.resize(n - 1);
    int q = 0;
    for (int i = 0; i < n - 1; i++) {
      q = max(q - 1, 0);
      while (s[i + q] == s[p[c[i] - 1] + q])
        q++;
      lcp[c[i] - 1] = q;
    }
  }

};

vector<int> l, r;
int get(int x) {
  if (l[x] != x) l[x] = get(l[x]);
  return l[x];
}

void inc(vector<int> &f, int x) {
  while (x < (int)f.size()) {
    f[x]++;
    x = x | (x + 1);
  }
}

ll sum(vector<int> &f, int r) {
  r--;
  ll res = 0;
  while (r >= 0) {
    res += f[r];
    r = (r & (r + 1)) - 1;
  }
  return res;
}

ll sum(vector<int> &f, int l, int r) {
  return sum(f, r) - sum(f, l);
}

int main() {
#ifdef LOCAL
  freopen("p9.in", "r", stdin);
  freopen("p9.out", "w", stdout);
#endif

  static char buf[200001];
  scanf("%s", buf);
  string a = buf;
  scanf("%s", buf);
  string b = buf;

  string s = a + "#" + b;
  SuffixArray sa(s);

//  cerr << sa.s << "\n";
//  for (int i : sa.p) {
//    cerr << i << " ";
//  }
//  cerr << "\n";
//  for (int i : sa.c) {
//    cerr << i << " ";
//  }
//  cerr << "\n";
//  for (int i : sa.lcp) {
//    cerr << i << " ";
//  }
//  cerr << "\n";

  vector<pair<int, int>> mg;
  for (int i = 0; i < (int)sa.lcp.size(); i++) {
    mg.push_back({sa.lcp[i], i});
  }
  sort(mg.rbegin(), mg.rend());


  int na = a.size();
  int nb = b.size();

  int mgc = 0;

  int n = sa.p.size();
  l.resize(n);
  r.resize(n);
  for (int i = 0; i < (int)l.size(); i++) l[i] = r[i] = i;

  vector<vector<int>> f(2, vector<int>(n));

  ll c0 = 0;
  ll c1 = 0;
  int n0 = 0;
  int n1 = 0;
  cout << setprecision(20);

  vector<pair<double, double>> res;

  for (int len = max(na, nb); len >= 1; len--) {
//    db(len);
    while (mgc < (int)mg.size() && mg[mgc].first >= len) {
      int x = mg[mgc++].second;
      int y = x + 1;

//      db(x);

      x = get(x);
      y = get(y);

      ll s0l = sum(f[0], l[x], r[x] + 1);
      ll s1l = sum(f[1], l[x], r[x] + 1);
      ll s0r = sum(f[0], l[y], r[y] + 1);
      ll s1r = sum(f[1], l[y], r[y] + 1);

      c0 -= s0l * s1r;
      c1 -= s1l * s0r;

      r[x] = r[y];
      l[y] = x;
    }
    if (len <= na) {
      int x = sa.c[na - len];
      inc(f[0], x);
      c1 += sum(f[1], 0, l[get(x)]);
      c0 += sum(f[1], r[get(x)] + 1, n);
      n0++;
    }
    if (len <= nb) {
      int x = sa.c[na + nb + 1 - len];
      inc(f[1], x);
      c0 += sum(f[0], 0, l[get(x)]);
      c1 += sum(f[0], r[get(x)] + 1, n);
      n1++;
    }
//    db2(c0, c1)
//    db2(n0, n1)
    if (n0 > 0 && n1 > 0) {
      double q0 = 1.0 * c0 / n0 / n1;
      double q1 = 1.0 * c1 / n0 / n1;
      res.push_back({q0, q1});
    }
  }
  reverse(res.begin(), res.end());
  for (auto p : res) {
    double q0 = p.first;
    double q1 = p.second;
    cout << q0 << " " << 1 - q0 - q1 << " " << q1 << "\n";
  }

  return 0;
}

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
#include <random>

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

const ll MOD = 998244353;

int p[500005];
int l[500005];
int r[500005];
int s[500005];

int get(int x) {
  if (p[x] != x) p[x] = get(p[x]);
  return p[x];
}

void join(int x, int y) {
  x = get(x);
  y = get(y);
//  assert(x != y);
  if (x == y) return;
  if (s[x] > s[y]) swap(x, y);
  p[x] = y;
  l[y] = min(l[x], l[y]);
  r[y] = max(r[x], r[y]);
  s[y] += s[x];
}

int solve_fast(vector<int> &a, int c) {
  int n = a.size();
  vector<pair<int, int>> b(n);
  for (int i = 0; i < n; i++) {
    b[i] = {a[i], i};
  }
  sort(b.begin(), b.end());
  for (int i = 0; i < n; i++) {
    p[i] = l[i] = r[i] = i;
    s[i] = 1;
  }
  ll res = 1;

  set<int> z;
  z.insert(-1);
  z.insert(n);
  for (int i = 0; i < n; i++) {
    int x = b[i].second;
    int xx = get(x);
    res *= s[xx];
    s[xx]--;
    res %= MOD;
    auto p = z.lower_bound(l[xx]);
    --p;
    int ll = max(l[xx], *p + c + 1);
    p = z.lower_bound(r[xx] + 1);
    int rr = min(r[xx], *p - c - 1);
    if (ll <= r[xx]) {
      while (true) {
        int y = r[get(ll - c)] + 1;
        if (y <= ll - 1) {
          join(y - 1, y);
        } else {
          break;
        }
      }
      if (l[xx] != r[xx]) join(ll - 1, ll);
    }
    if (rr >= l[xx]) {
      while (true) {
        int y = r[get(rr + 1)] + 1;
        if (y <= rr + c) {
          join(y - 1, y);
        } else {
          break;
        }
      }
      if (l[xx] != r[xx]) join(rr, rr + 1);
    }
    z.insert(x);
  }
  return res;
}

int solve_slow(vector<int> a, int c) {
  set<vector<int>> z;
  vector<vector<int>> q;
  q.push_back(a);
  z.insert(a);
  int n = a.size();
  for (int i = 0; i < (int)q.size(); i++) {
    for (int j = 0; j + c < n; j++) {
      a = q[i];
      int mn = a[j];
      for (int k = 1; k <= c; k++) {
        mn = min(mn, a[j + k]);
      }
      if (a[j] == mn) {
        sort(a.begin() + j + 1, a.begin() + j + c + 1);
        do {
          if (z.find(a) == z.end()) {
            z.insert(a);
            q.push_back(a);
          }
        } while (next_permutation(a.begin() + j + 1, a.begin() + j + c + 1));
      }
    }
    for (int j = c; j < n; j++) {
      a = q[i];
      int mn = a[j];
      for (int k = 1; k <= c; k++) {
        mn = min(mn, a[j - k]);
      }
      if (a[j] == mn) {
        sort(a.begin() + j - c, a.begin() + j);
        do {
          if (z.find(a) == z.end()) {
            z.insert(a);
            q.push_back(a);
          }
        } while (next_permutation(a.begin() + j - c, a.begin() + j));
      }
    }
  }
  return z.size();
}

void solve_test() {
  int n, c;
  scanf("%d%d", &n, &c);
  vector<int> a(n);
  for (int i = 0; i< n; i++) {
    scanf("%d", &a[i]);
  }
  cout << solve_fast(a, c) << "\n";
}



mt19937 rnd;

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
//
//  while (true) {
//    double start = clock() / (double)CLOCKS_PER_SEC;
//
//    int n = 2 + rnd() % 6;
//    int c = 2 + rnd() % 5;
//    vector<int> a(n);
//    for(int i = 0; i < n; i++) a[i] = i + 1;
//    for (int i = 0; i < n; i++) {
//      int j = rnd() % (i + 1);
//      swap(a[i], a[j]);
//    }
//    int s1 = solve_fast(a, c);
//    double finish = clock() / (double)CLOCKS_PER_SEC;
//    cerr << s1 << " " << finish - start << "\n";
//    int s2 = solve_slow(a, c);
//    if (s1 != s2) {
//      cout << n << " " << c << "\n";
//      for (int x : a) cout << x << " ";
//      cout << "\n" << s1 << " " << s2 << "\n";
//      break;
//    }
//    cerr << ".";
//  }
//
//
//  return 0;
  while (true) {
    double start = clock() / (double)CLOCKS_PER_SEC;

    int n = 500000;//2 + rnd() % 6;
    int c = 2 + rnd() % 500000;
    vector<int> a(n);
    for(int i = 0; i < n; i++) a[i] = i + 1;
    for (int i = 0; i < n; i++) {
      int j = rnd() % (i + 1);
      swap(a[i], a[j]);
    }
    int s1 = solve_fast(a, c);
    double finish = clock() / (double)CLOCKS_PER_SEC;
    cerr << s1 << " " << finish - start << "\n";
//    int s2 = solve_slow(a, c);
//    if (s1 != s2) {
//      cout << n << " " << c << "\n";
//      for (int x : a) cout << x << " ";
//      cout << "\n" << s1 << " " << s2 << "\n";
//      break;
//    }
    cerr << ".";
  }

  return 0;
}

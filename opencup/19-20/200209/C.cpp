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

pair<vector<int>, vector<int>> buildSufArray(vector<int> s) {
  int n = s.size();
  int sigma = *max_element(s.begin(), s.end()) + 1;
  vector<int> cnt(max(sigma, n));
  vector<int> p(n), pn(n), c(n), cn(n), o(n), lcp(n);

  for (int i = 0; i < n; i++) cnt[(int)s[i]]++;
  for (int i = 1; i < sigma; i++) cnt[i] += cnt[i - 1];
  for (int i = n - 1; i >= 0; i--) p[--cnt[s[i]]] = i;
  int cl = 1;
  c[p[0]] = 0;
  for (int i = 1; i < n; i++) {
    cl += s[p[i]] != s[p[i - 1]];
    c[p[i]] = cl - 1;
  }

  for (int len = 1; len < n; len <<= 1) {
    cnt.assign(cl, 0);
    for (int i = 0; i < n; i++) cnt[c[i]]++;
    for (int i = 1; i < cl; i++) cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; i++) pn[i] = (p[i] - len + n) % n;
    for (int i = n - 1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i];
    cl = 1;
    cn[p[0]] = 0;
    for (int i = 1; i < n; i++) {
      cl += c[p[i]] != c[p[i - 1]] || c[(p[i] + len) % n] != c[(p[i - 1] + len) % n];
      cn[p[i]] = cl - 1;
    }
    c.swap(cn);
  }

  for (int i = 0; i < n; i++) o[p[i]] = i;

  int z = 0;
  for (int i = 0; i < n; i++) {
    int j = o[i];
    if (j == n - 1) {
      z = 0;
    } else {
      while (s[i + z] == s[p[j + 1] + z]) z++;
    }
    lcp[j] = z;
    z -= !!z;
  }
  return {p, lcp};
}

pair<vector<int>, vector<int>> buildSufArray(string s) {
  vector<int> a(s.length());
  for (int i = 0; i < (int)s.length(); i++) a[i] = s[i];
  return buildSufArray(a);
}

char buf[100001];

void solve_test() {

  scanf("%s", buf);
  string a = buf;
  scanf("%s", buf);
  string b = buf;

  string c = a + b + "$";
  auto[p, lcp] = buildSufArray(c);
  int n = c.size() - 1;
  vector<pair<int,int>> s;
  s.push_back({1, n});
  ll res = 0;
  for (int ii = 0; ii < n + 1; ii++) {
    int i = p[ii];
    if (i < (int)a.size()) {
      int t = (int)a.size() - i + 1;
      int mx = n - i;
      while ((int)s.size() > 0 && s.back().second >= t) {
        if (s.back().first >= t) {
          res += min(mx, s.back().second) - s.back().first + 1;
          s.pop_back();
        } else {
          res += min(mx, s.back().second) - t + 1;
          s.back().second = t - 1;
          break;
        }
      }
    }
//    cout << i << " " << res << "\n";
//    for (auto p : s) {
//      cout << p.first << "-" << p.second << " ";
//    }
//    cout << "\n";
    int t = lcp[ii] + 1;
    while (true) {
      if (s.empty() || s.back().second < t) {
        s.push_back({t, n});
        break;
      }
      if (s.back().first <= t) {
        s.back().second = n;
        break;
      }
      s.pop_back();
    }
//    for (auto p : s) {
//      cout << p.first << "-" << p.second << " ";
//    }
//    cout << "\n\n";
  }
  cout << res << "\n";
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    solve_test();
  }


  return 0;
}

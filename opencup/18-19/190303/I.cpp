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

struct my_heap {
  multiset<ll> s1;
  multiset<ll> s2; // s2 <= s1
  ll sum1;

  my_heap() : sum1(0) {}

  void add(ll x) {
    if (s1.empty() || x >= *s1.begin()) {
      s1.insert(x);
      sum1 += x;
    }
    else s2.insert(x);
  }

  ll get(int k) {
    k = min(k, (int)s1.size() + (int)s2.size());
    while ((int)s1.size() < k) {
      ll x = *s2.rbegin();
      auto it = s2.end();
      s2.erase(--it);
      s1.insert(x);
      sum1 += x;
    }
    while ((int)s1.size() > k) {
      ll x = *s1.begin();
      s1.erase(s1.begin());
      sum1 -= x;
      s2.insert(x);
    }
    return sum1;
  }

  void del(ll x) {
    if (s1.find(x) != s1.end()) s1.erase(s1.find(x)), sum1 -= x;
    else if (s2.find(x) != s2.end()) s2.erase(s2.find(x));
    else assert(0);
  }

  int size() const {
    return s1.size() + s2.size();
  }
};


string solve(string s, int k) {
  s += "$";
  int n = s.length();
  auto o = buildSufArray(s);
  auto p = o.first;
  vector<int> rev(n);
  for (int i = 0; i < n; i++) rev[p[i]] = i;


  string res = "";
  int cur = 0;
  for (char c = 'z'; c >= 'a'; c--) {
    while (s[cur] == c) {
      res += s[cur++];
    }

    int cnt = 0;
    for (int i = cur + 1; i < n; i++) {
      cnt += s[i] == c && s[i - 1] != c;
    }

    if (cnt <= k) {
      for (int i = cur; i < n; i++) {
        if (s[i] == c) {
          res += c;
          cur = i + 1;
          k -= (i > cur && s[i] == c && s[i - 1] != c);
        }
      }
      k -= cnt;
      assert(k >= 0);
      continue;
    }

    if (k == 0) {
      res += s.substr(cur, n - 1 - cur);
      break;
    }


    vector<pair<int, int>> v;
    for (int i = cur; i < n; i++) {
      if (s[i] == c && s[i + 1] != c) {
        int cnt = 0;
        while (i - cnt >= cur && s[i - cnt] == c) cnt++;

        v.push_back({cnt, i + 1});
      }
    }

    vector<pair<int, int>> cand;
    my_heap h;
    for (int i = 0; i < (int)v.size(); i++) {
      cand.push_back({h.get(k - 1) + v[i].first, rev[v[i].second]});
      h.add(v[i].first);
    }

    auto o = *max_element(cand.begin(), cand.end());

    while (o.first--) res += c;
    for (int i = p[o.second]; i < n - 1; i++) res += s[i];
    break;
  }
  return res;
}

string slow(string s, int k) {
  int n = s.length();
  string res = "";
  for (int mask = 0; mask < (1 << n); mask++) {
    vector<char> a(n);
    for (int i = 0; i < n; i++) a[i] = (mask & (1 << i)) != 0;

    string cur = "";
    for (int i = 0; i < n; i++) if (a[i]) cur += s[i];

    int cost = 0;
    for (int i = 0; i < n; i++) if (!a[i] && (i == 0 || a[i - 1])) cost++;

    if (cost <= k) res = max(res, cur);
  }
  return res;
}

void stress() {
  for (int it = 89;; it++) {
    cerr << it << endl;
    srand(it);

    int n = rand() % 10 + 1;
    int k = rand() % n + 1;
    string s = "";
    for (int i = 0; i < n; i++) s += (char)('a' + rand() % 4);

    auto ans1 = solve(s, k);
    auto ans2 = slow(s, k);
    if (ans1 != ans2) {
      cout << ans1 << " instead of " << ans2 << endl;
      cout << s << " " << k << endl;
      exit(0);
    }
  }
}

int main() {
#ifdef LOCAL
  freopen("i.in", "r", stdin);
//  freopen("i.out", "w", stdout);
#endif
//  stress();

  int T;
  scanf("%d", &T);
  while (T--) {
    int k;
    static char buf[1111111];
    scanf("%d %s", &k, buf);

    printf("%s\n", solve(buf, k).c_str());
  }

  return 0;
}

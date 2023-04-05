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

char s[51'000];

const int MOD = 1000000007;

void add(int &a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

void sub(int &a, int b) {
  if ((a -= b) < 0) a += MOD;
}

int mul(int a, int b) {
  return (int) ((a * 1LL * b) % MOD);
}

int mpow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) res = mul(res, a);
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

int minv(int x) {
  return mpow(x, MOD - 2);
}

int main() {
#ifdef LOCAL
  freopen("g.in", "r", stdin);
  freopen("g.out", "w", stdout);
#endif

  int k;
  while (scanf("%s%d", s, &k) == 2) {
    int n = strlen(s);
    unordered_map<int, int> dps;

    auto encode = [&](const vector<int> &a, int shift) {
      int res = 0;
      for (int i = a.size() - 1; i > 0; i--) {
        res = res * 8 + min(k + 1, shift - a[i]);
      }
      return res;
    };
    auto decode = [&](int val, int shift, vector<int> &v) {
      for (int i = 0; i < (int) v.size(); i++) {
        v[i] = shift - (val % 8);
        val /= 8;
      }
    };

    {
      vector<int> initial(2 * k + 1);
      for (int i = 0; i < k; i++) {
        initial[i] = -k - 1;
      }
      initial.insert(initial.begin(), -k - 1);
      dps[encode(initial, 0)] = 1;
    }

    for (int i = 0; i < n; i++) {
      vector<char> cs;
      for (int j = -k; j <= k; j++) {
        if (0 <= i + j && i + j < n) {
          cs.push_back(s[i + j]);
        }
      }
      sort(cs.begin(), cs.end());
      cs.erase(unique(cs.begin(), cs.end()), cs.end());
      cs.push_back('!');
      unordered_map<int, int> ndps;
      ndps.rehash(dps.size() + 10);
      for (auto [v_, cnt] : dps) {
        static vector<int> v(2 * k + 1);
        decode(v_, i, v);

        for (char c : cs) {
          int shift = i - k;
          static vector<int> nv(2 * k + 2);
          nv.assign(2 * k + 2, 0);
          for (int t = 0; t < (int) v.size(); t++) {
            int pos = shift + t;
            nv[t] = max(nv[t], v[t]);
            if (0 <= pos && pos < n && c == s[pos]) {
              nv[t + 1] = max(nv[t + 1], v[t] + 1);
            }
            nv[t + 1] = max(nv[t + 1], nv[t]);
          }
          add(ndps[encode(nv, i + 1)], c == '!' ? mul(cnt, 27 - cs.size()) : cnt);
        }
      }
      dps = std::move(ndps);
    }
    int ans = 0;
    for (const auto &x : dps) {
      vector<int> v(2 * k + 1);
      decode(x.first, n, v);
      if (*max_element(v.begin(), v.end()) >= n - k) {
        add(ans, x.second);
      }
    }
    printf("%d\n", ans);
  }

  return 0;
}

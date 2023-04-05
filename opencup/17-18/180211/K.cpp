#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
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
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

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

const int MAXT = int(1e5) + 10;

char text[MAXT];

struct Pattern {
  int len, num;
  ll hash;

  bool operator < (const Pattern & p) const {
    if (len != p.len) {
      return len < p.len;
    }
    return hash < p.hash;
  }
};

const int P[2] = {997, int(1e6) + 3};
const int MOD[2] = {int(1e9) + 7, int(1e9) + 7};

int powP[2][MAXT];

ll pushChar(ll hash, char ch) {
  union {
    int h[2];
    ll hash;
  } h = {.hash = hash};
  eprintf("pushChar(%lld %c) = ", hash, ch);
  for (int i = 0; i < 2; ++i) {
//    eprintf("(%d * %d + %d) %% %d\n", h.h[i], P[i], ch, MOD[i]);
    h.h[i] = (int)((ll(h.h[i]) * P[i] + ch) % MOD[i]);
  }
  eprintf("%lld\n", h.hash);
  return h.hash;
}

ll popChar(ll hash, char ch, int len) {
  union {
    int h[2];
    ll hash;
  } h = {.hash = hash};
  eprintf("popChar(%lld %c %d) = ", hash, ch, len);
  for (int i = 0; i < 2; ++i) {
    h.h[i] = (int)((h.h[i] - ll(powP[i][len]) * ch) % MOD[i]);
    if (h.h[i] < 0) {
      h.h[i] += MOD[i];
    }
  }
  eprintf("%lld\n", h.hash);
  return h.hash;
}

ll calcHash(const char *s) {
  ll hash = 0;
  for (int i = 0; s[i]; ++i) {
    hash = pushChar(hash, s[i]);
  }
  eprintf("calcHash(%s) %lld\n", s, hash);
  return hash;
}

int main() {
#ifdef LOCAL
  freopen("k.in", "r", stdin);
  freopen("k.out", "w", stdout);
#endif

  int n, m;
  scanf("%d%d", &n, &m);
  scanf(" %s", text);

  for (int j = 0; j < 2; ++j) {
    powP[j][0] = 1;
    for (int i = 1; i <= n; ++i) {
      powP[j][i] = (int)((ll(powP[j][i - 1]) * P[j]) % MOD[j]);
    }
  }

  vector<Pattern> ps;
  for (int i = 0; i < m; ++i) {
    static char s[MAXT];
    scanf(" %s", s);
    int len = strlen(s);
    ps.push_back({len, i, calcHash(s)});
  }
  sort(ps.begin(), ps.end());

  vector <int> ans(m, 0);
  vector <int> canNextOccur(m, 0);
  for (int i = 0; i < m;) {
    int len = ps[i].len;
    eprintf("len %d\n", len);
    unordered_map<ll, int> table;
    int j, first = -1;
    for (j = i; j < m && ps[j].len == len; ++j) {
      if (j > i && ps[j].hash == ps[j - 1].hash) {
        ans[ps[j].num] = -(first + 1);
        eprintf("%d same as %d\n", ps[j].num, first);
      } else {
        eprintf("hash[%d] = %lld\n", ps[j].num, ps[j].hash);
        table[ps[j].hash] = ps[j].num;
        first = ps[j].num;
      }
    }
    i = j;

    ll hash = 0;
    for (j = 0; j < n; ++j) {
      hash = pushChar(hash, text[j]);
      if (j >= len - 1) {
        eprintf("hash[%d,%d] = %lld\n", j - len + 1, j, hash);
        auto it = table.find(hash);
        if (it != table.end()) {
          int num = it->second;
          eprintf("canNextOccur[%d] %d start %d\n", num, canNextOccur[num], j - len + 1);
          if (canNextOccur[num] <= j - len + 1) {
            ans[num] += 1;
            canNextOccur[num] = j + 1;
          }
        }

        hash = popChar(hash, text[j - len + 1], len - 1);
      }
    }
  }

  for (int i = 0; i < m; ++i) {
    eprintf("ans[%d] %d\n", i, ans[i]);
    if (ans[i] < 0) {
      printf("%d\n", ans[-(ans[i] + 1)]);
    } else {
      printf("%d\n", ans[i]);
    }
  }

  return 0;
}

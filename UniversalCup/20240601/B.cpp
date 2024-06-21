#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x)                                                           \
  eprintf("[" #x "] Time : %.3lf s.\n",                                        \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...)                                                     \
  eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__,                            \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char *what) : what(what){};
  __timestamper(const string &what) : what(what){};
  ~__timestamper() { TIMESTAMPf("%s", what.data()); }
} __TIMESTAMPER("end");
#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

using int128 = __int128_t;

string to_string(int128 x) {
  string ans = "";
  while (x) {
    ans += '0' + x % 10;
    x /= 10;
  }
  reverse(ans.begin(), ans.end());
  return ans;
}

int128  to_int(string s) {
  int128 r = 0;
  for (auto c : s) {
    r = r * 10 + c - '0';
  }
  return r;
}

int128 solve(string s) {
  vector<int128> cand;
  {
    for (int i = 1; i < 1000; i++) {
      cand.push_back(i);
    }
    int128 ten = 1000;
    int tlen = 4;
    for (;tlen <= 26; tlen++, ten *= 10) {
      for (int i = 0; i < 30; i++) {
        cand.push_back(ten - i);
      }
      for (int prefix = 0; prefix + 3 <= tlen; prefix++) {
        for (int next = 0; next <= 10; next++) {
          for (int last = (prefix + 3 == tlen) ? 0 : (100 - 50 / tlen - 1); last <= 100; last++) {
            for (int shift = 0; shift < tlen; shift++) {
              string temp(tlen, '?');
              temp[prefix] = '0' + next;
              for (int i = prefix + 1; i < tlen; i++) {
                temp[i] = '9';
              }
              temp[tlen - 2] = (last / 10) + '0';
              temp[tlen - 1] = (last % 10) + '0';
              for (int i = 0; i < (int)s.size(); i++) {
                int pos = (i + shift) % tlen;
                if (pos < prefix && s[i] != '?')
                  temp[pos] = s[i];
              }
              for (int i = 0; i < tlen; i++) {
                if (temp[i] == '?')
                  temp[i] = '0' + (i == 0);
              }
              if (temp[0] == '0')
                continue;
              cand.push_back(to_int(temp));
            }
          }
        }
      }
    }
  }

  sort(cand.begin(), cand.end());
  cand.erase(unique(cand.begin(), cand.end()), cand.end());
  eprintf("%d cand for %s\n", (int)cand.size(), s.c_str());
  for (auto c : cand) {
    string sub = "";
    auto cc = c;
    while (sub.size() < 55) {
      sub += to_string(cc++);
    }
    for (int i = 0; i + s.size() <= sub.size(); i++) {
      bool ok = true;
      for (int j = 0; j < (int)s.size(); j++) {
        if (sub[i + j] != s[j] && s[j] != '?') {
          ok = false;
          break;
        }
      }
      if (ok) {
        int128 len = 0;
        int128 ten = 1;
        int128 tlen = 1;
        while (10 * ten <= c) {
          len += 9 * ten * tlen;
          ten *= 10;
          tlen++;
        }
        len += (c - ten) * tlen;
        len += i + 1;
        return len;
      }
    }
  }
  assert(false);
}

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) {
    char s[30];
    scanf("%s", s);
    int128 ans = solve(s);
    printf("%d\n", (int)(ans % 998244353));
  }

  return 0;
}

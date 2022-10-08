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

char s[55];
int h[3];

bool check_prefix(int len, int n) {
  eprintf("check %.*s\n", len, s);
  int u[3];
  u[0] = 0;
  u[1] = 0;
  u[2] = 0;
  for (int i = 0; i < len; i++) {
    u[s[i] - 'a']++;
  }
  assert(u[0] <= h[0]);
  assert(u[1] <= h[1]);
  assert(u[2] <= h[2]);

  int x = 1;
  for (int i = 1; i < len; i++) {
    assert(s[i] >= s[i % x]);
    if (s[i] > s[i % x]) {
      x = i + 1;
    }
  }
  int ptr = len;

  do {
    if (ptr == n) {
      eprintf("HERE!\n");
      for (int i = 0; i <= n; i++) {
        if (i == n) return true;
        if (s[(i + n) % x] > s[i % x]) {
          break;
        }
        if (s[(i + n) % x] < s[i % x]) {
          return true;
        }
      }
    }
    char nc = s[ptr % x];
    u[nc - 'a']++;
    s[ptr++] = nc;
    while (u[0] > h[0] || u[1] > h[1] || u[2] > h[2]) {
      ptr--;
      while (ptr >= 0 && s[ptr] == 'c') {
        u[2]--;
        ptr--;
      }
      if (ptr < len) {
        return false;
      }
      u[s[ptr] - 'a']--;
      s[ptr]++;
      u[s[ptr] - 'a']++;
      ptr++;
      x = ptr;
    }
  } while (true);
}

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  scanf("%d%d%d", &h[0], &h[1], &h[2]);

  int n = h[0] + h[1] + h[2];

  int u[3];
  u[0] = u[1] = u[2] = 0;

  for (int i = 0; i < n; i++) {
    for (int j = 2;;j--) {
      assert(j >= 0);
      if (u[j] == h[j]) continue;
      u[j]++;
      s[i] = 'a' + j;
      if (check_prefix(i + 1, n)) {
        break;
      } else {
        u[j]--;
      }
    }
  }

  s[n] = 0;
  printf("%s\n", s);


  return 0;
}

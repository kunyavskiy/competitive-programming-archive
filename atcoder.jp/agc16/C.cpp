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

int get_val(int p, int c) {
  p %= c;
  if (p == 0) {
    return 10000;
  } else if (p == c - 1) {
    return -(c - 2 + 10000 + 1);
  } else {
    return 1;
  }
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int H, W, h, w;
  while (scanf("%d%d%d%d", &H, &W, &h, &w) == 4) {
    if (H % h == 0 && W % w == 0) {
      printf("No\n");
      continue;
    }
    printf("Yes\n");
    for (int i = 0; i < H; i++) {
      for (int j = 0; j < W; j++) {
        int val;
        if (H % h != 0) {
          val = get_val(i, h);
        } else {
          val = get_val(j, w);
        }
        printf("%d%c", val, " \n"[j == W - 1]);
      }
    }
  }
  return 0;
}

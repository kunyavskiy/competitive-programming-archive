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

const int MAXN = 100000;

int value[MAXN];

int ask(int pos) {
  if (value[pos] != -1) {
    return value[pos];
  }

  printf("%d\n", pos);
  fflush(stdout);
  char buf[100];
  scanf("%s", buf);
  if (buf[0] == 'M') {
    return value[pos] = 0;
  } else if (buf[0] == 'F') {
    return value[pos] = 1;
  } else {
    exit(0);
  }
}

int check(int lf, int rg) {
  int v1 = ask(lf);
  int v2 = ask(rg);
  return v1 ^ v2 ^ ((rg - lf) & 1);
}

int main() {
#ifdef LOCAL
//  freopen("c.in", "r", stdin);
//  freopen("c.out", "w", stdout);
#endif

  memset(value, -1, sizeof(value));


  int n;
  scanf("%d", &n);
  int lf = 0;
  int rg = n - 1;
  assert(check(lf, rg));

  while (true) {
    int m = (lf + rg) / 2;
    if (check(lf, m)) {
      rg = m;
    } else {
      assert(check(m, rg));
      lf = m;
    }
  }

  return 0;
}

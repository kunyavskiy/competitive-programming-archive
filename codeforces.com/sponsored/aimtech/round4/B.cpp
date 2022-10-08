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
#include <x86intrin.h>

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

pair<int,int> get(int pos) {
  printf("? %d\n", pos + 1);
  fflush(stdout);
  int a, b;
  scanf("%d%d", &a, &b);
  return {a, b - 1};
};

int get_rand() {
  return ((rand() << 15) ^ rand()) & 0x3fffffff;
}

int main() {

  int rd = __rdtsc();
  eprintf("%d\n", rd);
  srand(rd);

  int n, start, x;
  scanf("%d%d%d", &n, &start, &x);
  --start;

  auto st = get(start);

  pair<int, int> best = {st.first, start};

  for (int i = 0; i < 1000; i++) {
    int id = get_rand() % n;
    auto val = get(id);

    if (val.first >= x) {
      continue;
    }
    best = max(best, make_pair(val.second, id));
  }

  int id = best.second;
  while (id >= 0) {
    auto val = get(id);
    if (val.first >= x) {
      printf("! %d\n", val.first);
      return 0;
    }
    id = val.second;
  }

  printf("! %d\n", -1);
  return 0;
}

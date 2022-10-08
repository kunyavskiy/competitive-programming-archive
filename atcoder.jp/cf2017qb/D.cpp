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

const int MAXN = 500100;

char s[MAXN];

void ops(int l, int r) {
  string str = string(s + l, s + r);
  vector<int> ll;
  int ops = 0;
  for (int i = 2; i < (int)str.size(); i++) {
    if (i >= 2 && s[i - 2] == '1' && s[i - 1] == '0' && s[i] == '1') {
      s[i - 2] = '0';
      s[i - 1] = '1';
      s[i - 0] = '0';
      ops++;
      i -= 2;
    }
    ll[i] = ops;
  }
  str = string(s + l, s + r);
  vector<int> rr;
  ops = 0;
  for (int i = (int)str.size() - 1; i >= 0; i--) {
    if (i + 2 < (int)str.size() && s[i + 2] == '1' && s[i + 1] == '0' && s[i] == '1') {
      s[i + 2] = '0';
      s[i + 1] = '1';
      s[i + 0] = '0';
      ops++;
      i += 2;
    }
    rr[i] = ops;
  }
  int ans = 0;
  for (int i = 0; i < (int)str.size(); i++) {

  }
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int n;
  scanf("%d%s", &n, s);

  s[n] = s[n + 1] = '0';
  s[n + 2] = '\0';
  n += 2;

  int ops = 0;
  vector<int> v = vector<int>(1, 0);

  int start = -1;

  for (int i = 0; i < n; i++) {
    if (s[i] == '0') {
      if (start != -1 && s[i - 1] == '0') {
        ops += solve(start, i - 1);
      }
    } else {
      if (start == -1) {
        start = i;
      }
    }
  }

  printf("%d\n", ops);

  return 0;
}

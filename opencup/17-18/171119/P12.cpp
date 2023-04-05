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

const int MAXN = 1000100;

char x[MAXN];
char y[MAXN];
char z[MAXN];

pair<int, int> solve(const string& x, const string& y) {
  string s = x + '$' + y;
  vector<int> p(s.size());
  pair<int, int> res;
  res.first = res.second = -1;
  for (int i = 1; i < (int)p.size(); i++) {
    int j = p[i - 1];
    while (j && s[j] != s[i]) {
      j = p[j - 1];
    }
    if (s[j] == s[i]) j++;
    p[i] = j;
    if (j == (int)x.size()) {
      res.second = i - 2 * x.size();
      if (res.first == -1) {
        res.first = res.second;
      }
    }
  }
  return res;
}

void solve(const string& x, const string& y, const string& z) {
  pair<int, int> a = solve(x, z);
  pair<int, int> b = solve(y, z);

  if (a.first != -1 && b.first != -1) {
    if (a.first + (int)x.size() <= b.second || b.first + (int)y.size() <= a.second) {
      printf("YES\n");
      return;
    }
  }
  printf("NO\n");
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int t;
  scanf("%d", &t);
  while (t-- > 0) {
    scanf("%s%s%s", z, x, y);
    solve(x, y, z);
  }

  return 0;
}

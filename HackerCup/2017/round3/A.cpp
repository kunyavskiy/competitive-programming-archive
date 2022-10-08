//#include <iostream>
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
#include <stdarg.h>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if (_WIN32 || __WIN32__)
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "A"

typedef long long ll;
typedef long double ld;


char res[10000];

void check(string s, vector<int> p) {
  int n = (int)s.size();
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    a[i] = i;
  }
  sort(a.begin(), a.end(), [&s](int a, int b) {
    return s.substr(a) < s.substr(b);
  });
  for (int i = 0; i < n; i++) {
    assert(a[p[i]] == i);
  }
}

void solve() {
  int n;
  scanf("%d", &n);
  vector<int> p(n);
  for (int& x : p) {
    scanf("%d", &x);
    --x;
  }
  p.push_back(-1);
  vector<int> ord(n);
  for (int i = 0; i < n; i++) {
    assert(0 <= p[i] && p[i] < n);
    ord[p[i]] = i;
  }
  char cur = 'A';
  for (int i = 0; i < n; i++) {
    bool ok;
    if (!i) {
      ok = true;
    } else {
      int v = ord[i] + 1;
      int u = ord[i - 1] + 1;
      assert(0 <= v && v <= (int)p.size());
      assert(0 <= u && u <= (int)p.size());
      ok = p[u] < p[v];
    }
    if (!ok) {
      cur++;
      if (cur == 'Z' + 1) {
        printf("-1\n");
        return;
      }
    }
    res[ord[i]] = cur;
  }
  res[n] = 0;
  puts(res);
  check(res, p);
}

int main() {
  freopen(TASKNAME".in", "r", stdin);
  freopen(TASKNAME".out", "w", stdout);

  int t;
  scanf("%d", &t);
  for (int i = 1; i <= t; i++) {
    printf("Case #%d: ", i);
    solve();
//    break;
  }

  return 0;
}

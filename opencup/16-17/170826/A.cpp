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

typedef long double ld;

int main() {
  int n;
  scanf("%d", &n);
  vector<int> l(n);
  vector<int> r(n);
  for (int i = 0; i < n; i++){
    scanf("%d%d", &l[i], &r[i]);
    l[i]--;
    r[i]--;
  }
  vector<pair<int, int>> p(n);
  for (int i = 0; i < n; i++) {
    p[i] = make_pair(l[i], i);
  }
  sort(p.begin(), p.end());
  int j = 0;

  set<int> q;
  for (int i = 0; i < n; i++) {
    while (j < n && p[j].first == i) {
      q.insert(p[j].second);
      j++;
    }
    if (q.size() == 0) {
      printf("-1\n");
      return 0;
    }
    int x = *(q.begin());
//    q.delete(x);
  }

  return 0;
}

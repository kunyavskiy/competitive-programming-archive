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

char buf[200000];

void solve() {
  int n;
  scanf("%d", &n);
  vector<string> v;
  for (int i = 0; i < n; i++) {
    scanf("%s", buf);
    v.push_back(string(buf));
  }
  sort(v.begin(), v.end(), [](const string& a, const string & b) { return a.size() < b.size();});

  for (int i = 1; i < n; i++) {
    if (v[i].substr(0, v[i - 1].size()) != v[i - 1]) {
      printf("Impossible\n");
      return;
    }
  }
  printf("%d\n", (int)v.back().size());
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int t;
  scanf("%d", &t);
  while (t-->0) {
    solve();
  }

  return 0;
}

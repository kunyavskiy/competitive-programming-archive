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

int main() {
#ifdef LOCAL
  freopen("l.in", "r", stdin);
  freopen("l.out", "w", stdout);
#endif
  char temp[1000];
  int n;
  scanf("%d", &n);
  set<string> all;
  set<pair<string, string>> likes;
  for (int i = 0; i < n; i++) {
    scanf("%s", temp);
    string a = temp;
    scanf("%s", temp);
    string b = temp;
    all.insert(a);
    all.insert(b);
    pair<string, string> l = {a, b};
    if (likes.find(l) == likes.end()) {
      likes.insert(l);
    } else {
      likes.erase(l);
    }
  }
  map<string, int> nlikes;
  for (auto l : likes) {
    nlikes[l.second]++;
  }
  int maxl = 0;
  for (auto l : nlikes) {
    maxl = max(maxl, l.second);
  }
  for (auto s : all) {
    if (nlikes[s] == maxl) {
      cout << s << "\n";
    }
  }

  return 0;
}

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

struct dir {
  ll size;
  map<string, dir> next;

  dir() {
    size = 0;
  }
};

char buf[1100];

void print(const dir& d, int t, string path) {
  bool need = false;
  for (const auto &next : d.next) {
    if (next.second.size >= t) {
      need = true;
    }
  }

  if (d.next.empty()) {
    printf("  %s %lld\n", path.c_str(), d.size);
  } else if (!need) {
    printf("+ %s %lld\n", path.c_str(), d.size);
  } else {
    printf("- %s %lld\n", path.c_str(), d.size);
    for (const auto& next : d.next) {
      print(next.second, t, path + next.first + "/");
    }
  }
}

int main() {
#ifdef LOCAL
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  dir root;

  for (int i = 0; i < n; i++) {
    int size;
    scanf("%s%d", buf, &size);
    string s = "";
    int l = strlen(buf);
    dir *cur = &root;
    for (int j = 1; j < l; j++) {
      if (buf[j] == '/') {
        cur->size += size;
        cur = &cur->next[s];
        s = "";
      } else {
        s += buf[j];
      }
    }
    cur->size += size;
  }

  int t;
  scanf("%d", &t);

  print(root, t, "/");


  return 0;
}

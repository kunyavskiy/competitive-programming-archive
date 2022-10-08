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
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  string s;
  while (cin >> s) {
    if (s.size() < 26) {
      for (char c = 'a'; c <= 'z'; c++) {
        if (s.find(c) == string::npos) {
          printf("%s\n", (s + c).c_str());
          break;
        }
      }
    } else {
      string sold = s;
      if (!next_permutation(s.begin(), s.end())) {
        printf("-1\n");
      } else {
        while (true) {
          string t = s.substr(0, s.size() - 1);
          if (t > sold) {
            s = t;
          } else {
            break;
          }
        }
        printf("%s\n", s.c_str());
      }
    }
  }

  return 0;
}

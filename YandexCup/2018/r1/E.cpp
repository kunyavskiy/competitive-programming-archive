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
  clock_t start = clock();
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  vector<int> v(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &v[i]);
  }

  vector<int> all = v;
  sort(all.begin(), all.end());

  vector<int> cand;
  cand.push_back(1);
  for (int i = 1; i < n; i++) {
    cand.push_back(v[i] + v[i - 1] - 1);
    cand.push_back(v[i] + v[i - 1] + 1);
  }
  sort(cand.begin(), cand.end());
  cand.erase(unique(cand.begin(), cand.end()), cand.end());
  random_shuffle(cand.begin(), cand.end());
  for (int x : cand) {

    if (clock() - start > 1.8 * CLOCKS_PER_SEC) break;

    if (x % 2 == 0 && binary_search(all.begin(), all.end(), x / 2)) {
      continue;
    }
    if (x <= 0) continue;

    int prev = -1;
    bool bad = false;
    for (int i = 0; i < n; i++) {
      int next = -1;
      if (v[i] > prev) {
        next = v[i];
      }
      if (x - v[i] > prev && (x - v[i] < next || next == -1)) {
        next = x - v[i];
      }
      if (next == -1) {
        bad = true;
        break;
      }
      prev = next;
    }
    if (!bad) {
      printf("%d\n", x);
      int prev = -1;
      for (int i = 0; i < n; i++) {
        int next = -1;
        if (v[i] > prev) {
          next = v[i];
        }
        if (x - v[i] > prev && (x - v[i] < next || next == -1)) {
          next = x - v[i];
        }
        assert(next != -1);
        prev = next;
        printf("%d ", next);
      }
      printf("\n");
      return 0;
    }
  }
  printf("-1\n");

  return 0;
}

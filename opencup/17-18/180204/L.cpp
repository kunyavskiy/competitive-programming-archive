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

void apply_one(vector<int>& a, int k) {
  int n = a.size();
  int all = 0;
  if ((k / n) % 2) {
    for (int i = 0; i < n; i++) {
      all ^= a[i];
    }
  }
  k %= n;
  vector<int> xors(2 * n + 1);
  for (int i = 0; i < 2 * n; i++) {
    xors[i + 1] = xors[i] ^ a[i % n];
  }
  for (int i = 0; i < n; i++) {
    a[i] = xors[i + k] ^ xors[i] ^ all;
  }
}

void apply(vector<int>& a, int shift, int k) {
  int n = a.size();
  vector<bool> used(n);

  for (int i = 0; i < n; i++) {
    if (!used[i]) {
      vector<int> na;
      vector<int> pos;
      for (int j = i; !used[j]; j = (j + shift) % n) {
        na.push_back(a[j]);
        pos.push_back(j);
        used[j] = true;
      }

      apply_one(na, k);

      for (int j = 0; j < (int)pos.size(); j++) {
        a[pos[j]] = na[j];
      }
    }
  }
}

int main() {
#ifdef LOCAL
  freopen("l.in", "r", stdin);
  freopen("l.out", "w", stdout);
#endif

  int n, k;
  ll t;
  scanf("%d%d%lld\n", &n, &k, &t);

  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }

  for (int i = 0; i < 60; i++) {
    if (t & (1LL << i)) {
      apply(a, (1LL << i) % n, k);
    }
  }

  for (int i = 0; i < n; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
  return 0;
}

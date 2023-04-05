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

void gen_primes(int n);

#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

const int MAXN = 1001000;

int ans[MAXN];

int mind[MAXN];
vector<int> primes;

void gen_primes(int n) {
  mind[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (mind[i] == 0) {
      mind[i] = i;
      primes.push_back(i);
      ans[i] = -1;
    }
    for (int j : primes) {
      if (j > mind[i] || i * j > n) break;
      mind[i * j] = j;
    }
  }
}


pair<int, int> get(int n) {
  int bal = 0;
  int max_bal = 0;//, cc = 1;

  for (int i = 1; i <= n; i++) {
    if (mind[i] == i) {
      //ans[i] = (cc++ % 2) ? 1 : -1;
    } else {
      ans[i] = ans[i / mind[i]] * ans[mind[i]];
    }
    bal += ans[i];
    max_bal = max(abs(bal), max_bal);
  }
  return make_pair(max_bal, bal);
}

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  gen_primes(n);


  ans[1] = 1;

//  int a = get(n).second;
  for (int x : primes) {
    ans[x] = (x % 3 == 2) ? -1 : 1;
//    ans[x] *= -1;
//    int b = get(n).second;
//    ans[x] *= -1;
//    if (abs(b) < abs(a))
//      a = b, ans[x] *= -1;
  }

  get(n);

//  eprintf("%d\n", get(n).second);
//  eprintf("%d\n", get(n).first);
//  for (int i = 1; i <= n; i++)
//    eprintf("ans[%d] = %d\n", i, ans[i]);
//
//  int bmask = 0;
//  const int K = 15;
//  for (int i = 0; i < (1 << K); i++) {
//    for (int j = 0; j < K; j++) {
//      if (i & (1 << j)) {
//        ans[primes[j]] = 1;
//      } else {
//        ans[primes[j]] = -1;
//      }
//    }
//    int val = get(n);
//    if (max_bal > val) {
//      max_bal = val;
//      bmask = i;
//    }
////    eprintf("val = %d, mask = %x\n", val, i);
//  }
//
//  eprintf("val = %d, mask = %x\n", max_bal, bmask);
//
//  return 0;
//
//  for (int j : primes) {
//    ans[j] = -1;
//    int nmax_bal = get(n);
//    if (nmax_bal < max_bal || (nmax_bal == max_bal && (rand() & 1))) {
//      max_bal = nmax_bal;
//    } else {
//      ans[j] = 1;
//    }
//    eprintf("%d %d\n", p[j], max_bal);
//  }
////  assert(max_bal <= 20);
//
  for (int i = 1; i <= n; i++) {
    printf("%d ", ans[i]);
  }
  printf("\n");

  return 0;
}

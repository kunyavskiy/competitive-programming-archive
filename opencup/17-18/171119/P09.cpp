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

int mpow(int a, int b, int m) {
  int r = 1;
  while (b) {
    if (b & 1) r = (r * 1LL * a) % m;
    a = (a * 1LL * a) % m;
    b >>= 1;
  }
  return r;
}

const int MAXN = 10000000;

int mind[MAXN];
vector<int> primes;

void gen_primes(int n) {
  mind[1] = 1;
  for (int i = 2; i < n; i++) {
    if (mind[i] == 0) {
      mind[i] = i;
      primes.push_back(i);
    }
    for (int j : primes) {
      if (j > mind[i] || i * j >= n) break;
      mind[i * j] = j;
    }
  }
}


int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  gen_primes(MAXN);
  int q, n;
  TIMESTAMP("primes");
  while (scanf("%d%d", &q, &n) == 2) {
    vector<int> cn;
    int nn = n;
    for (int i = 2; i * i <= nn; i++) {
      if (n % i == 0) {
        cn.push_back(n / i);
        while (nn % i == 0) {
          nn /= i;
        }
      }
    }
    if (nn != 1) {
      cn.push_back(n / nn);
    }
    vector<int> ans;
    for (int p : primes) {
      if (mpow(q, n, p) == 1) {
        bool ok = true;
        for (int x : cn) {
          if (mpow(q, x, p) == 1) {
            ok = false;
            break;
          }
        }
        if (ok) {
          ans.push_back(p);
        }
      }
    }
    printf("%d\n", (int)ans.size());
    for (int x : ans) {
      printf("%d ", x);
    }
    printf("\n");
  }

  return 0;
}

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
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl


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

  int n, k;
  scanf("%d%d", &n, &k);
  int nn = n;
  int kk = k;
  const int MAX = 1000;
  vector<int> pn(MAX), pk(MAX);
  for (int i = 2; i < MAX; i++) {
    while (n % i == 0) {
      pn[i]++;
      n /= i;
    }
    while (k % i == 0) {
      pk[i]++;
      k /= i;
    }
  }
  n = nn; k = kk;
  for (int i = 0; i < MAX; i++) {
    if (pn[i] > 0 && pk[i] == 0) {
      cout << -1;
      return 0;
    }
  }
  vector<vector<int>> res;
  for (int i = 0; i < n / k; i++) {
    vector<int> a;
    for (int j = 0; j < k; j++) {
      a.push_back(i * k + j);
    }
    res.push_back(a);
  }

  int q = k;
  for (int i = 0; i < MAX; i++) {
    for (int j = 0; j < pn[i] - pk[i]; j++) {
      for (int t = 0; t < (n / q / i); t++) {
        for (int u = 0; u < q * i / k; u++) {
          vector<int> a;
          for (int e = 0; e < i; e++) {
            for (int x = 0; x < k / i; x++) {
              a.push_back(t * q * i + k / i * u + e * q + x);
            }
          }
          res.push_back(a);
        }
      }
      q *= i;
    }
  }

  cout << res.size() << "\n";
  for (auto &a : res) {
    for (int x : a) {
      cout << x + 1 << " ";
    }
    cout << "\n";
  }


  return 0;
}

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
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif

  string a, b;
  while (cin >> a >> b) {
    int n = a.size();
    int m = b.size();
    vector<vector<int>> v(n, vector<int>(m));
    vector<int> sum1(n);
    vector<int> sum2(m);
    for (int i = 0; i < n; i++) {
      sum1[i] = a[i] - '0';
    }
    for (int i = 0; i < m; i++) {
      sum2[i] = b[i] - '0';
    }
    for (int i = 0; i < n - 1; i++) {
      for (int j = 0; j < m - 1; j++) {
        v[i][j] = 1;
        sum1[i] ^= 1;
        sum2[j] ^= 1;
      }
    }
    for (int i = 0; i < n - 1; i++) {
      v[i][m - 1] = sum1[i];
      sum1[i] ^= v[i][m - 1];
      sum2[m - 1] ^= v[i][m - 1];
    }
    for (int i = 0; i < m - 1; i++) {
      v[n - 1][i] = sum2[i];
      sum1[n - 1] ^= v[n - 1][i];
      sum2[i] ^= v[n - 1][i];
    }
    if (sum1[n - 1] != sum2[m - 1]) {
      printf("-1\n");
      continue;
    }
    v[n - 1][m - 1] = sum1[n - 1];

    {
      int i = 0, j = 0;
      while (i < n - 1 && j < m - 1) {
        while (i < n && v[i][m - 1] == 1) i++;
        while (j < m && v[n - 1][j] == 1) j++;
        if (i < n && j < n) {
          v[i][j] ^= 1;
          v[i][m - 1] ^= 1;
          v[n - 1][j] ^= 1;
          v[n - 1][m - 1] ^= 1;
        }
      }
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        printf("%d", v[i][j]);
      }
      printf("\n");
    }
  }

  return 0;
}

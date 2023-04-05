//#include <iostream>
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
#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ( ( _WIN32 || __WIN32__ ) && __cplusplus < 201103L)
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "F"

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

const int N = 110;
char a[N][N];

char ans[N * N];
char cur[N * N];

int cmpChar(char x, char y) {
  return ((int)x - (int)y);
}

void solve(vector <string> & v) {
  int n = int(v.size());
  int m = int(v[0].size());
  sort(v.begin(), v.end(), greater<string>());
//  cur[n * m] = 0;
//  for (int i = 0, k = 0; i < n; ++i) {
//    for (int j = 0; j < m; ++j) {
//      cur[k++] = v[i][j];
//    }
//  }
//  if (strcmp(ans, cur) < 0) {
//    memcpy(ans, cur, n * m * sizeof(char));
//  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      int k = 0;
      int ok = 0;
      for (int p = j; p < m; ++p) {
        cur[k] = v[i][p];
        if (ok == 0) {
          ok = cmpChar(cur[k], ans[k]);
        }
        k++;
      }
      for (int p = 0; p < n; ++p) {
        if (p == i) { continue; }
        if (ok < 0) { break; }
        for (int q = 0; q < m; ++q) {
          cur[k] = v[p][q];
          if (ok == 0) {
            ok = cmpChar(cur[k], ans[k]);
          }
          k++;
        }
      }
      for (int p = 0; p < j; ++p) {
        cur[k] = v[i][p];
        if (ok == 0) {
          ok = cmpChar(cur[k], ans[k]);
        }
        k++;
      }
      if (ok > 0) {
        memcpy(ans, cur, n * m * sizeof(char));
      }
    }
  }
}

int main() {
#ifdef LOCAL
    assert(freopen(TASKNAME".in", "r", stdin));
    assert(freopen(TASKNAME".out", "w", stdout));
#endif

  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%s", a[i]);
  }

  memset(ans, '0' - 1, sizeof(ans));
  ans[n * m] = 0;

  vector <string> rows(n);
  vector <string> cols(m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      rows[i] += a[i][j];
      cols[j] += a[i][j];
    }
  }

  solve(rows);
  solve(cols);
  printf("%s\n", ans);

  return 0;
}

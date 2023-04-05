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

#define LEN 1111111

char S[LEN];
int d[LEN][26][2][2];

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  scanf("%s", S);
  int n = strlen(S);

  for (int i = 0; i < 26; i++) {
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 2; k++) {
        d[n][i][j][k] = -1;
      }
    }
  }

  vector<int> a(n);
  vector<int> reg(n);
  for (int i = 0; i < n; i++) {
    char c = S[i];
    if (c >= 'a' && c <= 'z') {
      a[i] = c - 'a';
      reg[i] = 0;
    } else {
      a[i] = c - 'A';
      reg[i] = 1;
    }
  }

  for (int i = n - 1; i >= 0; i--) {
    for (int c = 0; c < 26; c++) {
      for (int cr = 0; cr < 2; cr++) {
        for (int nd = 0; nd < 2; nd++) {
          if (a[i] == c && (reg[i] ^ cr) == nd) {
            d[i][c][cr][nd] = i;
          } else {
            d[i][c][cr][nd] = d[i + 1][c][cr ^ 1][nd];
          }
        }
      }
    }
  }

  int m;
  scanf("%d", &m);
  for (int i = 0; i < m; i++) {
    scanf("%s", S);
    int n = strlen(S);
    int pos = 0;
    int reg = 0;
    bool ok = true;
    for (int j = 0; j < n; j++) {
      char c = S[j];
      int cc;
      int rr;
      if (c >= 'a' && c <= 'z') {
        cc = c - 'a';
        rr = 0;
      } else {
        cc = c - 'A';
        rr = 1;
      }
      int pp = d[pos][cc][reg][rr];
      if (pp == -1) {
        ok = false;
        break;
      }
      reg = reg ^ ((pp - pos) & 1);
      pos = pp + 1;
    }
    if (ok) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }

  return 0;
}

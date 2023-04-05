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

int n;
vector<vector<bool>> aa;

int pp[100];

void dfs(int x, int p) {
  pp[x] = p;
  for (int i = 0; i < n; i++) {
    if (i != x && i != p && (aa[x][i] || aa[i][x])) {
      dfs(i, x);
    }
  }
}

int main() {
  cin >> n;
  if (n == 2) {
    cout << "! 1" << endl;
    return 0;
  }
  vector<bool> leaf(n);
  for (int i = 0; i <n ; i++) {
    cout << "? " << (n - 1);
    for (int j = 0; j < n; j++) {
      if (i != j) {
        cout << " " << (j + 1);
      }
    }
    cout << endl;
    int x;
    cin >> x;
    leaf[i] = x < n;
  }
  int s = 0;
  while (!leaf[s]) s++;

  vector<vector<bool>> q(n, vector<bool>(n));

  for (int i = s + 1; i < n; i ++) {
    if (!leaf[i]) continue;
    for (int j = 0; j < n; j++) {
      if (leaf[j]) continue;
      cout << "? 3 " << (s + 1) << " " << (i + 1) << " " << (j + 1) << endl;
      int x;
      cin >> x;
      q[j][i] = x == 3;
    }
  }

  for (int i = s + 1; i < n; i++) {
    if (leaf[i]) q[i][i] = true;
    q[s][i] = true;
  }

  vector<vector<bool>> a(n, vector<bool>(n));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      bool ok = true;
      for (int k = 0; k < n; k++) {
        if (q[j][k] && !q[i][k]) {
          ok = false;
          break;
        }
      }
      a[i][j] = ok;
    }
  }

  aa.assign(n, vector<bool>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (a[i][j]) {
        aa[i][j] = true;
        for (int k = 0; k < n; k++) {
          if (k != i && k != j) {
            if (a[i][k] && a[k][j]) {
              aa[i][j] = false;
              break;
            }
          }
        }
      }
    }
  }

  dfs(0, -1);
  cout << "! ";
  for (int i = 1; i < n; i++) {
    cout << " " << (pp[i] + 1);
  }
  cout << endl;

  return 0;
}

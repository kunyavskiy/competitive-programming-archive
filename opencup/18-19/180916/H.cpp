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
//#define TEST
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

int n, m;
char field[100][100];
int num[100][100];
int nnum[100][100];

int ask(string s) {
#ifdef TEST
  for (int y = 0; y < n; y++) {
    for (int x = 0; x < m; x++) {
      num[y][x] = field[y][x] == '*';
    }
  }
  int res = 0;
  for (char c : s) {
    int dx = 0, dy = 0;
    if (c == 's') dy++;
    if (c == 'n') dy--;
    if (c == 'w') dx--;
    if (c == 'e') dx++;
    for (int y = 0; y < n; y++) {
      for (int x = 0; x < m; x++) {
        nnum[y][x] = 0;
      }
    }
    for (int y = 0; y < n; y++) {
      for (int x = 0; x < m; x++) if (num[y][x] > 0) {
        int xx = x + dx;
        int yy = y + dy;
        if (field[yy][xx] == '#') {
          xx = x;
          yy = y;
        }
        nnum[yy][xx] += num[y][x];
      }
    }
    for (int y = 0; y < n; y++) {
      for (int x = 0; x < m; x++) {
        num[y][x] = nnum[y][x];
        if (field[y][x] == 'X') {
          res += num[y][x];
        }
      }
    }
  }
//  cout << s << " " << res << "\n";
  return res;
#else
  if (s.size() == 0) return 0;
  cout << "? " << s << endl;
  int x;
  cin >> x;
  return x;
#endif
}

bool empty(string s) {
  return ask(s) == ask(s.substr(0, s.size() - 1));
}

int main() {
#ifdef TEST
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);

  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) {
    scanf("%s", field[i]);
  }

#endif

  vector<int> up(100, -1);
  vector<int> down(100, -1);
  vector<vector<string>> ss(100, vector<string>(100));

  up[50] = 50;
  while (true) {
    ss[50][up[50] + 1] = ss[50][up[50]] + "s";
    if (empty(ss[50][up[50] + 1])) {
      up[50]++;
    } else {
      break;
    }
  }
  down[50] = 50;
  while (true) {
    ss[50][down[50] - 1] = ss[50][down[50]] + "n";
    if (empty(ss[50][down[50] - 1])) {
      down[50]--;
    } else {
      break;
    }
  }

  for (int x = 51; ; x++) {
    up[x] = up[x - 1];
    down[x] = down[x - 1];
    for (int y = down[x]; y <= up[x]; y++) {
      ss[x][y] = "w" + ss[x - 1][y];
    }
    while (up[x] >= down[x] && !empty(ss[x][up[x]])) {
      up[x]--;
    }
    while (up[x] >= down[x] && !empty(ss[x][down[x]])) {
      down[x]++;
    }
    if (up[x] < down[x]) {
      up[x] = down[x] = -1;
      break;
    }
    if (up[x] == up[x - 1]) {
      ss[x][up[x] + 1] = "s" + ss[x][up[x]];
      while (empty(ss[x][up[x] + 1])) {
        up[x]++;
        ss[x][up[x] + 1] = "s" + ss[x][up[x]];
      }
    }
    if (down[x] == down[x - 1]) {
      ss[x][down[x] - 1] = "n" + ss[x][down[x]];
      while (empty(ss[x][down[x] - 1])) {
        down[x]--;
        ss[x][down[x] - 1] = "n" + ss[x][down[x]];
      }
    }
  }

  // !!!!!

  for (int x = 49; ; x--) {
    up[x] = up[x + 1];
    down[x] = down[x + 1];
    for (int y = down[x]; y <= up[x]; y++) {
      ss[x][y] = "e" + ss[x + 1][y];
    }
    while (up[x] >= down[x] && !empty(ss[x][up[x]])) {
      up[x]--;
    }
    while (up[x] >= down[x] && !empty(ss[x][down[x]])) {
      down[x]++;
    }
    if (up[x] < down[x]) {
      up[x] = down[x] = -1;
      break;
    }
    if (up[x] == up[x + 1]) {
      ss[x][up[x] + 1] = "s" + ss[x][up[x]];
      while (empty(ss[x][up[x] + 1])) {
        up[x]++;
        ss[x][up[x] + 1] = "s" + ss[x][up[x]];
      }
    }
    if (down[x] == down[x + 1]) {
      ss[x][down[x] - 1] = "n" + ss[x][down[x]];
      while (empty(ss[x][down[x] - 1])) {
        down[x]--;
        ss[x][down[x] - 1] = "n" + ss[x][down[x]];
      }
    }
  }

  // !!!!!

  vector<vector<int>> x(100, vector<int>(100));

  for (int i = 0; i < 100; i++) {
    if (up[i] >= 0) {
      for (int j = down[i]; j <= up[i]; j++) {
//        x[i][j] = 1;
        for (int ii = i - 1; ii <= i + 1; ii++) {
          for (int jj = j - 1; jj <= j + 1; jj++) {
            x[ii][jj] = 1;
          }
        }
      }
    }
  }
//  x[50][50] = 2;

//  for (int i = 0; i < 100; i++) {
//    for (int j = 0; j < 100; j++) {
//      cout << x[i][j];
//    }
//    cout << endl;
//  }

  int res = 0;
  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
      if (x[i][j]) res++;
    }
  }

  cout << "! " << res << endl;

  return 0;
}

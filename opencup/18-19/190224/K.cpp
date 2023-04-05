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

string fast(string s, vector<int> pos) {
  int n = s.length();

  const int SIGMA = 26;
  vector<vector<int>> nxt(n + 1, vector<int>(SIGMA, n + 1));
  for (int i = n - 1; i >= 0; i--) {
    nxt[i] = nxt[i + 1];
    nxt[i][s[i] - 'a'] = i;
  }

  string res = "";
  int curC = 0;
  int mn = 0, mx = 0;

  auto flush = [&](int &val) {
    while (val--) {
      res += (char)('a' + curC);
    }
    mn = 0;
    mx = 0;
  };

  int cpos = 0;
  for (int j : pos) {
    int newC = s[j] - 'a';

    for (int t = 0; t < newC; t++) {
      while (1) {
        int npos = nxt[cpos][t];
        if (npos < j) {
          if (t < curC) flush(mn);
          else flush(mx);

          res += (char) ('a' + t);
          cpos = npos + 1;
        } else break;
      }
    }

    int cnt = 0;
    while (1) {
      int npos = nxt[cpos][newC];
      if (npos <= j) {
        cnt++;
        cpos = npos + 1;
      } else break;
    }

    if (curC < newC) {
      flush(mx);
      curC = newC;
      mn = 1;
      mx = cnt;
    } else if (curC == newC) {
      mn += 1;
      mx += cnt;
    } else {
      flush(mn);
      mn = 1;
      mx = cnt;
    }
    curC = newC;
  }
  flush(mn);

  return res;
}

string slow(string s, vector<int> pos) {
  int n = s.length();
  int tmask = 0;
  for (int j : pos) tmask |= 1 << j;

  string ans = "";
  for (int mask = 0; mask < (1 << n); mask++) {
    if (!((mask & tmask) == tmask)) {
      continue;
    }
    string t = "";
    for (int i = 0; i < n; i++) if (mask & (1 << i)) t += s[i];

    if (ans == "" || ans > t) ans = t;
  }
  return ans;
}

void stress() {
  for (int it = 0;; it++) {
    srand(it);
    cout << it << endl;

    int n = rand() % 10 + 1;
    string s = "";
    for (int i = 0; i < n; i++) s += (char)('a' + rand() % 4);

    int mask = rand() % ((1 << n) - 1) + 1;
    vector<int> pos;
    for (int i = 0; i < n; i++) if (mask & (1 << i)) pos.push_back(i);

    auto ans1 = fast(s, pos);
    auto ans2 = slow(s, pos);
    if (ans1 != ans2) {
      cout << s << endl;
      for (int j : pos) cout << j << " ";
      cout << endl;
      cout << "-----" << endl;
      cout << ans1 << " instead of " << ans2 << endl;
      exit(0);
    }
  }
}

int main() {
#ifdef LOCAL
  freopen("k.in", "r", stdin);
  //freopen("k.out", "w", stdout);
#endif

  //stress();

  char buf[(int)1.1e6];
  while (scanf("%s", buf) == 1) {
    string s = buf;
    int k;
    scanf("%d", &k);
    vector<int> pos(k);
    for (int i = 0; i < k; i++) {
      scanf("%d", &pos[i]);
      pos[i]--;
    }

    cout << fast(s, pos) << endl;
  }

  return 0;
}

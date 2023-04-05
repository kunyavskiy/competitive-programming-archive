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

const int MAXN = 3100;

char s[MAXN];

int LTSplit(int n) {
  vector<int> A(n + 1);
  for (int k = 1; k <= n; k++) {
    for (int a = k - 1; a >= 1; a--) {
      if (s[a] == s[k]) {
        int t = A[a];
        int c = a + 1;
        while (t < k && c < k) {
          if (A[c] > t) {
            swap(A[c], t);
          }
          c++;
        }
        A[a] = k;
      }
    }
  }

  int c = 0;
  int l = 1;
  for (int k = 1; k <= n - 1; k++) {
    int t = 0;
    for (int a = 1; a <= k; a++) {
      if (A[a] > k) t++;
    }
    if (t > c) {
      c = t;
      l = k;
    }
  }
  return l;
}

string lcs(string a, string b) {
  int n = a.size();
  int m = b.size();
  vector<vector<int>> dp(n + 1, vector<int>(m + 1));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
      if (a[i - 1] == b[j - 1]) {
        dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
      }
    }
  }

  string ans;
  while (n && m) {
    if (dp[n][m] == dp[n-1][m]) {
      n--;
    } else if (dp[n][m] == dp[n][m-1]) {
      m--;
    } else {
      assert(a[n-1] == b[m-1]);
      ans += a[n-1];
      n--, m--;
    }
  }
  reverse(ans.begin(), ans.end());
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; ++i) {
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    int l = LTSplit(n);
    string ans = lcs(string(s + 1, s + l + 1), string(s + l + 1, s + n + 1));
    ans += ans;
    printf("Case #%d: %d\n", i+1, (int)ans.size());
    if (!ans.empty()) {
      printf("%s\n", ans.c_str());
    }
  }


  return 0;
}

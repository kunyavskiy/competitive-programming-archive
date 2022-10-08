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

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  string chars;
  for (char c = 'A'; c <= 'Z'; c++) {
    chars += c;
  }
  for (char c = 'a'; c <= 'z'; c++) {
    chars += c;
  }
  for (char c = '0'; c <= '9'; c++) {
    chars += c;
  }

#ifdef LOCAL
#define TEST
#endif

#ifdef TEST
  string ans;
  //cin >> ans;
  ans = chars + chars + chars;
  ans = ans.substr(0, 128);
  random_shuffle(ans.begin(), ans.end());
#endif
  int ops = 0;
  auto ask = [&](const string& a) {
    ops++;
#ifdef TEST
    int n = a.size();
    int m = ans.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 1e9));
    dp[0][0] = 0;
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j <= m; j++) {
        if (i != n) dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + 1);
        if (j != m) dp[i][j + 1] = min(dp[i][j + 1], dp[i][j] + 1);
        if (i != n && j != m) dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j] + (a[i] != ans[j]));
      }
    }
    eprintf("d(%s, %s) = %d\n", a.c_str(), ans.c_str(), dp.back().back());
    return dp.back().back();
#else
    printf("? %s\n", a.c_str());
    fflush(stdout);
    int res;
    scanf("%d", &res);
    return res;
#endif
  };

  vector<string> s;
  int tot_length = 0;
  for (char i : chars) {
    int len = 128 - ask(string(128, i));
    if (len != 0) {
      s.emplace_back(len, i);
    }
    tot_length += len;
  }

  auto is_substring = [&](const string& a) {
    return ask(a) == tot_length - (int)a.size();
  };

  auto merge = [&](const string& a, const string& b) {
    int p1 = 0, p2 = 0;
    string prefix;
    while (p1 < (int)a.size() && p2 < (int)b.size()) {
      if (is_substring(prefix + b[p2] + a.substr(p1))) {
        prefix += b[p2++];
      } else {
        prefix += a[p1++];
      }
    }
    return prefix + a.substr(p1) + b.substr(p2);
  };

  while (s.size() > 1) {
    sort(s.begin(), s.end(), [](const string& a, const string &b) { return a.size() > b.size(); });
    string a = s.back(); s.pop_back();
    string b = s.back(); s.pop_back();
    s.push_back(merge(a, b));
  }

  assert(ops <= 850);
  eprintf("done in %d ops\n", ops);
#ifdef TEST
  assert(s[0] == ans);
#endif
  printf("! %s\n", s[0].c_str());

  return 0;
}

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

string solve_slow(string s, int n) {
  string t = "";
  for (int i = 0; i < (1 << n); i++) {
    int cnt[2];
    cnt[0] = cnt[1] = 0;
    string r = "";
    for (int j = 0; j < (int)s.size(); j++) {
      if (i & (1 << cnt[s[j] - 'a'])) {
        r += s[j];
      }
      cnt[s[j] - 'a']++;
    }
    t = max(t, r);
  }
  return t;
}

string solve_bbig(string s, int n) {
  string t;
  for (int pos = 0; pos <= n; pos++){
    int cnt[2];
    cnt[0] = cnt[1] = 0;
    string r = "";
    for (int j = 0; j < (int) s.size(); j++) {
      if (cnt[s[j] - 'a'] >= pos) {
        r += s[j];
      }
      cnt[s[j] - 'a']++;
    }
    t = max(t, r);
  }

  return t;
}

string solve_abig(string s, int n) {
  string t;
  int cnt[2];
  cnt[0] = cnt[1] = 0;
  int next_id = 0;
  char now = 'a';

  for (int i = 0; i < 2 * n; i++) {
    if (s[i] == now && cnt[s[i] - 'a'] == next_id) {
      t += now;
      now = 'a' + 'b' - now;
      next_id = max(next_id, cnt[now - 'a']);
    }
    cnt[s[i] - 'a']++;
  }
  return t;
}

string solve_big(string s) {
  assert(s.size() % 2 == 0);
  int bal = 0;
  for (int i = 0; i < (int)s.size(); i++) {
    if (s[i] == 'a') {
      bal++;
    }
    if (s[i] == 'b') {
      bal--;
    }
    assert(i == (int)s.size() - 1 || bal != 0);
  }
  assert(bal == 0);
  if (s[0] == 'a') {
    return solve_abig(s, s.size() / 2);
  } else {
    return solve_bbig(s, s.size() / 2);
  }
}

string solve_common(string s, int n) {
  vector<string> v;
  int bal = 0;
  string cur;
  for (int i = 0; i < 2 * n; i++) {
    cur += s[i];
    if (s[i] == 'a') {
      bal++;
    } else {
      bal--;
    }
    if (bal == 0) {
      v.push_back(solve_big(cur));
      cur = "";
    }
  }
  v.push_back(solve_big(cur));
  string res;
  for (int i = (int)v.size() - 1; i >= 0; i--) {
    res = max(res, v[i] + res);
  }
  return res;
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  {
    int n;
    string s;
    while (cin >> n >> s) {
      printf("%s\n", solve_common(s, n).c_str());
    }
    return 0;
  }

  string v;
  int n = 8;
  for (int i = 0; i < n; i++) {
    v += 'a';
  }
  for (int i = 0; i < n; i++) {
    v += 'b';
  }

  do {
    int bal = 0;
    bool ok = true;
    for (int i = 0; i < 2 * n; i++) {
      if (v[i] == 'a') {
        bal++;
      }
      if (v[i] == 'b') {
        bal--;
      }
      if (i != 2 * n - 1 && bal == 0) {
        ok = false;
        break;
      }
    }
    if (1 || ok) {
      string s1 = solve_slow(v, n);
      string s2 = solve_common(v, n);
      eprintf("%s %s %s\n", v.c_str(), s1.c_str(), s2.c_str());
      assert(s1 == s2);
    }
  } while (next_permutation(v.begin(), v.end()));

  return 0;
}

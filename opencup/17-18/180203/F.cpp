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

char buf[1000100];

vector<string> read_string() {
  scanf("%s", buf);
  int n = strlen(buf);
  vector<int> p(n);
  {
    int k = 0;
    for (int j = 0; j < 2; j++) {
      for (int i = j; i < n; i += 2) {
        p[k++] = i;
      }
    }
  }
  vector<string> v;
  vector<bool> used(n);
  for (int i = 0; i < n; i++) {
    if (!used[i]) {
      string s = "";
      for (int j = i; !used[j]; j = p[j]) {
        s += buf[j];
        used[j] = true;
      }
      v.push_back(s);
    }
  }

  return v;
}

pair<int, int> get_match(string a, string b) {
  int len = a.size();
  string s = b + '$' + a + a;
  vector<int> p(s.size());
  vector<int> res;
  for (int i = 1; i + 1 < (int)s.size(); i++) {
    int j = p[i - 1];
    while (j && s[j] != s[i]) j = p[j - 1];
    if (s[j] == s[i]) j++;
    p[i] = j;
    if (p[i] == len) {
      res.push_back(i - 2 * len);
    }
  }
  if (res.empty()) {
    return {-1, -1};
  }
  assert(len % res.size() == 0);
  int m = len / res.size();
  int r = res[0];
  for (int x : res) {
    assert(x % m == r);
  }
  return {r, m};
}

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  vector<string> s = read_string();
  vector<string> t = read_string();

  assert(s.size() == t.size());

  int l = 0;
  for (const string& x : s) {
    l = max(l, (int)x.size());
  }

  vector<int> ok(l + 1, -1);

  for (int i = 0; i < (int)s.size(); i++) {
    assert(s[i].size() == t[i].size());
    assert(l % s[i].size() == 0);

    pair<int, int> match = get_match(s[i], t[i]);
    eprintf("match(%s, %s) = {%d,%d}\n", s[i].c_str(), t[i].c_str(), match.first, match.second);
    if (match.first == -1) {
      printf("-1\n");
      return 0;
    }
    if (ok[match.second] == -1) {
      ok[match.second] = match.first;
    }
    if (ok[match.second] != match.first) {
      printf("-1\n");
      return 0;
    }
  }

  vector<int> cor(l + 1, 0);
  int need = 0;

  for (int i = 1; i <= l; i++) {
    if (ok[i] != -1) {
      eprintf("%d %d\n", i, ok[i]);
      assert(l % i == 0);
      for (int j = ok[i]; j < l; j += i) {
        cor[j]++;
      }
      need++;
    }
  }

  for (int i = 0; i < l; i++) {
    if (cor[i] == need) {
      printf("%d\n", i);
      return 0;
    }
  }

  printf("-1\n");
  return 0;
}

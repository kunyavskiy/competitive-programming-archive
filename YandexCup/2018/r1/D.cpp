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

bool eq(char a, char b) {
  return a == b || a == '?' || b == '?';
}

bool matches(string s, const string& t) {
  int n = s.size();
  int tot = n;
  vector<int> matched(s.size());
  while (tot > 0) {
    int old_tot = tot;
    for (int i = 0; i < n; i++) {
      while (matched[i] < t.size() && i + matched[i] < s.size() && eq(t[matched[i]], s[i + matched[i]])) {
        matched[i]++;
        if (matched[i] == t.size()) {
          for (int j = i; j < i + matched[i]; j++) {
            if (s[j] != '?') {
              tot--;
              s[j] = '?';
            }
          }
        }
      }
    }
    if (tot == old_tot) {
      return false;
    }
  }
  return true;
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  string s;
  cin >> s;
  int n = s.size();
  vector<string> cand;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j <= n; j++) {
      cand.push_back(s.substr(i, j - i));
    }
  }
  sort(cand.begin(), cand.end());
  cand.erase(unique(cand.begin(), cand.end()), cand.end());

  matches(s, "ba");

  for (const string &t : cand) {
    if (matches(s, t)) {
      printf("%s\n", t.c_str());
    }
  }


  return 0;
}

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

int main() {
#ifdef LOCAL
  freopen("k.in", "r", stdin);
  freopen("k.out", "w", stdout);
#endif
  int n, k;
  scanf("%d%d", &n, &k);
  vector<string> w(n);
  char cc[100001];
  for (int i = 0; i < n; i++) {
    scanf("%s", cc);
    w[i] = cc;
  };

  vector<vector<int>> trie(1, vector<int>(26));
  vector<vector<int>> ends(1);
  vector<int> sz(1);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j + k <= w[i].size(); j++) {
      int c = 0;
      for (int t = j; t < j + k; t++) {
        if (trie[c][w[i][t] - 'a'] == 0) {
          trie[c][w[i][t] - 'a'] = (int)trie.size();
          sz.push_back(0);
          ends.push_back(vector<int>());
          trie.push_back(vector<int>(26));
        }
        c = trie[c][w[i][t] - 'a'];
        sz[c]++;
      }
      ends[c].push_back(i);
    }
  }

  string res = "";
  {
    int c = 0;
    for (int i = 0; i < k; i++) {
      int ch = 0;
      while (sz[trie[c][ch]] == 0) ch++;
      res += (char) ('a' + ch);
      c = trie[c][ch];
    }
  }

  vector<bool> alive(n, true);
  int nlive = n;

  vector<int> pp(k + 1);
  for (int i = 0; i < k; i++) {
    int c = 0;
    for (int j = i; j < k; j++) {
      c = trie[c][res[j] - 'a'];
      if (c == 0) {
        pp[k - i] = -1;
        break;
      }
    }
    if (c > 0) {
      pp[k - i] = c;
    }
  }

  int z = 0;
  while (nlive > 0) {
    if (sz[pp[k]] > 0 && ends[pp[k]].size() > 0) {
      for (int i : ends[pp[k]]) {
        if (alive[i]) {
          alive[i] = false;
          nlive--;
          for (int j = 0; j + k <= w[i].size(); j++) {
            int c = 0;
            for (int t = j; t < j + k; t++) {
              c = trie[c][w[i][t] - 'a'];
              sz[c]--;
            }
          }
        }
      }
      z = 0;
    } else {
      int ch = 0;
      while (true) {
        bool ok = false;
        for (int i = z; i < k; i++) {
          if (pp[i] >= 0 && sz[trie[pp[i]][ch]] > 0) {
            ok = true;
            break;
          }
        }
        if (ok) break;
        ch++;
      }
      res += (char)('a' + ch);
      z++;
      for (int i = k; i > 0; i--) {
        pp[i] = pp[i - 1];
        if (pp[i] >= 0) {
          pp[i] = trie[pp[i]][ch];
          if (pp[i] == 0) pp[i] = -1;
        }
      }
    }
  }

  cout << res << "\n";

  return 0;
}

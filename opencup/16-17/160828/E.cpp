//#include <iostream>
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
#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ( ( _WIN32 || __WIN32__ ) && __cplusplus < 201103L)
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "E"

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

const int MOD = 1000000007;

const int MAXN = 100010;
const int MAXM = 15;

int n, k, m;
char s[MAXN];
char t[MAXM];

int current[MAXM][MAXM];

void add(int& a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

void sub(int& a, int b) {
  if ((a -= b) < 0) a += MOD;
}

void push_back(char c) {
  for (int len = m; len >= 1; len--) {
    for (int i = 0; i + len <= m; i++) {
      int j = i + len;
      if (t[j - 1] == c) {
        add(current[i][j], current[i][j-1]);
      }
    }
  }
}

void pop_front(char c) {
  for (int len = 1; len <= m; len++) {
    for (int i = 0; i + len <= m; i++) {
      int j = i + len;
      if (t[i] == c) {
        sub(current[i][j], current[i+1][j]);
      }
    }
  }
}


int main() {
#ifdef LOCAL
  assert(freopen(TASKNAME".in", "r", stdin));
  assert(freopen(TASKNAME".out", "w", stdout));
#endif

  scanf("%d%d%d", &n, &m, &k);
  scanf("%s%s", s, t);

  for (int i = 0; i <= m; i++) {
    current[i][i] = 1;
  }

  for (int i = 0; i < n; i++) {
    push_back(s[i]);
  }

  int ans = current[0][m];

  memset(current, 0, sizeof(current));
  for (int i = 0; i <= m; i++) {
    current[i][i] = 1;
  }

  for (int i = 0; i < k; i++) {
    push_back(s[i]);
  }

  for (int i = 0; i < n; i++) {
    pop_front(s[i]);
    if (s[i] == t[0]) {
      sub(ans, current[1][m]);
    }
    if (i + k < n) {
      push_back(s[i + k]);
    }
  }

  printf("%d\n", ans);
  return 0;
}

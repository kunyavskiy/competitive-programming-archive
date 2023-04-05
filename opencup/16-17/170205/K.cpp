#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

using namespace std;

#define TASKNAME "K"

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

const int MAXN = 251000;

char s[MAXN];
int pos[MAXN];
vector<int> parts[MAXN];

int solve_part(int n, int maxd, int L) {
  if (n <= 2) {
    return 0;
  }
  int ans = 0;
  for (int d = 1; d <= maxd; d++) {
    for (int i = 0; i < n; i++) {
      parts[pos[i] % d].push_back(pos[i]);
    }
    for (int i = 0; i < n; i++) {
      int pid = pos[i] % d;
      int sz = (int)parts[pid].size();
      if (sz == 0) continue;

      if ((L - pid - 1) / d >= n - 1) {
        int p = 0;
        for (int j = 0; j < sz; j++) {
          while (p < sz && parts[pid][j] + (n - 1) * d >= parts[pid][p]) p++;
          ans = max(ans, p - j);
//          fprintf(stderr, "n = %d, d = %d, p - j = %d, pid = %d\n", n, d, p - j, pid);
        }
      }

      parts[pid].clear();
    }
  }
  return n - ans;
}

void solve() {
  scanf("%s", s);
  int n = strlen(s);
  for (char c = 'a'; c <= 'z'; c++) {
    int ptr = 0;
    for (int i = 0; i < n; i++) {
      if (s[i] == c) {
        pos[ptr++] = i;
      }
    }
    if (ptr != 0) {
      int res;
      if (ptr <= 2) {
        res = 0;
      } else {
        res = solve_part(ptr, (n - 1) / (ptr - 1), n);
      }
      printf("%d ", res);
    }
  }
  printf("\n");
}

int main() {
#ifdef LOCAL
  assert(freopen(TASKNAME".in", "r", stdin));
  assert(freopen(TASKNAME".out", "w", stdout));
#endif

  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; i++)
    solve();
  return 0;
}

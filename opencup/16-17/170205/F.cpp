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

#define TASKNAME "F"

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

const int MAXN = int(1e6) + 100;
static char s[MAXN];

void winA() {
  printf("Apfelmann\n");
}

void winB() {
  printf("Bananenfrau\n");
}

void solve() {
  scanf("%s", s);
  int n = int(strlen(s));
  if (s[0] != 'A' && s[n - 1] != 'A') {
    winA();
    return;
  }
  if (s[0] != 'B' && s[n - 1] != 'B') {
    winB();
    return;
  }

  if (s[0] != 'A') {
    reverse(s, s + n);
  }
  assert(s[0] == 'A' && s[n - 1] == 'B');

  int pos = 0;
  while (s[pos] != 'C') {
    ++pos;
  }

  int i = pos - 1;
  int j = pos + 1;
  for (int move = 0; ; move ^= 1) {
    if (i < 0) {
      winA();
      return;
    }
    if (j >= n) {
      winB();
      return;
    }
    bool canL = (s[i] == 'A' + move);
    bool canR = (s[j] == 'A' + move);
    if (canL && canR) {
      //bool canL2 = (i - 1 >= 0 && s[i - 1] == 'A' + (move ^ 1));
      //bool canR2 = (i + 1 < n  && s[i + 1] == 'A' + (move ^ 1));
      if (move == 0) {
        --i;
      } else {
        ++j;
      }
    } else if (canL) {
      --i;
    } else if (canR) {
      ++j;
    }
  }
}

int main() {
#ifdef LOCAL
  assert(freopen(TASKNAME".in", "r", stdin));
  assert(freopen(TASKNAME".out", "w", stdout));
#endif

  int n;
  scanf("%d", &n);
  for (int ii = 0; ii < n; ++ii) {
    solve();
  }

  return 0;
}

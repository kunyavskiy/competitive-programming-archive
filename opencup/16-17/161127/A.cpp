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

#define TASKNAME "A"

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

char s[122][122];

string get(int x, int y, int n, int m) {
  string res = "";
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      res += s[x + i][y + j];
    }
  }
  string res2 = "";
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      res2 += s[x + n - i - 1][y + m - j - 1];
    }
  }
  res = min(res, res2);
  if (n == m) {
    res2 = "";
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        res2 += s[x + j][y + n - i - 1];
      }
    }
    res = min(res, res2);

    res2 = "";
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        res2 += s[x + n - j - 1][y + i];
      }
    }
    res = min(res, res2);
  }
  return res;
}

int main() {
#ifdef LOCAL
  assert(freopen(TASKNAME".in", "r", stdin));
  assert(freopen(TASKNAME".out", "w", stdout));
#endif

  int r, c;
  scanf("%d%d",&r, &c);
  for (int i = 0; i < r; i++) {
    scanf("%s", s[i]);
  }

  int n, m;
  n = m = -1;

  for (int i = 1; i < r; i++) {
    bool ok = true;
    for (int j = 0; j < c; j++) {
      ok &= s[i][j] == '#';
    }
    if (ok) {
      n = i - 1;
      break;
    }
  }
  assert(n != -1);

  for (int i = 1; i < c; i++) {
    bool ok = true;
    for (int j = 0; j < r; j++) {
      ok &= s[j][i] == '#';
    }
    if (ok) {
      m = i - 1;
      break;
    }
  }

  eprintf("%d %d\n", n, m);

  vector<string> v;

  for (int i = 1; i < r; i += n + 1) {
    for (int j = 1; j < c; j += m + 1) {
      v.push_back(get(i, j, n, m));
      eprintf("%s\n", v.back().c_str());
    }
  }

  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());
  printf("%d\n", (int)v.size());

  return 0;
}

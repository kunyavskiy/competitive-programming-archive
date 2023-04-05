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

/*int solve(vector<int> a, vector<int> b) {
  int ans = 0;
  for (int i = 0; i < (int)a.size(); i++) {
    if (a[i] != b[i]) {
      int j = i;
      while (a[j] != -1) {
        int x = a[j];
        a[j] = -1;
        ans++;
        j = x;
      }
    }
  }
  return ans;
}*/

int main() {
#ifdef LOCAL
  assert(freopen(TASKNAME".in", "r", stdin));
  assert(freopen(TASKNAME".out", "w", stdout));
#endif

  int n;
  scanf("%d", &n);
  vector<int> p(n), q(n);

  for (int &x : p) scanf("%d", &x), x--;
  for (int &x : q) scanf("%d", &x), x--;

  vector<int> v(n);

  int ans = 0;

  for (int i = 0; i < n; i++) {
    if (p[i] != q[i]) v[i] = 1;
    if (v[i]) {
      if (p[i] != -1) v[p[i]] = 1, ans++;
      if (q[i] != -1) v[q[i]] = 1, ans++;
    }
  }

  printf("%d\n", ans);
  return 0;
}

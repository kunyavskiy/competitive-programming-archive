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

#define TASKNAME "J"

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

bool dfs(int s, int t, vector <int> & path, vector <bool> & used, const vector <vector <int>> & a) {
  if (used[s]) {
    return false;
  }
  used[s] = true;
  path.push_back(s);
  if (s == t) {
    return true;
  }
  for (int i = 0; i < int(a.size()); ++i) {
    if (a[s][i] > 0) {
      if (dfs(i, t, path, used, a)) {
        return true;
      }
    }
  }
  path.pop_back();
  return false;
}

vector<int> findPath(int s, int t, const vector <vector<int>> & a) {
  vector <int> path;
  vector <bool> used(a.size(), false);
  dfs(s, t, path, used, a);
  return path;
}

int main() {
#ifdef LOCAL
  assert(freopen(TASKNAME".in", "r", stdin));
  assert(freopen(TASKNAME".out", "w", stdout));
#endif

  int n, m;
  scanf("%d%d", &n, &m);
  vector <vector<int>> a(n, vector<int>(n, -1));
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    --u, --v;
    a[u][v] = a[v][u] = w;
  }

  vector <int> path = findPath(0, n - 1, a);
  if (path.empty()) {
    printf("-1\n");
    return 0;
  }

  int k;
  scanf("%d", &k);
  vector <vector<int>> v(k);
  for (int i = 0; i < k; ++i) {
    int len;
    scanf("%d", &len);
    vector<int> & cur = v[i];
    for (int j = 0; j < len; ++j) {
      int x;
      scanf("%d", &x);
      --x;
      cur.push_back(x);
    }
  }

  int totLen = int(path.size());
  for (int i = 0; i < k; ++i) {
    totLen += (int(v[i].size()) - 1) * 2;
  }

  for (int i = 0; i < k; ++i) {
    printf("%d 1", totLen);
    for (int j = 0; j < k; ++j) {
      vector <int> & cur = v[(i + j) % k];
      for (int t = 1; t < int(cur.size()); ++t) {
        printf(" %d", cur[t] + 1);
      }
      for (int t = int(cur.size()) - 2; t >= 0; --t) {
        printf(" %d", cur[t] + 1);
      }
    }
    for (int i = 1; i < int(path.size()); ++i) {
      printf(" %d", path[i] + 1);
    }
    printf("\n");
  }

  return 0;
}

#include <bits/stdc++.h>

#define pb push_back
#define mp make_pair
#define TASKNAME "F"

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("[" #x "] Time = %.3lfs\n",clock()*1.0/CLOCKS_PER_SEC)

#ifdef _WIN32
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

#define sz(x) ((int)(x).size())
#define forn(i, n) for (int i = 0; i < (n); i++)

using namespace std;

typedef long double ld;
typedef long long ll;
typedef vector <ll> vll;
typedef vector<int> vi;
typedef vector <vi> vvi;
typedef vector<bool> vb;
typedef vector <vb> vvb;
typedef pair<int, int> pii;
typedef pair <ll, ll> pll;
typedef vector <pii> vpii;

const int inf = 1e9;
const ld eps = 1e-9;
const int INF = inf;
const ld EPS = eps;

#ifdef LOCAL
struct __timestamper {
  ~__timestamper(){
    TIMESTAMP(end);
  }
} __Timestamper;
#else
struct __timestamper {
};
#endif

/*Template end*/

vector<vector<int>> g;

struct item {
  int d, val;
  int x;

  bool operator<(const item &rhs) const {
    if (d != rhs.d) return d < rhs.d;
    if (val != rhs.val) return val < rhs.val;
    return false;
  }

  bool operator==(const item &rhs) const {
    return d == rhs.d && val == rhs.val;
  }

};

int m;

int mul(int a, int b) {
  return (a * 1LL * b) % m;
}

int pow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) res = mul(res, a);
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int b;
  scanf("%d%d", &b, &m);
  g.resize(m);

  for (int i = 0; i < m; i++) {
    for (int k = 0; k < b; k++) {
      g[(b * i + k) % m].push_back(i);
    }
  }

  vector<int> d(m, -1);
  d[0] = 0;

  queue<int> q;
  q.push(0);

  eprintf("bfs\n");

  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (int x : g[v]) {
      if (d[x] == -1) {
        d[x] = d[v] + 1;
        q.push(x);
      }
    }
  }
  eprintf("bfs done\n");

  vector<item> v;

  for (int i = 0; i < m; i++) {
    assert(d[i] != -1);
    v.push_back({d[i], mul(i, pow(b, d[i])), i});
  }

  sort(v.begin(), v.end());

  vector<int> comp(m);
  vector<int> ex;

  int id = -1;

  for (int i = 0; i < m; i++) {
    if (!i || !(v[i] == v[i-1])) {
      id++;
      ex.push_back(v[i].x);
    }
    comp[v[i].x] = id;
  }
  id++;

  printf("%d %d\n", id, comp[0]);
  for (int i = 0; i < id; i++) {
    printf("%c%c", "BG"[i == comp[0]], " \n"[i == id - 1]);
  }

  for (int i = 0; i < id; i++) {
    for (int j = 0; j < b; j++) {
      printf("%d%c", comp[(ex[i] * b + j) % m], " \n"[j == b - 1]);
    }
  }

  return 0;
}

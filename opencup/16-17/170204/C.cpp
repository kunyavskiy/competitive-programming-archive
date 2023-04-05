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

#define TASKNAME "C"

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

const int MAXN = 210000;

const int MOD = 1000000007;

ll mul(ll a, ll b) {
  return (a * 1LL * b) % MOD;
}

vector<int> g[MAXN];
vector<int> id[MAXN];
vector<ll> rnd[MAXN];
int tin[MAXN], tup[MAXN], used[MAXN];
ll h[MAXN];
int cnt[MAXN];
map<ll, int> hs;

int timer;
int n, m;
int comps, bridges;
ll bridges2;

void dfs(int v, int pid) {
  used[v] = 1;
  tin[v] = tup[v] = timer++;
  h[v] = 0;
  cnt[v] = 0;
  for (int i = 0; i < (int)g[v].size(); i++) {
    int to = g[v][i];
    if (id[v][i] == pid) continue;
    if (used[to] == 1) {
      cnt[v]++;
      h[v] ^= rnd[v][i];
      continue;
    }
    if (used[to] == 2) {
      cnt[v]--;
      h[v] ^= rnd[v][i];
      continue;
    }
    dfs(to, id[v][i]);
    cnt[v] += cnt[to];
    h[v] ^= h[to];
  }
  if (cnt[v] == 0 && pid != -1) {
    bridges++;
  }
  if (cnt[v] == 1) {
    bridges2++;
  }
  if (cnt[v] > 0) {
    bridges2 += hs[h[v]];
    hs[h[v]]++;
  }
  used[v] = 2;
}

ll mpow(ll a, ll b) {
  if (b < 0) return 0;
  ll res = 1;
  while (b) {
    if (b & 1) res = mul(res, a);
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

void solve() {
  for (int i = 0; i < n; i++) {
    g[i].clear();
    id[i].clear();
    rnd[i].clear();
    tin[i] = tup[i] = used[i] = 0;
  }
  hs.clear();
  for (int i = 0; i < m; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a, --b;
    g[a].push_back(b);
    g[b].push_back(a);
    id[a].push_back(i);
    id[b].push_back(i);
    ll r = lrand48() | (((ll)lrand48()) << 32);
    rnd[a].push_back(r);
    rnd[b].push_back(r);
  }

  comps = bridges = 0;
  bridges2 = 0;

  for (int i = 0; i < n; i++) {
    if (used[i]) continue;
    comps++;
    dfs(i, -1);
  }

  bridges2 %= MOD;

//  fprintf(stderr, "%d %lld %d\n", bridges, bridges2, comps);

  ll ans1 = mul(m - bridges, mpow(2, m - n + comps - 1));
  ll ans2 = mul(mul(m - bridges, m - bridges - 1) - 2 * bridges2, mpow(2, m - n + comps - 2));
  ll ans3 = mul(2 * bridges2, mpow(2, m - n + comps - 1));

  printf("%lld\n", ((ans1 + ans2 + ans3) % MOD + MOD) % MOD);
}

int main() {
#ifdef LOCAL
  assert(freopen(TASKNAME".in", "r", stdin));
  assert(freopen(TASKNAME".out", "w", stdout));
#endif

  while (scanf("%d%d", &n, &m) == 2) {
    solve();
//    break;
  }

  return 0;
}

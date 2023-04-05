#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;

void add(int& a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

struct item {
  int maxv, cnt;
};

item operator+(const item& a, const item& b) {
  if (a.maxv == b.maxv) {
    item res = a;
    add(res.cnt, b.cnt);
    return res;
  }
  if (a.maxv > b.maxv) return a;
  return b;
}

item operator*(const item& a, int x) {
  return {a.maxv, (int)((a.cnt * 1LL * x) % MOD)};
}

const int MAXN = 100000;

int lst;
item tree[4 * MAXN];
item upd[4 * MAXN];

void setval(int v, item x, int l, int r) {
  upd[v] = x;
  tree[v] = x * (r - l + 1);
}

void push(int v, int l, int r) {
  if (upd[v].maxv != -1) {
    setval(2*v, upd[v], l, (l + r) / 2);    
    setval(2*v + 1, upd[v], (l + r) / 2 + 1, r);
    upd[v].maxv = -1;
  }
}

item get(int v, int l, int r, int L, int R) {
  if (r < L || R < l) return {-1, 0};
  if (L <= l && r <= R) {
    return tree[v];
  }
  push(v, l, r);
  return get(2*v, l, (l+r)/2, L, R) + get(2*v+1, (l+r)/2 + 1, r, L, R);
}

void update(int v, int l, int r, int L, int R, item x) {
  if (r < L || R < l) return;
  if (L <= l && r <= R) {
    setval(v, x, l, r);
    return;
  }
  push(v, l, r);
  update(2*v, l, (l+r)/2, L, R, x);
  update(2*v+1, (l+r)/2 + 1, r, L, R, x);
  tree[v] = tree[2*v] + tree[2*v+1];
}



struct segment {
  int i;
  int l, r;
};

const int MAXA = 2500100;

vector<segment> segs[MAXA];


int main() {
  int n;
  scanf("%d", &n);
  vector<int> a(n);
  for (int &x : a) {
    scanf("%d", &x);
  }

  vector<pair<int, int>> v;

  for (int i = n - 1; i >= 0; i--) {
    vector<pair<int, int>> nv;
    nv.push_back({a[i], i});

    for (int j = 0; j < (int)v.size(); j++) {
      int g = __gcd(v[j].first, a[i]);
      if (g == nv.back().first) {
        nv.back().second = v[j].second;
      } else {
        nv.push_back({g, v[j].second});
      }
    }

    v = nv;

    for (int j = 0; j< (int)v.size(); j++) {
      segs[v[j].first].push_back({i, j ? v[j - 1].second + 1 : i, v[j].second + 1});
    }
  }

  lst = 2;
  while (lst <= n) lst *= 2;

  item ans = {0, 1};

  for (int g = 1; g < MAXA; g++) {
    if (!segs[g].size()) continue;

    //if (g != 1) continue;


    update(1, 0, lst - 1, 0, lst - 1, {0, 1});
    item cur = {0, 1};
    for (int i = 0; i < (int)segs[g].size(); i++) {
      //fprintf(stderr, "get(%d,%d)\n", segs[g][i].l + 1, segs[g][i].r);
      item res = get(1, 0, lst - 1, segs[g][i].l + 1, segs[g][i].r);
      res.maxv++;
      //fprintf(stderr, "res = %d,%d\n", res.maxv, res.cnt);
      cur = cur + res;
      //fprintf(stderr, "cur = %d,%d\n", cur.maxv, cur.cnt);
      update(1, 0, lst - 1, 0, segs[g][i].i, cur);
    }
    
    ans = ans + cur;
  }

  printf("%d %d\n", ans.maxv, ans.cnt);
}

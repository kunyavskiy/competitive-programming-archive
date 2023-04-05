/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define forab(i, a, b) for (int i = (a); i <= (b); i++)
#define sz(a) (int)(a).size()
#define all(a) (a).begin(), (a).end()
#define pb push_back

typedef pair<int,int> pii;

const int LOG = 11, N = 501, M = 1003 + 32, M1 = M / 32, inf = 1e8;

int n, m, k[N];
vector<int> a[N], ra[N], goal, rgoal;
int f[N], g[N][N];
bitset<M> pref[N][LOG], suf[N][LOG];
vector<bitset<M>> suf2[N][LOG];

void bfs1() {
  int qst = 0, qen = 0;
  int q[N];
  memset(f, 0x7F, sizeof(f));
  q[qen++] = 1, f[1] = 1;
  while (qst < qen) {
    int i = q[qst++];
    if (m == 1 && goal[0] == i) {
      printf("%d\n", f[i]);
      exit(0);
    }
    for (int x : a[i])
      if (f[x] > inf)
        f[x] = f[i] + 1, q[qen++] = x;
  }
}

void bfs2() {
  int qst = 0, qen = 0;
  pii q[N * N];
  memset(g, 0x7F, sizeof(g));
  auto add = [&]( int i, int j, int d ) {
    if (g[i][j] < inf)
      return;
    g[i][j] = d;
    q[qen++] = pii(i, j);
  };
  forn(j, a[1].size() - 1)
    add(a[1][j], a[1][j + 1], 2);
  while (qst < qen) {
    pii p = q[qst++];
    int x = p.first, y = p.second;
    int F = g[x][y] + 1;
    forn(j, a[x].size() - 1) add(a[x][j], a[x][j + 1], F);
    forn(j, a[y].size() - 1) add(a[y][j], a[y][j + 1], F);
    add(a[x].back(), *a[y].begin(), F);
  }
}

int ans = inf;

inline void relax( int x ) { ans = min(ans, x); }

bool is( bitset<M> &a, bitset<M> &b ) {
  unsigned *a0 = (unsigned *)&a, *b0 = (unsigned *)&b;
  forn(i, M1)
    if (a0[i] & b0[i])
      return 1;
  return 0;
}
 
vector<int> t, tmp;

bitset<M> calc_bitset( vector<int> &g, vector<int> &t, bool flag = 0 ) {
  static vector<int> a, p;
  a.clear();
  a.insert(a.end(), all(g));
  a.pb(-1);
  a.insert(a.end(), all(t));
  p.resize(sz(a));
  int k = 0;
  p[0] = k;
  for (int i = 1; i < sz(a); i++) {
    while (k && a[i] != a[k])
      k = p[k - 1];
    p[i] = (k += (a[i] == a[k]));
  }
  bitset<M> res;
  if (flag) {
    res[0] = 1;
    while (k)
      res[k] = 1, k = p[k - 1];
  } else {
    res[m] = 1;
    while (k)
      res[m - k] = 1, k = p[k - 1];
  }
  return res;
}

void calc_pref() {
  forab(i, 1, n) {
    t.clear();
    t.pb(i);
    forn(k, LOG) {
      pref[i][k] = calc_bitset(goal, t, 1);
      tmp.swap(t);
      t.clear();
      reverse(all(tmp));
      for (int x : tmp)
        for (int y : ra[x])
          if (sz(t) <= m)
            t.pb(y);
          else
            goto end;
      end:;
      reverse(all(t));
    }
  }
}

void calc_suf() {
  forab(i, 1, n) {
    t.clear();
    t.pb(i);
    forn(k, LOG) {
      suf[i][k] = calc_bitset(t, goal);
      tmp.swap(t);
      t.clear();
      for (int x : tmp)
        for (int y : a[x])
          if (sz(t) <= m)
            t.pb(y);
          else
            goto end;
      end:;
    }
  }
}

void calc_suf2() {
  forab(i, 1, n)  
    forn(k, LOG)
      suf2[i][k].resize(sz(a[i]));
  forab(i, 1, n) 
    forn(l, sz(a[i])) {
      t.clear();
      for (int j = l; j < sz(a[i]); j++)
        t.pb(a[i][j]);
      forn(k, LOG) {
        suf2[i][k][l] = calc_bitset(t, goal);
        tmp.swap(t);
        t.clear();
        for (int x : tmp)
          for (int y : a[x])
            if (sz(t) <= m)
              t.pb(y);
            else
              goto end;
        end:;
      }
    }
}

void out(bitset<M>& a) {
   for (int i = 0; i <= m; i++)
      printf("%d", (int)a[i]);
   puts("");
}

int main() {
  scanf("%d%d", &n, &m);
  forab(i, 1, n) {
    scanf("%d", &k[i]);
    a[i].resize(k[i]);
    for (int &x : a[i])
      scanf("%d", &x);
    ra[i] = a[i];
    reverse(all(ra[i]));
  }
  goal.resize(m);
  forn(i, m)
    scanf("%d", &goal[i]);
  rgoal = goal, reverse(all(rgoal));
    
  bfs1();
  bfs2();
  calc_pref();
  calc_suf();
  calc_suf2();
  
  forab(i, 1, n) 
    if (f[i] < inf) 
      for (int l = 1; l < sz(a[i]); l++)
        forn(k, LOG) {
          if (is(pref[a[i][l - 1]][k], suf2[i][k][l])) {
            relax(f[i] + k + 1);
/*
            if (f[i] + k == 2) {
               printf("i = %d, l = %d, k = %d, f[i] = %d,\n", i, l, k, f[i]);  
               out(pref[a[i][l-1]][k]);
               out(suf2[i][k][l]);
            }
*/
          }
        }
  forab(i, 1, n) 
    forab(j, 1, n) 
      if (g[i][j] < inf) 
        forn(k, LOG)
          if (is(pref[i][k], suf[j][k])) {
            relax(g[i][j] + k);            
/*            if (g[i][j] + k == 2) {
               printf("i = %d, j = %d, k = %d\n", i, j, k);               
            }*/
          }
  printf("%d\n", ans == inf ? -1 : ans);
}


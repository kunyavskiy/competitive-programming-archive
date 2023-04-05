/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int N = 1e6 + 1, K = 26;

int n, c, a[K][K], cost[K][K], pa[K], ans = 0, u[K], in[K];
char s[N], t[N];

int F() {
  int res = 0;
  forn(i, n)
    res += cost[i][pa[i]];
  fill(u, u + K, 0);

  int cc = 0, cnt_cycle = 0;
  forn(i, n)
    in[pa[i]]++;
  int good = 0;
  fill(in, in + K, 0);
  forn(i, n)
    good |= !in[i];
  forn(i, n) if (!u[i]) {
    int p = i;
    forn(_, n) p = pa[p];
    if (u[p])
      continue;
    int len = 0;
    cc++;
    while (u[p] != cc)
      u[p] = cc, p = pa[p], len++;
    int is = 0;
    forn(j, n)
      if (u[j] != cc && u[pa[j]] == cc)
        is = 1;
    if (!is && len > 1)
      cnt_cycle ++;
  }    
  return (!good && cnt_cycle > 0) ? INT_MAX : res + cnt_cycle * c;
}

void relax( int x ) { ans = min(ans, x); }

int main() {
  scanf("%d%d%s%s", &n, &c, s, t);
  for (int i = 0; s[i]; i++) { 
    a[s[i] - 'a'][t[i] - 'a']++;
    ans += (s[i] != t[i]);
  }
  if (c < ans) {
    forn(i, K) {
      int sum = accumulate(a[i], a[i] + K, 0);
      forn(j, K) 
        cost[i][j] = (i == j ? 0 : c) + (sum - a[i][j]);
      pa[i] = min_element(cost[i], cost[i] + K) - cost[i];
    }
    forn(t, 1000) {
      relax(F());
      swap(pa[rand() % n], pa[rand() % n]);
    }
  }
  printf("%d\n", ans);
}


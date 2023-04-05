/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

template <class T> inline void uix( T &a, T b ) { a = min(a, b); }
template <class T> inline void uax( T &a, T b ) { a = max(a, b); }

typedef long long ll;

const int MAX_D = 2e5 + 3;

ll f[MAX_D];
double g[MAX_D];

int main() {
  int n, D, p;
  scanf("%d%d%d", &n, &D, &p);
  int c[n], d[n];
  forn(i, n)
    scanf("%d%d", &c[i], &d[i]);
  int md = 2 * D + 1;
  fill(f, f + md, (ll)1e18);
  f[0] = 0;
  forn(i, D)
    forn(j, n)
      uix(f[i + d[j]], f[i] + c[j]);
  fill(g, g + md, 1e18);
  g[0] = 0;
  forn(i, md) if (i)
    if (f[i] <= p) {
      g[i] = 0;
      forn(j, n) 
        uix(g[min(md - 1, i + d[j])], (double)max(0LL, c[j] - (p - f[i])) / i);
    }
//  forn(i, md)
//    printf("%d; %.6f\n", i, g[i]);
  forn(i, D) if (i)
    forn(j, n) 
      uix(g[i + d[j]], g[i] + (double)c[j] / i);
//  forn(i, md)
//    printf("%d; %.6f\n", i, g[i]);
  printf("%.15f\n", *min_element(g + D, g + md));
}


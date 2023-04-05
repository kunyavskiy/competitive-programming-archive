#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

const int N = 100, K = 91;

#include "h.out"

int main() {
  freopen("unrumpf.in", "r", stdin);
  FILE *f = fopen("unrumpf.ans", "r");
  int tn;
  //printf("%g\n", log(2));
  scanf("%d", &tn);
  double diff = 0;
  forn(i, N) {
    int l = K, r = 0;
    forn(j, K) {
      if (border[i][j] != -1) {
        l = min(l, j);
        r = max(r, j);
      }
    }
    if (l <= r) {
      for (int j = l; j <= r; j++)
        if (border[i][j] == -1) {
          border[i][j] = border[i][j - 1];
/*
          int lj = j, rj = j;
          while (border[i][lj] == -1) lj--;
          while (border[i][rj] == -1) rj++;
          border[i][j] = border[i][lj] + (border[i][rj] - border[i][lj]) * (i - lj) / (rj - lj);
*/
        }
    }
  }
  forn(_, tn) {
    int n;
    scanf("%d", &n);
    int x[n], y[n];
    forn(i, n) scanf("%d%d", &x[i], &y[i]);
    double p = 0;
    long long s = 0;
    forn(i, n) {
      int j = (i + 1) % n;
      ll dx = x[j] - x[i];
      ll dy = y[j] - y[i];
      p += sqrt(dx * dx + dy * dy);
      s += (ll)x[j] * y[i] - (ll)x[i] * y[j];
    }
    s = abs<long long>(s);
    int ans;
    fscanf(f, "%d", &ans);
    double *b = border[n - 1];
    int mi = 0;
    double sum_w = 0, sum_value = 0;
    forn(i, K)
      if (fabs(b[i] - s) < fabs(b[mi] - s))
        mi = i;
    if (b[mi] == -1)
      mi = (n < 10 ? 10 : 100);
    mi = max(10, min(mi, 100));
    
/**
      if (b[i] != -1) {
        double z = max(b[i] / s, s / b[i]) - 1;
        double w = exp(-z * 3);
        sum_w += w;
        sum_value += w * i;
      }
    if (sum_w == 0)
      mi = (n < 10 ? 10 : 100);
    else
      mi = max(10, min((int)round(sum_value / sum_w), 100));
*/
    diff += fabs(log(ans) - log(mi));
  }
  printf("diff = %.5f\n", diff / tn);
}


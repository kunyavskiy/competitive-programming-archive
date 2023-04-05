#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;


int main() {
  freopen("hh.in", "r", stdin);
  FILE *f = fopen("hh.out", "r");
  int tn;
  scanf("%d", &tn);
  const int n = 100;
  vector<double> r[n + 1][n + 1];
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
    double r1 = sqrt(s / M_PI);
    double r2 = p / (2 * M_PI);
    r[ans][n].push_back(s);
    //r[ans].push_back(r1 / r2);
  }
  puts("double border[N][K] = {");
  for (int j = 1; j <= n; j++) { 
    printf("{");
    for (int i = 10; i <= n; i++) {
      auto &v = r[i][j];
      if (v.size()) {
        sort(v.begin(), v.end());
        printf("%g, ", v[v.size() / 2]);
      } else {
        printf("-1, ");
      }
    }
    printf("},\n");
  }
  puts("};");
}


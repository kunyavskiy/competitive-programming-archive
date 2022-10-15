#include <cstdio>
#include <cstdlib>

#define YES { printf("YES\n"); exit(0);}
#define NO { printf("NO\n"); exit(0);}

int x[11];
int y[11];

long long vp(int i, int j) {
  return x[i] * 1LL * y[j] - x[j] * 1LL * y[i];
}

long long sp(int i, int j) {
  return x[i] * 1LL * x[j] + y[i] * 1LL * y[j];
}

int main(){
  int a, b;
  scanf("%d%d",&a,&b);
  scanf("%d%d",&x[0], &y[0]);
  x[0] -= a;
  y[0] -= b;
  int n;
  scanf("%d",&n);
  for (int i = 1; i <= n; i++)
      scanf("%d%d",&x[i],&y[i]);
  if (!x[0] && !y[0]) YES;
  for (int i = 1; i <= n; i++) {
      if (vp(i, 0) == 0 && sp(i, 0) > 0) {
	YES;
	continue;
      }
      if (vp(i, 0) == 0 && sp(i, 0) < 0) continue;
      for (int j = 1; j <= n; j++) {
	if (vp(j, 0) == 0) continue;
	if (vp(i, 0) > 0 && vp(0, j) > 0 && vp(i, j) > 0) YES;
      }
  }
  NO;
}

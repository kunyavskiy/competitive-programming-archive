#include <cstdio>

const int MAXN = 100000;

int p[3][MAXN];

int get(int* p, int a) {
  if (a == p[a]) return a;
  return p[a] = get(p, p[a]);
}

int join(int* p, int a, int b){
  a = get(p, a);
  b = get(p, b);
  if (a == b) return 0;
  p[a] = b;
  return 1;
}

int main() {
  int n,m,q;
  scanf("%d %d %d",&n,&m,&q);
  int cnt[3];
  cnt[0] = cnt[1] = cnt[2] = n;
  for (int i = 0; i < n; i++)
      p[0][i] = p[1][i] = p[2][i] = i;
  for (int i = 0; i < m; i++) {
    int a, b, t;
    scanf("%d%d%d",&a,&b,&t);
    --a, --b;
    cnt[t] -= join(p[t], a, b);
    cnt[2] -= join(p[2], a, b);
  }

  int mina = cnt[1] - 1;
  int maxa = n - cnt[0];
  for (int i = 0; i < q; i++) {
    int a;
    scanf("%d",&a);
    if (cnt[2] == 1 && mina <= a && a <= maxa) {
      printf("YES\n");
    } else {
      printf("NO\n");
    }
  }
  return 0;
}

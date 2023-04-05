#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 100000;

int next[2*MAXN][2];
int cnt[2*MAXN];
char s[2*MAXN];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);

  memset(next, -1, sizeof(next));
  cnt[0] = 0;

  int ptr = 1;

  for (int i = 0; i < n; i++) {
    scanf("%s", s);

    int ans = 0;
    int v = 0;
    for (int j = 0; j < m && v != -1; j++) {
      if (s[j] == '0') {
        v = next[v][1];
      } else {
        if (next[v][1] != -1) {
          ans += cnt[next[v][1]];
        }
        v = next[v][0];
      }
    }
    printf("%d\n", ans);
    fflush(stdout);
    v = 0;
    cnt[0]++;
    for (int j = 0; j < m; j++) {
      if (next[v][s[j] - '0'] == -1) {
        next[v][s[j] - '0'] = ptr++;
      }
      v = next[v][s[j] - '0'];
      cnt[v]++;
    }
  }

  return 0;
}

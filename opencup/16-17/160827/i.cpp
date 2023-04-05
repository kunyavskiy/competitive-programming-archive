#include <cstdio>
#include <unordered_map>
#include <vector>
#include <cstdlib>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef pair<int, int> pii;

const int N = 3e6;

unordered_map<long long, pii> m(N);

unsigned R() { return (rand() << 15) ^ rand(); }

int main() {
  int n;
  scanf("%d", &n);
  vector<int> a(n);
  forn(i, n)
    scanf("%d", &a[i]), a[i]--;
  forn(_, min(N, 100 * n)) {
    int i = R() % n;
    int j = R() % n;
    if (i > j) swap(i, j);
    long long p = (long long)((i + j) % n) * n + (a[i] + a[j]) % n;
    if (!m.count(p))
      m[p] = {i, j};
    else {
      pii x = m[p];
      if (!(i == x.first && j == x.second)) {
        puts("Ja");
        printf("%d %d %d %d\n", i + 1, j + 1, x.first + 1, x.second + 1);
        return 0;
      }
    }     
  }
  puts("Nein");
}


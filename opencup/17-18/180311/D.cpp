#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <bitset>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL

static struct __timestamper {
  string what;

  __timestamper(const char *what) : what(what) {};

  __timestamper(const string &what) : what(what) {};

  ~__timestamper() {
    TIMESTAMPf("%s", what.data());
  }
} __TIMESTAMPER("end");

#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

string get_line() {
  static char buf[200];
  scanf(" %[^\n]", buf);
  return buf;
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int n, S, T, hp;
  scanf("%d%d%d%d", &n, &S, &T, &hp);
  int start = 0;
  vector<int> hb(n);
  vector<string> name(n);
  for (int i = 0; i < n; i++) {
    char s[2];
    scanf("%s", s);
    scanf("%d", &hb[i]);
    if (s[0] == '+') {
      start += 1 << i;
      hp -= hb[i];
    }
    name[i] = get_line();
  }

  int MAX = hp;
  for (int i = 0; i < n; i++) {
    MAX += hb[i];
  }

  vector<int> maxH(1 << n, hp);

  int N = (1 << n) * (MAX + 1);
  vector<int> d(N, -1);
  vector<int> p(N, -1);
  d[(S << n) + start] = 0;
  int t = 1;
  int h = 0;
  vector<int> q(N);
  q[0] = (S << n) + start;
  while (t > h) {
    int x = q[h++];
    int H1 = x >> n;
    int ST = x & ((1 << n) - 1);
//    cout << H1 << " " << ST << "\n";
    int L1 = hp;
    for (int i = 0; i < n; i++) {
      if ((x >> i) & 1) {
        L1 += hb[i];
      }
    }

    for (int i = 0; i < n; i++) {
      int L2 = L1;
      if ((x >> i) & 1) {
        L2 -= hb[i];
      } else {
        L2 += hb[i];
      }
//      int H2 = H1 * L2 / L1;
      int H2 = (H1 * L2 + L1 / 2) / L1;
      if (((L1 & 1) == 0) && ((H1 * L2 + L1 / 2) % L1 == 0)) {
        if ((H2 & 1) == 1) {
          H2--;
        }
      }

      int y = (H2 << n) + ST ^ (1 << i);
//      cout << " " << H2 << " " << y << "\n";
      if (d[y] == -1) {
        d[y] = d[x] + 1;
        p[y] = x;
        q[t++] = y;
      }
    }
  }

  int best = -1;
  for (int i = T; i <= MAX; i++) {
    if (d[(i << n) + start] != -1) {
      if (best == -1 || d[best] > d[(i << n) + start]) {
        best = (i << n) + start;
      }
    }
  }
  if (best == -1) {
    cout << "-1\n";
    return 0;
  }

//  cout << (best >> n) << "\n";

  vector<int> pp;
  int c = best;
  while (c >= 0) {
    pp.push_back(c);
    c = p[c];
  }
  reverse(pp.begin(), pp.end());

  cout << pp.size() - 1 << "\n";
  for (int i = 0; i < pp.size(); i++) {
    int x = pp[i];
    int H1 = x >> n;
    int ST = x & ((1 << n) - 1);
    int L1 = hp;
    for (int j = 0; j < n; j++) {
      if ((x >> j) & 1) {
        L1 += hb[j];
      }
    }
    cout << H1 << " / " << L1 << "\n";

    if (i + 1 < pp.size()) {
      int y = pp[i + 1];
      int j = 0;
      while (((x >> j) & 1) == ((y >> j) & 1)) {
        j++;
      }
      if (((y >> j) & 1)) {
        cout << "+ ";
      } else {
        cout << "- ";
      }
      cout << name[j] << "\n";
    }
  }

  return 0;
}

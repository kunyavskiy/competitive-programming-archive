#pragma GCC optimize("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx")
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
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char* what) : what(what){};
  __timestamper(const string& what) : what(what){};
  ~__timestamper(){
    TIMESTAMPf("%s", what.data());
  }
} __TIMESTAMPER("end");
#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;
#define mp make_pair
typedef pair<ll, ll> pll;

//const int MAXN = 1e7;
int mind[(int)1e6];
vector<int> primes;

void gen_primes(int n) {
  mind[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (mind[i] == 0) {
      mind[i] = i;
      primes.push_back(i);

    }
    for (int j : primes) {
      if (j > mind[i] || i * j > n) break;
      mind[i * j] = j;
    }
  }
}


int mob(int x) {
  for (int i = 2; i * i <= x; i++) {
    if (x % (i * i) == 0) return 0;
    if (x % i == 0) x /= i;
  }
  return 1;
}

const int MAXV = (int)1e9;

uint32_t used[MAXV / 32 + 1];

const int B = 8;

int p[500];
int nxt[500][2];
int nxt2[500][1 << B];
int win[500][1 << B];

int solve(string s) {
  /*
  int ans = MAXV;
  for (int shift = 0; shift < 32; shift++) {
    uint32_t mask = 0;
    for (int j = 0; j < 32; j++) {
      if (s[shift + j] == '1') {
        mask |= 1u << j;
      }
    }
    for (int i = 0; i < MAXV / 32; i++) {
      if (used[i] == mask) {
        int cand = i * 32 - shift;
        if (cand <= 0 || cand > MAXV - (int)s.size()) {
          continue;
        }
        if (cand == 1) {
          printf("cand = %d\n", cand);
        }
        bool ok = true;
        for (int j = 0; j < (int)s.size(); j++) {
          if ((s[j] == '1') != (((used[(cand + j) >> 5] >> ((cand + j) & 31))) & 1)) {
            ok = false;
            break;
          }
        }
        if (ok) {
          ans = min(ans, cand);
        }
      }
    }
  }
  */

  for (int i = 0; i < (int)s.size(); i++) {
    string cur = s.substr(0, i);
    for (int j = 0; j < 2; j++) {
      string ncur = cur + char('0' + j);
      while (s.substr(0, ncur.size()) != ncur) {
        ncur = ncur.substr(1);
      }
      nxt[i][j] = ncur.size();
    }
  }

  int sz = (int)s.size();
  for (int i = 0; i < sz; i++) {
    for (int j = 0; j < (1 << B); j++) {
      int cur = i;
      for (int k = 0; k < B; k++) {
        cur = nxt[cur][(j >> k) & 1];
        if (cur == sz) {
          win[i][j] = k;
          break;
        }
      }
      nxt2[i][j] = cur;
    }
  }
  int cur = 0;
  for (int i = 1; i < 32; i++) {
    cur = nxt[cur][(used[0] >> i) & 1];
  }
  for (int i = 1; i < MAXV / 32 + 1; i++) {
    for (int j = 0; j < 32; j += B) {
      int bits = (used[i] >> j) & ((1 << B) - 1);
      int old_cur = cur;
      cur = nxt2[cur][bits];
      if (cur == sz) {
//        eprintf("old_cur = %d, i = %d, j = %d, win = %d\n", old_cur, i, j, win[old_cur][bits]);
        return i * 32 + j + win[old_cur][bits] - sz + 1;
      }
    }
//    cur = nxt[cur][(used[i >> 5] >> (i & 31)) & 1];
//    eprintf("cur = %d\n", cur);
//    if (cur == sz) return i - sz + 1;
  }
  return -1;
}

void test() {
  string s = "";
  int st = 1e9 - 199;//99824435;
  for (int i = 0; i < 200; i++ ){
    s += (char)('0' + abs(mob(st + i)));
  }
  //for (int i = 0; i < 3; i++) s[177+i]='1';
  cout << solve(s) << endl;
  exit(0);
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  //freopen("c.out", "w", stdout);
#endif

  gen_primes(1e5);
  for (int i = 0; i < 9; i++) {
    used[i] |= 0x11111111;
  }
  for (int i = 0; i < 9 * 32; i += 9) {
    used[i >> 5] |= (1u << (i & 31));
  }
  for (int i = 9; i < MAXV / 32 + 1; i++) {
    used[i] = used[i - 9];
  }
  for (int i : primes) {
    if (i * i > MAXV) break;
    if (i <= 3) continue;
    int x = i * i;
    for (int j = x; j < MAXV; j += x) {
      used[j >> 5] |= (1u << (j & 31));
    }
  }
  for (int i = 0; i < MAXV / 32 + 1; i++) {
    used[i] = ~used[i];
  }

//  for (int i = 1; i < MAXV; i++) {
//    if (((used[i >> 5] >> (i & 31)) & 1) != abs(mob(i))) {
//      eprintf("i = %d, \n", i);
//      break;
//    }
//  }

//  for (int i = 0; i < 32; i++) {
//    printf("%d", (used[0] >> i) & 1);
//  }
//  printf("\n");

#ifdef LOCAL
//  test();
#endif

  string s;
  while (cin >> s) {
    string tmp;
    for (int i = 0; i < 9; i++) {
      cin >> tmp;
      s += tmp;
    }

    int ans = solve(s);
    if (ans > 999999801) ans = -1;
    cout << ans << endl;
  }

  return 0;
}

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

int q;
int start;
int x;
bool neg;

void init() {
  q = 0;
#ifdef LOCAL
  start = rand() % 1000 + 1;
  neg = rand() % 2;
  if (neg) {
    start *= -1;
  }
  x = start;
#endif
}

int ask(char c) {
  q++;
#ifdef LOCAL
  if (neg) {
    if (c == '-') x -= 2;
    if (c == '+') x += 1;
  } else {
    if (c == '-') x -= 1;
    if (c == '+') x += 2;
  }
  return x == 0;
#else
  cout << c << endl;
  int x;
  cin >> x;
  return x;
#endif
}

void answer(string s) {
#ifdef LOCAL
  cerr << q << " of " << abs(start) * 30 << endl;
  assert(s == (neg ? "bad" : "good"));
  assert(q <= abs(start) * 30);
#else
  cout << "! " << s << endl;
#endif
}

void solve() {
  init();
  string ans;

  auto checkAns = [&](string s){
    int x = ask('-');
    int y = ask('+');
    assert(x == 0);
    if (y == 1) {
      ans = "ugly";
    } else {
      ans = s;
    }
  };

  /*for (int m = 1;; m *= 5) {
    for (int i = 0; i < m; i++) {
      int t = ask('-');
      if (t == 1) {
        checkAns("good");
        answer(ans);
        return;
      }
    }
    for (int i = 0; i < 3 * m; i++) {
      int t = ask('+');
      if (t == 1) {
        checkAns("bad");
        answer(ans);
        return;
      }
    }
    for (int i = 0; i < 2 * m; i++) {
      int t = ask('-');
      if (t == 1) {
        checkAns("bad");
        answer(ans);
        return;
      }
    }
  }*/
  int L = -1, R = 1;

  int len = 1;
  int cit = 0;
  while (1) {
    //cerr << L << " " << R << " " << x << endl;
    //if (abs(R) >= abs(L)) {
    if (cit++ % 2 == 0) {
      for (int i = 0; i < len; i++) {
        int t = ask('-');
        if (t == 1) {
          checkAns("good");
          answer(ans);
          return;
        }
      }
      L -= 2 * R;
      //R = 1;
    } else {
      for (int i = 0; i < len; i++) {
        int t = ask('+');
        if (t == 1) {
          checkAns("bad");
          answer(ans);
          return;
        }
      }
      R += 2 * -L;
      //L = -1;
    }
    len *= 3;
  }
}

int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
  for (int it = 0;; it++) {
    cerr << "it " << it << endl;
    srand(it);
    solve();
  }
#endif

  solve();

  return 0;
}

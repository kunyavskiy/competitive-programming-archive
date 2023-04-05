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


int get_odd(const vector<int> &a) {
  vector<int> bit(*max_element(a.begin(), a.end()) + 1);

  auto add = [&](int n) {
    while (n < (int) bit.size()) {
      bit[n] ^= 1;
      n = n | (n + 1);
    }
  };

  auto get = [&](int n) {
    int ans = 0;
    while (n > -1) {
      ans ^= bit[n];
      n = (n & (n + 1)) - 1;
    }
    return ans;
  };

  int ans = 0;
  int tot = 0;

  for (int x : a) {
    ans ^= (tot ^ get(x));
    add(x);
    tot ^= 1;
  }

  return ans;
}

int match(const vector<int> &a, const vector<int> &b) {
  vector<int> aa = a; sort(aa.begin(), aa.end());
  vector<int> bb = b; sort(bb.begin(), bb.end());
  if (aa != bb) return 0;
  if (unique(aa.begin(), aa.end()) != aa.end()) return 3;
  if (a.empty()) return 3;

  int p = get_odd(a) ^ get_odd(b);
  return 1 << p;
}

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> a(n), b(n);
    for (int &x : a) scanf("%d", &x);
    for (int &x : b) scanf("%d", &x);

    auto sub = [](const vector<int> &x, int y) {
      vector<int> v;
      for (int i = y; i < (int) x.size(); i += 2) {
        v.push_back(x[i]);
      }
      return v;
    };

    int x = match(sub(a, 0), sub(b, 0));
    int y = match(sub(a, 1), sub(b, 1));

    if (x & y) {
      printf("1\n");
    } else {
      printf("0\n");
    }


  }
  return 0;
}

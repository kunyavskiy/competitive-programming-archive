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
#include <zconf.h>

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

const int N = 2.01e6;
int buf[N];


int readN() {
#ifdef LOCAL
  int n;
  scanf("%d", &n);
  return n;
#else
  read(STDIN_FILENO, buf, 4);
  return *buf;
#endif
}

vector<int> readArray(int n) {
#ifdef LOCAL
  vector<int> a(n);
  for (int i = 0; i < n; i++) scanf("%d", &a[i]);
  return a;
#else
  read(STDIN_FILENO, buf, 4 * n);
  vector<int> a(n);
  for (int i = 0; i < n; i++) a[i] = *(buf + i);
  return a;
#endif
}

void print(vector<int> a) {
#ifdef LOCAL
  printf("%d", (int)a.size());
  for (int x : a) printf(" %d", x);
#else
  int sz = a.size();
  if (!(a.size() == 1 && a[0] == -1)) {
    a.insert(a.begin(), sz);
  }
  write(STDOUT_FILENO, a.data(), a.size() * 4);
#endif
}

vector<int> solve(vector<int> need) {
  vector<int> pos(N, -1);
  int n = need.size();
  for (int i = 0; i < n; i++) {
    pos[need[i]] = i;
  }

  int mx = *max_element(need.begin(), need.end());
  if (mx == 0) {
    return vector<int>();
  }

  int max_pos = 0;
  for (int i = 0; i < n; i++) if (need[i] != 0) max_pos = i;


  vector<int> ans;
  vector<int> cur(need.size());

  int last_pos = -1;
  for (int i = 1; i <= mx; i++) {
//    db(last_pos);
//    dbv(cur);
    if (pos[i] == -1) {
      if (last_pos < max_pos) {
        cur[++last_pos] = i;
        ans.push_back(0);
      } else {
        ans.push_back(pos[mx] + 1);
        ans.push_back(0);
        cur[pos[mx]] = i;
      }
    } else {
      if (pos[i] > last_pos + 1) {
        return vector<int>(1, -1);
      }
      if (pos[i] == last_pos + 1) {
        cur[++last_pos] = i;
        ans.push_back(0);
        continue;
      }
      assert(cur[pos[i]] != 0);
      ans.push_back(pos[i] + 1);
      ans.push_back(0);
      cur[pos[i]] = i;
    }
  }
  for (int i = 0; i < n; i++) {
    if (cur[i] != 0 && need[i] == 0) {
      ans.push_back(i + 1);
      cur[i] = 0;
    }
  }
//  dbv(need);
//  dbv(cur);
  assert(cur == need);
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("p5.in", "r", stdin);
//  freopen("p5.out", "w", stdout);
#endif

  int n = readN();
  auto a = readArray(n);
  print(solve(a));

  return 0;
}

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
#define pb push_back
#define sz(a) (int)(a).size()
#define all(a) (a).begin() (a).end()
#define pw(x) (1ll << (x))


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

int subsolve(vector<int> prob, vector<int> time, vector<vector<int>> a) {
  vector<int> first;
  while (1) {
    if (prob[0] > prob[1] || (prob[0] == prob[1] && time[0] <= time[1])) {
      first.push_back(0);
    } else {
      first.push_back(1);
    }

    if (a[0].empty() && a[1].empty()) break;

    int cur = first.back() ^ 1;
    if (a[cur].empty()) cur ^= 1;

    prob[cur]++;
    time[cur] += a[cur].back();
    a[cur].pop_back();
  }
  int ans = 0;
  for (int i = 1; i < (int)first.size(); i++) ans += first[i - 1] != first[i];
  return ans;
}

int solve(vector<int> prob, vector<int> time, vector<vector<int>> a) {
  for (int i = 0; i < 2; i++) {
    sort(a[i].begin(), a[i].end());
  }

  int ans = 0;
  for (int i1 = 0; i1 < 2; i1++) {
    for (int i2 = 0; i2 < 2; i2++) {
      ans = max(ans, subsolve(prob, time, a));

      reverse(a[1].begin(), a[1].end());
    }
    reverse(a[0].begin(), a[0].end());
  }
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  //freopen("b.out", "w", stdout);
#endif

  vector<int> prob(2);
  vector<int> time(2);
  vector<vector<int>> a(2);
  for (int it = 0; it < 2; it++) {
    scanf("%d%d", &prob[it], &time[it]);
    int k;
    scanf("%d", &k);
    a[it].resize(k);
    for (int i = 0; i < k; i++) {
      scanf("%d", &a[it][i]);
    }
  }

  printf("%d\n", solve(prob, time, a));

  return 0;
}

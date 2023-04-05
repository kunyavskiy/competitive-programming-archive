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
#include <random>

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

vector<int> ps;

template<int MOD>
void add(int &a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

template<int MOD>
void sub(int &a, int b) {
  if ((a -= b) < 0) a += MOD;
}

template<int MOD>
int mul(int a, int b) {
  return (int) ((a * 1LL * b) % MOD);
}

template<int MOD>
int mpow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) res = mul<MOD>(res, a);
    a = mul<MOD>(a, a);
    b >>= 1;
  }
  return res;
}

template<int MOD>
int minv(int x) {
  return mpow<MOD>(x, MOD - 2);
}

bool is_prime(int x) {
  for (int i = 2; i * i <= x; i++) {
    if (x % i == 0) return false;
  }
  return true;
}

vector<int> primes;


constexpr int MOD1 = 695551063;
constexpr int MOD2 = 356326963;
constexpr int MOD3 = 429239309;

template<int MOD>
int eval(const map<int, int>& r, int i, int m) {
  int left = 0;
  for (auto[p, c] : r) {
    add<MOD>(left, mul<MOD>(c < 0 ? c + MOD : c, mpow<MOD>(i, p)));
  }
  int right = mpow<MOD>(i, m);
  sub<MOD>(right, 1);
  assert(right != 0);
  left = mul<MOD>(left, minv<MOD>(right));
  if (left > MOD / 2) left -= MOD;
  return left;
}

int solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  map<int, int> r;

  int tot_cf = 0;

  for (int i = 0; i < n; i++) {
    int c, a;
    scanf("%d%d", &c, &a);
    tot_cf += c;
    r[a % m] -= c;
    r[(a + 1) % m] += c;
  }

  int ans = 0;
  if (tot_cf % m == 0) {
    eprintf("1 is ok\n");
    ans++;
  }

  if (all_of(r.begin(), r.end(), [](const pair<int, int>& a) { return a.second == 0;})) {
    return -1;
  }

  vector<int> cand;
  int last = r.begin()->second;
  if (n >= 1000) {
    for (int i = 1; i * 1LL * i * i <= n; i++) {
      cand.push_back(i);
    }
    int sqrt;
    for (sqrt = 1; sqrt * 1LL * sqrt * sqrt <= n; sqrt++);
    for (int i = 1; i * 1LL * i * i <= n; i++) {
      cand.push_back(sqrt - i);
    }
  } else{
    for (int i = 1; i * i <= n; i++) {
      cand.push_back(i);
    }
  }

  for (int i = 1; i <= 10; i++) {
    for (int c = -1; c <= 1; c += 2) {
      int d = abs(last + i * c);
      for (int j = 1; j * j <= d; j++) {
        if (d % j == 0) {
          cand.push_back(j);
          cand.push_back(d / j);
        }
      }
    }
  }
  sort(cand.begin(), cand.end());
  cand.erase(unique(cand.begin(), cand.end()), cand.end());


  eprintf("%d\n", (int)cand.size());

  for (int i : cand) {
    if (i == 1) continue;

    int val1 = eval<MOD1>(r, i, m);
    if (abs(val1) > 2 * n / i) continue;
    int val2 = eval<MOD2>(r, i, m);
    if (val1 != val2) continue;
    int val3 = eval<MOD3>(r, i, m);
    if (val1 != val3) continue;
    eprintf("%d is ok\n", i);
    ans++;
  }

  return ans;
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  mt19937 rnd{random_device()()};
  uniform_int_distribution<int> gen(1e8, 1e9);

  while (primes.size() < 3) {
    int x = gen(rnd);
    if (is_prime(x)) {
      primes.push_back(x);
    }
  }

  eprintf("%d %d %d\n", primes[0], primes[1], primes[2]);

  int t;
  scanf("%d", &t);
  while (t-- > 0) {
    int res = solve();
    printf("%d\n", res);
  }

  return 0;
}

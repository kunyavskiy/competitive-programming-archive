#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

using namespace std;

#define TASKNAME "H"

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

bool brute(vector <int> & v, vector <bool> & used, int sum, const vector <int> & nums, const vector <bool> & prime) {
  int n = int(nums.size());
  if (int(v.size()) == n) {
    return true;
  }
  for (int i = 0; i < n; ++i) {
    if (!used[i] && !prime[sum + nums[i]]) {
      used[i] = true;
      v.push_back(nums[i]);
      if (brute(v, used, sum + nums[i], nums, prime)) {
        return true;
      }
      v.pop_back();
      used[i] = false;
    }
  }
  return false;
}

void solve(int n) {
  vector <bool> prime(n * n + 1, true);
  for (int i = 2; i <= n * n; ++i) {
    if (prime[i]) {
      for (int j = 2 * i; j <= n * n; j += i)
        prime[j] = false;
    }
  }

  vector <int> nums(n);
  for (int i = 0; i < n; ++i) {
    nums[i] = i + 1;
  }
  random_shuffle(nums.begin(), nums.end());

  vector <int> v;
  vector <bool> used(n, false);
  if (brute(v, used, 0, nums, prime)) {
    for (int x : v) {
      printf("%d ", x);
    }
    printf("\n");
  } else {
    printf("-1\n");
  }
}

int main() {
#ifdef LOCAL
  assert(freopen(TASKNAME".in", "r", stdin));
  assert(freopen(TASKNAME".out", "w", stdout));
#endif

  int n;
  scanf("%d", &n);
  solve(n);
  /*for (int n = 1; n <= 100; ++n) {
    solve(n);
  }*/

  return 0;
}

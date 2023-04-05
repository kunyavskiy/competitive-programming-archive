#include <bits/stdc++.h>

#define pb push_back
#define mp make_pair
#define TASKNAME "A"

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("[" #x "] Time = %.3lfs\n",clock()*1.0/CLOCKS_PER_SEC)

#ifdef _WIN32
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

#define sz(x) ((int)(x).size())
#define forn(i, n) for (int i = 0; i < (n); i++)

using namespace std;

typedef long double ld;
typedef long long ll;
typedef vector <ll> vll;
typedef vector<int> vi;
typedef vector <vi> vvi;
typedef vector<bool> vb;
typedef vector <vb> vvb;
typedef pair<int, int> pii;
typedef pair <ll, ll> pll;
typedef vector <pii> vpii;

const int inf = 1e9;
const ld eps = 1e-9;
const int INF = inf;
const ld EPS = eps;

#ifdef LOCAL
struct __timestamper {
  ~__timestamper(){
    TIMESTAMP(end);
  }
} __Timestamper;
#else
struct __timestamper {
};
#endif

/*Template end*/

const int MAXA = 10000100;

int have[MAXA];

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int n;
  scanf("%d", &n);
  vector<int> a(n);

  for (int &x : a) {
    scanf("%d", &x);
    have[x] = 1;
  }

  sort(a.begin(), a.end());

  for (int x : a) {
    int ok = 1;
    for (int i = 2*x; i <= MAXA; i += x) {
      if (have[i]) {
        ok = 0;
        break;
      }
    }
    if (ok) {
      printf("%d ", x);
    }
  }


  return 0;
}

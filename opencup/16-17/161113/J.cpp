#include <bits/stdc++.h>

#define pb push_back
#define mp make_pair
#define TASKNAME "J"

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

int main() {
//  freopen("input.txt", "r", stdin);
//  freopen("output.txt", "w", stdout);

  int n;
  while (scanf("%d", &n) == 1) {
    vector<string> v;
    for (int i = 0; i < n; ++i) {
      static char s[20];
      scanf("%s", s);
      int len = strlen(s);
      sort(s, s + len);
      len = unique(s, s + len) - s;
      s[len] = 0;
      v.push_back(string(s));
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    printf("%d\n", int(v.size()));
  }

  return 0;
}

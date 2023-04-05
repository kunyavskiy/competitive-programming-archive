//#include <iostream>
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
#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ( ( _WIN32 || __WIN32__ ) && __cplusplus < 201103L)
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "D"

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


int main() {
#ifdef LOCAL
  assert(freopen(TASKNAME".in", "r", stdin));
  assert(freopen(TASKNAME".out", "w", stdout));
#endif

  int n, m;
  scanf("%d%d",&n,&m);
  if (m == 2) {
    printf("Nein\n");
  } else {

    vector<int> v;
    for (int i = 0; i < m; i++) {
      v.push_back(i);
    }
    bool done = false;
    do {
      int ok = true;
      for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
          if (i != j && (i + v[j]) % m == (j + v[i]) % m) {
            ok = false;
          }
      if (ok) {
        done = true;
        break;
        for (int i = 0; i < 4; i++) {
          printf("%d ", v[i]);
        }
        printf("\n");
      }
    }while (next_permutation(v.begin(), v.end()));
    assert(done);
    printf("Ja\n");
    for (int i = 0; i < m; i++)
      for (int j = 0; j < m; j++) {
        printf("%d%c", (i + j) % m, " \n"[j == m - 1]);
      }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        printf("%d%c", ((i % 2 == 0 ? j : v[j])) % m, " \n"[j == m - 1]);
      }
    }

    /*printf("Ja\n");
    int t;
    for (t = 2; t < m; t++) {
      if (__gcd(t - 1, m) == 1 && __gcd(t, m) == 1) {
        break;
      }
    }
    assert(t != m);
    for (int i = 0; i < m; i++)
      for (int j = 0; j < m; j++) {
        printf("%d%c", (i + j) % m, " \n"[j == m - 1]);
      }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        printf("%d%c", (j * (i % 2 == 0 ? 1 : t)) % m, " \n"[j == m - 1]);
      }
    }

    for (int i = 0; i < m; i++)
      for (int j = 0; j < m; j++)
        if (i != j && (i + t * j) % m == (j + t * i) % m) {
          eprintf("%d %d %d\n", i, j, t);
          eprintf("\n");
          assert(0);
        }

        */
  }

  return 0;
}

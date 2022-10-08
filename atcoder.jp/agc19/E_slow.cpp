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
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

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

int solve(string A, string B) {
  vector<int> a, b;
  for (int i = 0; i < (int)A.size(); i++) {
    if (A[i] == '1') a.push_back(i);
    if (B[i] == '1') b.push_back(i);
  }
  int cnt = 0;
  do {
    sort(b.begin(), b.end());
    do {
      string AA = A;
      for (int i = 0; i < (int)a.size(); i++) {
        swap(AA[a[i]], AA[b[i]]);
      }
      if (AA == B) {
        cnt++;
        for (int i = 0; i < (int)a.size(); i++) {
          printf("%d ", a[i]);
        }
        printf("    ");
        for (int i = 0; i < (int)a.size(); i++) {
          printf("%d ", b[i]);
        }
        printf("\n");
      } else {
      }
    } while (next_permutation(b.begin(), b.end()));
  } while (next_permutation(a.begin(), a.end()));
  return cnt;
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  static char A[10010], B[10010];

  while (scanf("%s%s", A, B) == 2) {
    printf("%d\n", solve(A, B));
    break;
  }

  return 0;
}

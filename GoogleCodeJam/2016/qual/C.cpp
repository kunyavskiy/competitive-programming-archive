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

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "C"
#define TASKMOD "large"

typedef long long ll;
typedef long double ld;

const int N = 32;
const int J = 500;

char s[N + 1];
int divs[11];

int main(){
  freopen(TASKNAME "-" TASKMOD ".in","r",stdin);
  freopen(TASKNAME "-" TASKMOD ".out","w",stdout);

  printf("Case #1:\n");
  s[0] = s[N - 1] = '1';
  int ok = 0;
  set<string> ss;
  while (ok < J) {
    for (int i = 1; i < N - 1; i++) {
      s[i] = rand() % 2 + '0';
    }
    if (ss.count(s)) continue;

    bool done = true;
    for (int d = 2; d <= 10; d++) {
      divs[d] = -1;
      for (int j = 2; j <= 100; j++) {
        int x = 0;
        for (int k = 0; k < N; k++) {
          x = (x * d + (s[k] - '0')) % j;
        }
        if (x == 0) {
          divs[d] = j;
        }
      }
      if (divs[d] == -1) {
        done = false;
        break;
      }
    }
    if (done) {
      ss.insert(s);
      ok++;
      printf("%s", s);
      for (int j = 2; j <= 10; j++) {
        printf(" %d", divs[j]);
      }
      printf("\n");
    }
   
  }
  return 0;
}

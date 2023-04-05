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

int main() {
#ifdef LOCAL
  freopen("i.in", "r", stdin);
  freopen("i.out", "w", stdout);
#endif

  printf("46\n");
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      printf("%dm%d %d%dm\n", i, j, j, i);
    }
  }

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 2; k++) {
        printf("%d%d%dm %db%d%dm\n", i, j, k, i, j, k);
      }
    }
  }

  for (int j = 0; j < 2; j++) {
    for (int k = 0; k < 2; k++) {
      printf("+%d%dm +b%d%dm\n", j, k, j, k);
    }
  }


  printf("mb b\n");

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      printf("%d+%d +%d%dm\n", i, j, j, i);
    }
  }

  printf("+0 b0c\n");
  printf("+1 b1c\n");
  printf("c0 b0c\n");
  printf("c1 b1c\n");
  printf("cb b\n");
  printf("+ b\n");
  printf("m p\n");
  printf("bp p\n");
  printf("bq q\n");

  for (int k = 0; k < 2; k++) {
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        printf("b%d%d%c %c%d\n", i, j, char('p' + k), char('p' + (i + j + k) / 2), (i + j + k) % 2);
      }
    }
  }

  for (int k = 0; k < 2; k++) {
    for (int i = 0; i < 2; i++) {
      printf("%d%c %c%d\n", i, char('p' + k), char('p' + (i + k) / 2), (i + k) % 2);
    }
  }

  printf("p d\n");
  printf("q d1\n");
  printf("d0 0\n");
  printf("d1 1\n");


  return 0;
}

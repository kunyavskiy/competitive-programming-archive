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

const char *cmds[10]={"CCC", "ACG", "UGA", "UGC", "UAC", "GCG", "UCC", "AGG", "UGU", "CAC"};

void stop() { printf("%s", cmds[0]);}
void right() { printf("%s", cmds[1]);}
void left() { printf("%s", cmds[2]);}
void inc() { printf("%s", cmds[3]);}
void dec() { printf("%s", cmds[4]);}
void output() { printf("%s", cmds[5]);}
void input() { printf("%s", cmds[6]);}
void loop(std::function<void()> inside) {
    printf("%s", cmds[7]);
    inside();
    printf("%s", cmds[8]);
}
void debug() {
#ifdef LOCAL
    printf("%s", cmds[9]);
#endif
}

int main() {
#ifdef LOCAL
  freopen("l.in", "r", stdin);
  freopen("l.out", "w", stdout);
#endif

  int k;
  scanf("%d", &k);

  input();
  inc();
  loop([&] {
      dec();
      // *
      // 01234
      // i110000
      for (int i = 0; i < k; i++) {
          right();
      }
      for (int i = k - 2; i >= 0; i--) {
          left();
          loop([&] {
              dec();
              for (int j = i; j < 10 * i; j++) {
                  right();
              }
              for (int j = 0; j < 10; j++) {
                  right();
                  inc();
              }
              for (int j = 0; j < 10; j++) {
                  left();
              }
              for (int j = i; j < 10 * i; j++) {
                  left();
              }
          });
      }
      left();
      loop([] {
          dec();
          right();
          inc();
          left();
      });
      right();
      loop([] {
          loop([] {
              dec();
              left();
              inc();
              right();
          });
          inc();
          left();
          dec();
      });
      right();
      loop([&] {
          for (int i = 0; i < k - 1; i++) {
              right();
          }
          loop([&] {
              for (int i = 0; i < k; i++) {
                  dec();
                  left();
              }
              for (int i = 0; i < k; i++) {
                  right();
              }
          });
          right();
      });
      for (int i = 0; i < k; i++) {
          left();
      }
      left();
      input();
      inc();
  });
  right();
  debug();
  loop([] {
     dec();
     output();
     stop();
  });
  inc();
  output();
  stop();
  printf("\n");


  return 0;
}

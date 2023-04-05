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

int getRank(char ch) {
  const char ranks[15] = "23456789TJQKAJ";
  int rank = strchr(ranks, ch) - ranks;
  eprintf("ch %c rank %d\n", ch, rank);
  assert(0 <= rank && rank < 14);
  return rank;
}

int getSuit(char ch) {
  const char suits[5] = "SCDH";
  int suit = strchr(suits, ch) - suits;
  assert(0 <= suit && suit < 4);
  return suit;
}

int readSuit() {
  char ch;
  scanf(" %c", &ch);
  return getSuit(ch);
}

int readCard() {
  static char s[5];
  scanf("%s", s);
  if (s[1] == 'J') {
    if (s[0] == 'B') {
      return 52;
    }
    if (s[0] == 'R') {
      return 53;
    }
    assert(0);
  }
  int rank = getRank(s[0]);
  int suit = getSuit(s[1]);
  return (rank << 2) + suit;
}

void solve() {
//  int mask[2] = {0, 0};
  int jokers[2] = {0, 0};
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 6; ++j) {
      static char s[5];
      scanf("%s", s);
      if (s[1] == 'J') {
        jokers[i]++;
      }
    }
  }
  for (int i = 0; i < 42; ++i) {
    scanf("%*s");
  }
  eprintf("%d %d\n", jokers[0], jokers[1]);
  scanf(" %*c");

  if (jokers[1] == 2) {
    printf("Johann\n");
  } else {
    printf("Sebastian\n");
  }
}

int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
#endif

  int tt;
  scanf("%d", &tt);
  for (int ii = 0; ii < tt; ++ii) {
    solve();
  }

  return 0;
}

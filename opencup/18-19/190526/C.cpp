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
#include <unordered_set>

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

ll rand_hash[52][53];

struct State {
  ll hash;
  vector<int> lieOn;

  State() : hash(0), lieOn(52, -1) {
  }

  void putOn(int card1, int card2) {
    if (lieOn[card1] != -1) hash ^= rand_hash[card1][lieOn[card1]];
    lieOn[card1] = card2;
    if (lieOn[card1] != -1) hash ^= rand_hash[card1][lieOn[card1]];
  }

  bool isLieUnder(int card1, int card2) {
    for (int x = card1; x != -1; x = lieOn[x]) {
      if (x == card2) { return true; }
    }
    return false;
  }
};

#define CARD(suit, value) ((suit) * 13 + (value))

vector<int> target;
const char *suits = "DHSC";
const char *values = "A23456789TJQK";

int readCard() {
  static char s[10];
  scanf("%s", s);
  int suit = strchr(suits, s[1]) - suits;
  int value = strchr(values, s[0]) - values;
  return CARD(suit, value);
}

const char *printCard(int card) {
  int suit = card / 13;
  int value = card % 13;
  static char s[10];
  sprintf(s, "%c%c", values[value], suits[suit]);
  return s;
}

int get_prev_card(int card) {
  int suit = card / 13;
  int value = card % 13;
  if (value == 0) return -1;
  --value;
  return CARD(suit, value);
}

unordered_set<ll> cache;

clock_t startTime = clock();

bool brute(State & st, vector<int> & res) {
  {
    static int iters = 0;
    ++iters;
    if (iters == 1000) {
      iters = 0;
      if (clock() - startTime > 0.9 * CLOCKS_PER_SEC) {
        printf("NO\n");
        exit(0);
      }
    }
  }


  if (st.lieOn == target) { return true; }
  if (cache.count(st.hash)) {
    return false;
  }

  cache.insert(st.hash);

  bool top[52];
  for (int i = 0; i < 52; ++i) {
    top[i] = true;
  }
  for (int i = 0; i < 52; ++i) {
    top[st.lieOn[i]] = false;
  }
  int top_count = 0;
  for (int i = 0; i < 52; ++i) {
    if (top[i]) top_count++;
  }
  if (top_count < 7) {
    bool changed = false;
    for (int suit = 0; suit < 4; ++suit) {
      int card = CARD(suit, 12);
      int z = st.lieOn[card];
      if (z == -1) { continue; }

      changed = true;
      res.push_back(card);
      st.putOn(card, -1);
      if (brute(st, res)) {
        return true;
      }
      st.putOn(card, z);
      res.pop_back();
    }
    if (changed) { return false; }
  }

  for (int card1 = 0; card1 < 52; ++card1) {
    if (!top[card1]) { continue; }
    int card2 = get_prev_card(card1);
    if (card2 == -1) { continue; }

    if (st.isLieUnder(card1, card2)) { continue; }

    int z = st.lieOn[card2];

    res.push_back(card2);
    st.putOn(card2, card1);
    if (brute(st, res)) {
      return true;
    }
    st.putOn(card2, z);
    res.pop_back();
  }
  return false;
}

bool solve() {
  cache.clear();
  State st;
  for (int i = 0; i < 7; ++i) {
    int k;
    if (scanf("%d", &k) != 1) return false;

    vector<int> v;
    for (int j = 0; j < k; ++j) {
      v.push_back(readCard());
    }

    for (int j = 1; j < k; ++j) {
      st.putOn(v[j], v[j - 1]);
    }
  }

  vector<int> res;
  if (brute(st, res)) {
    printf("YES\n%d\n", int(res.size()));
    for (int card : res) {
      printf("%s ", printCard(card));
    }
    printf("\n");
  } else {
    printf("NO\n");
  }
  return true;
}

ll rand63() {
  return (ll(rand()) << 31) | rand();
}

int main() {

  for (int i = 0; i < 52; ++i) {
    for (int j = 0; j < 53; ++j) {
      rand_hash[i][j] = rand63();
    }
  }

  target.assign(52, -1);
  for (int i = 0; i < 52; ++i) {
    int j = get_prev_card(i);
    if (j != -1) {
      target[j] = i;
    }
  }

#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  while (solve()) {

  }

  return 0;
}

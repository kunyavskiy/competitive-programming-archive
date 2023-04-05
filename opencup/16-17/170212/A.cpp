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

#define TASKNAME "A"

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

const int MAXN = int(1e7) + 100;
static char s[MAXN];
static char t[MAXN];
int piNext[MAXN][10];

bool check(int n, int i, int d,
           vector <int> & len,
           vector <int> & pi) {
//  eprintf("check i %d d %d t %s\n", i, d, t);
  if (i == 0) {
    return n >= 4;
  }
  int j = len[i - 1] - 1;
  //eprintf("check i %d d %d j %d t[j] %c\n", i, d, j, t[j]);
  int prefLen, prefPi;
  if (d == t[j] - '0') {
    prefLen = j + 1;
    prefPi = pi[j];
  } else {
    prefLen = j + 2;
    prefPi = piNext[j][d];
  }
  for (int ii = 0; ii < 2; ++ii) {
    int prefPer = prefLen - (prefPi + 1);
    //eprintf("pref(len %d pi %d per %d)\n", prefLen, prefPi, prefPer);
    int lostChars = n - i - 1;
    if (prefPer == 1) {
      return lostChars >= 3;
//      assert(prefLen == 1);
//      prefPer++;
//      prefLen++;
//      lostChars--;
    }

    int needChars = (2 * prefPer - (prefLen % (2 * prefPer))) % (2 * prefPer);
//    eprintf("pref(len %d pi %d per %d) needChars %d lostChars %d\n", prefLen, prefPi, prefPer, needChars, lostChars);
    if (needChars <= lostChars) {
      return true;
    }
    prefPi = pi[prefPi];
  }
  return false;
}

void appendChar(int i,
                vector<int> & len,
                vector<int> & pi) {
  //eprintf("%s i %d\n", __func__, i);
  if (i == 0) {
    t[0] = s[0];
    t[1] = 0;
    pi[0] = -1;
    len[0] = 1;
    for (int j = 0; j < 10; ++j) {
      piNext[0][j] = -1;
    }
    piNext[0][t[0] - '0'] = 0;
    return;
  }
  if (s[i - 1] == s[i]) {
    len[i] = len[i - 1];
    return;
  }
  len[i] = len[i - 1] + 1;
  t[len[i] - 1] = s[i];
  t[len[i]] = 0;

  i = len[i] - 1;
  pi[i] = piNext[i - 1][t[i] - '0'];
//  int j = pi[i - 1];
//  while (j >= 0 && t[i] != t[j + 1]) {
//    j = pi[j];
//  }
//  if (t[i] == t[j + 1]) {
//    ++j;
//  }
//  pi[i] = j;

  for (int j = 0; j < 10; ++j) {
    if (t[pi[i] + 1] == j + '0') {
      piNext[i][j] = pi[i] + 1;
    } else {
      piNext[i][j] = (pi[i] == -1 ? -1 : piNext[pi[i]][j]);
    }
  }
}

bool isCorrect(const char *s) {
  string t(s);
  t.erase(unique(t.begin(), t.end()), t.end());
  int n = (int)t.size();
  if (n % 2 != 0) { return false; }
  for (int i = 0; i < n / 2; ++i) {
    if (t[i] != t[i + n / 2]) {
      return false;
    }
  }
  return true;
}

//#define STRESS

#ifdef STRESS
static int N = 1010;

bool isGood(int x) {
  static char s[20];
  sprintf(s, "%d", x);
  return isCorrect(s);
}

int solve_stupid(int n) {
  for (int i = n - 1; ; --i) {
    if (isGood(i)) {
      return i;
    }
    assert(i >= 0);
  }
}
#endif

bool solve() {
#ifndef STRESS
  if (scanf("%s", s) != 1) {
    return false;
  }
//  int LEN = 5000000;
//  for (int i = 0; i < LEN; ++i) {
//    s[i] = '0' + (rand() % 10);
//  }
//  s[LEN] = 0;
#else
  if (N % 10 == 0) {
    eprintf("%d\n", N);
  }
  if (N >= 1000000) { return false; }
  ++N;
//  int X = N;
  int X = rand() % int(1e9);
  sprintf(s, "%d", X);
#endif

  int n = int(strlen(s));
//  eprintf("n %d\n", n);
//  eprintf("n %d s %s\n", n, s);
  vector <int> len(n, 0);
  vector <int> pi(n, -1);
//  vector <vector<int>> piNext(n, vector<int>(10, -1));
  for (int i = 0; i < n; ++i) {
    appendChar(i, len, pi);
  }

  /*
  int k = len[n - 1];


  eprintf("k %d t %s\n", k, t);

  for (int i = 0; i < k; ++i) {
    eprintf("%d ", pi[i]);
  }
  eprintf("\n");

  for (int i = 0; i < k; ++i) {
    for (int j = 0; j < 10; ++j) {
      eprintf("%d ", piNext[i][j]);
    }
    eprintf("\n");
  }
  eprintf("\n");*/

  int bestI = -1, bestD = -1;
  for (int i = n - 1; i >= 0; --i) {
    for (int d = s[i] - '0' - 1; d >= (i == 0 ? 1 : 0); --d) {
      if (check(n, i, d, len, pi)) {
        bestI = i;
        bestD = d;
        break;
      }
    }
    if (bestI != -1) {
      break;
    }
  }

//  eprintf("bestI %d bestD %d\n", bestI, bestD);

  if (bestI == -1) {
  #ifdef STRESS
      int RES = solve_stupid(X);
  #endif
    if (n <= 4) {
      printf("-1\n");
    } else {
      for (int i = 0; i < n - 5; ++i) {
        s[i] = '9';
      }
      strcpy(s + n - 5, "9898");
      printf("%s\n", s);
      assert(isCorrect(s));
  #ifdef STRESS
     assert(RES == atoi(s));
  #endif
    }
  } else {
    s[bestI] = (char)('0' + bestD);
    appendChar(bestI, len, pi);
    for (int i = bestI + 1; i < n; ++i) {
      int d = 9;
      while (d >= 0 && !check(n, i, d, len, pi)) {
        d--;
      }
      assert(d >= 0);
      s[i] = (char)('0' + d);
      appendChar(i, len, pi);
    }
    printf("%s\n", s);
    assert(isCorrect(s));
  #ifdef STRESS
    int RES = solve_stupid(X);
    assert(RES == atoi(s));
  #endif
  }

  fflush(stdout);
  return true;
}

int main() {
#ifdef LOCAL
    assert(freopen(TASKNAME".in", "r", stdin));
//    assert(freopen(TASKNAME".out", "w", stdout));
#endif

  while (solve()) {
  }

  return 0;
}

/*
 *
 * 12121212122
 * 12121212112
 */

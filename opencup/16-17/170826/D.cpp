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

#define MAX 500100

int main() {
  ios_base::sync_with_stdio(false);
  string s;
  cin >> s;
  int n;
  cin >> n;
  vector<bool> p(2 * MAX);
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    p[x + MAX] = true;
  }
  vector<bool> ss(2 * MAX);
  int shift = 0;
  for (int i = 0; i < (int)s.size(); i++) {
    if (s[i] == 'R') shift++;
    if (s[i] == 'L') shift--;
    if (s[i] == 'X') ss[shift + MAX] = !ss[shift + MAX];
  }

//  cerr << shift << endl;

  int mod = abs(shift);
  if (mod == 0) {
    int min1 = 0;
    while (min1 < (int)p.size() && !p[min1]) min1++;
    int min2 = 0;
    while (min2 < (int)ss.size() && !ss[min2]) min2++;
    if ((min1 == (int)p.size()) != (min2 == (int)ss.size())) {
      cout << "NO" << endl;
      return 0;
    }
    for (int i = 0; i < MAX; i++) {
      bool x = min1 + i < (int)p.size() ? p[min1 + i] : false;
      bool y = min2 + i < (int)ss.size() ? ss[min2 + i] : false;
      if (x != y) {
        cout << "NO" << endl;
        return 0;
      }
    }
    string res = "";
    if (min1 < min2) {
      for (int i = 0; i < min2 - min1; i++) {
        res += "L";
      }
    } else if (min1 > min2) {
      for (int i = 0; i < min1 - min2; i++) {
        res += "R";
      }
    }
    cout << res << endl;
  } else {
    vector<bool> pm(mod);
    vector<bool> sm(mod);
    for (int i = 0; i < (int)p.size(); i++) {
      pm[i % mod] = pm[i % mod] ^ p[i];
      sm[i % mod] = sm[i % mod] ^ ss[i];
    }
    vector<int> q(3 * mod + 1);
    for (int i = 0; i < mod; i++) {
      q[i] = sm[i] ? 1 : 0;
      q[i + 1 + mod] = pm[i] ? 1 : 0;
      q[i + 1 + 2 * mod] = pm[i] ? 1 : 0;
    }
    q[mod] = 2;
//    for (int i = 0; i < (int)q.size(); i++) {
//      cerr << q[i] << " ";
//    }
//    cerr << endl;
    vector<int> pr(q.size());
    pr[0] = -1;
    pr[1] = 0;
    int myshift = -1;
    for (int i = 2; i < (int)q.size(); i++) {
      int k = pr[i - 1];
      while (k >= 0) {
        if (q[k] == q[i - 1]) {
          break;
        }
        k = pr[k];
      }

      pr[i] = k + 1;
//      cerr << i << " " << pr[i] << endl;
      if (pr[i] == mod) {
        myshift = i - 2 * mod - 1;
        break;
      }
    }
    if (myshift == -1) {
      cout << "NO" << endl;
      return 0;
    }


    for (int i = 0; i < (int)ss.size(); i++) {
      if (ss[i]) {
        p[i + myshift] = !p[i + myshift];
      }
    }
    for (int i = 0; i < (int)p.size(); i++) {
      if (p[i]) {
        p[i + mod] = !p[i + mod];
      }
    }
    int cur = MAX;
    string res = "";
    for (int i = 0; i < (int)p.size(); i++) {
      if (p[i]) {
        int x = shift > 0 ? i : i - shift;
        while (x < cur) {
          res += "L";
          cur--;
        }
        while (x > cur) {
          res += "R";
          cur++;
        }
        res += "X";
      }
    }
    while (cur > myshift + MAX) {
      res += "L";
      cur--;
    }
    while (cur < myshift + MAX) {
      res += "R";
      cur++;
    }
    cout << res << endl;
  }

  return 0;
}

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

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  string s;
  while (cin >> s) {
    vector<char> letters(s.begin(), s.end());
    sort(letters.begin(), letters.end());
    letters.erase(unique(letters.begin(), letters.end()), letters.end());

    assert(letters.size() == 10);
    vector<int> v(10);
    for (int i = 0; i < 10; i++) {
      v[i] = i;
    }
    vector<ll> all;
    vector<int> ls(s.size());
    for (int i = 0; i < (int)s.size(); i++) {
      ls[i] = find(letters.begin(), letters.end(), s[i]) - letters.begin();
    }
    do {
      ll r = 0;
      ll c = 1;
      for (int i = 1; i < (int)s.size(); i++) {
        int idp = ls[i - 1];
        int idc = ls[i];
        if (v[idp] < v[idc]) {
        } else if (v[idp] == v[idc]) {
          assert(s[i] == s[i - 1]);
          r += c;
        } else {
          r += 2 * c;
        }
        c *= 3;
      }
      all.push_back(r);
    } while (next_permutation(v.begin(), v.end()));
    TIMESTAMP("done\n");
    sort(all.begin(), all.end());
    TIMESTAMP("done\n");
    string res = "Impossible";
    for (int i = 0; i < (int)all.size(); i++) {
      if (i != 0 && all[i] == all[i - 1]) continue;
      if (i != (int)all.size() - 1 && all[i] == all[i + 1]) continue;
      res = "";
      res += s[0];
      ll r = all[i];
      for (int j = 1; j < (int)s.size(); j++) {
        if (r % 3 == 0) {
          res += " < ";
        } else if (r % 3 == 1) {
          res += " = ";
        } else {
          res += " > ";
        }
        res += s[j];
        r /= 3;
      }
      break;
    }
    cout << res << endl;
    break;
  }

  return 0;
}

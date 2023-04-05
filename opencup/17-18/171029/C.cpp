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

ll res = 0;

void go(string& s1, string& s2, string& s3, string& s4) {
//  cout << s1 << " " << s2 << " " << s3 << " " << s4 << "\n";
  vector<vector<vector<int>>> q3(26, vector<vector<int>>(26, vector<int>(110)));
  vector<vector<vector<int>>> q4(26, vector<vector<int>>(26, vector<int>(110)));
  for (int i = 0; i < (int)s3.size(); i++) {
    for (int j = i + 1; j < (int)s3.size(); j++) {
      q3[s3[i] - 'a'][s3[j] - 'a'][j - i]++;
    }
  }
  for (int i = 0; i < (int)s4.size(); i++) {
    for (int j = i + 1; j < (int)s4.size(); j++) {
      q4[s4[i] - 'a'][s4[j] - 'a'][j - i]++;
    }
  }

  for (int a = 2; a < 110; a++) {
    if (a + 1 > (int)s3.size() || a + 1 > (int)s4.size()) break;
    for (int d = -110; d < 110; d++) {
      int l = max(0, d);
      int r = min((int)s1.size(), (int)s2.size() + d);
      if (r - l < 3) continue;
      ll s = 0;
//      cout << a << " " << d << " " << l << " " << r << "\n";
      for (int i = r - 1; i >= l + 2; i--) {
        s += q4[s1[i] - 'a'][s2[i - d] - 'a'][a];
//        for (int j = -110; j <= 0; j++) {
//          if (a - j < (int)s4.size()) {
//            if (s4[0 - j] == s1[i] && s4[a - j] == s2[i - d]) {
//              s++;
//            }
//          }
//        }
        res += s * q3[s1[i - 2] - 'a'][s2[i - 2 - d]- 'a'][a];
//        for (int j = -110; j <= 0; j++) {
//          if (a - j < (int)s3.size()) {
//            if (s3[0 - j] == s1[i - 2] && s3[a - j] == s2[i - 2 - d]) {
//              res += s;
//            }
//          }
//        }
      }
    }
  }
//  cout << res << "\n";
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  string s[4];
  cin >> s[0] >> s[1] >> s[2] >> s[3];

  vector<int> p(4);
  for(int i = 0; i < 4; i++) p[i] = i;
  while (true) {
    go(s[p[0]], s[p[1]], s[p[2]], s[p[3]]);
    if (!next_permutation(p.begin(), p.end())) {
      break;
    }
  }
  cout << res << "\n";

  return 0;
}

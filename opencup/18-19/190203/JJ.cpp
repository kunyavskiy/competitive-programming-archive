#include <unordered_map>
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
#define pb push_back
#define sz(a) (int)(a).size()
#define all(a) (a).begin() (a).end()
#define pw(x) (1ll << (x))


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

bool prime(ll x) {
  if (x <= 1) return 0;
  for (ll i = 2; i * i <= x; i++) {
    if (x % i == 0) {
      return 0;
    }
  }
  return 1;
}

void build() {
  set<string> bad;
  queue<string> q;
  q.push("");
  while (!q.empty()) {
    string s = q.front();
    if (s.length() == 8) break;
//    db(s);
    //cerr << s << ",";
    q.pop();
    for (char c = '0'; c <= '9'; c++) {
      string t = string(1, c) + s;
      bool badSub = 0;
      /*for (int j = 1; j < (int)t.length(); j++) {
        string pref = t.substr(0, j);
        if (bad.find(pref) != bad.end()) {
          badPref = 1;
          break;
        }
      }*/
      for (int mask = 1; mask < (1 << (t.length())); mask++) {
        string cur = "";
        for (int i = 0; i < (int)t.length(); i++) if (mask & (1 << i)) cur += t[i];
        if (bad.find(cur) != bad.end()) {
          badSub = 1;
          break;
        }
      }
      if (badSub) continue;
      ll x = atoll(t.c_str());
      if (prime(x)) {
        bad.insert(t);
        db(t);
      } else {
        //if (t == "0") continue;
        q.push(t);
      }
    }
  }
  ll prod = 1;
  for (auto s : bad) prod *= s.length();
  db(prod);
  dbv(bad);
  for (string s : bad) cout << "\"" << s << "\",";
}

const vector<string> bad = {"11","19","2","3","409","41","449","499","5","60000049","60649","61","6469","66000049","66600049","666649","6949","7","881","89","9001","9049","946669","9649","991","9949"};

ll solve(ll N) {
  string a = to_string(N);
  int n = a.size();

  //map<pair<vector<int>, int>, ll> mp;
  //mp[make_pair(vector<int>(bad.size()), 0)] = 1;
  unordered_map<ll, ll> mp;
  mp[0] = 1;
  for (int i = 0; i < n; i++) {
    //map<pair<vector<int>, int>, ll> nmp;
    unordered_map<ll, ll> nmp;
    for (auto it : mp) {
      for (char c = '0'; c <= '9'; c++) {
        if (it.first.second == 0 && c > a[i]) continue;
        int nf = it.first.second || c < a[i];

        auto cur = it.first.first;
        bool fail = 0;
        for (int j = 0; j < (int)cur.size(); j++) {
          cur[j] += bad[j][cur[j]] == c;
          if (cur[j] == (int)bad[j].length()) {
            fail = 1;
            break;
          }
        }
        if (fail) continue;
        nmp[make_pair(cur, nf)] += it.second;
      }
    }
    mp = nmp;
  }
  ll ans = 0;
  for (auto it : mp) {
    ans += it.second;
  }
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  //freopen("j.out", "w", stdout);
#endif

  //build();

  int T;
  cin >> T;
  while (T--) {
    ll L, R;
    cin >> L >> R;
    cout << solve(R) - solve(L - 1) << endl;
  }

  return 0;
}

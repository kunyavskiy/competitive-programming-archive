#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <cstdlib>
#include <cstdio>
#include <stack>
#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <iterator>
#include <functional>
#include <bitset>
#include <ctime>
#include <cassert>
#include <sstream>

#define pb push_back
#define mp make_pair      
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
 
typedef long long ll;
typedef long double ld;

const int MAXW = 300010;
const int MAXD = 1000000100;

class Depot {
  vector<int> split(const string& s) {
    stringstream str;
    str << s;
    vector<int> v;
    int x;
    while (str >> x) {
      v.push_back(x);
    }
    return v;
  }

public:
  int countPositive(vector<string> a, vector<string> q) {
    vector<long long> v(MAXW, MAXD);
    v[0] = 0;
    for (const string& s: a) {
      vector<int> tmp = split(s);
      ll D = tmp[0];
      ll I = tmp[1];
      ll M = tmp[2];
      ll S = tmp[3];

      M = min((MAXD - D) / I + 1, M);
      M = min(MAXW / S + 1, M);

      for (int j = 0; j < S; j++) {
        multiset<long long> c;
        multiset<pair<int, long long>> c_rem;
        multiset<long long> incr;
        multiset<pair<int, long long>> add_incr;
        multiset<pair<int, long long>> rem_incr;
        for (int k = j; k < MAXW; k += S) {
          while (!c_rem.empty() && c_rem.begin()->first <= k) {
            c.erase(c.find(c_rem.begin()->second));
            c_rem.erase(c_rem.begin());
          }
          while (!add_incr.empty() && add_incr.begin()->first <= k) {
            incr.insert(add_incr.begin()->second);
            add_incr.erase(add_incr.begin());
          }
          while (!rem_incr.empty() && rem_incr.begin()->first <= k) {
            incr.erase(incr.find(rem_incr.begin()->second));
            rem_incr.erase(rem_incr.begin());
          }
          long long &ans = v[k];
          long long nans = ans;
          if (!c.empty()) {
            nans = min(nans, *c.begin());
          }
          if (!incr.empty()) {
            nans = min(nans, D + I * (k - j) / S + *incr.begin());
          }

          c.insert(ans);
          ll lim = min((ll)M, (ans - D + I - 1) / I);
          lim = max(lim, 0LL);
          c_rem.insert({k + S * lim, ans});
          if (lim != M) {
            add_incr.insert({k + S * lim, -I * ((k - j) / S + 1)});
            rem_incr.insert({k + S * (M + 1), -I * ((k - j) / S + 1)});
          }

          ans = nans;
        }
      }
    }

    auto process = [&](int d, int s) {
//      eprintf("%d %d\n", d, s);
      return v[s] <= d;
    };

    int ans = 0;

    for (const string& s : q) {
      vector<int> tmp = split(s);
      if (tmp.size() == 2) {
        ans += process(tmp[0], tmp[1]);
      } else {
        for (int i = 0; i < tmp[6]; i++) {
          ans += process((tmp[0] + i * 1LL * tmp[2] - 1) % tmp[3] + 1, (tmp[1] + i * 1LL * tmp[4] - 1) % tmp[5] + 1);
        }
      }
    }

    return ans;
  }
};











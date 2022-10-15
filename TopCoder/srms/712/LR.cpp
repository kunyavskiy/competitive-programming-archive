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
#define pb push_back
#define mp make_pair      
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
 
typedef long long ll;
typedef long double ld;


const char *NO = "No solution";

class LR {
  map<vector<int>, string> v;

public:
  string construct(vector<ll> from, vector<ll> to) {
    ll sum_from = getSum(from);
    ll sum_to = getSum(to);

    if (sum_from == 0) {
      if (sum_to == 0) return "";
      return NO;
    }

    if (sum_to % sum_from != 0) {
      return NO;
    }

    ll cnt = sum_to / sum_from;
    if (cnt & (cnt - 1)) {
      return NO;
    }

    cnt = __builtin_ctzll(cnt);

    int n = from.size();

    for (int i = 0; i < cnt; i++) {
      vector<ll> next(n);
      for (int j = 0; j < n; j++) {
        next[j] = from[j] + from[(j + n - 1) % n];
      }
      from = next;
    }

    string s(cnt, 'L');

    for (int i = 0; i < n && i <= cnt; i++) {
      if (from == to) {
        return s;
      }
      if (i != cnt) {
        s[i] = 'R';
        rotate(from.begin(), from.begin() + 1, from.end());
      }
    }
    return NO;
  }

  ll getSum(const vector<ll> &from) const {
    ll sum = 0;
    for (ll x : from) {
      sum += x;
    }
    return sum;
  }

};











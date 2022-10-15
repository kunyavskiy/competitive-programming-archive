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


class MinimizeAbsoluteDifferenceDiv1 {


  pair<ll, ll> eval(vector<int> order, vector<int> a) {
    ll n = abs(a[order[0]] * 1LL * a[order[3]] - a[order[1]] * 1LL * a[order[2]]);
    ll d = a[order[1]] * 1LL * a[order[3]];
    ll g = __gcd(n , d);
    return {n / g, d / g};
  }

public:
  vector<int> findTuple(vector<int> a) {
    vector<int> order(5);
    for (int i = 0; i < 5; i++) {
      order[i] = i;
    }
    pair<ll, ll> best = eval(order, a);
    vector<int> ans = order;

    while (next_permutation(order.begin(), order.end())) {
      pair<ll, ll> res = eval(order, a);
      if (best.first * res.second > best.second * res.first) {
        best = res;
        ans = order;
      }
      if (best == res && order < ans) {
        ans = order;
      }
    }
    ans.pop_back();
    return ans;
  }
};











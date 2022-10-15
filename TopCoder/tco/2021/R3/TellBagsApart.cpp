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


class TellBagsApart {
  // log of prob of this outcome if f is small
  double prob(int fs, int fd, int ss, int sd) {
    return log(3.0 / 7) * fs + log(4.0 / 7) * fd + log(19.0 / 39) * ss + log(20.0 / 39) * sd;
  }

  int solve(int fs, int fd, int ss, int sd) {
    return prob(fs, fd, ss, sd) > prob(ss, sd, fs, fd);
  }

public:
    string whichBagIsSmaller(vector <int> v) {
        string ans = "";
        for (int i = 0; i < (int)v.size(); i += 8) {
          bool res = solve(v[i] + v[i + 3], v[i + 1] + v[i + 2], v[i + 4] + v[i + 7], v[i + 5] + v[i + 6]);
          ans += res ? "1" : "2";
        }
        return ans;
    }
};











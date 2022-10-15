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


class RPSMagicTrick {
public:
  string guess(string ex, string exa, string qs) {
    string ans = "AB";
    if (exa == "Wrong.") {
      swap(ans[0], ans[1]);
    }
    if (ex == "BA" || ex == "CB" || ex == "AC") {
      swap(ans[0], ans[1]);
    }
    string res = "";
    for (auto c : qs) {
      if (c == '?') res += ans;
      else swap(ans[0], ans[1]);
    }
    return res;
  }
};











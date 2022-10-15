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

const string YES = "possible";
const string NO = "impossible";

class UniformingMatrix {
  void flip(vector<string>& s, int i, int j) {
    for (int k = 0; k < (int)s.size(); k++) {
      s[k][j] ^= 1;
    }
    for (int k = 0; k < (int)s[i].size(); k++) {
      s[i][k] ^= 1;
    }
  }

  bool check3(vector<string> s) {
    for (int i = 1; i < (int)s.size(); i++) {
      if (s[i].back() == '0') {
        flip(s, i, s[0].size() - 1);
        flip(s, 0, s[0].size() - 1);
      }
    }
    for (int i = 1; i < (int)s[0].size(); i++) {
      if (s.back()[i] == '0') {
        flip(s, s.size() - 1, i);
        flip(s, s.size() - 1, 0);
      }
    }
    for (const string& x : s) {
      for (char c : x) {
        if (c != '1') {
          return false;
        }
      }
    }
    return true;
  }

  bool check2(vector<string> s) {
    if (check3(s)) return true;
    flip(s, s.size() - 1, 0);
    return check3(s);
  }


  bool check(vector<string> s) {
    if (check2(s)) return true;
    flip(s, 0, s[0].size() - 1);
    return check2(s);
  }

public:
    string isPossible(vector <string> s) {
      if (check(s)) return YES;
      flip(s, 0, 0);
      if (check(s)) return YES;
      return NO;
    }
};











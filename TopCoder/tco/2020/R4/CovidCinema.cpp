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


class CovidCinema {
public:
  vector<string> seat(int r, int c, int a, int b) {
    if (a + b > r * c) return {};
    if (r > c) {
      vector<string> temp = seat(c, r, a, b);
      vector<string> res(r, string(c, '.'));
      for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
          res[i][j] = temp[j][i];
        }
      }
      return res;
    }
    char A = 'A', B = 'B';
    if (a > b) {
      swap(a, b);
      swap(A, B);
    }
    vector<pair<int, int>> ps;
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        ps.emplace_back(i, j);
      }
    }
    sort(ps.begin(), ps.end(),[](const pair<int, int>& a, const pair<int, int>&b ) {
      if (a.first + a.second != b.first + b.second) {
        return a.first + a.second < b.first + b.second;
      }
      return a.first < b.first;
    });
    vector<string> res(r, string(c, '.'));

    for (int i = 0; i < a; i++) {
      res[ps[i].first][ps[i].second] = A;
    }
    for (int i = 0; i < b; i++) {
      res[ps[r * c - i - 1].first][ps[r * c - i - 1].second] = B;
    }

    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        if (res[i][j] == '.') continue;
        if (i && res[i - 1][j] != res[i][j] && res[i - 1][j] != '.') return {};
        if (j && res[i][j - 1] != res[i][j] && res[i][j - 1] != '.') return {};
      }
    }

    return res;
  }
};











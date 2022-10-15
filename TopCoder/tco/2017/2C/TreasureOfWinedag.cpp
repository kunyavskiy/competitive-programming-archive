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

const int MAXN = 110000;

class TreasureOfWinedag {

  int dp[26][MAXN];
  int last[26];

  int solve(int n, int k, const string& s) {
    memset(last, -1, sizeof(last));
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i < 26; i++) {
      dp[i][0] = 0;
    }
    for (int i = 0; i < n; i++) {
      last[s[i] - 'a'] = i;
      vector<int> v(last, last + 26);
      sort(v.rbegin(), v.rend());
      for (int j = 1; j < 26; j++) {
        for (int k = j - 1; k < 26; k++) {
          dp[k][i+1] = min(dp[k][i+1], dp[k - j + 1][v[j]] + 1);
        }
      }
    }
    for (int i = 0; i < 26; i++) {
      if (dp[i][n] <= k)
        return k + i;
    }
    assert(0);
  }

public:
  int solvePuzzle(int N, int K, int m, int c0, vector<int> c1, vector<int> c2, vector<int> c3, vector<int> c4, string s) {
    for (int i = s.size(); i < N; i++) {
      int t = (i * 1LL * c0) % m;
      char newChar = 'z';
      for (int j = 0; j < 25; j++) {
        if ((t >= c3[j]) && (t <= c4[j]) && ((t % c1[j]) == c2[j])) {
          newChar = 'a' + j;
          break;
        }
      }
      s += newChar;
    }
    return solve(N, K, s);
  }
};











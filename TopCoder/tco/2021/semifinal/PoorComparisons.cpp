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


class PoorComparisons {
  int count(vector<string> v) {
    bool good[27];
    memset(good, 0, sizeof(good));
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        for (int k = 0; k < 10; k++) {
          auto check = [](int a, int b) {
            if (a < b) return 0;
            if (a == b) return 1;
            return 2;
          };
          good[check(i, j) + 3 * check(i, k) + 9 * check(j, k)] = true;
        }
      }
    }
    int n = v.size();
    int score = 0;
    for (int a = 0; a < n; a++) {
      for (int b = a + 1; b < n; b++) {
        for (int c = b + 1; c < n; c++) {
          auto conv = [](char c) {
            if (c == '<') return 0;
            if (c == '=') return 1;
            return 2;
          };
          if (!good[conv(v[a][b]) + 3 * conv(v[a][c]) + 9 * conv(v[b][c])]) {
            score++;
          }
        }
      }
    }
    return score;
  }
  vector<string> solve(int n) {
    vector<string> ans(n, string(n, '='));
    int p1 = n / 3;
    int p2 = (n + 1) / 3;
    std::function<char()> gen[3][3];
    gen[0][0] = [] { return rand() % 2 ? '<' : '>'; };
    gen[1][1] = [] { return rand() % 2 ? '<' : '>'; };
    gen[2][2] = [] { return rand() % 2 ? '<' : '>'; };

    gen[0][1] = [] { return '='; };
    gen[0][2] = [] { return '='; };
    gen[1][2] = [] { return '<'; };

    int ret;
    do {
      for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
          auto part = [&](int x) {
            if (x < p1) return 0;
            else if (x < p1 + p2) return 1;
            return 2;
          };
          int part1 = part(i);
          int part2 = part(j);
          ans[i][j] = gen[part1][part2]();
          if (ans[i][j] == '>') ans[j][i] = '<';
          else if (ans[i][j] == '=') ans[j][i] = '=';
          else if (ans[i][j] == '<') ans[j][i] = '>';
        }
      }
      ret = count(ans);
      eprintf("n = %d, ret = %d, part = %lf\n", n, ret, ret / (1.0 * n * (n - 1) * (n - 2) / 6));
    } while (ret <= 0.81 * n * (n - 1) * (n - 2) / 6);
    return ans;
  }
public:
  string construct(int) {
    for (int i = 20; i <= 300; i++) {
      solve(i);
    }
    return "";
  }
};











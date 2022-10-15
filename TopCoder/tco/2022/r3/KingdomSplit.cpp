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


class KingdomSplit {
public:
  vector<int> split(string color, int n, vector<int> x, vector<int> y) {
    vector<bitset<501>> v(n);
    for (int i = 0; i < (int) x.size(); i++) {
      v[x[i]][y[i]].flip();
      v[y[i]][x[i]].flip();
    }
    for (int i = 0; i < n; i++) {
      int cnt = v[i].count();
      if (cnt % 2 == 0) {
        if (color == "blue") {
          // 0 -> even 0 -> even 1
          // 1 -> even 1
        } else {
          // 0 -> even 0 -> even 1 -> even with me
          // 1 -> odd 1  -> even with me
          v[i][i] = true;
        }
      } else {
        if (color == "blue") {
          // 0 -> even 0 -> odd 1 -> odd with me
          // 1 -> even 1 -> odd with me
          v[i][i] = true;
          v[i][n] = true;
        } else {
          // 0 -> even 0 -> odd 1
          // 1 -> odd 1
          v[i][n] = true;
        }
      }
    }

    int ptr = 0;
    for (int i = 0; i < n; i++) {
      for (int j = ptr; j < n; j++) {
        if (v[j][i]) {
          swap(v[j], v[ptr]);
          break;
        }
      }
      if (!v[ptr][i]) {
        continue ;
      }
      for (int j = 0; j < n; j++) {
        if (j != ptr && v[j][i]) {
          v[j] ^= v[ptr];
        }
      }
      ptr++;
    }


    for (int i = ptr; i < n; i++) {
      if (v[i].count()) {
        return {-1};
      }
    }
    vector<int> ans1;
    for (int i = 0; i < ptr; i++) {
      if (v[i][n] == 1) {
        for (int j = 0; j < n; j++) {
          if (v[i][j]) {
            ans1.push_back(j);
            break;
          }
        }
      }
    }
    vector<int> ans;
    for (int i = 0; i < n; i++) {
      if (std::count(ans1.begin(), ans1.end(), i) == 0) {
        ans.push_back(i);
      }
    }
    sort(ans.rbegin(), ans.rend());
    return ans;
  }
};











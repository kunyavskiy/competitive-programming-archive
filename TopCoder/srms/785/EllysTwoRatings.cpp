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


class EllysTwoRatings {
public:
  double getChance(int N, int A, int B) {
    const int LIM = 1000;
    --A, --B;
    if (A == B) return 1;
    double ans = 0;
    vector<vector<double>> probs(LIM, vector<double>(LIM));
    probs[B][A] = 1;

    vector<vector<double>> nprobs(LIM, vector<double>(LIM + 1));
    for (int it = 0; it < 2 * N; it++) {
      for (int i = 0; i < LIM; i++) {
        std::fill(nprobs[i].begin(), nprobs[i].end(), 0);
        for (int j = 0; j < LIM; j++) {
          int minr = max(j - 100, 0);
          int maxr = min(j + 101, LIM);
          double prob = probs[i][j] / (maxr - minr);
          nprobs[i][minr] += prob;
          nprobs[i][maxr] -= prob;
        }
        for (int j = 1; j < LIM; j++) {
          nprobs[i][j] += nprobs[i][j - 1];
        }
      }

      for (int i = 0; i < LIM; i++) {
        for (int j = 0; j < LIM; j++){
          probs[i][j] = nprobs[j][i];
        }
      }
      for (int i = 0; i < LIM; i++) {
        ans += probs[i][i];
        probs[i][i] = 0;
      }
    }
    return ans;
  }
};











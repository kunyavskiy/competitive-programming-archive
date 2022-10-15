#include <cstdio>
#include <vector>
#include <algorithm>
#define prev prev_i_love_std
using namespace std;


vector<vector<int>> prev;

int main(){
    int L;
    scanf("%d",&L);
    prev.resize(L + 1);
    for (int m = 1; m*m <= L; m++) {
      for (int n = 1; n < m && n * n + m * m <= L; n++)
	if (__gcd(n, m) == 1 && ((n & 1) != (m & 1))) {
	  int a = m * m - n * n;
	  int b = 2 * n * m;
	  int c = m * m + n * n;
	  for (int k = 1; c * k <= L; k++){
	      prev[c * k].push_back(a * k);
	      prev[c * k].push_back(b * k);
	  }
	}
    }


    vector<int> dp(L + 1);

    for (int i = 1; i <= L; i++) {
      dp[i] = 0;
      for (int p : prev[i])
	  dp[i] = max(dp[i], dp[p] + 1);
    }
    printf("%d\n", dp[L]);
    return 0;
}

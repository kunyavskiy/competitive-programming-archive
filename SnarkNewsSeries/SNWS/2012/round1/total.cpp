#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <memory.h>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iterator>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

#define taskname "total"

using namespace std;

typedef long long ll;
typedef long double ld;

ll dp[2][1100];
int a[1100];

int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif

    int n,m;
    scanf("%d %d",&n,&m);
    assert(n <= 1000 && m <= 5000);
    for (int i = 0; i < n; i++){
        scanf("%d",&a[i]);
        assert(0 <= a[i] && a[i] <= 1000);
        dp[0][i] = -(1<<30);
        dp[1][i] = -(1<<30);
    }
    dp[0][0] = a[0];

    for (int I = 0; I < m; I++){
        int i = I & 1;
        int i1 = i ^ 1;
        for (int j = 0; j < n; j++){
            int t = j;
            for (int k = 0; k < 6; k++){
                t++; if (t == n) t-=n;
                dp[i1][t] = max(dp[i1][t], dp[i][j] + a[t]);
            }
            dp[i][j] = -(1<<30);
        }
    }

    cout << *max_element(dp[m&1],dp[m&1]+n) << endl;
	return 0;
} 
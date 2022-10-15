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

using namespace std;

typedef long long ll;
typedef long double ld;

int n,m;

int cnt[11000];
double dp[11000];
double dp2[11000];

double get(int x){
	if (!x)	return 0;
	return x * log(x*1.0/n) / n;
}

int main(){
    #ifdef LOCAL
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif

    while (true){
    	scanf("%d %d",&n,&m);
    	if (n == m && m == 0)
    		return 0;
    	memset(cnt,0,sizeof(cnt));
    	for (int i = 0; i < n; i++){
    		int x;
    		scanf("%d",&x);
    		cnt[x]++;
    	}

		for (int i = 0; i <= 10000; i++)
			dp[i] = -1e100;
		dp[0] = 0;

    	for (int i = 1; i <= m+1; i++){
			for (int i = 0; i <= 10000; i++)
				dp2[i] = -1e100;

			int ptr = 0;

			int sum = 0;

			for (int i = 0; i <= 10000; i++){
				sum += cnt[i];
				while (ptr < i && dp[ptr] - get(sum) < dp[ptr+1] - get(sum - cnt[ptr]))
					sum -= cnt[ptr], ptr++;
				dp2[i] = dp[ptr] + get(sum);
			}

			for (int i = 0; i <= 10000; i++)
				dp[i] = dp2[i];
    	}
    		

    	cout.precision(15);
    	cout << fixed << dp[10000]  << endl;
    }


    return 0;
} 
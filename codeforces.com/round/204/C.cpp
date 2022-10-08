//#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <bitset>
#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "C"

#ifdef LOCAL
static struct __timestamper {
	~__timestamper(){
		TIMESTAMP(end);
	}
} __TIMESTAMPER;
#endif

typedef long long ll;
typedef long double ld;

const int MAXN = 25;

int a[MAXN];
int b[MAXN];

int cnt[MAXN];

int dp[2][26000];


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif
  	int n,m;
  	scanf("%d %d",&n,&m);
  	for (int i = 0; i < n; i++)
  		scanf("%d",&a[i]);
  	for (int i = 0; i < n; i++)
  		scanf("%d",&b[i]);

	if (m < 1000){	
		memset(dp, 0x3f, sizeof(dp));
		dp[0][0] = 0;
		for (int i = 0; i < n*m; i++){
			for (int j = 0; j <= i; j++){
				dp[1][j+1] = min(dp[1][j+1], dp[0][j] + a[i % n]);
				if (j)
    				dp[1][j-1] = min(dp[1][j-1], dp[0][j] + b[i % n]);
			}
			memcpy(dp[0], dp[1], sizeof(dp[0]));
			memset(dp[1], 0x3f, sizeof(dp[1]));	
		}
		printf("%d\n", dp[0][0]);
		return 0;
	}	
                 
    vector<pair<int,int> > v(n);
    for (int i = 0; i < n; i++)
    	v[i] = mp(b[i] - a[i], i);

	sort(v.begin(), v.end());

	int total = n*m/2;

	for (int i = 0; i < n; i++) {
		cnt[v[i].second] = min(total, m);
		total -= cnt[v[i].second];
	}

	int bal = 0;
	for (int i = 0; i < n; i++){
	    if (cnt[i] == m) bal--;
	    else bal++;
	    if (bal < 0){
	    	for (int j = 0; j < n; j++)  
	    		if (cnt[v[j].second] < m){
	    			cnt[i]--;
	    			cnt[v[j].second]++;
	    			break;
	    		}
	    	bal += 2;
	    }
	}

	bal = 0;
	for (int i = n-1; i > 0; i--){
	    if (cnt[i] == 0) bal++;
	    else bal--;
	    if (bal > 0){                  
	    	for (int j = n-1; j > 0; j--)
	    		if (cnt[v[j].second] > 0){
	    			cnt[i]++;
	    			cnt[v[j].second]--;
	    			break;
	    		}
	    	bal -= 2;
	    }
	}

	int ans = 0;

	for (int i = 0; i < n; i++) {
		ans += a[i] * (m - cnt[i]) + b[i] * cnt[i];
		eprintf("%d\n", cnt[i]);
	}

	printf("%d\n", ans);	 
      
    return 0;
}
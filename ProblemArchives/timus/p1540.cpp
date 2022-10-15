#include <iostream>
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

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "1540"

typedef long long ll;
typedef long double ld;

int dp[55][105][105];

vector<int> a[55];

int n;

int calc(int i,int l,int r){
	if (l >= r) return 0;
	if (dp[i][l][r] != -1) return dp[i][l][r];	
	vector<int> v;
	for (int j = l; j < r; j++){
		int g = 0;
		int last = l;
		for (int k = l; k <= r; k++)
			if (a[i][k] <= a[i][j]){
				g ^= calc(i,last,k);
				last = k+1;
			}
		v.pb(g);			
	}
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	v.pb(1<<30);
	for (int j = 0; ; j++)
		if (v[j] != j)
			return dp[i][l][r] = j;
	assert(false);
}

int can(int i,int l,int r,int need){
	if (l >= r) return -1;
	for (int j = l; j < r; j++){
		int g = 0;
		int last = l;
		for (int k = l; k <= r; k++)
			if (a[i][k] <= a[i][j]){
				g ^= calc(i,last,k);
				last = k+1;
			}
		if (g == need)
			return j;
	}
	return -1;
}


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  	scanf("%d",&n);

  	memset(dp,-1,sizeof(dp));

  	for (int i = 0; i < n; i++){
  		int l;
  		scanf("%d",&l);
  		a[i].resize(l);
  		for (int j = 0;  j < l; j++)
  			scanf("%d",&a[i][j]);
  	}
                                

  	int g = 0;

  	for (int i = 0; i < n; i++)
  		g ^= calc(i,0,a[i].size());

	if (g == 0){
		printf("S\n");
		return 0;
	}

	printf("G\n");
	for (int i = 0; i < n; i++){
		int t = can(i,0,a[i].size(),g ^ calc(i,0,a[i].size()));
		if (t != -1){
			printf("%d %d\n",i+1,t+1);
			return 0;
		}
	}
	assert(false);      
    return 0;
}
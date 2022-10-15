#ifndef LOCAL
    #pragma comment(linker, "/STACK:33554432")
#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <queue>
#include <memory.h>
#include <stack>
#define mp make_pair
#define pb push_back                     
#define setval(a,v) memset(a,v,sizeof(a))

#ifndef M_PI
	#define M_PI 3.1415926535897932384626433832795
#endif


#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;


pair<pair<int,int>,int> a[510];
int n;

int dp[510];

bool cmp(const pair<pair<int,int>,int>& a,const pair<pair<int,int>,int>& b){
	return a.first.second - a.first.first < b.first.second - b.first.first;
}

void gen(int i){
	if (dp[i] == 1){
		printf("%d ",a[i].second);
		return;
	}
	for (int j = 0; j < i; j++)
   		if (a[i].first.first < a[j].first.first && a[j].first.second < a[i].first.second)
   			if (dp[i] == dp[j]+1){
   				gen(j);
   				printf("%d ",a[i].second);
   				return;
   			}

}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    scanf("%d",&n);
    for (int i = 0; i < n; i++)
    	scanf("%d %d",&a[i].first.first,&a[i].first.second),a[i].second = i+1;

    sort(a,a+n,cmp);

    int maxv = 0;

    for (int i = 0; i < n; i++){
    	dp[i] = 1;
    	for (int j = 0; j < i; j++)
    		if (a[i].first.first < a[j].first.first && a[j].first.second < a[i].first.second)
    			dp[i] = max(dp[i],dp[j]+1);
        maxv = max(maxv,dp[i]);
    }

    for (int i = 0; i < n; i++)
    	if (dp[i] == maxv){
    		printf("%d\n",maxv);
    		gen(i);
		    printf("\n");
    		return 0;
    	}
    return 0;
}
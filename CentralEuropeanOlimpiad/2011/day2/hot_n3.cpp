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

#if ( _WIN32 || __WIN32__ )
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

const int MAXN = 200;

int rcost[MAXN];
int pcost[MAXN];
int size[MAXN];
int nsize[MAXN];

int64 dp[MAXN][MAXN][MAXN];


int64 calc(int n,int m,int o){
	if (n == -1 || m == -1 || o == 0)
		return 0;
	int64& ans = dp[n][m][o];
	if (ans != -1)
		return ans;
	ans = calc(n-1,m,o);
	ans = max(ans,calc(n,m-1,o));
	if (size[n] >= nsize[m])
		ans = max(ans,calc(n-1,m-1,o-1) + pcost[m] - rcost[n]);
	return ans;		
}

pair<int,int> temp[MAXN];

bool cmpsec(const pair<int,int>& a,const pair<int,int>& b){
	if (a.second != b.second)
		return a.second < b.second;
	return a.first < b.first;
}

bool cmpfirst(const pair<int,int>& a,const pair<int,int>& b){
	if (a.first != b.first)
		return a.first < b.first;
	return a.second < b.second;
}

void read(int n,int* cost,int* size,bool sec){
	for (int i=0;i<n;i++)
		scanf("%d %d",&temp[i].second,&temp[i].first);
	sort(temp,temp+n,sec?cmpsec:cmpfirst);
	for (int i=0;i<n;i++){
		cost[i] = temp[i].second;
		size[i] = temp[i].first;
	}
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.a","w",stdout);
  #endif
	int n,m,o;
	scanf("%d %d %d",&n,&m,&o);
	read(n,rcost,size,true);
	read(m,pcost,nsize,false);
	memset(dp,-1,sizeof(dp));
	cout << calc(n-1,m-1,o) << endl;
	return 0;
}
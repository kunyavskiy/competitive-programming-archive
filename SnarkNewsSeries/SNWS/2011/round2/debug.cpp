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
#include <sstream>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

#define taskname "debug"

using namespace std;

typedef long long int64;
typedef long double ld;

int size[(1<<20)+100];
int g[25];
double cost[(1<<20)+100];
int t[25];
bool good[25];

int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++){
		scanf("%d",&t[i]);
		scanf("%lf",&cost[1<<i]);
		string s;
		getline(cin,s);
		stringstream str(s);
		int a;
		for (;str>>a;)
			g[i]|=(1<<(a-1));
	}
	for (int i=1;i<(1<<n);i++){
		cost[i]=cost[i&(i-1)]+cost[i&(~(i-1))];
		size[i]=size[i&(i-1)]+1;
	}
	double ans=1e+15;
	for (int i=0;i<(1<<n);i++){
		if (cost[i] > ans) continue;
		int used=i;
		for (int j=0;j<n;j++){
			if (size[(~used)&g[j]] < t[j])
				used|=(1<<j);
		}
		if (used & (1<<(n-1)))
			ans=min(ans,cost[i]);		
	}
	cout.precision(15);
	cout<<fixed<<ans<<endl;
	return 0;
} 
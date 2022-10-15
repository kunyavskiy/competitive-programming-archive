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

#define taskname "a"

#ifdef LOCAL
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

int x[1000];
int y[1000];

int main(){
	#ifdef LOCAL
		#ifndef taskname
			#error taskname is not defined
		#else
			freopen(taskname".in","r",stdin);
			freopen(taskname".out","w",stdout);
		#endif
	#endif
	int n,m;
	scanf("%d %d",&n,&m);
	for (int i=0;i<n;i++)
		scanf("%d %d",&x[i],&y[i]);
	int lx,ly,rx,ry;
	int a;
	scanf("%d",&a);
	--a;
	lx=rx=x[a];
	ly=ry=y[a];
	for (int i=1;i<m;i++){
		scanf("%d",&a);
		--a;
		lx=min(lx,x[a]);
		rx=max(rx,x[a]);
		ly=min(ly,y[a]);
		ry=max(ry,y[a]);
	}
	int ans=0;
	for (int i=0;i<n;i++)
		if (lx<=x[i] && x[i]<=rx)
			if (ly<=y[i] && y[i]<=ry)
				ans++;
	cout<<ans<<endl;
	return 0;
} 
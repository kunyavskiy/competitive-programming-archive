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

int t[110][110][110];

pair<int,int> temp[110];
int x[110];
int y[110];
int hs[110];
int n,m,a;

int calc(int l,int r,int curh){
	if (l >= r)
		return 0;
	int& ans = t[l][r][curh];
	if (ans != -1)
		return ans;
	if (y[l] <= hs[curh])
		return ans = calc(l+1,r,curh);
	if (y[r-1] <= hs[curh])
		return ans = calc(l,r-1,curh);
	//cerr <<"IN "<<l<<" "<<r<<" "<<curh<<endl;		
	ans = 1LL<<30;
	for (int i=l+1;i<r;i++)
		ans = min(ans,calc(l,i,curh)+calc(i,r,curh));
	//cerr <<"OUT' "<<l<<" "<<r<<" "<<curh<<" : "<<ans << endl;
	for (int i=curh+1;i<m;i++)
		if (((x[r-1]-x[l])*1LL*hs[i]) <= a)
			ans = min(ans,calc(l,r,i)+1);

	return ans;
}



int main(){
    freopen("photo.in","r",stdin);
    freopen("photo.out","w",stdout);
	scanf("%d %d",&n,&a);
	for (int i=0;i<n;i++)
		scanf("%d %d",&temp[i].first,&temp[i].second);
	sort(temp,temp+n);
	for (int i=n-2;i>=0;i--)
		if (temp[i].first == temp[i+1].first)
			temp[i] = temp[i+1];
	n = unique(temp,temp+n) - temp;
	for (int i=0;i<n;i++)
		x[i] = temp[i].first,y[i] = temp[i].second,hs[i] = temp[i].second;
	hs[n] = -1;
	sort(hs,hs+n+1);
	m = unique(hs,hs+n+1)-hs;
	memset(t,-1,sizeof(t));
	cout << calc(0,n,0) << endl;
	return 0;
}
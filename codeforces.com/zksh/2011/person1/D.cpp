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
#define forn(i,n) for(int i=0;i<(n);++i)
#define ford(i,n) for(int i=(n)-1;i>=0;--i)
#define y1 botva

#if ( _WIN32 || __WIN32__ )
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long long ll;
typedef long double ld;

int x1[110];
int y1[110];
int x2[110];
int y2[110];

int xc[110];
int yc[110];
int64 m[110];

const ld eps=1e-05;

bool inside(int x1,int y1,int x2,int y2,int64 a,int64 b,int64 m){
	if (a<x1*m || a>x2*m)
		return false;
	if (b<y1*m || b>y2*m)
		return false;
	return true;
}

bool check(int k){
	int64 x=0,y=0;
	int64 m=0;
	for (int i=k;i>=0;i--){
		x=x+xc[i]*::m[i];
		y=y+yc[i]*::m[i];
		m+=::m[i];
		//cerr<<x<<" "<<y<<" "<<m<<endl;
		//cerr<<x1[i]<<" "<<y1[i]<<" "<<x2[i]<<" "<<y2[i]<<endl;
		if (i==0){
			if (!inside(x1[i],y1[i],x2[i],y2[i],x,y,m))
				return false;
		}
		else {
			if (!inside(max(x1[i],x1[i-1]),max(y1[i],y1[i-1]),min(x2[i],x2[i-1]),min(y2[i],y2[i-1]),x,y,m))
				return false;		
		}
	}
	return true;
}

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++){
		scanf("%d %d %d %d",&x1[i],&y1[i],&x2[i],&y2[i]);
		int a=abs(x2[i]-x1[i]);
		m[i]=a*a*a;
		x1[i]*=2;
		y1[i]*=2;
		x2[i]*=2;
		y2[i]*=2;
		xc[i]=(x1[i]+x2[i])/2;
		yc[i]=(y1[i]+y2[i])/2;
		if (x1[i]>x2[i])
			swap(x1[i],x2[i]);
		if (y1[i]>y2[i])
			swap(y1[i],y2[i]);
		if (!check(i)){
			printf("%d\n",i);
			return 0;
		}
	}
	printf("%d\n",n);
    return 0;
}
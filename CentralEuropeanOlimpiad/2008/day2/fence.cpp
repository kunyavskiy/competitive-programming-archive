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
#define abs fmdlgmfdg
#define min fdsfdgfgh

#if ( _WIN32 || __WIN32__ )
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

inline int abs(int a){
	return (a<0)?(-a):a;
}

inline int min(int a,int b){
	return (a<b)?a:b;
}


struct point{
	int x,y;
	point(){
	}
	point(int x,int y):x(x),y(y){
	}
};

inline int operator*(const point& a,const point& b){
	return a.x*b.y - a.y*b.x;
}

inline bool operator<(const point& a,const point& b){
	return a*b > 0;
}

inline point operator-(const point& a,const point& b){
	return point(a.x-b.x,a.y-b.y);	
}

inline point operator+(const point& a,const point& b){
	return point(a.x+b.x,a.y+b.y);	
}


int cnt[110][110];

point a[110];
point b[110];
int n,m;

inline bool in(const point& a,const point& b,const point& c,const point& p){
	return abs((c-a)*(b-a)) == abs((p-a)*(p-b)) + abs((p-b)*(p-c)) + abs((p-c)*(p-a));
}

int countin(const point& a,const point& b,const point& c){
	int ans = 0;
	for (int i=0;i<m;i++)
		ans += in(a,b,c,::b[i]);
	return ans;
}

bool icmp(int a,int b){
	return ::a[a] < ::a[b];
}


vector<int> order;

int dp[110];

int solve(int start){
	order.clear();
	for (int i=0;i < ::n;i++)
		if (a[i].y > a[start].y || (a[i].y == a[start].y && a[i].x >a[start].x))
			order.pb(i);
	int n = order.size();
//	cerr << start <<" "<<n << endl;
	
	for (int i=0;i<n;i++)
		a[order[i]] = a[order[i]] - a[start];
	
	sort(order.begin(),order.end(),icmp);
	
	for (int i=0;i<n;i++)
		a[order[i]] = a[order[i]] + a[start];
	
	for (int i=0;i<n;i++)
		for (int j=i+1;j<n;j++)
			cnt[i][j] = cnt[j][i] = countin(a[start],a[order[i]],a[order[j]]);
			
/*	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			cerr<<cnt[i][j] <<" \n"[j==n-1];*/
			
	int ans = 111 * m;
			
	for (int i=0;i<n;i++){
		dp[i] = 40;
		for (int j=0;j<i;j++)
			dp[i] = min(dp[i],20+dp[j] - 111 * cnt[i][j]);
		ans = min(ans,dp[i] + 111*m);
	}	
	return ans;
}






int main(){
  #ifdef LOCAL
    freopen("fence.in","r",stdin);
    freopen("fence.out","w",stdout);
  #endif
	scanf("%d %d",&n,&m);
	for (int i=0;i<n;i++)
		scanf("%d %d",&a[i].x,&a[i].y);
	for (int i=0;i<m;i++)
		scanf("%d %d",&b[i].x,&b[i].y);
	int ans = 1<<30;
	for (int i=0;i<n;i++){
		ans = min(ans,solve(i));
	//	cerr << a[i].x << " "<<a[i].y << " "<<ans << endl;
	}
	cout << ans << endl;
	return 0;
}
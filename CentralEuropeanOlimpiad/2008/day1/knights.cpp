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

const int dx[4] = {-2,-2,-1,1};
const int dy[4] = {-1,1,-2,-2};

int dst[1000][1000];
int win[1000][1000];
int n;

/*void dfs(int x,int y){
	if (win[x][y] != -1)
		return;
	win[x][y] = 0;
	for (int i=0;i<4;i++)
		if (x+dx[i]>=0 && y+dy[i] >= 0 && x+dx[i] < n && y+dy[i] < n){
			dfs(x+dx[i],y+dy[i]);
			if (!win[x+dx[i]][y+dy[i]])
				win[x][y] = true;			
		}
	if (win[x][y]){
		dst[x][y] = 0;
		for (int i=0;i<4;i++)
			if (x+dx[i]>=0 && y+dy[i] >= 0 && x+dx[i] < n && y+dy[i] < n){
				if (!win[x+dx[i]][y+dy[i]])
					dst[x][y] = max(dst[x][y],dst[x+dx[i]][y+dy[i]]+1);
			}
	}
	else {
		dst[x][y] = 1<<30;
		bool q = false;
		for (int i=0;i<4;i++)
			if (x+dx[i]>=0 && y+dy[i] >= 0 && x+dx[i] < n && y+dy[i] < n)
				dst[x][y] = min(dst[x][y],dst[x+dx[i]][y+dy[i]]+1),q=true;
		if (!q)
			dst[x][y] = 0;
	}
}*/

int get(int x,int y){
	int a = x/4;
	int b = y/4;
	if (x%4 < 2 && y%4 < 2)
		return 2*(a+b);
	if (x%4 < 2 || y%4 < 2)
		return 2*(a+b)+1;
	if (x%4 == 2 && y%4 == 2)
		return 2*(a+b)+1;
	if (x%4 == 2 && y%4 == 3)
		return 2*(a+b)+3 - 2*(b == (n-1)/4);
	if (x%4 == 3 && y%4 == 2)
		return 2*(a+b)+3 - 2*(a == (n-1)/4);
	return 2*(a+b)+3 - (b == (n-1)/4 && a == (n-1)/4);
}



vector<pair<int,int> > to;



int main(){
	#ifdef LOCAL
	    freopen("knights.in","r",stdin);
    	freopen("knights.out","w",stdout);
    #endif
	int k;
	scanf("%d %d",&k,&n);
	memset(win,-1,sizeof(win));
	int maxval = 0;
	for (int i=0;i<k;i++){
		int x,y;
		scanf("%d %d",&x,&y);
		--x,--y;
		int dest = get(x,y);
	//	cerr << dest << endl;
		maxval = max(maxval,dest);
		for (int i=0;i<4;i++){
//			cerr << x+dx[i] <<" "<<y+dy[i] << endl;
			if (x+dx[i] <0 && y+dy[i] < 0)
				continue;
			if (get(x+dx[i],y+dy[i]) == dest - 1){
				to.pb(mp(x+dx[i],y+dy[i]));
				break;
			}					
		}
	}
	if (maxval %2 == 0){
		printf("NO\n");
		return 0;
	}
	printf("YES\n");
	for (int i=0;i<k;i++)
		printf("%d %d\n",to[i].first+1,to[i].second+1);
	return 0;
}
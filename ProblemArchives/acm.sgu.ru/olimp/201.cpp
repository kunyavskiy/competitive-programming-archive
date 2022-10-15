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

const int MAXN=110000;

vector<int> onx[MAXN];
vector<int> ony[MAXN];
int x[MAXN];
int y[MAXN];
char ans[MAXN];
int kolx[MAXN][3];
int koly[MAXN][3];

void findx(int);

void findy(int y){
	for (;ony[y].size() && ans[ony[y].back()]!=0;ony[y].pop_back());
	if (ony[y].size()){
		int v=ony[y].back();
		--kolx[x[v]][0];
		--koly[::y[v]][0];
		++kolx[x[v]][2];
		++koly[::y[v]][2];
		ans[v]='1';		
		findx(x[v]);
	}
}

void findx(int x){
	for (;onx[x].size() && ans[onx[x].back()]!=0;onx[x].pop_back());
	if (onx[x].size()){
		int v=onx[x].back();
		--kolx[::x[v]][0];
		--koly[y[v]][0];
		++kolx[::x[v]][1];
		++koly[y[v]][1];
		ans[v]='0';		
		findy(y[v]);
	}
}

pair<int,int> tmp[MAXN];
int n;



void sjat(){
	for (int i=0;i<n;i++)
		tmp[i]=mp(x[i],i);
	sort(tmp,tmp+n);
	int X=-1;
	for (int i=0;i<n;i++){
		if (i==0 || tmp[i].first!=tmp[i-1].first)
			X++;
		x[tmp[i].second]=X;
	}
	
	for (int i=0;i<n;i++)
		tmp[i]=mp(y[i],i);
	sort(tmp,tmp+n);
	int Y=-1;
	for (int i=0;i<n;i++){
		if (i==0 || tmp[i].first!=tmp[i-1].first)
			Y++;
		y[tmp[i].second]=Y;
	}
	
}


int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		scanf("%d %d",&x[i],&y[i]);	
	sjat();
	for (int i=0;i<n;i++){
		onx[x[i]].pb(i);
		ony[y[i]].pb(i);
		kolx[x[i]][0]++;
		koly[y[i]][0]++;	
	}
	for (int i=0;i<n;i++)
		if (kolx[i][0]%2==1)
			findx(i);
	for (int i=0;i<n;i++)
		if (koly[i][0]%2==1)
			findy(i);
	for (int i=0;i<n;i++)
		for (;onx[i].size();)
			findx(i);
	for (int i=0;i<n;i++)
		for (;ony[i].size();)
			findy(i);
	for (int i=0;i<n;i++)
		printf("%c\n",ans[i]);	

	
    return 0;
}
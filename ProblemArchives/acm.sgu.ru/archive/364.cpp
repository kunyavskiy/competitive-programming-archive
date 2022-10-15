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
#define int64 long long
#define ld long double  
#define setval(a,v) memset(a,v,sizeof(a))
using namespace std;

int c[101][3];
int s;
int kol[101][101][2][2];
int t[101][101][2][2];
int n;
int sx,sy;
int ex,ey;
const int inf=1<<30;

pair<int,int> cnt(int w,int f,int nap,int rev,int x=-1,bool fall=false)
{
	int y,lx,rx;
	if (kol[w][f][nap][rev]!=-1)
		return mp(kol[w][f][nap][rev],t[w][f][nap][rev]);	
	if (f!=0){
		if (x==-1)
			x=c[f][nap];
		y=c[w][2];
		lx=c[w][0];
		rx=c[w][1];
	}
	else{
		x=sx;
		int go=-1;
		y=sy;
		for (int i=1;i<n;i++)
			if ((c[i][0]<=sx && c[i][1]>=sx))
				if (c[i][2]<=y)
					if (go==-1 || c[go][2]<c[i][2])
						go=i;
		if (go==-1)
			return mp(kol[w][f][nap][rev]=inf,0);
		y=c[go][2];	
		lx=c[go][0];
		rx=c[go][1];
		w=go;
	}	
	if (y<ey)
		return mp(kol[w][f][nap][rev]=inf,0);
	if (y==ey){
		if (lx<=ex && rx>=ex)
		{
			kol[w][f][nap][rev]=(((x>ex)^(nap==0))?1:0)*(x!=ex);
			t[w][f][nap][rev]=abs(x-ex);
			if (fall)
				t[w][f][nap][rev]+=sy-y;
			return mp(kol[w][f][nap][rev],t[w][f][nap][rev]);
		}
		return mp(kol[w][f][nap][rev]=inf,0);
	}
	kol[w][f][nap][rev]=inf;
	pair<int,int> tmp;
	if (!rev)
	{
		tmp=cnt(w,f,1-nap,1,x);
		tmp.first+=1;
	}
	else
		tmp=mp(inf,0);
	if (nap==0){
		pair<int,int> tmp2;
		int go=-1;
		for (int i=1;i<n;i++)
			if ((i!=w) && (c[i][0]<=lx && c[i][1]>=lx))
				if (c[i][2]<y)
					if (go==-1 || c[go][2]<c[i][2])
						go=i;
		if (go!=-1)
		{
			tmp2=cnt(go,w,nap,0);
			tmp2.second+=x-lx;
			tmp2.second+=y-c[go][2];
			tmp=min(tmp,tmp2);
		}
	}
	else {
		pair<int,int> tmp2;
		int go=-1;
		for (int i=1;i<n;i++)
			if ((i!=w) && (c[i][0]<=rx && c[i][1]>=rx))
				if (c[i][2]<y)
					if (go==-1 || c[go][2]<c[i][2])
						go=i;
		if (go!=-1)
		{
			tmp2=cnt(go,w,nap,0);
			tmp2.second+=rx-x;
			tmp2.second+=y-c[go][2];
			tmp=min(tmp,tmp2);
		}
	}		
	if (fall)
		tmp.second+=sy-y;		
	kol[w][f][nap][rev]=tmp.first;
	t[w][f][nap][rev]=tmp.second;	
	return mp(kol[w][f][nap][rev],t[w][f][nap][rev]);
}

int main()
{
	#ifndef ONLINE_JUDGE
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
	memset(kol,-1,sizeof(kol));
	int N;
	scanf("%d %d",&N,&s);
	scanf("%d %d %d %d",&sx,&sy,&ex,&ey);
	scanf("%d",&n);
	n++;
	c[0][0]=c[0][1]=sx;
	c[0][2]=sy;
	for (int i=1;i<n;i++)
		scanf("%d %d %d",&c[i][0],&c[i][1],&c[i][2]);
	pair<int,int> tmp;
	tmp=cnt(0,0,1,0,-1,true);
	tmp.first=N-tmp.first;
	if (tmp.first<=0)
		printf("0 0\n");
	else
		printf("%d %d\n",tmp.first,(N-1)*s+tmp.second);
	return 0;
}

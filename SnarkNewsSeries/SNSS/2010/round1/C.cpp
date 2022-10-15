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
#include <cassert>
#include <iterator>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

#define taskname "C"

using namespace std;

typedef long long int64;
typedef long double ld;

const int dx[4]={-1,0,1,0};
const int dy[4]={0,-1,0,1};
const string name[4]={"North","West","South","East"};

int a[1100][1100];  
int n;

bool good(int x,int y){
	return x>=0 && x<n && y>=0 && y<n;
}

void read(){
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			scanf("%d",&a[i][j]);
}

int height(int x,int y){
	if (!good(x,y))
		return 0;
	return a[x][y];
}

void findtop(int& x,int& y){
	int mh=0;
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			mh=max(mh,a[i][j]);
	//cerr<<mh<<endl;
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			if (a[i][j]==mh)
			{
				int mnap=0;
				for (int k=1;k<4;k++)
					if (height(i+dx[k],j+dy[k]) < height(i+dx[mnap],j+dy[mnap]))
						mnap=k;
				bool q=true;
				for (int k=0;k<4;k++)
					if (height(i+dx[k],j+dy[k]) == height(i+dx[mnap],j+dy[mnap]) && k!=mnap)
						q=false;
				if (q)
					{
						x=i;
						y=j;
						return;
					}				
			}
//	assert(false);
}

int main(){
	#ifdef LOCAL
		#ifndef taskname
			#error taskname is not defined
		#else
			freopen(taskname".in","r",stdin);
			freopen(taskname".out","w",stdout);
		#endif
	#endif
	read();
	int x,y;
	findtop(x,y);
//	cerr<<x<<" "<<y<<endl;
	int nap=0;
	for (;;){
		int bnap=nap;
		for (int i=nap;i<nap+4;i++)
			if (height(x+dx[i&3],y+dy[i&3]) < height(x+dx[bnap],y+dy[bnap]))
				bnap=(i&3);
		if (height(x+dx[bnap],y+dy[bnap]) >= height(x,y)){
			printf("Trapped\n");
			return 0;
		}
		nap=bnap;
		x+=dx[nap];
		y+=dy[nap];
		if (!good(x,y)){
			cout<<name[nap]<<endl;
			return 0;
		}
	}
	return 0;
} 
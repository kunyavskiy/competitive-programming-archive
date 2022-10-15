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

#ifdef LOCAL
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

#define taskname "moon"

using namespace std;

typedef long long int64;
typedef long double ld;

char s[55][55];
const int dx[4]={0,1,0,-1};
const int dy[4]={1,0,-1,0};
int n,m;

bool can[55][55][4];

bool good(int x,int y){
	return (0<=x && x<n) && (0<=y && y<m);
}

void read(){
	scanf("%d %d",&m,&n);
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
			scanf(" %c ",&s[i][j]);			
}

void print(){
	int cnt=0;
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
			cnt+=(s[i][j]=='G' && (can[i][j][0] || can[i][j][1] || can[i][j][2] || can[i][j][3]));
	cout<<cnt<<endl;
}

void dfs(int x,int y,int val){
	if (!good(x,y))
		return;
	if (val<0)
		return;
	if (can[x][y][val])
		return;
	if (s[x][y]=='R')
		val=3;
	can[x][y][val]=true;
	for (int i=0;i<4;i++)
		dfs(x+dx[i],y+dy[i],val-(s[x][y]=='D'));	
}



int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif
	read();
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
			if (s[i][j]=='S'){
				dfs(i,j,3);	
				print();
				return 0;
			}
	printf("0\n");
	return 0;
} 
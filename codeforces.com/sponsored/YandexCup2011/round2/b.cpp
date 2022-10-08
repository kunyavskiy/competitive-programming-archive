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

char s[1100][1100];
int n,m;

void err(){
	printf("-1\n");
	exit(0);
}


const int dx[4] = {0,1,0,-1};
const int dy[4] = {1,0,-1,0};

bool good(int x,int y){
	return x>=0 && y>=0 && x<n && y<m;
}

bool used[255];

void color(int x,int y,int x1,int y1){
	for (int i='0';i<='9';i++)
		used[i] = false;
	assert(s[x][y] == '.' && s[x1][y1] == '.');
	for (int i=-1;i<=1;i++)
		for (int j=-1;j<=1;j++)
		if (good(x+i,y+j))
			used[(int)s[x+i][y+j]] = true;
	for (int i=-1;i<=1;i++)
		for (int j=-1;j<=1;j++)
		if (good(x1+i,y1+j))
			used[(int)s[x1+i][y1+j]] = true;

	for (s[x][y] = '0';used[(int)s[x][y]];s[x][y]++);
	s[x1][y1] = s[x][y];	
}

void color(int x,int y){
	for (int i=0;i<4;i++)
		if (good(x+dx[i],y+dy[i]) && s[x+dx[i]][y+dy[i]] != '#'){
			s[x][y] = s[x+dx[i]][y+dy[i]];
			return;
		}
	err();
}

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	scanf("%d %d",&n,&m);
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
			scanf(" %c ",&s[i][j]);
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
			if (good(i+1,j) && s[i][j]=='.' && s[i+1][j]=='.')
				color(i,j,i+1,j);
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
			if (good(i,j+1) && s[i][j]=='.' && s[i][j+1]=='.')
				color(i,j,i,j+1);
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
			if (s[i][j] == '.')
				color(i,j);
	for (int i=0;i<n;i++){
		s[i][m] = 0;
		puts(s[i]);
	}
	return 0;
}
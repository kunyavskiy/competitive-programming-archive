#ifndef LOCAL
    #pragma comment(linker, "/STACK:33554432")
#endif

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

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

char s[50][50];
bool used[50][50];
const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};
int n;

int ans = 0;

void dfs(int x,int y){
	if (used[x][y])
		return;
	used[x][y] = true;
	for (int i = 0; i < 4; i++){
		int nx = x+dx[i],ny = y+dy[i];
		if (nx < 0 || ny < 0 || nx >= n || ny >= n || s[nx][ny] == '#'){
			ans += 9;
			continue;
		}
		dfs(nx,ny);
	}
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	scanf("%d",&n);
  	for (int i = 0; i < n; i++)
  		for (int j = 0; j < n; j++)
  			scanf(" %c ",&s[i][j]);
  	dfs(0,0);
  	if (!used[n-1][n-1])
  		dfs(n-1,n-1);
  	ans -= 4*9;
  	cout << ans << endl;	
  return 0;
}
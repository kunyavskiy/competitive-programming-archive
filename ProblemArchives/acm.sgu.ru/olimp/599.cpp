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


bool g[110][110];
bool used[110];
int n;


void dfs(int v){
	used[v]=true;
	for (int i=0;i<n;i++)
		if (g[v][i] && !used[i])
			dfs(i);
}

bool check(){
	memset(used,0,sizeof(used));
	dfs(0);
	for (int i=0;i<n;i++)		
		if (!used[i])
			return false;
	return true;
}


int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	scanf("%d",&n);
	for (int i=0;i<n;i++){
		int a,b;
		scanf("%d %d",&a,&b);
		--a;--b;
		g[a][b]=g[b][a]=true;
	}
	for (int i=0;i<n;i++)
		for (int j=i+1;j<n;j++)
			if (g[i][j]){
				g[i][j]=g[j][i]=false;
				if (check())
					cout<<i+1<<" "<<j+1<<endl;
				g[i][j]=g[j][i]=true;	
			}
    return 0;
}
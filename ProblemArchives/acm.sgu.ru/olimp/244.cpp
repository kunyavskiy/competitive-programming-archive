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

int n,m;
char c[55][55];
bool used[55][55];

vector<string> ans;
char buf[100];

void dohor(int x,int y){
	int cnt=0;
	for (;y+cnt<m && c[x][y+cnt]==c[x][y];++cnt)
		used[x][y+cnt]=true;
	memset(buf,0,sizeof(buf));
	sprintf(buf,"H %d %d %d %c",x+1,y+1,cnt,c[x][y]);
	ans.pb(string(buf));
}

void dovert(int x,int y){
	int cnt=0;
	for (;x+cnt<n && c[x+cnt][y]==c[x][y];++cnt)
		used[x+cnt][y]=true;
	memset(buf,0,sizeof(buf));
	sprintf(buf,"V %d %d %d %c",x+1,y+1,cnt,c[x][y]);
	ans.pb(string(buf));
}

void color(int x,int y){
	if (x<n && c[x+1][y]==c[x][y])
		dovert(x,y);
	else
		dohor(x,y);
}

int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	scanf("%d %d",&n,&m);
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
			scanf(" %c ",&c[i][j]);
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
			if (!used[i][j])
				color(i,j);
	cout<<ans.size()<<endl;
	for (int i=0;i<ans.size();i++)	
		cout<<ans[i]<<endl;
	
    return 0;
}
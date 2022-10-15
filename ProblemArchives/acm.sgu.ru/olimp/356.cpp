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
#define norm(a) if (a>=3) a-=3
using namespace std;

int a[10][10];
int b[10][10];
int cnt[10];
int n,m;
int ans;

const int dx[5]={-1,0,0,0,1};
const int dy[5]={0,-1,0,1,0};

void read(){
	cin>>n>>m;
	char c;
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
			{
				cin>>c;
				if (c=='R') a[i][j]=0;
				else if (c=='G') a[i][j]=1;
				else a[i][j]=2;
			}
}

void nextcolor(){
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++){
			++a[i][j];
			norm(a[i][j]);
		}
}

bool good(int x,int y){
	return x>=0 && y>=0 && x<n && y<m;
}

void push(int x,int y){
	for (int i=0;i<5;i++)
		if (good(x+dx[i],y+dy[i])){
			b[x+dx[i]][y+dy[i]]++;
			norm(b[x+dx[i]][y+dy[i]]);
		}
}

const int inf=1<<30;


int calc(){
	memcpy(b,a,sizeof(b));
	int ans=0;
	for (int i=0;i<m;i++)
		for (int j=0;j<cnt[i];j++){
			push(0,i);
			++ans;
		}
	for (int i=1;i<n;i++)
		for (int j=0;j<m;j++)
			for (;b[i-1][j]!=0;push(i,j))
				ans++;
	for (int i=0;i<m;i++)
		if (b[n-1][i]!=0)
			return inf;

	return ans;
}

void perebor(int pos){
	if (pos==m){
		ans=min(ans,calc());
		return;
	}
	for (int i=0;i<3;i++){
		cnt[pos]=i;
		perebor(pos+1);
	}
}

int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
	read();  
	ans=inf;
	for (int i=0;i<3;i++){
		perebor(0);
		nextcolor();
	}
	if (ans==inf) 
		cout<<-1<<endl;
	else
		cout<<ans<<endl;
  return 0;
}
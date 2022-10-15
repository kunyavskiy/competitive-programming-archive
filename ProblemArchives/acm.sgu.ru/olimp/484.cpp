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

int64 min(int64 a,int64 b){
	return a<b?a:b;
}

int64 min(int a,int b){
	return a<b?a:b;
}

int64 min(int a,int64 b){
	return a<b?a:b;
}

int64 min(int64 b,int a){
	return a<b?a:b;
}



const int64 inf=1LL<<60LL;

int cost[1100];
vector<int> type[2];
int64** t[2][3];
int n,k;

bool cmp(int a,int b){
	return cost[a]<cost[b];
}

void gen(int ty,int c,int i,int j){
//	cerr<<ty<<" "<<c<<" "<<i<<" "<<j<<endl;
	if (i==0 && j==0)
		return;
	if (c!=1)
		gen(ty,c-1,i-(ty==0),j-(ty==1));
	else {
		int64 ans=inf;
		int ansc;
		ansc=-1;
		for (int c=0;c<=2;c++)
			if (ans > t[ty^1][c][i-(ty==0)][j-(ty==1)]){
				ans=t[ty^1][c][i-(ty==0)][j-(ty==1)];
				ansc=c;			
			}
		assert(ansc!=-1);
		gen(ty^1,ansc,i-(ty==0),j-(ty==1));	
	}
	if (ty==0)
		cout<<type[0][i-1]+1<<" ";
	else
		cout<<type[1][j-1]+1<<" ";
}

int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    
	scanf("%d %d",&k,&n);
	for (int i=0;i<n;i++){
		int t;
		scanf("%d %d",&cost[i],&t);
		type[t].pb(i);
	}
	sort(type[0].begin(),type[0].end(),cmp);
	sort(type[1].begin(),type[1].end(),cmp);
	int sz0=type[0].size();
	int sz1=type[1].size();
	
	for (int i=0;i<2;i++)
		for (int j=0;j<3;j++){
			t[i][j]=new int64*[sz0+1];
			for (int l=0;l<=sz0;l++){
				t[i][j][l]=new int64[sz1+1];
				for (int q=0;q<=sz1;q++)
					t[i][j][l][q]=inf;
			}				
		}
		
	t[0][0][0][0]=t[1][0][0][0]=0;	
	
	
	for (int i=0;i<k;i++)
		for (int j=0;j<=i && j<=sz0;j++){
			int g=i-j;
			if (g>sz1) continue;
			for (int c=0;c<=2;c++){
				if (c!=2 && j!=sz0)
					t[0][c+1][j+1][g]=min(t[0][c+1][j+1][g],t[0][c][j][g]+(k-i)*1LL*cost[type[0][j]]);
				if (g!=sz1)
					t[1][1][j][g+1]=min(t[1][1][j][g+1],t[0][c][j][g]+(k-i)*1LL*cost[type[1][g]]);
			}
			for (int c=0;c<=2;c++){
				if (j!=sz0)
					t[0][1][j+1][g]=min(t[0][1][j+1][g],t[1][c][j][g]+(k-i)*1LL*cost[type[0][j]]);
				if (c!=2 && g!=sz1)
					t[1][c+1][j][g+1]=min(t[1][c+1][j][g+1],t[1][c][j][g]+(k-i)*1LL*cost[type[1][g]]);
			}
		}
	int64 ans=inf;
	int ansc,ansi,ansj,anst;
	ansc=ansi=ansj=anst=-1;
	for (int i=0;i<=sz0 && i<=k;i++)
		if (k-i<=sz1){
			for (int ty=0;ty<2;++ty)
				for (int c=0;c<=2;c++)
					if (ans > t[ty][c][i][k-i]){
						ans=t[ty][c][i][k-i];
						ansc=c;
						ansi=i;
						ansj=k-i;
						anst=ty;
					}
		
		}

	if (ans==inf)
		cout<<"Impossible";
	else
		gen(anst,ansc,ansi,ansj);
	cout<<endl;
    return 0;
}
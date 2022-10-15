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

const int maxn=300;
int l[maxn],r[maxn],pred[maxn],p[maxn],dfs[maxn],bfs[maxn];
int n;

void clear(){
	memset(l,-1,sizeof(int)*n);
	memset(r,-1,sizeof(int)*n);
	memset(pred,0,sizeof(int)*n);
	memset(p,-1,sizeof(int)*n);
	l[0]=0;
	r[0]=n;
}

void solve(){
	clear();
	int ptr1=0;
	int ptr2=1;
	for (;ptr2<n;){
		int a=bfs[ptr1];
		int lv=-1;
		for (;;){
			if (ptr2==n || pred[bfs[ptr2]]!=bfs[ptr1])
				break;
			if (lv!=-1 && bfs[ptr2]<lv)
				break;
			p[bfs[ptr2]]=a;
			if (lv!=-1){
				r[lv]=l[lv];
				for (;dfs[r[lv]]!=bfs[ptr2];++r[lv]){
					pred[dfs[r[lv]]]=lv;
					assert(r[lv]<=r[a]);
				}		
				l[bfs[ptr2]]=r[lv];
			}
			else
				l[bfs[ptr2]]=l[a]+1;
			lv=bfs[ptr2];
			ptr2++;
		}	
		if (lv!=-1){
			r[lv]=l[lv];
			for (;r[lv]<r[a];++r[lv]){
				pred[dfs[r[lv]]]=lv;
				assert(r[lv]<=r[a]);
			}		
		}
		ptr1++;
		assert(ptr1<ptr2);
	}
}

int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	scanf("%d",&n);	
	for (int i=0;i<n;i++){
		scanf("%d",&bfs[i]);
		--bfs[i];
	}
	for (int i=0;i<n;i++){
		scanf("%d",&dfs[i]);
		--dfs[i];
	}
	assert(dfs[0]==0);
	assert(bfs[0]==0);
	solve();
	for (int i=1;i<n;i++)
		printf("%d %d\n",p[i]+1,i+1);
	return 0;
}
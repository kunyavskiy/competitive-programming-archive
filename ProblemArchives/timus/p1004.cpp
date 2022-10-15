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

#ifndef M_PI
	#define M_PI 3.1415926535897932384626433832795
#endif


#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

const int MAXN = 100;

int g[MAXN][MAXN];
int d[MAXN];
int p[MAXN];
bool used[MAXN];
int n,m;


bool read(){
	scanf("%d",&n);
	if (n == -1)
		return false;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			g[i][j] = 0xfffffff*(i != j);		

	scanf("%d",&m);
	for (int i = 0; i < m; i++){
		int a,b,c;
		scanf("%d %d %d",&a,&b,&c);
		--a,--b;              
		g[a][b] = g[b][a] = min(g[b][a],c);
	}
	return true;
}


void print(int v,bool rev){
	if (v == -1)
		return;
	if (!rev)
		printf("%d ",v+1);
	print(p[v],rev);
    if (rev && p[v] != -1)
    	printf("%d ",v+1);	
}


void solve(){
	int ans = 0xfffffff;
	int id ,id1,id2;
	id = id1 = id2 = -1;
	for (int it = 0; it < n; it++){
		memset(d,0x3f,n*sizeof(int));
		memset(p,-1,n*sizeof(int));
		memset(used,0,n*sizeof(bool));
		d[it] = 0;
		for (int i = 0; i< n; i++){
			int best = -1;
			for (int j = 0; j < n; j++)
				if (!used[j])
					if (best == -1 || d[best] > d[j])
						best = j;
			if (best == -1)
				break;
			if (d[best] == 0x3f3f3f3f)
				break;
			//cerr << it <<" "<<best << endl;
			used[best] = 1;
			for (int j = 0; j < n; j++){
				if (j != p[best] && used[j] && j != best){
					if (ans > d[best] + d[j] + g[best][j]){
						ans = d[best] + d[j] + g[best][j];
						id = it;
						id1 = best;
						id2 = j;
                    }
				}
                   if (d[j] > d[best] + g[best][j]){                    	
                   	d[j] = d[best] + g[best][j];
					p[j] = best;
                   }
					
			}
		}
	}


//	cerr << ans <<" "<<id <<" "<<id1 <<" "<<id2<<endl;
//	cerr <<"!!!"<<endl;

	if (id == -1){
		printf("No solution.\n");
		return;
	}

	memset(d,0x3f,n*sizeof(int));
	memset(p,-1,n*sizeof(int));
	memset(used,0,n*sizeof(bool));
	d[id] = 0;
	for (int i = 0; i< n; i++){
		int best = -1;
		for (int j = 0; j < n; j++)
			if (!used[j])
				if (best == -1 || d[best] > d[j])
					best = j;
		if (best == -1)
			break;
		if (d[best] == 0x3f3f3f3f)
			break;
		used[best] = 1;
		for (int j = 0; j < n; j++){
          if (d[j] > d[best] + g[best][j]){
           	d[j] = d[best] + g[best][j];
			p[j] = best;
          }
		}
	}
//	cerr <<"!!!"<<endl;
	print(id1,false);
	print(id2,true);
	printf("\n");
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  while (read())
  	solve();
  return 0;
}
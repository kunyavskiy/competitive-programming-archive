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

#undef assert
#define assert(x) if (!(x)) throw 1


#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

vector<int> a[2100];


int first[110];
int second[110];

int l[110];
int r[110];

int used[110],useptr;
int n,k;

void change(int id,int val,int to){
	if (first[id] == val)
		first[id] = to;
	else {
		assert(second[id] == val);
	    second[id] = to;
	}
}


bool dfs(int v,int toc){
	if (used[v] == useptr)
		return false;
	used[v] = useptr;
	for (int i = l[v]; i < r[v]; i++){
		if (first[v] == i || second[v] == i || toc == i)
			continue;
		if (a[i].size() < k){
			change(v,toc,i);
			assert(first[v] != second[v]);
			a[i].pb(v);
			return true;
		}
	}
	for (int i = l[v]; i < r[v]; i++){
		if (first[v] == i || second[v] == i || toc == i)
			continue;
		//cerr << v<<" "<<toc<<" :  "<<first[v] <<" "<<second[v] << " "<<toc <<" "<<i<<endl;
		for (int j = 0; j < k; j++)
			if (dfs(a[i][j],i)){
				a[i][j] = v;
		//		cerr << v<<" :  "<<first[v] <<" "<<second[v] << " "<<toc <<" "<<i<<endl;
				change(v,toc,i);
				assert(first[v] != second[v]);
				return true;
			}
	}
   return false;	
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  scanf("%d %d",&n,&k);

  for (int i = 0; i < n; i++){
  	scanf("%d %d",&l[i],&r[i]);
  	r[i] += l[i];
  }

  memset(first,-1,sizeof(first));
  memset(second,-1,sizeof(second));

  for (int i = 0; i < n; i++){
  	++useptr;
  	if (!dfs(i,-1)){
/*  		for (int j = 0; j < 2000; j++)
  			random_shuffle(a[j].begin(),a[j].end());
  		++useptr;
  		assert(!dfs(i,-1));*/
  		printf("No\n");
  		return 0;
  	}
  	++useptr;
  	if (!dfs(i,-1)){
  	/*	for (int j = 0; j < 2000; j++)
  			random_shuffle(a[j].begin(),a[j].end());
  		++useptr;
  		assert(!dfs(i,-1));*/
  		printf("No\n");
  		return 0;
  	}
  }

  printf("Yes\n");
  for (int i = 0; i < n; i++) {
//  	assert(first[i] != second[i]);
//  	assert(l[i] <= first[i] && first[i] < r[i]);
//  	assert(l[i] <= second[i] && second[i] < r[i]);
  	printf("%d %d\n",min(first[i],second[i]),max(first[i],second[i]));
  }
  return 0;
}
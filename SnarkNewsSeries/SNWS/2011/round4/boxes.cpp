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

#define taskname "boxes"

using namespace std;

typedef long long int64;
typedef long double ld;

const int MAXN=510;

int a[MAXN];
int b[MAXN];
int c[MAXN];
vector<int> g[MAXN];
int mt[MAXN];
bool used[MAXN];


bool kunn(int v){
	if (used[v])
		return false;
	used[v]=true;	
	for (int i=0,sz=g[v].size();i<sz;i++){
		int to=g[v][i];
		if (mt[to]==-1 || kunn(mt[to])){
			mt[to]=v;
			return true;
		}
	}
	return false;
}



int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif
	
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++){
		scanf("%d %d %d",&a[i],&b[i],&c[i]);
		}
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			if (a[i] < a[j] && b[i] < b[j] && c[i] < c[j])
				g[j].pb(i);			
	memset(mt,-1,sizeof(mt));
	for (int i=0;i<n;i++){
		memset(used,0,sizeof(used));
		kunn(i);
	}
	int ans=n;
	for (int i=0;i<n;i++)
		if (mt[i]!=-1)
			ans--;
	cout<<ans<<endl;
	return 0;
} 
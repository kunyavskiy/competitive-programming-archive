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

using namespace std;

typedef long long int64;
typedef long double ld;


const int maxtime=18000;
int t[20000];

vector<pair<int,int> > g[20000];

int main(){
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++){
		int b,l,r;
		scanf("%d %d %d",&b,&l,&r);
		++b;
		g[b+l-1].pb(mp(b,r));	
	}
	for (int i=1;i<=maxtime;i++){
		t[i]=t[i-1];
		int sz=g[i].size();
		for (int j=0;j<sz;j++)
			t[i]=max(t[i],t[g[i][j].first-1]+g[i][j].second);
	//	cerr<<i<<" "<<t[i]<<endl;
	}
	cout<<t[maxtime]<<endl;
	return 0;
} 
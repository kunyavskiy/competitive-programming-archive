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
#include <cassert>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

set<int> g[110000];
int a[110000];
bool used[110000];
int ptr;
int n,m;

void dfs(int v){
	assert(a[ptr] == v);
	ptr++;
	used[v] = true;

	while (ptr < n){
    	if (g[v].find(a[ptr]) != g[v].end())
    		dfs(a[ptr]);
    	else {
    		for (set<int>::iterator iter = g[v].begin(); iter != g[v].end(); ++iter)
    			if (!used[*iter]){
    				printf("No\n");
    				exit(0);
    			}
    		return;
    	}
	}
	return;
}

int main(){
    #ifdef LOCAL
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif
    scanf("%d %d",&n,&m);
    for (int i = 0; i < m; i++){
    	int a,b;
    	scanf("%d %d",&a,&b);
    	--a,--b;
    	g[a].insert(b);
    	g[b].insert(a);
    }

    for (int i = 0; i < n; i++)
    	scanf("%d",&a[i]),--a[i];

    while (ptr < n)
	    dfs(a[ptr]);

    printf("Yes\n");

    return 0;
} 
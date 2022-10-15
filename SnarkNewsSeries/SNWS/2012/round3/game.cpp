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

#define taskname "game"

using namespace std;

typedef long long int64;
typedef long double ld;

int res[31][31][31][31];


int dfs(int a,int b,int c,int d){
    if (a < 0 || b < 0 || c <0 || d < 0)
        return 1;
    int& res = ::res[a][b][c][d];
    if (res != -1)
        return res;
    res = 0;
    res = max(res, 1 - dfs(a-2,b-1,c,d-2));
    res = max(res, 1 - dfs(a-1,b-1,c-1,d-1));
    res = max(res, 1 - dfs(a,b,c-2,d-1));
    res = max(res, 1 - dfs(a,b-3,c,d));
    res = max(res, 1 - dfs(a-1,b,c,d-1));
    return res;
}

const string out[2] = {"Second\n","First\n"};

int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif

    memset(res,-1,sizeof(res));

    int t;
    scanf("%d",&t);
    for (int i = 0; i < t; i++){
        int a,b,c,d;
        scanf("%d %d %d %d",&a,&b,&c,&d);
        cout << out[dfs(a,b,c,d)];
    }

	return 0;
} 
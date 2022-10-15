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

#define taskname "matrixmaze"

using namespace std;

typedef long long int64;
typedef long double ld;


int _a[3];
int a,b,c;

bool used[110][110];
int v[110][110];
int n,m;

const int dx[4] = {1,0,-1,0};
const int dy[4] = {0,1,0,-1};

bool good(int x,int y){
    return x >= 0 && y >= 0 && x < n && y < m && (v[x][y] == a || v[x][y] == b || v[x][y] == c);
}

bool dfs(int x,int y){
    if (used[x][y])
        return false;
    if (x == n-1)
        return true;
    used[x][y] = true;
    for (int i = 0; i < 4; i++)
        if (good(x+dx[i],y+dy[i]))
            if (dfs(x+dx[i],y+dy[i]))
                return true;
    return false;
}

void go(int pos){
    if (pos == 3){
        a = _a[0];
        b = _a[1];
        c = _a[2];
        memset(used,0,sizeof(used));
        for (int i = 0; i < m; i++)
            if (good(0,i) && dfs(0,i)){
                printf("%d %d %d\n",a,b,c);
                exit(0);
            }
        return;
    }
    for (_a[pos] = 0; _a[pos] < 10; _a[pos]++)
        go(pos+1);
}

int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif

    scanf("%d %d",&m,&n);
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < m; j++)
            scanf("%d",&v[i][j]);
    go(0);
    printf("%d %d %d\n",-1,-1,-1);

	return 0;
} 
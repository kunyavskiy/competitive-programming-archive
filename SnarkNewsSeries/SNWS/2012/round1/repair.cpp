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

#define taskname "repair"

using namespace std;

typedef long long int64;
typedef long double ld;

const int MAXN = 1100;

vector<int> g[MAXN];
int n,m,s,t;
bool used[MAXN];
int mt[MAXN];


bool dfs(int v){
    if (v == t)
        return true;
    if (used[v])
        return false;
    //cerr << v << endl;
    used[v] = true;
    if (dfs(mt[v])){
        mt[v] = v;
        return true;
    }
    for (int i = 0; i < g[v].size(); i++){
        int to = g[v][i];
        if (dfs(mt[to])){
            mt[to] = v;
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

    scanf("%d %d %d %d",&n,&m,&s,&t);
    --s,--t;
    for (int i = 0; i < m; i++){
        int a,b;
        scanf("%d %d",&a,&b);
        --a,--b;
        g[a].pb(b);
        g[b].pb(a);
        if ((a == s && b == t) || (a == t && b == s)){
            printf("0\n");
            return 0;
        }
    }

    int cnt = 0;

    for (int i = 0; i < n; i++)
        mt[i] = i;


    for (;;){
        memset(used,0,sizeof(used));
        mt[t] = t;
        if (dfs(s))
            cnt++;
        else
            break;
//        cerr << endl << endl;
    }

    cout << cnt << endl;
    return 0;
} 